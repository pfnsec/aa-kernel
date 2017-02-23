#ifndef SLCR_H
#define SLCR_H
#include <stdint.h>
                                              /*  Reset      Description  */
#define SLCR_SCL                     0x00000000 //0x00000000 Secure Configuration Lock
#define SLCR_LOCK                    0x00000004 //0x00000000 SLCR Write Protection Lock
#define SLCR_UNLOCK                  0x00000008 //0x00000000 SLCR Write Protection Unlock
#define SLCR_LOCK_STATUS             0x0000000C //0x00000001 SLCR Write Protection Status
#define SLCR_ARM_PLL_CTRL            0x00000100 //0x0001A008 ARM PLL Control
#define SLCR_DDR_PLL_CTRL            0x00000104 //0x0001A008 DDR PLL Control
#define SLCR_IO_PLL_CTRL             0x00000108 //0x0001A008 IO PLL Control
#define SLCR_PLL_STATUS              0x0000010C //0x0000003F PLL Status
#define SLCR_ARM_PLL_CFG             0x00000110 //0x00177EA0 ARM PLL Configuration
#define SLCR_DDR_PLL_CFG             0x00000114 //0x00177EA0 DDR PLL Configuration
#define SLCR_IO_PLL_CFG              0x00000118 //0x00177EA0 IO PLL Configuration
#define SLCR_ARM_CLK_CTRL            0x00000120 //0x1F000400 CPU Clock Control
#define SLCR_DDR_CLK_CTRL            0x00000124 //0x18400003 DDR Clock Control
#define SLCR_DCI_CLK_CTRL            0x00000128 //0x01E03201 DCI clock control
#define SLCR_APER_CLK_CTRL           0x0000012C //0x01FFCCCD AMBA Peripheral Clock Control
#define SLCR_USB0_CLK_CTRL           0x00000130 //0x00101941 USB 0 ULPI Clock Control
#define SLCR_USB1_CLK_CTRL           0x00000134 //0x00101941 USB 1 ULPI Clock Control
#define SLCR_GEM0_RCLK_CTRL          0x00000138 //0x00000001 GigE 0 Rx Clock and Rx Signals Select
#define SLCR_GEM1_RCLK_CTRL          0x0000013C //0x00000001 GigE 1 Rx Clock and Rx Signals Select
#define SLCR_GEM0_CLK_CTRL           0x00000140 //0x00003C01 GigE 0 Ref Clock Control
#define SLCR_GEM1_CLK_CTRL           0x00000144 //0x00003C01 GigE 1 Ref Clock Control
#define SLCR_SMC_CLK_CTRL            0x00000148 //0x00003C21 SMC Ref Clock Control
#define SLCR_LQSPI_CLK_CTRL          0x0000014C //0x00002821 Quad SPI Ref Clock Control
#define SLCR_SDIO_CLK_CTRL           0x00000150 //0x00001E03 SDIO Ref Clock Control
#define SLCR_UART_CLK_CTRL           0x00000154 //0x00003F03 UART Ref Clock Control
#define SLCR_SPI_CLK_CTRL            0x00000158 //0x00003F03 SPI Ref Clock Control
#define SLCR_CAN_CLK_CTRL            0x0000015C //0x00501903 CAN Ref Clock Control
#define SLCR_CAN_MIOCLK_CTRL         0x00000160 //0x00000000 CAN MIO Clock Control
#define SLCR_DBG_CLK_CTRL            0x00000164 //0x00000F03 SoC Debug Clock Control
#define SLCR_PCAP_CLK_CTRL           0x00000168 //0x00000F01 PCAP Clock Control
#define SLCR_TOPSW_CLK_CTRL          0x0000016C //0x00000000 Central Interconnect Clock Control
#define SLCR_FPGA0_CLK_CTRL          0x00000170 //0x00101800 PL Clock 0 Output control
#define SLCR_FPGA0_THR_CTRL          0x00000174 //0x00000000 PL Clock 0 Throttle control
#define SLCR_FPGA0_THR_CNT           0x00000178 //0x00000000 PL Clock 0 Throttle Count control
#define SLCR_FPGA0_THR_STA           0x0000017C //0x00010000 PL Clock 0 Throttle Status read
#define SLCR_FPGA1_CLK_CTRL          0x00000180 //0x00101800 PL Clock 1 Output control
#define SLCR_FPGA1_THR_CTRL          0x00000184 //0x00000000 PL Clock 1 Throttle control
#define SLCR_FPGA1_THR_CNT           0x00000188 //0x00000000 PL Clock 1 Throttle Count
#define SLCR_FPGA1_THR_STA           0x0000018C //0x00010000 PL Clock 1 Throttle Status control
#define SLCR_FPGA2_CLK_CTRL          0x00000190 //0x00101800 PL Clock 2 output control
#define SLCR_FPGA2_THR_CTRL          0x00000194 //0x00000000 PL Clock 2 Throttle Control
#define SLCR_FPGA2_THR_CNT           0x00000198 //0x00000000 PL Clock 2 Throttle Count
#define SLCR_FPGA2_THR_STA           0x0000019C //0x00010000 PL Clock 2 Throttle Status
#define SLCR_FPGA3_CLK_CTRL          0x000001A0 //0x00101800 PL Clock 3 output control
#define SLCR_FPGA3_THR_CTRL          0x000001A4 //0x00000000 PL Clock 3 Throttle Control
#define SLCR_FPGA3_THR_CNT           0x000001A8 //0x00000000 PL Clock 3 Throttle Count
#define SLCR_FPGA3_THR_STA           0x000001AC //0x00010000 PL Clock 3 Throttle Status
#define SLCR_CLK_621_TRUE            0x000001C4 //0x00000001 CPU Clock Ratio Mode select
#define SLCR_PSS_RST_CTRL            0x00000200 //0x00000000 PS Software Reset Control
#define SLCR_DDR_RST_CTRL            0x00000204 //0x00000000 DDR Software Reset Control
#define SLCR_TOPSW_RST_CTRL          0x00000208 //0x00000000 Central Interconnect Reset Control
#define SLCR_DMAC_RST_CTRL           0x0000020C //0x00000000 DMAC Software Reset Control
#define SLCR_USB_RST_CTRL            0x00000210 //0x00000000 USB Software Reset Control
#define SLCR_GEM_RST_CTRL            0x00000214 //0x00000000 Gigabit Ethernet SW Reset Control
#define SLCR_SDIO_RST_CTRL           0x00000218 //0x00000000 SDIO Software Reset Control
#define SLCR_SPI_RST_CTRL            0x0000021C //0x00000000 SPI Software Reset Control
#define SLCR_CAN_RST_CTRL            0x00000220 //0x00000000 CAN Software Reset Control
#define SLCR_I2C_RST_CTRL            0x00000224 //0x00000000 I2C Software Reset Control
#define SLCR_UART_RST_CTRL           0x00000228 //0x00000000 UART Software Reset Control
#define SLCR_GPIO_RST_CTRL           0x0000022C //0x00000000 GPIO Software Reset Control
#define SLCR_LQSPI_RST_CTRL          0x00000230 //0x00000000 Quad SPI Software Reset Control
#define SLCR_SMC_RST_CTRL            0x00000234 //0x00000000 SMC Software Reset Control
#define SLCR_OCM_RST_CTRL            0x00000238 //0x00000000 OCM Software Reset Control
#define SLCR_FPGA_RST_CTRL           0x00000240 //0x01F33F0F FPGA Software Reset Control
#define SLCR_A9_CPU_RST_CTRL         0x00000244 //0x00000000 CPU Reset and Clock control
#define SLCR_RS_AWDT_CTRL            0x0000024C //0x00000000 Watchdog Timer Reset Control
#define SLCR_REBOOT_STATUS           0x00000258 //0x00400000 Reboot Status, persistent
#define SLCR_BOOT_MODE               0x0000025C //x Boot Mode Strapping Pins
#define SLCR_APU_CTRL                0x00000300 //0x00000000 APU Control
#define SLCR_WDT_CLK_SEL             0x00000304 //0x00000000 SWDT clock source select
#define SLCR_TZ_DMA_NS               0x00000440 //0x00000000 DMAC TrustZone Config
#define SLCR_TZ_DMA_IRQ_NS           0x00000444 //0x00000000 DMAC TrustZone Config for Interrupts
#define SLCR_TZ_DMA_PERIPH_NS        0x00000448 //0x00000000 DMAC TrustZone Config for Peripherals
#define SLCR_PSS_IDCODE              0x00000530 //x PS IDCODE
#define SLCR_DDR_URGENT              0x00000600 //0x00000000 DDR Urgent Control
#define SLCR_DDR_CAL_START           0x0000060C //0x00000000 DDR Calibration Start Triggers
#define SLCR_DDR_REF_START           0x00000614 //0x00000000 DDR Refresh Start Triggers
#define SLCR_DDR_CMD_STA             0x00000618 //0x00000000 DDR Command Store Status
#define SLCR_DDR_URGENT_SEL          0x0000061C //0x00000000 DDR Urgent Select
#define SLCR_DDR_DFI_STATUS          0x00000620 //0x00000000 DDR DFI status
#define SLCR_MIO_PIN_00              0x00000700 //0x00001601 MIO Pin 0 Control
#define SLCR_MIO_PIN_01              0x00000704 //0x00001601 MIO Pin 1 Control
#define SLCR_MIO_PIN_02              0x00000708 //0x00000601 MIO Pin 2 Control
#define SLCR_MIO_PIN_03              0x0000070C //0x00000601 MIO Pin 3 Control
#define SLCR_MIO_PIN_04              0x00000710 //0x00000601 MIO Pin 4 Control
#define SLCR_MIO_PIN_05              0x00000714 //0x00000601 MIO Pin 5 Control
#define SLCR_MIO_PIN_06              0x00000718 //0x00000601 MIO Pin 6 Control
#define SLCR_MIO_PIN_07              0x0000071C //0x00000601 MIO Pin 7 Control
#define SLCR_MIO_PIN_08              0x00000720 //0x00000601 MIO Pin 8 Control
#define SLCR_MIO_PIN_09              0x00000724 //0x00001601 MIO Pin 9 Control
#define SLCR_MIO_PIN_10              0x00000728 //0x00001601 MIO Pin 10 Control
#define SLCR_MIO_PIN_11              0x0000072C //0x00001601 MIO Pin 11 Control
#define SLCR_MIO_PIN_12              0x00000730 //0x00001601 MIO Pin 12 Control
#define SLCR_MIO_PIN_13              0x00000734 //0x00001601 MIO Pin 13 Control
#define SLCR_MIO_PIN_14              0x00000738 //0x00001601 MIO Pin 14 Control
#define SLCR_MIO_PIN_15              0x0000073C //0x00001601 MIO Pin 15 Control
#define SLCR_MIO_PIN_16              0x00000740 //0x00001601 MIO Pin 16 Control
#define SLCR_MIO_PIN_17              0x00000744 //0x00001601 MIO Pin 17 Control
#define SLCR_MIO_PIN_18              0x00000748 //0x00001601 MIO Pin 18 Control
#define SLCR_MIO_PIN_19              0x0000074C //0x00001601 MIO Pin 19 Control
#define SLCR_MIO_PIN_20              0x00000750 //0x00001601 MIO Pin 20 Control
#define SLCR_MIO_PIN_21              0x00000754 //0x00001601 MIO Pin 21 Control
#define SLCR_MIO_PIN_22              0x00000758 //0x00001601 MIO Pin 22 Control
#define SLCR_MIO_PIN_23              0x0000075C //0x00001601 MIO Pin 23 Control
#define SLCR_MIO_PIN_24              0x00000760 //0x00001601 MIO Pin 24 Control
#define SLCR_MIO_PIN_25              0x00000764 //0x00001601 MIO Pin 25 Control
#define SLCR_MIO_PIN_26              0x00000768 //0x00001601 MIO Pin 26 Control
#define SLCR_MIO_PIN_27              0x0000076C //0x00001601 MIO Pin 27 Control
#define SLCR_MIO_PIN_28              0x00000770 //0x00001601 MIO Pin 28 Control
#define SLCR_MIO_PIN_29              0x00000774 //0x00001601 MIO Pin 29 Control
#define SLCR_MIO_PIN_30              0x00000778 //0x00001601 MIO Pin 30 Control
#define SLCR_MIO_PIN_31              0x0000077C //0x00001601 MIO Pin 31 Control
#define SLCR_MIO_PIN_32              0x00000780 //0x00001601 MIO Pin 32 Control
#define SLCR_MIO_PIN_33              0x00000784 //0x00001601 MIO Pin 33 Control
#define SLCR_MIO_PIN_34              0x00000788 //0x00001601 MIO Pin 34 Control
#define SLCR_MIO_PIN_35              0x0000078C //0x00001601 MIO Pin 35 Control
#define SLCR_MIO_PIN_36              0x00000790 //0x00001601 MIO Pin 36 Control
#define SLCR_MIO_PIN_37              0x00000794 //0x00001601 MIO Pin 37 Control
#define SLCR_MIO_PIN_38              0x00000798 //0x00001601 MIO Pin 38 Control
#define SLCR_MIO_PIN_39              0x0000079C //0x00001601 MIO Pin 39 Control
#define SLCR_MIO_PIN_40              0x000007A0 //0x00001601 MIO Pin 40 Control
#define SLCR_MIO_PIN_41              0x000007A4 //0x00001601 MIO Pin 41 Control
#define SLCR_MIO_PIN_42              0x000007A8 //0x00001601 MIO Pin 42 Control
#define SLCR_MIO_PIN_43              0x000007AC //0x00001601 MIO Pin 43 Control
#define SLCR_MIO_PIN_44              0x000007B0 //0x00001601 MIO Pin 44 Control
#define SLCR_MIO_PIN_45              0x000007B4 //0x00001601 MIO Pin 45 Control
#define SLCR_MIO_PIN_46              0x000007B8 //0x00001601 MIO Pin 46 Control
#define SLCR_MIO_PIN_47              0x000007BC //0x00001601 MIO Pin 47 Control
#define SLCR_MIO_PIN_48              0x000007C0 //0x00001601 MIO Pin 48 Control
#define SLCR_MIO_PIN_49              0x000007C4 //0x00001601 MIO Pin 49 Control
#define SLCR_MIO_PIN_50              0x000007C8 //0x00001601 MIO Pin 50 Control
#define SLCR_MIO_PIN_51              0x000007CC //0x00001601 MIO Pin 51 Control
#define SLCR_MIO_PIN_52              0x000007D0 //0x00001601 MIO Pin 52 Control
#define SLCR_MIO_PIN_53              0x000007D4 //0x00001601 MIO Pin 53 Control
#define SLCR_MIO_LOOPBACK            0x00000804 //0x00000000 Loopback function within MIO
#define SLCR_MIO_MST_TRI0            0x0000080C //0xFFFFFFFF MIO pin Tri-state Enables, 31:0
#define SLCR_MIO_MST_TRI1            0x00000810 //0x003FFFFF MIO pin Tri-state Enables, 53:32
#define SLCR_SD0_WP_CD_SEL           0x00000830 //0x00000000 SDIO 0 WP CD select
#define SLCR_SD1_WP_CD_SEL           0x00000834 //0x00000000 SDIO 1 WP CD select
#define SLCR_LVL_SHFTR_EN            0x00000900 //0x00000000 Level Shifters Enable
#define SLCR_OCM_CFG                 0x00000910 //0x00000000 OCM Address Mapping
#define SLCR_GPIOB_CTRL              0x00000B00 //0x00000000 PS IO Buffer Control
#define SLCR_GPIOB_CFG_CMOS18        0x00000B04 //0x00000000 MIO GPIOB CMOS 1.8V config
#define SLCR_GPIOB_CFG_CMOS25        0x00000B08 //0x00000000 MIO GPIOB CMOS 2.5V config
#define SLCR_GPIOB_CFG_CMOS33        0x00000B0C //0x00000000 MIO GPIOB CMOS 3.3V config
#define SLCR_GPIOB_CFG_HSTL          0x00000B14 //0x00000000 MIO GPIOB HSTL config
#define SLCR_GPIOB_DRVR_BIAS_CTRL    0x00000B18 //0x00000000 MIO GPIOB Driver Bias Control
#define SLCR_DDRIOB_ADDR0            0x00000B40 //0x00000800 DDR IOB Config for A[14:0], CKE and DRST_B
#define SLCR_DDRIOB_ADDR1            0x00000B44 //0x00000800 DDR IOB Config for BA[2:0], ODT, CS_B, WE_B, RAS_B and CAS_B
#define SLCR_DDRIOB_DATA0            0x00000B48 //0x00000800 DDR IOB Config for Data 15:0
#define SLCR_DDRIOB_DATA1            0x00000B4C //0x00000800 DDR IOB Config for Data 31:16
#define SLCR_DDRIOB_DIFF0            0x00000B50 //0x00000800 DDR IOB Config for DQS 1:0
#define SLCR_DDRIOB_DIFF1            0x00000B54 //0x00000800 DDR IOB Config for DQS 3:2
#define SLCR_DDRIOB_CLOCK            0x00000B58 //0x00000800 DDR IOB Config for Clock Output
#define SLCR_DDRIOB_DRIVE_SLEW_ADDR  0x00000B5C //0x00000000 Drive and Slew controls for Address and Command pins of the DDR Interface
#define SLCR_DDRIOB_DRIVE_SLEW_DATA  0x00000B60 //0x00000000 Drive and Slew controls for DQ pins of the DDR Interface
#define SLCR_DDRIOB_DRIVE_SLEW_DIFF  0x00000B64 //0x00000000 Drive and Slew controls for DQS pins of the DDR Interface
#define SLCR_DDRIOB_DRIVE_SLEW_CLOCK 0x00000B68 //0x00000000 Drive and Slew controls for Clock pins of the DDR Interface
#define SLCR_DDRIOB_DDR_CTRL         0x00000B6C //0x00000000 DDR IOB Buffer Control
#define SLCR_DDRIOB_DCI_CTRL         0x00000B70 //0x00000020 DDR IOB DCI Config
#define SLCR_DDRIOB_DCI_STATUS       0x00000B74 //0x00000000 DDR IO Buffer DCI Status

void zynq_slcr_sd_enable();

#endif
