# Boot from a QSPI memory or SD card

> Last update: Vivado/Vitis 2021.2

This example assumes that you have a valid project, capable of being built as a bitstream, and the corresponding standalone source code for the processor.

## Export Hardware Platform and launch Vitis

* *Create Block Design* based on a *Zynq Processing System*
  * The corresponding QSPI or SD controller must be enabled and well configured
* *Generate Bitstream*
* Go to *File* -> *Export* -> *Export Hardware*
  * Click on *Next*
  * Select *Include bitstream*, click on *Next*
  * Select a *XSA file name* (for this example I recommend you to use the default), an *Export to* location and click on *Finish*
* Go to *Tools* -> *Launch Vitis IDE*

## Create the FSBL app

To boot from a QSPI memory or SD card, a First Stage Boot loader is needed.

* Select a workspace
* Go to *File* -> *New* -> *Application Project*
* Click *Next* in the *Create a new Application Project* screen
* Select the tab *Create a new platform from hardware (XSA)*, *Browse*, select the platform that you generated in the previous section (`design_1_wrapper.xsa` by default) and click on *Next*
* Select an *Application project name* (`FSBL` in this example) and cloick on *Next*
* Click *Next* in the *Domain* screen
* Select the *Zynq FSBL* template (commonly at the bottom of the list) and click on *Finish*
* Right click over `FSBL_system` and select *Build Project*

## Create your app

* Go to *File* -> *New* -> *Application Project*
* Click *Next* in the *Create a new Application Project* screen
* Under the tab *Select a platform repository*, select your previous added platform (`design_1_wrapper [custom]`) and click on *Next*
* Select an *Application project name* (`myapp` in this example) and click on *Next*
* Click *Next* in the *Domain* screen
* Select the *Empty Application (c)* template and click on *Finish*
* Right click over `myapp_system` -> `myapp` -> `src` and select *Import Sources*
  * *Browse*, select and include the source code of your application
* Right click over `myapp_system` and select *Build Project*

## Create Boot Image

* Left click over `myapp_system` and go to *Xilinx* -> *Create Boot Image*
* *Architecture* should be `Zynq` or `Zynq MP` depending on the device that you specified in your Vivado project
* *Output Format* must be `BIN` in case of QSPI or SD card images
* Verify that there are three *Boot image partitions* listed:
  * the bootloader (`fsbl.elf`)
  * your bitstream (`design_1_wrapper.bit`)
  * your app (`myapp.elf`)
* Click on *Create Image*

> **NOTE:** sometimes (commonly) you will receive a warning about an empty BIF file and the *Boot image partitions* list will be empty.
> If this happens click on *Cancel* and return to *Xilinx* -> *Create Boot Image*

## Boot from a QSPI memory

* With the board OFF, select the needed jumpers to boot from the QSPI (it is board dependant, check the corresponding user guide)
  * **ZYBO:** JP5 between the **QSPI** pins
  * **ZCU102:** SW6[4:1]=ON,ON,OFF,ON
* Power ON the board
* In Vitis, left click over `myapp_system` and go to *Xilinx* -> *Program Flash*
* Click on *Program*
* Power OFF and then ON

## Boot from a SD card

* Save the generated image (`<WORKSPACE>/myapp_system/_die/bootimage/BOOT.bin`) in a SD card with its first partition formated as FAT32
* With the board OFF, select the needed jumpers to boot from the SD card (it is board dependant, check the corresponding user guide)
  * **ZYBO:** JP5 between the **SD** pins
  * **ZCU102:** SW6[4:1]=OFF,OFF,OFF,ON
* Insert the SD card
* Power ON the board

> **NOTE:** the name of the image must be `BOOT.bin` in the SD card, or it will be not found.
