# AXI DMA

AXI DMA is an IP block from Xilinx ([PG021](https://www.xilinx.com/support/documentation/ip_documentation/axi_dma/v7_1/pg021_axi_dma.pdf)), that provides high-bandwidth Direct Memory Access between memory and AXI4-Stream target peripherals.
It can be used in Direct Register (Simple) or Scatter-Gather mode.
The second one provides higher performance, at expense of more resources and more complex functionality, based on descriptors.

Examples:
* [polling](polling): AXI DMA in simple mode, by polling.
* [interrupts](interrupts): AXI DMA in simple mode, by interrupts.
