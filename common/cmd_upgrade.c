/* @file     cmd_upgrade.c
 * @note     XX Technology Co., Ltd. All Right Reserved.
 * @brief
 * @author   JINWEI
 * @date     2015-8-30
 * @version  v1.0.0
 * @note     u-boot environment[upgrade, u-boot, factory etc]
 * @note History:
 * @note     <JINWEI>   <2015-8-30>    <v1.0.0 >   <desc>
 * @note
 * @warning
 */

#include <common.h>
#include <command.h>
#include <malloc.h>
#include <net.h>
#include <asm/io.h>
#include <spi_api.h>
#include <manufacturer/bootflash.h>

#define UPFILE_NAME  "upgrade.bin"

int do_factoryinfo_write(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
    int filesize;
	unsigned long flash_buffer = 0x80200000;
    BOOT_PARAMS *boot_params;
	
    load_addr = 0x80100000;
	boot_params = (BOOT_PARAMS *)load_addr;

	memset((char *)load_addr, 0xff, CFG_FACTORY_SIZE);
	memset((char *)flash_buffer, 0xff, CFG_FACTORY_SIZE);
	
    copy_filename(BootFile, "Factory.bin", sizeof(BootFile));

    if ((filesize = NetLoop(TFTP)) < 0)
        return 0;

	if (filesize > CFG_FACTORY_SIZE)
	{
		printf("Factory.bin is not correct: The size is too large!\n");
		return 0;
	}

	if (boot_params->magicNumber != CFG_MAGIC)
	{
		printf("Factory.bin is not correct: CFG MAGIC error!\n");
		return 0;
	}

    printf("Write factory info %d bytes into flash ...\n", filesize);

    if (raspi_erase(CONFIG_FACTORY_OFFSET, CFG_FACTORY_SIZE))
    {
        printf("Erase factory info failed, media err of the flash?\n");
        return 0;
    }

    raspi_write((char *)load_addr, CONFIG_FACTORY_OFFSET, CFG_FACTORY_SIZE);
    raspi_read((char *)flash_buffer, CONFIG_FACTORY_OFFSET, CFG_FACTORY_SIZE);

	if (memcmp((void *)load_addr, (void *)flash_buffer, filesize) == 0)
		printf("Writing factory info Successful!\n");
	else
		printf("Writing factory info Failed!\n");
	
    return 1;
}

U_BOOT_CMD(factory, 1, 1, do_factoryinfo_write, "factory - Write factory info into media\n", NULL);


int do_factoryinfo_erase(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
    if (raspi_erase(CONFIG_FACTORY_OFFSET, CFG_FACTORY_SIZE))
    {
        printf("Erase factory info failed, media err of the flash?\n");
    }
	
    return 0;
}

U_BOOT_CMD(facers, 1, 1, do_factoryinfo_erase, "facers  - Erase factory info\n", NULL);


#define CHECK_ADDR 		0x82000000   /* ¾àÀëÄÚ´æÆðÊ¼ Offset: 32MB */
int do_upgrade(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	DECLARE_GLOBAL_DATA_PTR;
	bd_t *bd = gd->bd;

	int tftpsize;
	ulong check_buf = CHECK_ADDR;
	int kernel_size = bd->bi_flashsize - (CFG_BOOTLOADER_SIZE + CFG_CONFIG_SIZE + CFG_FACTORY_SIZE);
	
    copy_filename(BootFile, UPFILE_NAME, sizeof(BootFile));

    load_addr = CFG_LOAD_ADDR;
	memset((char *)load_addr, 0xff, kernel_size);
	memset((char *)check_buf, 0xff, kernel_size);
	
    /* Download by TFTP */
    if ((tftpsize = NetLoop(TFTP)) < 0)
    {
        return -1;
    }
	
	printf("Image size: 0x%x \n", tftpsize);
	if (tftpsize > kernel_size)
	{
		printf("ERROR: The upgrade image is too large\n");
		printf("Kernel sect size: 0x%x\n", kernel_size);
		return -1;
	}
	
    /*erase flash space */
    printf("Erasing SPI flash: size(0x%x)...", kernel_size);
    if (raspi_erase((CFG_KERN_ADDR - CFG_FLASH_BASE), kernel_size))
    {
        printf("Erasing SPI Flash error!\n");
        return -1;
    }
    printf("done\n");


    /* write to flash space */
    printf("Writing SPI flash...");
    raspi_write((char *)load_addr, (CFG_KERN_ADDR - CFG_FLASH_BASE), kernel_size);
    printf("done\n");

    printf("Upgrade check ......");
    raspi_read((char *)check_buf, (CFG_KERN_ADDR - CFG_FLASH_BASE), kernel_size);
    if (memcmp((char *)load_addr, (char *)check_buf, tftpsize))
    {
        printf("Upgrade Error:Image check failed !\n");
		return -1;
    }
    /*reprotect flash space*/
    printf("done\n");	
    printf("\nUpgrade success!\n");

    /* upgrade success, reset the machine */
    printf("\nInput 'reset' command to reboot\n");

    return 0;
}

U_BOOT_CMD(
    upgrade, 2, 1, do_upgrade,
    "upgrade - upgrade the device.\n",
    " file-name \n"
    "\tupgrade the firmware, default file-name is upgrade.bin\n"
    );

int burn_uboot(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
    unsigned long flash_buffer = 0x80200000;
    int filesize = 0;

    load_addr = 0x80100000;
    if (argc == 2)
    {
        copy_filename(BootFile, argv[1], sizeof(BootFile));
    }
    else
    {
        copy_filename(BootFile, "u-boot-spi.bin", sizeof(BootFile));
        printf("using default file \"u-boot-spi.bin\" \n");
    }

	memset((char *)load_addr, 0xff, CFG_BOOTLOADER_SIZE);
	memset((char *)flash_buffer, 0xff, CFG_BOOTLOADER_SIZE);
	
    if ((filesize = NetLoop(TFTP)) < 0)
        return 0;

	printf("Uboot size: 0x%x\n", filesize);
	if (filesize > CFG_BOOTLOADER_SIZE)
	{
		printf("buboot error: The uboot image is too large\n");
		return -1;
	}

    printf("Erasing SPI flash...\n");
    if (raspi_erase(0, CFG_BOOTLOADER_SIZE))
    {
    	printf("Erasing Flash error!\n");
        return 0;
    }
    printf("done\n");
	
    raspi_write((char *)load_addr, 0, CFG_BOOTLOADER_SIZE);
    raspi_read((char *)flash_buffer, 0, CFG_BOOTLOADER_SIZE);
	
	printf("buboot: Check image...\n");
    if (memcmp((char *)load_addr, (char *)flash_buffer, filesize))
    {
        printf("buboot Error: Image check failed !\n");
		return -1;
    }
    printf("Done...\n");
	
    printf("Erasing Enviroment..\n");
    if (raspi_erase(CFG_BOOTLOADER_SIZE, CFG_CONFIG_SIZE))
    {
        printf("Erasing Enviroment failed!\n");
        return 0;
    }
    printf("done\n");
    return 0;
}

U_BOOT_CMD(
    buboot, 2, 1, burn_uboot,
    "buboot  - burn bootloader in the flash.\n",
    " file-name \n"
    "\tburn binary image in the flash, default file-name is u-boot-spi.bin .\n"
    );

