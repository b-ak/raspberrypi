  ## Table of Contents   
  * [1. Cloning tools and code](#1-cloning-tools-and-code)
  * [2. SD card setup](#2-sd-card-setup)
     * [2.1 Using the raspbian wheezy image](#21-using-the-raspbian-wheezy-image)
     * [2.2 Cloning SD cards](#22-cloning-sd-cards)    
        * [2.2.1 Better Way](#221-better-way)
     * [2.3 Moving to a newer branch](#23-moving-to-a-newer-branch)
     * [2.4 Building a custom kernel](#24-building-a-custom-kernel)
  * [3. Setting up a Git repository](#3-setting-up-a-git-repository)
     * [3.1 Generating SSH keys](#31-generating-ssh-keys)
     * [3.2 Initialize repository](#32-initialize-repository)
     * [3.3 Committing to the repo](#33-committing-to-the-repo)
  * [4. How does Pi boot](#4-how-does-pi-boot)
  * [5. Making our own minimalistic kernel](#5-making-our-own-minimalistic-kernel)
     * [5.1 Booting the Operating System](#51-booting-the-operating-system)
     * [5.2 Kernel Implementation](#52-kernel-implementation)
     * [5.3 Linking the Kernel](#53-linking-the-kernel)
     * [5.4 Booting the Kernel](#54-booting-the-kernel)
  * [6. RPi - Ubuntu Snappy Core](#6-rpi---ubuntu-snappy-core)
     * [6.1 U-Boot compilation](#61-u-boot-compilation)
     * [6.2 Raspberry Pi 2 bootstrap](#62-raspberry-pi-2-bootstrap)
     * [6.3 Booting Snappy ubuntu on RPi 2](#63-booting-snappy-ubuntu-on-rpi-2)
        * [6.3.1 Recreating snappy ubuntu files](#631-recreating-snappy-ubuntu-files)
  * [7. Wi-Fi on RPi](#7-wi-fi-on-rpi)
     * [7.1 Connecting to Wi-Fi](#71-connecting-to-wi-fi)
     * [7.2 VNC Server on RPi](#72-vnc-server-on-rpi)
     * [7.3 VNC Client/Viewer](#73-vnc-clientviewer)
     * [7.4 Autostart VNC server at boot time](#74-autostart-vnc-server-at-boot-time)


## 1. Cloning tools and code

Get the ARM Toolchain
```
git clone https://github.com/raspberrypi/tools
```

Get the Kernel sources 
```
git clone --depth=1 https://github.com/raspberrypi/linux
```

The bootloader and other configs
```
https://github.com/raspberrypi/firmware.git
```

## 2. SD card setup 
The Raspberry Pi will not boot without a properly formatted SD Card, containing the bootloader and a suitable operating system.

### 2.1 Using the raspbian wheezy image
Writing the Raspbian image to your SD card

```
sudo dd bs=1M if=2015-05-05-raspbian-wheezy.img of=/dev/sdb
sync
```
### 2.2 Cloning SD cards
Cloning a 4GB SD card into a 8GB SD card

```
time sudo dd bs=64K conv=sync,noerror if=/dev/sdc of=/dev/sdb
```

Cloning a 32GB SD card into a 16GB SD card
1. Partition the 16GB with two partitions FAT(lba) and EXT4
2. Mount both the cards and use rsync to copy data
```
cd /meddia/b-ak
rsync -ah --info=progress2 --partial ./boot/ ./boot1/
sudo rsync -ah --info=progress2 --partial ./7f593562-9f68-4bb9-a7c9-2b70ad620873/ ./4d7d6d24-a608-46fb-9b39-a4f30ddb8902/
```
#### 2.2.1 Better Way 
1. Shrink the 32 GiB card
![](documents/images/32gb_to_16gb.png?raw=true)

2. Make this calculation to get the end of the 16 GiB space.
```
Total Size in MiB = 14.77 * 1024 + 4 + 63 = 15192
bs (in dd command) = 4M. So 15192/4 = 3798 blocks
```
3. Hit the command
```
sudo dd bs=4M of=dapm-91.img if=/dev/mmcblk0 count=3798
```
4. Copy the image to the smaller SD card.

### 2.3 Moving to a newer branch

List references(branches, tags, etc.,) in a local repository
```
git show-ref
	...
	...
	b6cafbf16c095a671b1a5e90dd734390f53046b2 refs/remotes/origin/rpi-4.4.y_rebase
	237402141fd74ca989bd86ebb76d834cb6fa5454 refs/remotes/origin/rpi-4.5.y
	2b1791a6693b0e22568426a5c99efa92403f3ffe refs/remotes/origin/rpi-4.6.y
	c2cbd9c611256e7b957f75c23d9f76d58a4893c1 refs/remotes/origin/rpi-4.7.y
	061dccce6cf6705bbb5da29a643f4b0ad1d11630 refs/remotes/origin/rpi-4.8.y
	3f53e7886737a975e3fe76bc8ae6cc78f33c8cf8 refs/remotes/origin/rpi-4.9.y
	ad9d278a772d0f725126f1d947427e1947d7a39a refs/remotes/origin/rpi-4.9.y-rebase
	8fa2e19c4fdbe17704947e444674e19ea47c8ddd refs/remotes/origin/rpi-patches
	935c7ce84c982a26f567a03a58a1537424569938 refs/remotes/origin/rpi-r.9.y
	...
	...
```

Checkout the branch of interest
```
git checkout 3f53e7886737a975e3fe76bc8ae6cc78f33c8cf8
```

Switch to that branch from the existing one
```
git checkout rpi-4.9.y
```

### 2.4 Building a custom kernel

Export the toolchain
```
export PATH=$PATH:/data/raspberry-pi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin
```
Raspberry Pi
```
cd linux
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- bcmrpi_defconfig
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-

mkdir ../modules
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- INSTALL_MOD_PATH=../modules/ modules
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- INSTALL_MOD_PATH=../modules/ modules_install

cd ../tools/mkimage/
./imagetool-uncompressed.py  ../../linux/arch/arm/boot/zImage
mv kernel.img /media/b-ak/boot/

cd /data/raspberry-pi/modules/lib
tar -cvzf modules.tar.gz *
mv modules.tar.gz /media/b-ak/13d368bf-6dbf-4751-8ba1-88bed06bef77/tmp/
```

Raspberry Pi 2/3
```
cd linux
KERNEL=kernel7
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- bcm2709_defconfig
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- zImage modules dtbs -j 4

sudo make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- INSTALL_MOD_PATH=/media/b-ak/13d368bf-6dbf-4751-8ba1-88bed06bef77/ modules_install

sudo scripts/mkknlimg arch/arm/boot/zImage /media/b-ak/boot/$KERNEL.img
sudo cp arch/arm/boot/dts/*.dtb /media/b-ak/boot/
sudo cp arch/arm/boot/dts/overlays/*.dtb* /media/b-ak/boot/

sudo umount /media/b-ak/*

```

Or

Use the script [RPi 3 kernel builder](https://gist.github.com/b-ak/ecf6640241e12bd31bcc7e433fa60d40)

## 3. Setting up a Git repository


### 3.1 Generating SSH keys

[Generating SSH keys involves the following steps](https://help.github.com/categories/ssh/)

### 3.2 Initialize repository
```
git init
git remote add origin git@github.com:b-ak89/RPi.git
```
### 3.3 Committing to the repo
```
git add README
git commit -m "first commit"
git push -u origin master
```

## 4. How does Pi boot

1. When the Raspberry Pi is first turned on, the ARM core is off, and the GPU core is on.
   At this point the SDRAM is disabled.
2. The GPU starts executing the first stage bootloader (ROM code), which is stored in ROM
   on the SoC. The first stage bootloader reads the SD card, and loads the second stage
   bootloader (bootcode.bin) into the L2 cache, and runs it.
3. bootcode.bin enables SDRAM, and reads the third stage bootloader (loader.bin) from
   the SD card into RAM, and runs it.
4. loader.bin reads the GPU firmware (start.elf).
5. start.elf reads config.txt, cmdline.txt and kernel.img, and at last the ARM cpu is
   started running that kernel image.

loader.bin doesn't do much. It can handle .elf files, and so is needed to load start.elf
at the top of memory (ARM uses SDRAM from address zero). There is a plan to add elf
loading support to bootcode.bin, which would make loader.bin unnecessary, but it's a low
priority (I guess it might save you 100ms on boot).

[Source](http://raspberrypi.stackexchange.com/questions/10489/how-does-raspberry-pi-boot)   
[Bare metal examples](https://github.com/dwelch67/raspberrypi)

## 5. Making our own minimalistic kernel


We need three input files:
1. `boot.s` - kernel entry point that sets up the processor environment
2. `kernel.c` - your actual kernel routines
3. `linker.ld` - for linking the above files
4. Booting the kernel

### 5.1 Booting the Operating System

The section `.text.boot` will be used in the linker script to place the `boot.S` as
the very first thing in our kernel image. The code initializes a minimum C environment,
which means having a stack and zeroing the BSS segment, before calling the `kernel_main` function.

Note that the code avoids using `r0-r2` so the remain valid for the `kernel_main` call.

You can then assemble boot.S using:
`arm-none-eabi-gcc -mcpu=arm1176jzf-s -fpic -ffreestanding -c boot.S -o boot.o`

### 5.2 Kernel Implementation

The GPU bootloader passes arguments to the kernel via `r0-r2` and the `boot.S` makes sure
to preserve those 3 registers.

They are the first 3 arguments in a C function call.
* The argument `r0` contains a code for the device the rpi was booted from.
This is generally `0` but its actual value depends on the firmware of the board.
* `r1` contains the `ARM Linux Machine Type` which for the `rpi` is `3138 (0xc42)`
identifying the `bcm2708 cpu`. Full list of [ARM Machine Types](http://www.arm.linux.org.uk/developer/machines/).
* `r2` contains the address of the `ATAGs`.

Compile it using:   
`arm-none-eabi-gcc -mcpu=arm1176jzf-s -fpic -ffreestanding -std=gnu99 -c kernel.c -o kernel.o -O2 -Wall -Wextra`

### 5.3 Linking the Kernel

We can now assemble boot.s and compile kernel.c. This produces two object files
that each contain part of the kernel.

To create the full and final kernel we will have to link these object files into the
final kernel program, usable by the bootloader. When developing user-space programs,
your toolchain ships with default scripts for linking such programs.

However, these are unsuitable for kernel development and we need to provide our own
customized linker script.

Create a `linker.ld`:

* `ENTRY(_start)` declares the entry point for the kernel image.
The symbol `(_start)` was declared in the `boot.S` file.

* SECTIONS declares sections. It decides where the bits and pieces of our code and data
go and also sets a few symbols that help us track the size of each section.

* The "." denotes the current address so the first line tells the linker to set the current
address to `0x8000`, where the kernel starts. The current address is automatically
incremented when the linker adds data. The second line then creates a symbol `__start`
and sets it to the current address.

* After that sections are defined for text (code), read-only data, read-write data and BSS
(0 initialized memory). Other than the name the sections are identical so lets just look
at one of them.

```
__text_start = .;
.text : {
KEEP(*(.text.boot))
*(.text)
}
. = ALIGN(4096); /* align to page size */
__text_end = .;
```

* The first line creates a `__text_start` symbol for the section. The second line opens a `.text`
section for the output file which gets closed in the fifth line. Lines 3 and 4 declare what
sections from the input files will be placed inside the output `.text` section.
In our case `.text.boot` is to be placed first followed by the more general `.text`. `.text.boot`
is only used in `boot.S` and ensures that it ends up at the beginning of the kernel image. `.text`
then contains all the remaining code

* Any data added by the linker automatically increments the current addrress ("."). In line 6
we explicitly increment it so that it is aligned to a 4096 byte boundary (which is the page
size for the RPi). And last line 7 creates a `__text_end` symbol so we know where the section ends.

* What are the `__text_start` and `__text_end` for and why use page alignment ?   
 The 2 symbols can be used in the kernel source and the linker will then place the correct addresses into the binary.   
 As an example the `__bss_start` and `__bss_end` are used in `boot.S`. But you can also use the symbols from C by declaring them extern first.   
 *After all sections are declared the `__end` symbol is created. If you ever want to know how large your kernel is at runtime you can use `__start` and `__end` to find out.*
 
 You can then link your kernel using:   
`arm-none-eabi-gcc -T linker.ld -o myos.elf -ffreestanding -O2 -nostdlib boot.o kernel.o`   
`arm-none-eabi-objcopy myos.elf -O binary myos.bin`

* `arm-none-eabi-objcopy`   
This utility is used to copy binary files (and possibly preform transformations on them
in the process).    
We use it to copy our linked program into an IMG file.

[Further reading](http://wiki.osdev.org/Raspberry_Pi_Bare_Bones)     
[Reference Link](https://rpidev.wordpress.com/)

### 5.4 Booting the Kernel

`cp myos.bin /media/b-ak/boot/kernel.img`   
`sync`   
`umount /media/b-ak/*`

Put the SD card into the Pi. It should work.

## 6. RPi - Ubuntu Snappy Core 

### 6.1 U-Boot compilation

```
git clone git://git.denx.de/u-boot.git

make ARCH=arm CROSS_COMPILE=arm-bcm2708-linux-gnueabi- rpi_2_defconfig
make ARCH=arm CROSS_COMPILE=arm-bcm2708-linux-gnueabi-

echo 'kernel=u-boot.bin' > /media/b-ak/boot/config.txt
```

[RPi U-Boot](http://elinux.org/RPi_U-Boot)

### 6.2 Raspberry Pi 2 bootstrap

1. Format a micro-SD card with a legacy (PC/MBR/BIOS/legacy) partition table -- Raspberry Pi 2's 
   ROM doesn't support GPT.
2. Create a FAT32 partition [boot partition]; this will hold bootloaders, A/B kernels and initrds, 
   U-Boot config and script. Copy files (bcm2709-rpi-2-b.dtb, bootcode.bin, start.elf, fixup.dat, u-boot.bin, zImage) 
   in this directory in the partition.
3. Boot Raspberry Pi 2 and get to the U-Boot prompt (press enter on serial console).

Run these U-Boot commands
```
       set fdtfile bcm2709-rpi-2-b.dtb
       setenv bootargs "earlyprintk console=tty0 console=ttyAMA0 root=/dev/mmcblk0p2 rootfstype=ext4 rootwait noinitrd"
       saveenv

       mmc dev 0
       setenv zImage "fatload mmc 0:1 ${kernel_addr_r} zImage"
       setenv devtree "fatload mmc 0:1 ${fdt_addr_r} ${fdtfile}"
       setenv up "bootz ${kernel_addr_r} - ${fdt_addr_r}"
       saveenv

       run zImage
       run devtree
       run up
```

This should boot up to the linux kernel.


### 6.3 Booting Snappy ubuntu on RPi 2

```
wget http://people.canonical.com/~platform/snappy/raspberrypi2/ubuntu-15.04-snappy-armhf-rpi2.img.xz
xzcat ubuntu-15.04-snappy-armhf-rpi2.img.xz | sudo dd of=/dev/sdc bs=32M
sync
```

#### 6.3.1 Recreating snappy ubuntu files


[bootcode.bin and start.elf are SPL bits and is available under LICENCE.broadcom](https://github.com/raspberrypi/firmware/tree/master/boot)

Following files were extracted from 
- zImage is boot/vmlinuz-3.19.1-2-generic-bcm2709
- bcm2836-rpi-2-b.dtb is lib/firmware/3.19.1-2-generic-bcm2709/device-tree/bcm2709-rpi-2-b.dtb

`kernel7.img` is `u-boot.bin` as built from [swarren/u-boot](https://github:swarren/u-boot) with Ubuntu's `arm-linux-gnueabihf` cross-compiler.

[Reference-only]   
```
boot.env is a saveenv U-Boot environment (binary format) with:   
mmc_boot changed from:
if mmc dev ${devnum}; then setenv devtype mmc; run scan_dev_for_boot_part; fi
to:
if mmc dev ${devnum}; then setenv devtype mmc; if run loadbootenv; 
then echo Loaded environment from ${bootenv}; 
run importbootenv; fi; if test -n "$uenvcmd"; 
then echo Running uenvcmd ...; run uenvcmd; 
fi; 
run scan_dev_for_boot_part; 
fi
and defined:
bootenv=uEnv.txt
loadbootenv=load ${devtype} ${devnum} ${loadaddr} ${bootenv}
importbootenv=
importbootenv=echo Importing environment from mmc ...; env import -t -r $loadaddr $filesize
```

## 7. Wi-Fi on RPi

### 7.1 Connecting to Wi-Fi

1. Setup a hotspot on your phones or connect to a local router
2. Modify the wpa_supplicant   
  `sudo vi /etc/wpa_supplicant/wpa_supplicant.conf`
  ```
  ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
  update_config=1
  country=GB

  network={
          ssid="TP-LINK"
          psk="12345678"
          key_mgmt=WPA-PSK
          priority=1
          id_str="homeFlash"
  }

  network={
          ssid="slyfox"
          psk="grapesaresour"
          key_mgmt=WPA-PSK
          priority=2
          id_str="Nexus"
  }
  ```


### 7.2 VNC Server on RPi

1. Install VNC server on RPi   
  `sudo apt-get install tightvncserver`
2. Run `tightvncserver` in the terminal and setup passwords
3. Creating a view only password is optional

### 7.3 VNC Client/Viewer

1. Install `RealVNC Viewer`
2. Find RPi’s IP address   
`sudo arp-scan --localnet` or `sudo nmap -sP --disable-arp-ping 192.168.43.0/24`
3. Connect to raspberry pi using RealVNC

### 7.4 Autostart VNC server at boot time

1. Copy the systemd service file [tightvncserver.service](./documents/vnc/tightvncserver.service) to `/etc/systemd/system`
2. Change the file so it is owned by root
```
$ sudo chown root:root /etc/systemd/system/tightvncserver.service
```
3. Make the file executable by running
```
$ sudo chmod 755 /etc/systemd/system/tightvncserver.service
```
4. Enable startup at boot using
```
$ sudo systemctl enable tightvncserver.service
```
6. Reboot. Check if VNCserver is listed in the running units
```
$ systemctl list-units | grep vnc
  tightvncserver.service     loaded active running   TightVNC remote desktop server
```
7. If the script is changed, reload the service
```
$ sudo systemctl daemon-reload
$ sudo systemctl restart  tightvncserver.service
```


[END]
