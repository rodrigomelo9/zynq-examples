/*
* AXI DMA in Simple Polling Mode
*
* Copyright (c) 2018-2022, Rodrigo A. Melo
* Licensed under ISC License
* SPDX-License-Identifier: ISC
*
*/

#include "xaxidma.h"

// "Width of buffer length register" in AXI DMA
#define BITS           26 // 2^26 -> 64M

#define BYTES          ((1 << BITS) - 1)
#define SAMPLES        BYTES / sizeof(data_t)

#ifdef PLATFORM_ZYNQ
#define DDR_BASE_ADDR  XPAR_PS7_DDR_0_S_AXI_BASEADDR
#else
#define DDR_BASE_ADDR  XPAR_AXI_DMA_0_BASEADDR
#endif

#define TX_BASE_ADDR   DDR_BASE_ADDR + 0x01000000
#define RX_BASE_ADDR   TX_BASE_ADDR + BYTES

//Select one or add your own size
#define data_t         u32 // u8 u16 u32 u64

XAxiDma dma;

int dma_init(int device_id) {
  XAxiDma_Config *cfg;
  int status;
  cfg = XAxiDma_LookupConfig(device_id);
  if (!cfg) {
    xil_printf("No configuration found for AXI DMA with device ID %d\r\n", device_id);
    return XST_FAILURE;
  }
  status = XAxiDma_CfgInitialize(&dma, cfg);
  if (status != XST_SUCCESS) {
    xil_printf("ERROR: DMA configuration failed\r\n");
    return XST_FAILURE;
  }
  if (! XAxiDma_HasSg(&dma)) {
    xil_printf("INFO: Device configured in Simple Mode.\r\n");
  } else {
    xil_printf("ERROR: Device configured in Scatter Gather Mode.\r\n");
    return XST_FAILURE;
  }
  return XST_SUCCESS;
}

int dma_example() {
  int i, status, try;
  data_t *tx_buf, *rx_buf;

  tx_buf = (data_t *)TX_BASE_ADDR;
  rx_buf = (data_t *)RX_BASE_ADDR;

  for (try = 1; try <= 10; try++) {
    xil_printf("Try %d\r\n", try);
    for (i = 0; i < SAMPLES; i++)
      tx_buf[i] = i+try;

    Xil_DCacheFlushRange((UINTPTR)tx_buf, BYTES);
    Xil_DCacheFlushRange((UINTPTR)rx_buf, BYTES);

    status = XAxiDma_SimpleTransfer(&dma,(UINTPTR)tx_buf, BYTES, XAXIDMA_DMA_TO_DEVICE);
    if (status != XST_SUCCESS) {
      xil_printf("DMA TX SimpleTransfer failed\r\n");
      return XST_FAILURE;
    }
    status = XAxiDma_SimpleTransfer(&dma,(UINTPTR)rx_buf, BYTES, XAXIDMA_DEVICE_TO_DMA);
    if (status != XST_SUCCESS) {
      xil_printf("DMA RX SimpleTransfer failed\r\n");
      return XST_FAILURE;
    }
    while ((XAxiDma_Busy(&dma,XAXIDMA_DEVICE_TO_DMA)) || (XAxiDma_Busy(&dma,XAXIDMA_DMA_TO_DEVICE)));

    for (i = 0; i < SAMPLES; i++) {
      if (rx_buf[i] != tx_buf[i]) {
        xil_printf("ERROR: mismatch (data %d) between TX(%d) and RX(%d)\r\n", i+1, tx_buf[i], rx_buf[i]);
        return XST_FAILURE;
      }
    }
    xil_printf("Try %d passed\r\n", try);
  }
  return XST_SUCCESS;
}

int main() {
  int status;
  xil_printf("* DMA Simple Mode by Polling Example\r\n");
  xil_printf("* Initializing DMA\r\n");
  status = dma_init(XPAR_AXIDMA_0_DEVICE_ID);
  if (status != XST_SUCCESS) {
    xil_printf("DMA initialization failed\r\n");
    return XST_FAILURE;
   }
  xil_printf("* Playing with DMA\r\n");
  status = dma_example();
  if (status != XST_SUCCESS) {
    xil_printf("* Example Failed\r\n");
    return XST_FAILURE;
  }
  xil_printf("* Example Passed\r\n");
  return XST_SUCCESS;
}
