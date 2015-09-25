/*
 * Configuration settings for the Novena U-boot.
 *
 * Copyright (C) 2014 Marek Vasut <marex@denx.de>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_H
#define __CONFIG_H

/* System configurations */
#define CONFIG_BOARD_EARLY_INIT_F
#define CONFIG_BOARD_LATE_INIT
#define CONFIG_MISC_INIT_R
#define CONFIG_FIT
#define CONFIG_KEYBOARD

/* U-Boot Commands */
#define CONFIG_CMD_ASKENV
#define CONFIG_CMD_BMODE
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_EEPROM
#define CONFIG_CMD_I2C
#define CONFIG_FAT_WRITE
#define CONFIG_CMD_MII
#define CONFIG_CMD_PCI
#define CONFIG_CMD_PING
#define CONFIG_CMD_SATA
#define CONFIG_CMD_TIME
#define CONFIG_CMD_USB
#define CONFIG_VIDEO

/* U-Boot general configurations */
#define CONFIG_VERSION_VARIABLE			/* U-BOOT version */

/* U-Boot environment */
#define CONFIG_ENV_SIZE			(16 * 1024)
/*
 * Environment is on MMC, starting at offset 512KiB from start of the card.
 * Please place first partition at offset 1MiB from the start of the card
 * as recommended by GNU/fdisk. See below for details:
 * http://homepage.ntlworld.com./jonathan.deboynepollard/FGA/disc-partition-alignment.html
 */
#ifdef CONFIG_CMD_MMC
#define CONFIG_ENV_IS_IN_MMC
#define CONFIG_SYS_MMC_ENV_DEV		0
#define CONFIG_ENV_OFFSET		(512 * 1024)
#define CONFIG_ENV_SIZE_REDUND		CONFIG_ENV_SIZE
#define CONFIG_ENV_OFFSET_REDUND	\
		(CONFIG_ENV_OFFSET + CONFIG_ENV_SIZE)
#else
#define CONFIG_ENV_IS_NOWHERE
#endif

/* Booting Linux */
#define CONFIG_BOOTARGS			"console=ttymxc1,115200 "
#define CONFIG_HOSTNAME			novena

/* Physical Memory Map */
#define CONFIG_NR_DRAM_BANKS		1
#define PHYS_SDRAM			MMDC0_ARB_BASE_ADDR
#define PHYS_SDRAM_SIZE			0xF0000000

#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM
#define CONFIG_SYS_INIT_RAM_ADDR	IRAM_BASE_ADDR
#define CONFIG_SYS_INIT_RAM_SIZE	IRAM_SIZE

#define CONFIG_SYS_INIT_SP_OFFSET \
	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR \
	(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)

#define CONFIG_SYS_MEMTEST_START	0x10000000
#define CONFIG_SYS_MEMTEST_END		0x20000000

#define CONFIG_SYS_MALLOC_LEN		(64 * 1024 * 1024)

/* SPL */
#define CONFIG_SPL_EXT_SUPPORT
#define CONFIG_SPL_MMC_SUPPORT
#include "imx6_spl.h"			/* common IMX6 SPL configuration */
#include <config_distro_defaults.h>
#include "mx6_common.h"

/* Ethernet Configuration */
#ifdef CONFIG_CMD_NET
#define CONFIG_FEC_MXC
#define CONFIG_MII
#define IMX_FEC_BASE			ENET_BASE_ADDR
#define CONFIG_FEC_XCV_TYPE		RGMII
#define CONFIG_ETHPRIME			"FEC"
#define CONFIG_FEC_MXC_PHYADDR		0x7
#define CONFIG_PHYLIB
#define CONFIG_PHY_MICREL
#define CONFIG_PHY_MICREL_KSZ9021
#define CONFIG_ARP_TIMEOUT		200UL
#endif

/* I2C */
#define CONFIG_SYS_I2C
#define CONFIG_SYS_I2C_MXC
#define CONFIG_SYS_I2C_MXC_I2C3		/* enable I2C bus 3 */
#define CONFIG_I2C_MULTI_BUS
#define CONFIG_I2C_MXC
#define CONFIG_SYS_I2C_SPEED		100000

/* I2C EEPROM */
#ifdef CONFIG_CMD_EEPROM
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN	2
#define CONFIG_SYS_SPD_BUS_NUM		2
#endif

/* MMC Configs */
#define CONFIG_SYS_FSL_ESDHC_ADDR	0
#define CONFIG_SYS_FSL_USDHC_NUM	2

/* PCI express */
#ifdef CONFIG_CMD_PCI
#define CONFIG_PCI
#define CONFIG_PCI_PNP
#define CONFIG_PCI_SCAN_SHOW
#define CONFIG_PCIE_IMX
#define CONFIG_PCIE_IMX_PERST_GPIO	IMX_GPIO_NR(3, 29)
#define CONFIG_PCIE_IMX_POWER_GPIO	IMX_GPIO_NR(7, 12)
#endif

/* PMIC */
#define CONFIG_POWER
#define CONFIG_POWER_I2C
#define CONFIG_POWER_PFUZE100
#define CONFIG_POWER_PFUZE100_I2C_ADDR	0x08

/* SATA Configs */
#ifdef CONFIG_CMD_SATA
#define CONFIG_DWC_AHSATA
#define CONFIG_SYS_SATA_MAX_DEVICE	1
#define CONFIG_DWC_AHSATA_PORT_ID	0
#define CONFIG_DWC_AHSATA_BASE_ADDR	SATA_ARB_BASE_ADDR
#define CONFIG_LBA48
#define CONFIG_LIBATA
#endif

/* UART */
#define CONFIG_MXC_UART
#define CONFIG_MXC_UART_BASE		UART2_BASE

/* USB Configs */
#ifdef CONFIG_CMD_USB
#define CONFIG_USB_EHCI
#define CONFIG_USB_EHCI_MX6
#define CONFIG_USB_STORAGE
#define CONFIG_USB_KEYBOARD
#define CONFIG_SYS_USB_EVENT_POLL_VIA_CONTROL_EP
#define CONFIG_USB_HOST_ETHER
#define CONFIG_USB_ETHER_ASIX
#define CONFIG_USB_ETHER_SMSC95XX
#define CONFIG_USB_MAX_CONTROLLER_COUNT 2
#define CONFIG_MXC_USB_PORTSC		(PORT_PTS_UTMI | PORT_PTS_PTW)
#define CONFIG_MXC_USB_FLAGS		0
/* Gadget part */
#define CONFIG_CI_UDC
#define CONFIG_USBD_HS
#define CONFIG_USB_GADGET_DUALSPEED
#define CONFIG_USB_ETHER
#define CONFIG_USB_ETH_CDC
#define CONFIG_NETCONSOLE
#endif

/* Video output */
#ifdef CONFIG_VIDEO
#define CONFIG_VIDEO_IPUV3
#define CONFIG_CFB_CONSOLE
#define CONFIG_VGA_AS_SINGLE_DEVICE
#define CONFIG_SYS_CONSOLE_IS_IN_ENV
#define CONFIG_VIDEO_BMP_RLE8
#define CONFIG_SPLASH_SCREEN
#define CONFIG_BMP_16BPP
#define CONFIG_VIDEO_LOGO
#define CONFIG_IPUV3_CLK		260000000
#define CONFIG_CMD_HDMIDETECT
#define CONFIG_CONSOLE_MUX
#define CONFIG_IMX_HDMI
#define CONFIG_IMX_VIDEO_SKIP
#endif


/*
 * Memory layout for where various images get loaded by boot scripts:
 *
 * scriptaddr can be pretty much anywhere that doesn't conflict with something
 *   else. Put it low in memory to avoid conflicts.
 *
 * pxefile_addr_r can be pretty much anywhere that doesn't conflict with
 *   something else. Put it low in memory to avoid conflicts.
 *
 * kernel_addr_r must be within the first 128M of RAM in order for the
 *   kernel's CONFIG_AUTO_ZRELADDR option to work. Since the kernel will
 *   decompress itself to 0x8000 after the start of RAM, kernel_addr_r
 *   should not overlap that area, or the kernel will have to copy itself
 *   somewhere else before decompression. Similarly, the address of any other
 *   data passed to the kernel shouldn't overlap the start of RAM. Pushing
 *   this up to 16M allows for a sizable kernel to be decompressed below the
 *   compressed load address.
 *
 * fdt_addr_r simply shouldn't overlap anything else. Choosing 32M allows for
 *   the compressed kernel to be up to 16M too.
 *
 * ramdisk_addr_r simply shouldn't overlap anything else. Choosing 33M allows
 *   for the FDT/DTB to be up to 1M, which is hopefully plenty.
 */
#define ENV_MEM_LAYOUT_SETTINGS \
	"bootm_size=0x20000000\0" \
	"scriptaddr=0x0010000000\0" \
	"pxefile_addr_r=0x00200000\0" \
	"kernel_addr_r=0x12000000\0" \
	"fdt_addr_r=0x13000000\0" \
	"ramdisk_addr_r=0x13100000\0" \

#define BOOT_TARGET_DEVICES(func) \
	func(MMC, mmc, 0) \
	func(USB, usb, 0) \
	func(PXE, pxe, na) \
	func(DHCP, dhcp, na)
#include <config_distro_bootcmd.h>

#define CONFIG_EXTRA_ENV_SETTINGS \
	ENV_MEM_LAYOUT_SETTINGS \
	"fdtfile=" CONFIG_DEFAULT_DEVICE_TREE ".dtb\0" \
	BOOTENV

#endif				/* __CONFIG_H */
