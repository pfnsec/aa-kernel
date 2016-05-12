PREFIX := aarch64-linux-gnu-

#LLVM Flags
#TARGET_CFLAGS  := -target aarch64 -mcpu=cortex-a57 -Isrc/include/arch/armv8 -Isrc/include/platform/virt
#TARGET_ASFLAGS := $(TARGET_CFLAGS) -Qunused-arguments

#GCC Flags
TARGET_CFLAGS  :=  -mcpu=cortex-a57 -Isrc/include/arch/armv8 -Isrc/include/platform/virt
TARGET_ASFLAGS := $(TARGET_CFLAGS) 
DRIVER_LIST    := pl011
LDSCRIPT       := armv8.ld
