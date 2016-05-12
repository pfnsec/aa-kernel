PREFIX := arm-none-eabi-


ifeq ($(PLATFORM), rpi)
TARGET_CFLAGS    := -marm -mcpu='arm1176jzf-s' -Isrc/include/arch/armv7 -Isrc/include/platform/rpi
LDSCRIPT         :=  rpi.ld
DRIVER_LIST      :=  pl011
PLATFORM_BINARY  :=  kernel.img

PLATFORM_OBJCOPY := $(PREFIX)objcopy $(BINARY) -O binary $(PLATFORM_BINARY)

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
