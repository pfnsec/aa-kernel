include config.out.mk

ifeq ($(ARCH),armv7)
export PREFIX=arm-linux-gnu-

export CC=$(PREFIX)gcc
export LD=$(PREFIX)ld
export AS=$(PREFIX)gcc

export CFLAGS=-Wall -nostdlib -ffreestanding -Isrc/include \
	-mcpu='cortex-a8' -mfpu='neon' -fdiagnostics-color=always #-funsafe-math-optimizations	

export LDFLAGS=-Tlink/link-armv7.ld -nostdlib
export ASFLAGS=-mcpu='cortex-a8' -Isrc/include 

#export ASM_SOURCES:=$(shell find src/arch/armv7 -type f -name '*.S')

else
ifeq ($(ARCH),armv8)
export PREFIX=aarch64-linux-gnu-

export CC=$(PREFIX)gcc
export LD=$(PREFIX)ld
export AS=$(PREFIX)gcc

export CFLAGS=-Wall -g -nostdlib -ffreestanding -Isrc/include \
	-march='armv8-a'  -funsafe-math-optimizations -fdiagnostics-color=always

export LDFLAGS=-Tlink/link-armv8.ld -nostdlib
export ASFLAGS=-march='armv8-a' -Isrc/include -ffreestanding -nostdlib \
	-fdiagnostics-color=always

#export ASM_SOURCES:=$(shell find src/arch/armv8 -type f -name '*.S')

else
ifeq ($(ARCH),i386)
	export CC=clang
	export LD=i686-elf-ld
	export AS=i686-elf-as

export PLATFORM_INCLUDE=src/include/platform/pc

export CFLAGS=-Wall -Wundef -g -nostdlib -ffreestanding -Isrc/include -I$(PLATFORM_INCLUDE) -Isrc/include/arch/$(ARCH) \
	-march=i386 -target i686-elf

export LDFLAGS=-Tlink/link-i386.ld -nostdlib 
#export ASFLAGS=-march=i486 -Isrc/include -ffreestanding -nostdlib -target i686-elf
export ASFLAGS=-g -march=i386 -Isrc/include -nostdlib 

#export ASM_SOURCES:=$(shell find src/arch/i386 -type f -name '*.S')

#export PLATFORM_SOURCES:=$(shell find src/drivers/platform/pc -type f -name '*.c' -and -path src/platform -prune)

endif
endif
endif

export KERNEL_BINARY=kernel.elf

#export C_SOURCES:=$(shell find src/ -type f -name '*.c'-and -path src/drivers/platform -prune -o -print)
#export C_SOURCES+=$(PLATFORM_SOURCES)
export OBJECTS:=$(patsubst %.S,%.o,$(patsubst %.c,%.o,$(SOURCES)))

all: $(KERNEL_BINARY)

$(KERNEL_BINARY): $(OBJECTS) link/link-$(ARCH).ld
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.c src/include/config.h 
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S src/include/config.h 
	$(AS) $(ASFLAGS) -c $< -o $@


clean:
	rm -f $(OBJECTS)
