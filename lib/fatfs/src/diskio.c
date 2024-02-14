// based on this lib : https://github.com/colosimo/fatfs-stm32

#include "ff.h"
#include "diskio.h"

#include <stm32f4xx.h>

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
	DWORD start;

	k_delay(1);

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
	start = k_ticks();

	while (1)
	{

		if (k_elapsed(start) > ms_to_ticks(100))
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
				err("%s timeout idx=%d arg=%08x\n", __func__, idx, (uint32_t)arg);
				return 0;
			}

			/* check if crc err */
			if (s & 1 << 1)
			{
				if (idx == 1 || idx == 12 || idx == 41)
					break;
				err("%s crcfail idx=%d arg=%08x\n", __func__, idx, (uint32_t)arg);
				return 0;
			}

			if (s & 1 << 6)
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
	DWORD t;
	DWORD resp;

	t = k_ticks();

	while (k_elapsed(t) < ms_to_ticks(tout_ms))
	{
		if (send_cmd(13, ((DWORD)card_rca) << 16, RESP_SHORT, &resp) && ((resp & 0x01e00) == 0x00800))
			return 1;
	}
	return 0;
}

DSTATUS disk_initialize(BYTE pdrv)
{
	DWORD resp[4];
	DWORD start;
	WORD cmd;
	/* DWORD clkcr; */
	int i;

	dstatus = STA_NOINIT;

	/* SDIO_CD: input gpio, card detect */
	gpio_func(IO(PORTB, 15), 0);
	gpio_dir(IO(PORTB, 15), 0);
	gpio_mode(IO(PORTB, 15), PULL_NO);

	/* SDIO_D0 */
	gpio_func(IO(PORTC, 8), 12);
	gpio_mode(IO(PORTC, 8), PULL_NO);

	/* SDIO_D1 */
	gpio_func(IO(PORTC, 9), 12);
	gpio_mode(IO(PORTC, 9), PULL_NO);

	/* SDIO_D2 */
	gpio_func(IO(PORTC, 10), 12);
	gpio_mode(IO(PORTC, 10), PULL_NO);

	/* SDIO_D3 */
	gpio_func(IO(PORTC, 11), 12);
	gpio_mode(IO(PORTC, 11), PULL_NO);

	/* SDIO_CK */
	gpio_func(IO(PORTC, 12), 12);
	gpio_mode(IO(PORTC, 12), PULL_NO);

	/* SDIO_CMD */
	gpio_func(IO(PORTD, 2), 12);
	gpio_mode(IO(PORTD, 2), PULL_NO);

	dstatus &= ~STA_NOINIT;

	if (gpio_rd(IO(PORTB, 15)))
		dstatus |= STA_NODISK;

	if (dstatus & STA_NODISK)
		return RES_OK;

	or32(RCC_APB2ENR, BIT11);
	wr32(R_SDIO_CLKCR, BIT8 | ((42000 / 400) - 2)); /* clk set to 400kHz */
	wr32(R_SDIO_POWER, 0b11);

	send_cmd(0, 0, 0, NULL);

	start = k_ticks();
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
				log("card type: SD2\n");
				break;
			}
		} while (k_elapsed(start) < ms_to_ticks(1000));

		if (!card_type)
		{
			err("could not read card type\n");
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
				(resp[0] & BIT31))
			{
				break;
			}
			if (k_elapsed(start) > ms_to_ticks(1000))
			{
				err("cmd %d failed\n", cmd);
				goto fail;
			}
		}
	}

	byte_swap(&card_info[32], resp[0]);
	log("card OCR: %08x\n", ((uint *)card_info)[8]);

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
		or32(R_SDIO_CLKCR, BIT11);
	}

	/* increase clock up to 4MHz */
	and32(R_SDIO_CLKCR, ~0xff);
	or32(R_SDIO_CLKCR, 10);

	dstatus &= ~STA_NOINIT;

	return RES_OK;

fail:
	dstatus = STA_NOINIT;
	and32(RCC_APB2ENR, ~BIT11);
	wr32(R_SDIO_POWER, 0b00);
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
	DWORD t;
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

	t = k_ticks();
	rd = 0;

	SDIO->DCTRL = ((0b1001 << 4) | (1 << 1));
	SDIO->DLEN = (512 * count);
	SDIO->DTIMER = 400000;

	sta = 0;
	if (!send_cmd(cmd, sector, RESP_SHORT, &resp) || (resp & 0xc0580000))
		return RES_ERROR;
	SDIO->ICR = 0xff;
	SDIO->DCTRL |= (1 << 0);

	while (k_elapsed(t) < ms_to_ticks(1000))
	{

		sta = SDIO->STA;

		if (sta & ((1 << 3) | (1 << 5) | (1 << 9)))
		{
			err("%s SDIO_STA: %08x\n", __func__, (uint32_t)sta);
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
	DWORD t;
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

	t = k_ticks();
	wr = 0;
	SDIO->DCTRL = (0b1001 << 4);
	SDIO->DLEN = (512 * count);
	SDIO->DTIMER = 400000;

	if (!send_cmd(cmd, sector, RESP_SHORT, &resp) || (resp & 0xC0580000))
	{
		err("%s %d\n", __func__, __LINE__);
		return RES_ERROR;
	}

	SDIO->ICR = 0xff;
	SDIO->DCTRL |= (1 << 0);

	while (k_elapsed(t) < ms_to_ticks(1000))
	{

		sta = SDIO->STA;

		if (sta & ((1 << 3) | (1 << 9)))
		{
			err("%s SDIO_STA: %08x\n", __func__, (uint32_t)sta);
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