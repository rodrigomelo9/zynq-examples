# Zynq UltraScale+ Overview

> See the [Zynq UltraScale+ Device Technical Reference Manual (UG1085)](https://www.xilinx.com/support/documentation/user_guides/ug1085-zynq-ultrascale-trm.pdf)) for details.

> I copied/adapted content from a great public course from [CERN](https://ohwr.org/project/soc-course/wikis/home), basically from [here](https://ohwr.org/project/soc-course/wikis/MPSoC-Architecture-Overview) and [here](https://ohwr.org/project/soc-course/wikis/MPSoC-Address-Map).

![Zynq UltraScale+ block diagram](images/zynq-usp.png)
*Zynq UltraScale+ block diagram*

Zynq UltraScale+ MPSoC is the Xilinx second-generation Zynq platform, combining a powerful processing system (PS) and user-programmable logic (PL) into the same device, built on a 16 nm process technology.
The processing system features a quad or dual-core Cortex A53 and a dual-core Cortex-R5F real-time processor.

## Processing Units

In the MPSoC, there are two main blocks with different specialized processing units:

Processing System (PS):
* APU: Quad or Dual core Cortex-A53 (r0p4-50rel0) application processing unit. ARM v8 64-bit architecture. It supports:
  * Asymmetric Multi Processing (AMP): each core running different applications (limited support due to shared HW infrastructure).
  * Symmetric Multi Processing (SMP): all of the cores running the same software (e.g. Linux operating system).
* RPU: Dual core Cortex-R5F (r1p3) real-time processing unit. ARM v7 32-bit architecture.
  * Split Mode: each core running different applications as totally independent CPUs.
  * Lockstep Mode: both cores running the same application for higher security.
* PMU: Platform management unit based on triple module redundant Microblaze processor.
* CSU: Configuration Security Unit based on triple module redundant Microblaze processor.
* GPU: MALI-400 graphic processing unit (available in EG and EV MPSoC families).

Programmable Logic (PL):
* VCU: Video control unit with hardware codecs and compression (available in EV MPSoC family).
* RF: Radio frequency unit with up to 16 channels RF-ADCs and RF-DACs (available in RFSoC family).
* CLBs (based on LUT6), BRAM, UltraRAM and DSPs.
* Configurable SelectIO technology.
  * High density (HD) I/Os.
  * High performance (HP) I/Os.
* Multi-gigabit transceivers.
  * GTY (up to 32.75 Gb/s).
  * GTH (up to 16.375 Gb/s).
  * **Note:** there are also PS-GTR (up to 6 Gb/s).
* PCI v3.1
* 100 Gb/s Ethernet.
* 150 Gb/s Interlaken v1.2.

### Power Management

The power management in the MPSoC is handled by the Platform Management Unit (PMU).

There are four different power domains:
* Low Power Domain (LPD): RPU, PMU, CSU, LPD_DMA, and LPD peripherals
* Full Power Domain (FPD): APU, FPD_DMA, and FPD peripherals
* PL Power Domain (PLPD): Programmable logic
* Battery Power Domain (BPD): Real Time clock and Battery-backed RAM (BBRAM) for secure configuration key.

Each power domain can be individually isolated. The platform management unit (PMU) on the LPD facilitates the isolation of each of the power domains. Additionally, the isolation can be turned on automatically when one of the power supplies of the corresponding power domain is accidentally powered down. Since each power domain can be individually isolated, functional isolation (an important aspect of safety and security applications) is possible.

* **Note:** because the PS and PL resides in two different power domains, the Processing System can be used as a full-featured SoC without powering up the Programmable Logic.

The MPSoC supports three different operational power modes:
* Battery Powered Mode: maintain critical information over the time when MPSoC is powered-off.
* Low Power Mode: only the devices in the LPD are powered up.
* Full Power Mode: all the power domains are activated, including Programmable Logic.

### Memory Interfaces

### I/O peripherals

Low Power Domain (LPD):
* General Purpose I/O (GPIO)
* Quad SPI Flash Memory (QSPI)
* NAND ONFI 3.1 Controller.
* 4x Gigabit Ethernet MAC
* 2x USB3
* 2x Secure Digital IO (SDIO) for SD / eMMC.
* 2x Serial Peripheral Interface (SPI).
* 2x CAN
* 2x I2C
* 2x UART
* System Monitor

Full Power Domain (FPD):
* PCIe Gen2 x1/x2/x4
* 2x Serial Advanced Technology Attachment (SATA)
* 2x Display Port 1.2 (DP)

Programmable Logic Power Domain (PLPD):
* PCIe Gen3 x16, Gen4 x8.
* 100G Ethernet.
* 150G Interlaken v1.2.
* GTH and GTY Transceivers.

The peripherals' I/O interfaces can be router to the Multiplexed I/O (MIO) and the Extended Multiplexed I/O (EMIO).
* There are up to 78 MIO ports divided in three banks available from the processing system and the MIO itself resides in the Low Power Domain.
* As the number of MIO ports is limited, many of the available peripherals can be routed to the programmable logic through the Extended MIO (EMIO).

### PS-PL interfaces

## AXI interfaces

PS master, PL slave:
* 3 x HPM: PS General Purpose Master interfaces (32, 64, and 128 bits width, default 128)
  * 2 x HPM FPD: From full power domain
  * 1 x HPM LPD: From low power domain (low latency from peripherals and RPU)

PL master, PS slave:
* 7 x PL General Purpose Master interfaces (32, 64, and 128 bits width, default 128):
  * 2 x S-AXI HPC FPD: access to full power domain
  * 4 x S-AXI HP FPD: access to full power domain and DDR controller
  * 1 x AXI LPD: access to low power domain
* 1 x S-AXI ACE: PL Master AXI Coherency Extension (ACE) interface for coherent I/O to A53 L1 and L2 cache (128 bits width)
* 1 x S-AXI ACP-FPD: PL Master ACP interface for L2 cache allocation from PL masters, limited to 64-byte cache line transfers (128 bits width).

## Address Map
