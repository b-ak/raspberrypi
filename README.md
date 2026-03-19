# Raspberry Pi Notes

A collection of notes, scripts, and projects for Raspberry Pi development — covering setup, kernel building, bare-metal programming, Python projects, and more.

## Repository Structure

| Directory | Description |
|-----------|-------------|
| [`android-11-rpi4/`](android-11-rpi4/) | Android 11 build guide and scripts for Raspberry Pi 4 |
| [`bare-bones/`](bare-bones/) | Bare-metal C/Assembly examples (blinky LED, UART driver) |
| [`python-projects/`](python-projects/) | Python GPIO projects (blinky LED, light sensor with IFTTT) |
| [`documents/`](documents/) | Reference PDFs, images, and VNC service files |

---

## Table of Contents

- [1. Getting Started](#1-getting-started)
  - [1.1 Cloning Tools and Code](#11-cloning-tools-and-code)
  - [1.2 SD Card Setup](#12-sd-card-setup)
    - [1.2.1 Writing a Raspbian Image](#121-writing-a-raspbian-image)
    - [1.2.2 Cloning SD Cards](#122-cloning-sd-cards)
    - [1.2.3 Setting Up a Git Repository](#123-setting-up-a-git-repository)
- [2. How does Pi boot](#2-how-does-pi-boot)
- [3. Building a Custom Kernel](#3-building-a-custom-kernel)
  - [3.1 Moving to a Newer Kernel Branch](#31-moving-to-a-newer-kernel-branch)
  - [3.2 Cross-Compiling the Kernel](#32-cross-compiling-the-kernel)
- [4. Making our own minimalistic kernel](#4-making-our-own-minimalistic-kernel)
  - [4.1 Booting the Operating System](#41-booting-the-operating-system)
  - [4.2 Kernel Implementation](#42-kernel-implementation)
  - [4.3 Linking the Kernel](#43-linking-the-kernel)
  - [4.4 Deploying to the Pi](#44-deploying-to-the-pi)
- [5. Ubuntu Snappy Core on RPi 2](#5-ubuntu-snappy-core-on-rpi-2)
  - [5.1 U-Boot Compilation](#51-u-boot-compilation)
  - [5.2 Raspberry Pi 2 Bootstrap](#52-raspberry-pi-2-bootstrap)
  - [5.3 Booting Snappy Ubuntu](#53-booting-snappy-ubuntu)
    - [5.3.1 Recreating Snappy Ubuntu Files](#531-recreating-snappy-ubuntu-files)
- [6. Wi-Fi and Remote Access](#6-wi-fi-and-remote-access)
  - [6.1 Connecting to Wi-Fi](#61-connecting-to-wi-fi)
  - [6.2 VNC Server on RPi](#62-vnc-server-on-rpi)
  - [6.3 VNC Client/Viewer](#63-vnc-clientviewer)
  - [6.4 Autostart VNC Server at Boot](#64-autostart-vnc-server-at-boot)

---

## 1. Getting Started

### 1.1 Cloning Tools and Code

Get the ARM toolchain:
```
git clone https://github.com/raspberrypi/tools
```

Get the kernel sources:
```
git clone --depth=1 https://github.com/raspberrypi/linux
```

Get the bootloader and firmware configs:
```
git clone https://github.com/raspberrypi/firmware.git
```

### 1.2 SD Card Setup

The Raspberry Pi will not boot without a properly formatted SD card containing the bootloader and a suitable operating system.

#### 1.2.1 Writing a Raspbian Image

Write the Raspbian image to your SD card:
```
sudo dd bs=1M if=2015-05-05-raspbian-wheezy.img of=/dev/sdb
sync
```

#### 1.2.2 Cloning SD Cards

**Cloning a 4 GB SD card to an 8 GB SD card:**
```
time sudo dd bs=64K conv=sync,noerror if=/dev/sdc of=/dev/sdb
```

**Cloning a 32 GB SD card to a 16 GB SD card:**

1. Partition the 16 GB card with two partitions: FAT (lba) and EXT4.
2. Mount both cards and use rsync to copy data:
```
cd /media/b-ak
rsync -ah --info=progress2 --partial ./boot/ ./boot1/
sudo rsync -ah --info=progress2 --partial ./7f593562-9f68-4bb9-a7c9-2b70ad620873/ ./4d7d6d24-a608-46fb-9b39-a4f30ddb8902/
```

**Alternative: shrink the 32 GiB card first**

1. Shrink the 32 GiB card using a partition tool:
   ![](documents/images/32gb_to_16gb.png?raw=true)

2. Calculate the block count to fit within 16 GiB:
```
Total Size in MiB = 14.77 * 1024 + 4 + 63 = 15192
bs (in dd command) = 4M, so 15192/4 = 3798 blocks
```

3. Create the image:
```
sudo dd bs=4M of=dapm-91.img if=/dev/mmcblk0 count=3798
```

4. Copy the image to the smaller SD card.

#### 1.2.3 Setting Up a Git Repository

**Generate SSH keys** — [follow the GitHub SSH guide](https://help.github.com/categories/ssh/)

**Initialize a repository:**
```
git init
git remote add origin git@github.com:b-ak89/RPi.git
```

**Commit and push:**
```
git add README
git commit -m "first commit"
git push -u origin master
```

---

## 2. How does Pi boot

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

---

## 3. Building a Custom Kernel

### 3.1 Moving to a Newer Kernel Branch

List all references (branches, tags, etc.) in a local kernel repository:
```
git show-ref
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
```

Check out a specific commit:
```
git checkout 3f53e7886737a975e3fe76bc8ae6cc78f33c8cf8
```

Or switch to a named branch:
```
git checkout rpi-4.9.y
```

### 3.2 Cross-Compiling the Kernel

Export the toolchain path:
```
export PATH=$PATH:/data/raspberry-pi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin
```

**Raspberry Pi (original, BCM2835):**
```
cd linux
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- bcmrpi_defconfig
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-

mkdir ../modules
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- INSTALL_MOD_PATH=../modules/ modules
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- INSTALL_MOD_PATH=../modules/ modules_install

cd ../tools/mkimage/
./imagetool-uncompressed.py ../../linux/arch/arm/boot/zImage
mv kernel.img /media/b-ak/boot/

cd /data/raspberry-pi/modules/lib
tar -cvzf modules.tar.gz *
mv modules.tar.gz /media/b-ak/13d368bf-6dbf-4751-8ba1-88bed06bef77/tmp/
```

**Raspberry Pi 2/3 (BCM2836/BCM2837):**
```
cd linux
KERNEL=kernel7
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- bcm2709_defconfig
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- zImage modules dtbs -j4

sudo make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- INSTALL_MOD_PATH=/media/b-ak/13d368bf-6dbf-4751-8ba1-88bed06bef77/ modules_install

sudo scripts/mkknlimg arch/arm/boot/zImage /media/b-ak/boot/$KERNEL.img
sudo cp arch/arm/boot/dts/*.dtb /media/b-ak/boot/
sudo cp arch/arm/boot/dts/overlays/*.dtb* /media/b-ak/boot/

sudo umount /media/b-ak/*
```

Alternatively, use the [RPi 3 kernel builder script](https://gist.github.com/b-ak/ecf6640241e12bd31bcc7e433fa60d40).

---

## 4. Making our own minimalistic kernel

> See also: [`bare-bones/`](bare-bones/) for source files.

We need three input files:
1. `boot.s` - kernel entry point that sets up the processor environment
2. `kernel.c` - your actual kernel routines
3. `linker.ld` - for linking the above files
4. Booting the kernel

### 4.1 Booting the Operating System

The section `.text.boot` will be used in the linker script to place the `boot.S` as
the very first thing in our kernel image. The code initializes a minimum C environment,
which means having a stack and zeroing the BSS segment, before calling the `kernel_main` function.

Note that the code avoids using `r0-r2` so the remain valid for the `kernel_main` call.

Assemble `boot.S`:
```
arm-none-eabi-gcc -mcpu=arm1176jzf-s -fpic -ffreestanding -c boot.S -o boot.o
```

### 4.2 Kernel Implementation

The GPU bootloader passes arguments to the kernel via registers `r0–r2`, preserved by `boot.S`:

| Register | Value |
|----------|-------|
| `r0` | Device the RPi booted from (usually `0`) |
| `r1` | ARM Linux Machine Type — `3138 (0xc42)` for BCM2708 ([full list](http://www.arm.linux.org.uk/developer/machines/)) |
| `r2` | Address of the ATAGs |

Compile `kernel.c`:
```
arm-none-eabi-gcc -mcpu=arm1176jzf-s -fpic -ffreestanding -std=gnu99 -c kernel.c -o kernel.o -O2 -Wall -Wextra
```

### 4.3 Linking the Kernel

Create a `linker.ld` with the following structure:

- `ENTRY(_start)` — declares the entry point (defined in `boot.S`).
- `SECTIONS` — places code and data at the correct addresses and creates boundary symbols.
- The kernel is linked to start at `0x8000`.

Example text section:
```
__text_start = .;
.text : {
    KEEP(*(.text.boot))
    *(.text)
}
. = ALIGN(4096); /* align to page size */
__text_end = .;
```

- `.text.boot` is placed first to ensure `boot.S` is at the start of the kernel image.
- Sections are page-aligned (4096 bytes) for the RPi memory model.
- `__bss_start` and `__bss_end` symbols are used in `boot.S` to zero the BSS segment. They can also be referenced from C with `extern` declarations.
- `__start` and `__end` can be used at runtime to determine kernel size.

Link and convert to a binary image:
```
arm-none-eabi-gcc -T linker.ld -o myos.elf -ffreestanding -O2 -nostdlib boot.o kernel.o
arm-none-eabi-objcopy myos.elf -O binary myos.bin
```

> `arm-none-eabi-objcopy` copies and transforms binary files; here it strips the ELF container to produce a raw kernel image.

**References:**
- [OSDev Wiki — Raspberry Pi Bare Bones](http://wiki.osdev.org/Raspberry_Pi_Bare_Bones)
- [RPi Dev Blog](https://rpidev.wordpress.com/)

### 4.4 Deploying to the Pi

```
cp myos.bin /media/b-ak/boot/kernel.img
sync
umount /media/b-ak/*
```

Put the SD card into the Pi — it should boot your kernel.

---

## 5. Ubuntu Snappy Core on RPi 2

### 5.1 U-Boot Compilation

```
git clone git://git.denx.de/u-boot.git

make ARCH=arm CROSS_COMPILE=arm-bcm2708-linux-gnueabi- rpi_2_defconfig
make ARCH=arm CROSS_COMPILE=arm-bcm2708-linux-gnueabi-

echo 'kernel=u-boot.bin' > /media/b-ak/boot/config.txt
```

Reference: [RPi U-Boot — elinux.org](http://elinux.org/RPi_U-Boot)

### 5.2 Raspberry Pi 2 Bootstrap

1. Format a micro-SD card with a legacy MBR partition table (GPT is not supported by the RPi 2 ROM).
2. Create a FAT32 boot partition and copy the following files into it:
   `bcm2709-rpi-2-b.dtb`, `bootcode.bin`, `start.elf`, `fixup.dat`, `u-boot.bin`, `zImage`
3. Boot the RPi 2 and interrupt at the U-Boot prompt (press Enter on the serial console).

Run these U-Boot commands:
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

This should boot to the Linux kernel.

### 5.3 Booting Snappy Ubuntu

```
wget http://people.canonical.com/~platform/snappy/raspberrypi2/ubuntu-15.04-snappy-armhf-rpi2.img.xz
xzcat ubuntu-15.04-snappy-armhf-rpi2.img.xz | sudo dd of=/dev/sdc bs=32M
sync
```

#### 5.3.1 Recreating Snappy Ubuntu Files

[`bootcode.bin` and `start.elf` are SPL bits available under LICENCE.broadcom](https://github.com/raspberrypi/firmware/tree/master/boot)

The following files were extracted from the Snappy image:
- `zImage` → `boot/vmlinuz-3.19.1-2-generic-bcm2709`
- `bcm2836-rpi-2-b.dtb` → `lib/firmware/3.19.1-2-generic-bcm2709/device-tree/bcm2709-rpi-2-b.dtb`

`kernel7.img` is `u-boot.bin` built from [swarren/u-boot](https://github.com/swarren/u-boot) with Ubuntu's `arm-linux-gnueabihf` cross-compiler.

<details>
<summary>boot.env reference (U-Boot environment, binary format)</summary>

`mmc_boot` was changed from:
```
if mmc dev ${devnum}; then setenv devtype mmc; run scan_dev_for_boot_part; fi
```
to:
```
if mmc dev ${devnum}; then setenv devtype mmc;
  if run loadbootenv; then
    echo Loaded environment from ${bootenv};
    run importbootenv;
  fi;
  if test -n "$uenvcmd"; then
    echo Running uenvcmd ...;
    run uenvcmd;
  fi;
  run scan_dev_for_boot_part;
fi
```
Additional variables defined:
```
bootenv=uEnv.txt
loadbootenv=load ${devtype} ${devnum} ${loadaddr} ${bootenv}
importbootenv=echo Importing environment from mmc ...; env import -t -r $loadaddr $filesize
```
</details>

---

## 6. Wi-Fi and Remote Access

### 6.1 Connecting to Wi-Fi

1. Set up a hotspot on your phone or connect to a local router.
2. Edit the WPA supplicant config:
   ```
   sudo vi /etc/wpa_supplicant/wpa_supplicant.conf
   ```
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

### 6.2 VNC Server on RPi

1. Install TightVNC server:
   ```
   sudo apt-get install tightvncserver
   ```
2. Run `tightvncserver` and follow the prompts to set passwords (a view-only password is optional).

### 6.3 VNC Client/Viewer

1. Install **RealVNC Viewer** on your desktop/laptop.
2. Find the RPi's IP address:
   ```
   sudo arp-scan --localnet
   ```
   or
   ```
   sudo nmap -sP --disable-arp-ping 192.168.43.0/24
   ```
3. Connect to the RPi using RealVNC Viewer.

### 6.4 Autostart VNC Server at Boot

1. Copy the systemd service file to `/etc/systemd/system`:
   ```
   sudo cp documents/vnc/tightvncserver.service /etc/systemd/system/
   ```
2. Set ownership and permissions:
   ```
   sudo chown root:root /etc/systemd/system/tightvncserver.service
   sudo chmod 755 /etc/systemd/system/tightvncserver.service
   ```
3. Enable and verify the service:
   ```
   sudo systemctl enable tightvncserver.service
   ```
4. Reboot, then check that the service is running:
   ```
   systemctl list-units | grep vnc
     tightvncserver.service     loaded active running   TightVNC remote desktop server
   ```
5. If the service file is updated, reload and restart:
   ```
   sudo systemctl daemon-reload
   sudo systemctl restart tightvncserver.service
   ```
