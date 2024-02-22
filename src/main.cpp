#include <stm32f4xx.h>
#include "clock.h"
#include "tick.h"
#include "debug.h"
// #include "vga.h"

#include <ff.h>

#define SYSTEM_CLOCK_SPEED 180000000

#define FNAME "test.txt"
char CONTENT[] = "This is a test file, created by ff_demo\n";

int create_file(const char *fname, const char *content)
{
    FIL fp;
    int ret;
    unsigned wr;

    println("I will now create file %s with a dummy content", fname);

    ret = f_open(&fp, fname, FA_CREATE_ALWAYS | FA_WRITE);
    if (ret != FR_OK)
    {
        println("Error ! %s open failed", fname);
        return ret;
    }

    ret = f_write(&fp, content, sizeof(CONTENT), &wr);
    if (ret != FR_OK || wr != sizeof(CONTENT))
        println("Error ! %s fwrite failed, written %d bytes", fname, wr);

    f_close(&fp);
    return ret;
}

int read_file(const char *fname)
{
    FIL fp;
    int ret;
    char buf[64];
    unsigned rd;
    int i;

    println("I will now try to open the file %s and dump its "
            "content here",
            fname);

    ret = f_open(&fp, FNAME, FA_OPEN_EXISTING | FA_READ);
    if (ret != FR_OK)
    {
        println(FNAME " open failed");
        return ret;
    }

    println("----" FNAME " dump begin ----");
    do
    {
        ret = f_read(&fp, buf, sizeof(buf), &rd);
        for (i = 0; i < rd; i++)
            sendChar(buf[i]);
    } while (rd && ret == FR_OK);
    println("----" FNAME " dump end   ----");

    f_close(&fp);

    return ret;
}

void fatfs_test()
{
    FATFS fs;
    FILINFO finfo;
    int ret;

    println("Hello from ff_demo");
    ret = f_mount(&fs, "", 1);
    if (ret != FR_OK)
    {
        println("Mount failed");
        return;
    }

    ret = create_file(FNAME, CONTENT);
    if (ret != FR_OK)
        return;

    ret = f_stat(FNAME, &finfo);
    if (ret != FR_OK)
    {
        println("Error ! could not find " FNAME);
        return;
    }
    println(FNAME " size: %d bytes", (uint32_t)finfo.fsize);

    read_file(FNAME);
}

int main()
{
    // setup
    systemClockInit();
    sysTickInit(SYSTEM_CLOCK_SPEED);
    ioInit();

    // fatfs
    fatfs_test();

    // vga
    // VGA vga;

    // loop
    while (1)
    {
    }

    return 0;
}