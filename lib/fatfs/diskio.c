// based on this lib : https://github.com/colosimo/fatfs-stm32

#include "ff.h"
#include "diskio.h"

#include <stm32f4xx.h>
#include "lib_defs.h"

#define NULL 0

#define RESP_NONE 0
#define RESP_SHORT 1
#define RESP_LONG 2

#define CT_MMC 0x01				 /* MMC ver 3 */
#define CT_SD1 0x02				 /* SD ver 1 */
#define CT_SD2 0x04				 /* SD ver 2 */
#define CT_SDC (CT_SD1 | CT_SD2) /* SD */
#define CT_BLOCK 0x08			 /* Block addressing */

#define ACMD(x) ((x) | 0x80)

static DSTATUS dstatus = STA_NOINIT;

static WORD card_rca;
static BYTE card_type;
static BYTE card_info[36]; /* CSD, CID, OCR */

static void byte_swap(BYTE *dest, DWORD src)
{
	int i;
	for (i = 0; i < 4; i++)
		dest[i] = src >> (24 - 8 * i);
}

static int send_cmd(WORD idx, DWORD arg, int resp_type, DWORD *buf)
{
	DWORD cmd;
	DWORD s;

	lib_delay_ms(1);

	if (idx & 0x80)
	{ /* ACMD class */
		if (!send_cmd(55, ((DWORD)card_rca) << 16, RESP_SHORT, buf) || !(buf[0] & 0x00000020))
			return 0;
	}

	idx &= 0x3F;
	SDIO->ICR = 0xc007ff;

	SDIO->ARG = arg;

	cmd = (1 << 10) | idx;
	if (resp_type == RESP_SHORT)
		cmd |= (1 << 6);
	else if (resp_type == RESP_LONG)
		cmd |= (1 << 6) | (1 << 7);

	SDIO->CMD = cmd;
	lib_beginCounter(100);

	while (1)
	{

		if (lib_isTimeElapsed())
		{
			break;
		}

		s = SDIO->STA;
		if (resp_type == RESP_NONE)
			return s & (1 << 7) ? 1 : 0;
		else
		{
			/* check if timeout */
			if (s & (1 << 3))
			{
				lib_println("Error ! %s timeout idx=%d arg=%d", __func__, (uint32_t)idx, (uint32_t)arg);
				return 0;
			}

			/* check if crc err */
			if (s & (1 << 1))
			{
				if (idx == 1 || idx == 12 || idx == 41)
					break;
				lib_println("Error ! %s crcfail idx=%d arg=%d", __func__, (uint32_t)idx, (uint32_t)arg);
				return 0;
			}

			if (s & (1 << 6))
				break;
		}
	}

	buf[0] = SDIO->RESP1;
	if (resp_type == RESP_LONG)
	{
		buf[1] = SDIO->RESP2;
		buf[2] = SDIO->RESP3;
		buf[3] = SDIO->RESP4;
	}

	return 1;
}

static int check_tran(DWORD tout_ms)
{
	DWORD resp;

	lib_beginCounter(tout_ms);

	while (!lib_isTimeElapsed())
	{
		if (send_cmd(13, ((DWORD)card_rca) << 16, RESP_SHORT, &resp) && ((resp & 0x01e00) == 0x00800))
			return 1;
	}
	return 0;
}

DSTATUS disk_initialize(BYTE pdrv)
{
	DWORD resp[4];
	WORD cmd;
	/* DWORD clkcr; */
	int i;

	dstatus = STA_NOINIT;

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

	/* SDIO_CD: PB15 input gpio, card detect */
	GPIOB->MODER &= ~(0b11 << (15 << 1)); // reset mode, input
	GPIOB->PUPDR &= ~(0b11 << (15 << 1));

	/* SDIO_D0 PC8 */
	lib_setPinAF(GPIOC, 8, 12);
	GPIOC->PUPDR &= ~(0b11 << (8 << 1));

	/* SDIO_D1 */
	lib_setPinAF(GPIOC, 9, 12);
	GPIOC->PUPDR &= ~(0b11 << (9 << 1));

	/* SDIO_D2 */
	lib_setPinAF(GPIOC, 10, 12);
	GPIOC->PUPDR &= ~(0b11 << (10 << 1));

	/* SDIO_D3 */
	lib_setPinAF(GPIOC, 11, 12);
	GPIOC->PUPDR &= ~(0b11 << (11 << 1));

	/* SDIO_CK */
	lib_setPinAF(GPIOC, 12, 12);
	GPIOC->PUPDR &= ~(0b11 << (12 << 1));

	/* SDIO_CMD */
	lib_setPinAF(GPIOD, 2, 12);
	GPIOD->PUPDR &= ~(0b11 << (2 << 1));

	dstatus &= ~STA_NOINIT;

	if (GPIOB->IDR & (1 << 15))
		dstatus |= STA_NODISK;

	if (dstatus & STA_NODISK)
		return RES_OK;

	RCC->APB2ENR |= RCC_APB2ENR_SDIOEN;
	SDIO->CLKCR |= ((45000 / 400) - 2); /* clk set to 400kHz */
	SDIO->CLKCR |= SDIO_CLKCR_CLKEN;
	// power on the card
	SDIO->POWER |= 0b11;

	send_cmd(0, 0, 0, NULL);

	lib_beginCounter(1000);
	if (send_cmd(8, 0x1AA, RESP_SHORT, resp) && ((resp[0] & 0xfff) == 0x1aa))
	{
		/* sdc v2 */
		card_type = 0;
		do
		{
			if (send_cmd(ACMD(41), 0x40ff8000, RESP_SHORT, resp) &&
				(resp[0] & (1 << 31)))
			{
				card_type = (resp[0] & (1 << 30)) ? CT_SD2 | CT_BLOCK : CT_SD2;
				lib_println("card type: SD2");
				break;
			}
		} while (!lib_isTimeElapsed());

		if (!card_type)
		{
			lib_println("Error ! could not read card type");
			goto fail;
		}
	}
	else
	{
		/* sdc v1 or mmc */
		if (send_cmd(ACMD(41), 0x00ff8000, RESP_SHORT, resp))
		{
			/* ACMD41 is accepted -> sdc v1 */
			card_type = CT_SD1;
			cmd = ACMD(41);
		}
		else
		{
			/* ACMD41 is rejected -> mmc */
			card_type = CT_MMC;
			cmd = 1;
		}
		while (1)
		{
			if (send_cmd(cmd, 0x00FF8000, RESP_SHORT, resp) &&
				(resp[0] & (1 << 31)))
			{
				break;
			}
			if (lib_isTimeElapsed())
			{
				lib_println("Error ! cmd %d failed", cmd);
				goto fail;
			}
		}
	}

	byte_swap(&card_info[32], resp[0]);
	lib_println("card OCR: %d", ((uint32_t *)card_info)[8]);

	/* card state 'ready' */
	if (!send_cmd(2, 0, RESP_LONG, resp)) /* enter ident state */
		goto fail;

	for (i = 0; i < 4; i++)
		byte_swap(&card_info[16 + i * 4], resp[i]);

	/* card state 'ident' */
	if (card_type & CT_SDC)
	{
		if (!send_cmd(3, 0, RESP_SHORT, resp))
			goto fail;
		card_rca = (WORD)(resp[0] >> 16);
	}
	else
	{
		if (!send_cmd(3, 1 << 16, RESP_SHORT, resp))
			goto fail;
		card_rca = 1;
	}

	/* card state 'standby' */
	if (!send_cmd(9, ((DWORD)card_rca) << 16, RESP_LONG, resp))
		goto fail;

	for (i = 0; i < 4; i++)
		byte_swap(&card_info[i * 4], resp[i]);

	if (!send_cmd(7, ((DWORD)card_rca) << 16, RESP_SHORT, resp))
		goto fail;

	/* card state 'tran' */
	if (!(card_type & CT_BLOCK))
	{
		if (!send_cmd(16, 512, RESP_SHORT, resp) || (resp[0] & 0xfdf90000))
			goto fail;
	}

	if (card_type & CT_SDC)
	{
		/* Set wide bus */
		if (!send_cmd(ACMD(6), 2, RESP_SHORT, resp) || (resp[0] & 0xfdf90000))
			goto fail;
		SDIO->CLKCR |= (1 << 11);
	}

	/* increase clock up to 4MHz */

	SDIO->CLKCR &= ~(0xFF);
	SDIO->CLKCR |= 10;

	dstatus &= ~STA_NOINIT;

	return RES_OK;

fail:
	dstatus = STA_NOINIT;
	RCC->APB2ENR &= ~(RCC_APB2ENR_SDIOEN);
	SDIO->POWER &= ~(0b11);
	return RES_ERROR;
}

DSTATUS disk_status(BYTE pdrv)
{
	return dstatus;
}

DRESULT disk_read(BYTE pdrv, BYTE *buf, DWORD sector, UINT count)
{
	DWORD resp;
	int cmd;
	int rd;
	DWORD sta;
	DWORD data;

	if (count < 1 || count > 127)
		return RES_PARERR;

	if (dstatus & STA_NOINIT)
		return RES_NOTRDY;

	if (!(card_type & CT_BLOCK))
		sector *= 512;

	if (!check_tran(500))
		return RES_ERROR;

	cmd = (count > 1) ? 18 : 17;

	lib_beginCounter(1000);
	rd = 0;

	SDIO->DCTRL = ((0b1001 << 4) | (1 << 1));
	SDIO->DLEN = (512 * count);
	SDIO->DTIMER = 400000;

	sta = 0;
	if (!send_cmd(cmd, sector, RESP_SHORT, &resp) || (resp & 0xc0580000))
		return RES_ERROR;
	SDIO->ICR = 0xff;
	SDIO->DCTRL |= (1 << 0);

	while (!lib_isTimeElapsed())
	{

		sta = SDIO->STA;

		if (sta & ((1 << 3) | (1 << 5) | (1 << 9)))
		{
			lib_println("Error ! %s SDIO_STA: %d", __func__, (uint32_t)sta);
			break;
		}

		if (sta & (1 << 19))
			continue;

		if (rd == 0 && !(sta & (1 << 21)))
			continue;

		data = SDIO->FIFO;

		buf[rd++] = data;
		buf[rd++] = data >> 8;
		buf[rd++] = data >> 16;
		buf[rd++] = data >> 24;

		if (rd == 512 * count)
			break;
	}

	if (rd < 512 * count || cmd == 18)
		send_cmd(12, 0, RESP_SHORT, &resp);

	return SDIO->DCOUNT ? RES_ERROR : RES_OK;
}

DRESULT disk_write(BYTE pdrv, const BYTE *buf, DWORD sector, UINT count)
{
	DWORD resp;
	int cmd;
	int wr;
	DWORD sta;
	DWORD data;

	if (count < 1 || count > 127)
		return RES_PARERR;

	if (dstatus & STA_NOINIT)
		return RES_NOTRDY;

	/* FIXME Check Write Protect Pin, if any */

	if (!(card_type & CT_BLOCK))
		sector *= 512;

	if (!check_tran(500))
		return RES_ERROR;

	if (count == 1) /* Single block write */
		cmd = 24;
	else
	{ /* Multiple block write */
		cmd = (card_type & CT_SDC) ? ACMD(23) : 23;
		if (!send_cmd(cmd, count, RESP_SHORT, &resp) || (resp & 0xC0580000))
			return RES_ERROR;
		cmd = 25;
	}

	lib_beginCounter(1000);
	wr = 0;
	SDIO->DCTRL = (0b1001 << 4);
	SDIO->DLEN = (512 * count);
	SDIO->DTIMER = 400000;

	if (!send_cmd(cmd, sector, RESP_SHORT, &resp) || (resp & 0xC0580000))
	{
		lib_println("Error ! %s %d", __func__, __LINE__);
		return RES_ERROR;
	}

	SDIO->ICR = 0xff;
	SDIO->DCTRL |= (1 << 0);

	while (!lib_isTimeElapsed())
	{

		sta = SDIO->STA;

		if (sta & ((1 << 3) | (1 << 9)))
		{
			lib_println("Error ! %s SDIO_STA: %d", __func__, (uint32_t)sta);
			break;
		}

		if (sta & (1 << 16))
			continue;

		data = buf[wr++];
		data = data | (((DWORD)buf[wr++]) << 8);
		data = data | (((DWORD)buf[wr++]) << 16);
		data = data | (((DWORD)buf[wr++]) << 24);

		SDIO->FIFO = data;

		if (wr >= 512 * count)
		{
			break;
		}
	}

	if (wr < 512 * count || (cmd == 25 && (card_type & CT_SDC)))
		send_cmd(12, 0, RESP_SHORT, &resp);

	return wr < 512 * count ? RES_ERROR : RES_OK;
}

DRESULT disk_ioctl(BYTE pdrv, BYTE cmd, void *buff)
{
	/* Dummy, unneeded */
	return RES_ERROR;
}