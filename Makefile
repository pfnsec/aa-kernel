include config.out.mk

ifeq ($(ARCH),armv7)
export PREFIX=arm-linux-gnu-

export CC=$(PREFIX)gcc
export LD=$(PREFIX)ld
export AS=$(PREFIX)gcc

export CFLAGS=-Wall -g -nostdlib -ffreestanding -Isrc/include \
	-mcpu='cortex-a8' -mfpu='neon' -fdiagnostics-color=always #-funsafe-math-optimizations	

export LDFLAGS=-Tlink/link-armv7.ld -nostdlib
export ASFLAGS=-mcpu='cortex-a8' -Isrc/include #-fdiagnostics-color=always

export ASM_SOURCES:=$(shell find src/arch/armv7 -type f -name '*.S')

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

export ASM_SOURCES:=$(shell find src/arch/armv8 -type f -name '*.S')

else
ifeq ($(ARCH),i386)
	export CC=clang
	export LD=i686-elf-ld
	export AS=clang

export CFLAGS=-Wall -g -nostdlib -ffreestanding -Isrc/include \
	-march=i486 -m32

export LDFLAGS=-Tlink/link-i386.ld -nostdlib 
export ASFLAGS=-march=i486 -m32 -Isrc/include -ffreestanding -nostdlib \
	-fdiagnostics-color=always

export ASM_SOURCES:=$(shell find src/arch/i386 -type f -name '*.S')

endif
endif
endif

export KERNEL_BINARY=kernel.elf

export C_SOURCES:=$(shell find src/ -type f -name '*.c')
export OBJECTS:=$(patsubst %.c,%.o,$(C_SOURCES))
export OBJECTS+=$(patsubst %.S,%.o,$(ASM_SOURCES))

all: $(KERNEL_BINARY)

$(KERNEL_BINARY): $(OBJECTS) $(ASM_SOURCES) link/link-$(ARCH).ld
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.c src/include/config.h 
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S src/include/config.h 
	$(AS) $(ASFLAGS) -c $< -o $@


clean:
	rm -f $(OBJECTS)
