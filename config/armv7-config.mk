PREFIX := arm-none-eabi-


ifeq ($(PLATFORM), rpi)
TARGET_CFLAGS    := -marm -mcpu='arm1176jzf-s' -Isrc/include/arch/armv7 -Isrc/include/platform/rpi
LDSCRIPT         :=  rpi.ld
DRIVER_LIST      :=  pl011
PLATFORM_BINARY  :=  kernel.img

PLATFORM_OBJCOPY := $(PREFIX)objcopy $(BINARY) -O binary $(PLATFORM_BINARY)

endif



ifeq ($(PLATFORM), zynq)
#LLVM Flags
#TARGET_CFLAGS  := -target arm -mcpu=cortex-a9 -mfloat-abi=hard -Isrc/include/arch/armv7 -Isrc/include/platform/zynq
#TARGET_ASFLAGS := $(TARGET_CFLAGS) -Qunused-arguments

#GCC Flags
TARGET_CFLAGS    := -marm -mcpu='cortex-a9' -mno-unaligned-access -Isrc/include/arch/armv7 -Isrc/include/platform/zynq
TARGET_ASFLAGS   := $(TARGET_CFLAGS) 

SUBARCH          := cortex-a9

LDSCRIPT         := zynq.ld
DRIVER_LIST      := sdhci pl390 pl310 display_surface
#DRIVER_LIST      := sdhci pl390 pl310 pcm_channel

#U-boot kernel format - unneeded if booting from JTAG
PLATFORM_BINARY  :=  kernel.bin

PLATFORM_OBJCOPY :=  $(PREFIX)objcopy $(BINARY) -O binary $(PLATFORM_BINARY) && \
                      mkimage -f uboot/zynq.its fit.itb

endif



ifeq ($(PLATFORM), integratorcp)
TARGET_CFLAGS   := -marm -mcpu='cortex-a8' -Isrc/include/arch/armv7 -Isrc/include/platform/integratorcp
LDSCRIPT        :=  integratorcp.ld
DRIVER_LIST     :=  pl011 pl110
endif



ifeq ($(PLATFORM), cubieboard)
TARGET_CFLAGS   := -marm -mcpu='cortex-a8' -Isrc/include/arch/armv7 -Isrc/include/platform/cubieboard
LDSCRIPT        :=  sunxi.ld
DRIVER_LIST     :=  sunxi
endif

TARGET_ASFLAGS  := $(TARGET_CFLAGS) 
