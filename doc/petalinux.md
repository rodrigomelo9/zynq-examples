# Petalinux

## Resources

* [PetaLinux Tools Documentation: Reference Guide (UG1144)](https://docs.xilinx.com/r/en-US/ug1144-petalinux-tools-reference-guide)

## Installation

* Run the script provided [here](https://support.xilinx.com/s/article/73296?language=en_US) (`sudo ./plnx-env-setup.sh`) to install dependencies.
* Download the Petalinux installer and `chmod +x petalinux*.run`.
* Run `./petalinux-<VERSION>-installer.run -d <LOCATION>` (you should have access rights on the specified `<LOCATION>`).
* PetaLinux tools require `bash` as your host `/bin/sh`, so run `sudo dpkg-reconfigure dash`, press tab and then select no.
* Donwload the `bsp` for your board.

## Project creation

* From a BSP: `petalinux-create -t project -s <path-to-bsp> --name <PROJECT_NAME>`
* From a template: `petalinux-create -t project --template <PLATFORM> --name <PROJECT_NAME>`

> Where `<PLATFORM>` can be `versal`, `zynqMP`, `zynq` or `microblaze`

## Configuring, Building and Packaging

```
cd <PROJECT_NAME>
petalinux-config --get-hw-description <PATH-TO-XSA-FILE>
petalinux-build
petalinux-package --boot --u-boot
```

For further configurations, other possible `petalinux-config` are:
* Configure system-level options `petalinux-config`
* Configure U-Boot `petalinux-config -c u-boot`
* Configure the Linux kernel `petalinux-config -c kernel`
* Configure the root filesystem `petalinux-config -c rootfs`

## Custom App

```
cd <PROJECT_NAME>
petalinux-create -t apps --template <TYPE> --name <APP_NAME> --enable
```

> Where `<TYPE>` is `c` by default

> Modify/replace `project-spec/meta-user/recipes-apps/<APP_NAME>/<APP_NAME>.c`

Then, build all (`petalinux-build`) or only your app into an existing system image:
```
petalinux-build -c rootfs
petalinux-build -x package
```

#  Booting (SD card)

* Partitioning and Formatting an SD Card

* Copy `BOOT.BIN`, `image.ub` and `boot.scr` from `<PROJECT_NAME>/images/linux` or `<PROJECT_NAME>/pre-built/linux/images` into the boot directory of the first partition (FAT32)
• Extract `rootfs.tar.gz` into the ext4 partition
* Plug the SD card into the board
* Set the boot mode of the board to SD boot
* Connect the serial port and launch a serial console (baud rate 115200)
* Power on the board

You should see a boot message on the serial console.
