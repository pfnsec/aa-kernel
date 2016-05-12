#ifndef DWC2_USB_H
#define DWC2_USB_H
#include <stdint.h>
#include "peripherals.h"

#define DWC2_FIFO_SIZE 1024

#define DWC2_BASE (PERIPH_BASE + 0x980000)

#define DWC2_OTG_CTL         *(uint32_t *)(DWC2_BASE)
#define DWC2_AHB_CFG         *(uint32_t *)(DWC2_BASE + 0x008)
#define DWC2_USB_CFG         *(uint32_t *)(DWC2_BASE + 0x00C)
#define DWC2_CORE_RESET      *(uint32_t *)(DWC2_BASE + 0x010)
#define DWC2_CORE_MASK       *(uint32_t *)(DWC2_BASE + 0x018)
#define DWC2_RX_FIFO_SIZE    *(uint32_t *)(DWC2_BASE + 0x024)
#define DWC2_NP_TX_FIFO_SIZE *(uint32_t *)(DWC2_BASE + 0x028)
#define DWC2_P_TX_FIFO_SIZE  *(uint32_t *)(DWC2_BASE + 0x100)

#define DWC2_HOST_CFG        *(uint32_t *)(DWC2_BASE + 0x400)
#define DWC2_HOST_PORT_CFG   *(uint32_t *)(DWC2_BASE + 0x440)


#define DWC2_AHB_INT_ENABLE     1

#define DWC2_USB_EXT_OC_CMP    (1 << 21)
#define DWC2_USB_EXT_VBUS_DRV  (1 << 20)
#define DWC2_USB_CLK_SUSM      (1 << 19)
#define DWC2_USB_FSLS          (1 << 17)
#define DWC2_USB_HNP_CAP       (1 << 9)
#define DWC2_USB_SRP_CAP       (1 << 8)
#define DWC2_PHY_SEL           (1 << 6)
#define DWC2_UTMI_ULPI         (1 << 4)
#define DWC2_PHY_IF_SIZE       (1 << 3)

#define DWC2_RESET_SOFT         1
#define DWC2_AHB_IDLE          (1 << 31)
#define DWC2_AHB_DMA_EN        (1 << 5)

#define DWC2_FSLS_SUPP         (1 << 2)
#define DWC2_FSLS_CLK_48        1

#define DWC2_CHAN_XF_CTL       (0 << 18)
#define DWC2_CHAN_XF_ISOC      (1 << 18)
#define DWC2_CHAN_XF_BULK      (2 << 18)
#define DWC2_CHAN_XF_IRQ       (3 << 18)
#define DWC2_CHAN_IN           (1 << 15)
#define DWC2_CHAN_EP(n)        (n << 11)



#endif
