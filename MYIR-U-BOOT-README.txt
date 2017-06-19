# MYIR-U-Boot

## Introduction

To be able to use development boards of MYIR with the u-boot, you have to prepare the SDCard.  

There are several  types of development boards, each has a different configuration.


Board Name 	| Configuration  	| Details  
-----------|--------------|---------   
MYD-AM335X(NAND) 	| myd_c335x_defconfig 	| http://www.myirtech.com/list.asp?id=466  
MYD-AM335X(EMMC) 	| myd_c335x_emmc_defconfig 	| http://www.myirtech.com/list.asp?id=466  
MYD-AM335X-Y(NAND) 	| myd_y335x_defconfig 	| http://www.myirtech.com/list.asp?id=492  
MYD-AM335X-Y(EMMC) 	| myd_y335x_emmc_defconfig 	| http://www.myirtech.com/list.asp?id=492  
MYD-AM335X-J(NAND) 	| myd_j335x_defconfig 	| http://www.myirtech.com/list.asp?id=493  
MYD-AM335X-J(EMMC) 	| myd_j335x_emmc_defconfig 	| http://www.myirtech.com/list.asp?id=493  
MYD-C437X(EMMC) 	| myd_c437x_defconfig 	|http://www.myirtech.com/list.asp?id=536 
MYD-C437X_PRU(EMMC) 	| myd_c437x_defconfig 	| http://www.myirtech.com/list.asp?id=559 
MYIR_RICOBOARD(EMMC) 	| myir_ricoboard_defconfig 	| http://www.myirtech.com/list.asp?id=510
MYIR_RICOBOARD(QSPI) 	| myir_ricoboard_qspi_defconfig 	| http://www.myirtech.com/list.asp?id=510 

## How to build it  

**1. Cross toolchain and env setting**

download cross toolchain at https://releases.linaro.org/components/toolchain/binaries/5.3-2016.02/arm-linux-gnueabihf/  
```
$export PATH=$PATH:$CROSS_TOOLCHAIN_PATH/bin
$export ARCH=arm
$export CROSS_COMPILE=arm-linux-gnueabihf-
```  

**2. Build u-boot**

e.g. For MYD-AM335X-Y. 

```
$ make myd_y335x_defconfig
$ make 
```  
**3. Result of the build**

After building, you should get a tree like this:
```
  myir-u-boot
  ├── MLO
  ├── u-boot.img
  ├── u-boot.bin	--  for QSPI boot
  ├── u-boot-spl.bin
  └── uEnv.txt
```
## How to use it  

e.g. For MYD-AM335X-Y.

**1. Boot from TF/SD card with ramdisk**
  - Prepare the uEnv.txt for this mode as shown below.
```
# This uEnv.txt file can contain additional environment settings that you
# want to set in U-Boot at boot time.  This can be simple variables such
# as the serverip or custom variables.  The format of this file is:
#    variable=value
# NOTE: This file will be evaluated after the bootcmd is run and the
#       bootcmd must be set to load this file if it exists (this is the
#       default on all newer U-Boot images.  This also means that some
#       variables such as bootdelay cannot be changed by this file since
#       it is not evaluated until the bootcmd is run.
#optargs=video=HDMI-A-1:800x600

# Uncomment the following line to enable HDMI display and disable LCD display.
fdtfile=myd_y335x.dtb
devtype=mmc
devnum=0
bootdir=/
bootpart=0:1
uenvcmd=if run loadimage; then run loadfdt; run loadramdisk; echo Booting from mmc${mmcdev} ...; run ramargs; print bootargs; bootz ${loadaddr} ${rdaddr} ${fdtaddr}; fi;

```
  - Format TF/SD with fat/fat32 format
  - Copy MLO, u-boot.img, uEnv.txt, zImage, myd_y335x.dtb, ramdisk.gz to TF/SD card.
  - Insert the TF/SD card to slot, and set bootmode to mmc0
  - Powreoff and poweron to boot from TF/SD card with ramdisk
   
**2. Boot from TF/SD card with EXT4 partition on TF/SD card**
  - Prepare the uEnv.txt for this mode as shown below.
```
# This uEnv.txt file can contain additional environment settings that you
# want to set in U-Boot at boot time.  This can be simple variables such
# as the serverip or custom variables.  The format of this file is:
#    variable=value
# NOTE: This file will be evaluated after the bootcmd is run and the
#       bootcmd must be set to load this file if it exists (this is the
#       default on all newer U-Boot images.  This also means that some
#       variables such as bootdelay cannot be changed by this file since
#       it is not evaluated until the bootcmd is run.
#optargs=video=HDMI-A-1:800x600

# Uncomment the following line to enable HDMI display and disable LCD display.
fdtfile=myd_y335x.dtb
```
  - Program sdcard.img(built with buildroot) to TF/SD card with Win32DiskImager.exe on windows pc.
  - Powreoff and poweron to boot from TF/SD card with ext4 partition on TF/SD card.

**3. Boot from Ethernet with NFS**
  - Enter U-boot console by press 'space' when u-boot booting from TF/SD card.
  - setenv serverip 192.168.1.2 ( nfs server and tftp server hosted on 192.168.1.2)
  - setenv ipaddr 192.168.1.100 ( set the ipaddr of myd_y335x board)
  - run findfdt
  - setenv rootpath /home/sunny/export/rootfs ( exported nfs directory with /etc/exports file on nfs server)
  - run netboot

**4. Boot from Ethernet with ramdisk**
  - Enter U-boot console by press 'space' when u-boot booting from TF/SD card.
  - setenv serverip 192.168.1.2 ( nfs server and tftp server hosted on 192.168.1.2)
  - setenv ipaddr 192.168.1.100 ( set the ipaddr of myd_y335x board)
  - setenv bootargs console=ttyO0,115200n8 root=/dev/ram0 rw rootfstype=ext2 ip=none earlyprintk
  - tftpboot ${loadaddr} zImage  ( zImage was copied to tftp server root directory)
  - tftpboot ${rdaddr} ramdisk.gz ( ramdisk.gz was copied to tftp server root directory)
  - tftpboot ${fdtaddr} myd_y335x.dtb  ( myd_y335x.dtb was copied to tftp server root directory)
  - bootz  ${loadaddr} ${rdaddr} ${fdtaddr}

**5. Update images from TF/SD card to NAND**
  - Prepare uEnv.txt as shown below.
```
# This uEnv.txt file can contain additional environment settings that you
# want to set in U-Boot at boot time.  This can be simple variables such
# as the serverip or custom variables.  The format of this file is:
#    variable=value
# NOTE: This file will be evaluated after the bootcmd is run and the
#       bootcmd must be set to load this file if it exists (this is the
#       default on all newer U-Boot images.  This also means that some
#       variables such as bootdelay cannot be changed by this file since
#       it is not evaluated until the bootcmd is run.
#optargs=video=HDMI-A-1:800x600

# Uncomment the following line to enable HDMI display and disable LCD display.
fdtfile=myd_y335x.dtb
devtype=mmc
devnum=0
bootdir=/
bootpart=0:1
uenvcmd=if run loadimage; then run loadfdt; run loadramdisk; echo Booting from mmc${mmcdev} ...; run ramargs; print bootargs; bootz ${loadaddr} ${rdaddr} ${fdtaddr}; fi;
```
  - Copy MLO, u-boot.img, uEnv.txt, zImage, myd_y335x.dtb, ramdisk.gz, rootfs.ubi to TF/SD card.
  - Insert the TF/SD card to slot, and set bootmode to mmc0
  - PowerOff and PowerOn to boot from TF/SD card, press 'space' to interrupt u-boot and enter the u-boot console
  - Execute 'run updatesys' in u-boot console to write MLO, u-boot.img, zImage, myd_y335x.dtb, rootfs.ubi to nand
  - Set bootmode to nand and poweron

**6. Update images from USB mass storage device to NAND**
  - Prepare uEnv.txt for this mode as shown below. 
> NOTE: Users can customize the update commands in uEnv.txt with a variable 'updatecmd', for example:
> updatecmd=env delete updatecmd;load mmc 0 0x82000000 MLO;nand erase.part NAND.SPL;nand write 0x82000000 0 ${filesize};

```
# This uEnv.txt file can contain additional environment settings that you
# want to set in U-Boot at boot time.  This can be simple variables such
# as the serverip or custom variables.  The format of this file is:
#    variable=value
# NOTE: This file will be evaluated after the bootcmd is run and the
#       bootcmd must be set to load this file if it exists (this is the
#       default on all newer U-Boot images.  This also means that some
#       variables such as bootdelay cannot be changed by this file since
#       it is not evaluated until the bootcmd is run.
#optargs=video=HDMI-A-1:800x600

# Uncomment the following line to enable HDMI display and disable LCD display.
fdtfile=myd_y335x.dtb
devtype=usb
devnum=0
bootdir=/
bootpart=0:1
optargs=earlyprintk updatesys
uenvcmd=if run loadimage; then run loadfdt; run loadramdisk; echo Booting from usb${devnum} ...; run ramargs; print bootargs; bootz ${loadaddr} ${rdaddr} ${fdtaddr}; fi;
```
  - Copy MLO, u-boot.img, uEnv.txt, zImage, myd_y335x.dtb, ramdisk.gz, rootfs.ubi to USB mass storage device.
  - Insert the USB mass storage device to USB Host 0 and boot from NAND.
  - PowerOff and PowerOn to boot from NAND, press 'space' to interrupt u-boot and enter the u-boot console
  - Execute 'run updatesys' in u-boot console to write MLO, u-boot.img, zImage, myd_y335x.dtb, rootfs.ubi to NAND
  - Set bootmode to NAND and poweron

## Links  
1. http://www.denx.de/
2. http://git.ti.com/ti-u-boot
3. https://sourceforge.net/projects/win32diskimager/
