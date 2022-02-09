# AXI DMA in simple mode, by polling

> Last update: Vivado/Vitis 2021.2

![ZYBO status](https://img.shields.io/badge/ZYBO-supported-darkgreen)
![ZCU102 status](https://img.shields.io/badge/ZCU102-unsupported-darkred)

## Vivado project creation

* Launch Vivado.
* *Quick start* -> *Create Project*.
  * *Next* in the splash screen.
  * Select a Project *name* and *location*, *Next*.
  * Select *RTL Proyect* and *Do not specify sources at this time*, *Next*.
  * Select your desired device/board (**Zybo**, **ZCU102**, other), *Next*.
  * *Finish* in the summary screen.

## Block design creation

* For a supported board, go to the *Tcl Console* and run `source <REPO_ROOT>/axidma/polling/polling_<BOARD>.tcl`.
* If your board is not supported, or if you want to create it from scratch, proceed with the instructions for the desired device family.

Instructions for `Zynq-7000` devices:
* *Create Block Design*, *OK* (default values).
* Click `+` (*Add IP*), search `zynq` and select `ZYNQ7 Processing System`.
* Click *Run Block Automation*, check *Apply Board Preset*, *OK*.
* Double click on *processing_system7_0*.
  * *PS-PL Configuration*:
    * *AXI Non Secure Enablement* -> *GP Master AXI Interface* -> *M_AXI_GP0 interface* should be checked.
    * Check *HP Slave AXI Interface* -> *S_AXI_HP0 interface*.
  * *Peripheral I/O Pins*:
    * Verify that at least one UART is configured (which is normally true if you specified a board).
    * Optionally, uncheck other interfaces.
  * *OK* to finish, *OK* after validation.
* Click `+` (*Add IP*), search `axi dma` and select `AXI Direct Memory Access`.
* Double click on *axi_dma_0*.
  * Uncheck *Enable Scatter Gather Engine*.
  * Increase *Width of Buffer Length Register* to 26 bits.
  * *OK*.
* Click `+` (*Add IP*), search `fifo` and select `AXI4-Stream Data FIFO`.
* Perform the following manual connections:
  * *M_AXIS_MM2S* output (DMA) to *S_AXIS* input (FIFO).
  * *M_AXIS* output (FIFO) to *S_AXIS_S2MM* input (DMA).
* Click *Run Connection Automation*, select *All Automation* and click *OK*.
* Click *Run Connection Automation*, select *All Automation* and click *OK*.
* Click *Validate design* (F6), *OK*.
* **Optional:** click on *Regenerate Layout*.

Instructions for `Zynq-UltraScale+` devices:
 * Coming soon...

![PS-PL configuration](images/ps-pl-config.png)
*Zynq-7000 PS-PL configuration*

![AXI-DMA configuration](images/axi-dma-config.png)
*Zynq-7000 AXI-DMA configuration*

![Zynq-7000](images/block_design.png)
*Zynq-7000 block design*

## Bitstream generation, export and launch Vitis

* Right click on *Sources* -> *Design Sources* -> *design_1*
* Select *Create HDL wrapper*, *Let Vivado manage wrapper and auto-update*, *OK*.
* Click on *Generate Bitstream*, *Yes* (launch synthesis and implementation), *OK*.
* Wait for *Bitstream Generation successfully completed*, and *Cancel* (don't open implemented design).
* *File* -> *Export* -> *Export Hardware*. *Next*.
* Select *include bitstream*. *Next*.
* Select where to export and *Next*, then *Finish*.
* *Tools* -> *Launch Vitis IDE*.

## Vitis project creation

* *Select a directory as workspace*, *Launch*.
* *File* -> *New* -> *Application Project*.
* *Next* in the splash screen.
* Got to *Create a new platform hardware (XSA)*, *Browse*.
* Find the previously exported `design_1_wrapper.xsa`, select it and *Open*, *Next*.
* Specify an *Application project name* (`polling` for example), *Next*.
* *Next* on the Domain screen.
* Select the *Empty Application (C)* template, *Finish*.
* Right click on *<YOUR_APP_NAME>_system* -> *<YOUR_APP_NAME>* -> *src* and select *Import sources*.
* Browse *<REPO_ROOT>/axidma/polling*, *Open*.
* Check `polling.c`.
* **Optional:** click *Advanced*, check *create links on workspace*.
* *Finish*.

## Build and run

* Right click on *<YOUR_APP_NAME>_system* -> *<YOUR_APP_NAME>*, select *Build project*.
* Connect and energize your board (configured for JTAG programming).
* Configure a serial terminal at 115200 (ex: `screen /dev/ttyUSB1 115200`).
* Right click on *<YOUR_APP_NAME>_system* -> *<YOUR_APP_NAME>*, select *Run As* -> *Launch Hardware*.
* Verify the output of the serial terminal:
```C
* DMA Simple Mode by Polling Example
* Initializing DMA
INFO: Device configured in Simple Mode.
* Playing with DMA
Try 1
Try 1 passed
Try 2
Try 2 passed
Try 3
Try 3 passed
Try 4
Try 4 passed
Try 5
Try 5 passed
Try 6
Try 6 passed
Try 7
Try 7 passed
Try 8
Try 8 passed
Try 9
Try 9 passed
Try 10
Try 10 passed
* Example Passed
```
