include config.out.mk

ifeq ($(ARCH),armv7)
export PREFIX=arm-linux-gnu-

export CC=$(PREFIX)gcc
export LD=$(PREFIX)ld
export AS=$(PREFIX)gcc

export CFLAGS=-Wall -g -nostdlib -ffreestanding -Isrc/include \
	-mcpu='cortex-a8' -mfpu='neon' -fdiagnostics-color=always #-funsafe-math-optimizations	

export LDFLAGS=-Tlink.ld -nostdlib
export ASFLAGS=-mcpu='cortex-a8' -Isrc/include #-fdiagnostics-color=always

export SOURCES:=$(shell find src/arch/armv7 -type f -name '*.S')

else
ifeq ($(ARCH),armv8)
export PREFIX=aarch64-linux-gnu-

export CC=$(PREFIX)gcc
export LD=$(PREFIX)ld
export AS=$(PREFIX)gcc

export CFLAGS=-Wall -g -nostdlib -ffreestanding -Isrc/include \
	-march='armv8-a'  -funsafe-math-optimizations -fdiagnostics-color=always

export LDFLAGS=-Tlink.ld -nostdlib
export ASFLAGS=-march='armv8-a' -Isrc/include -ffreestanding -nostdlib \
	-fdiagnostics-color=always

export SOURCES:=$(shell find src/arch/armv8 -type f -name '*.S')

else
ifeq ($(ARCH),i386)
	export CC=gcc
	export LD=ld
	export AS=gcc

export CFLAGS=-Wall -g -nostdlib -ffreestanding -Isrc/include \
	-mcpu=i486 -m32

export LDFLAGS=-Tlink.ld -nostdlib 
export ASFLAGS=-march=i486 -Isrc/include -ffreestanding -nostdlib \
	-fdiagnostics-color=always

export SOURCES:=$(shell find src/arch/i386 -type f -name '*.S')

endif
endif
endif

export KERNEL_BINARY=kernel.elf

export SOURCES+=$(shell find src/ -type f -name '*.c')
export OBJECTS:=$(patsubst %.c,%.o,$(patsubst %.S,%.o,$(SOURCES)))

all: $(KERNEL_BINARY)

$(KERNEL_BINARY): $(OBJECTS) 
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@

.c: src/include/config.h 
	$(warning $(SOURCES))
	$(CC) $(CFLAGS) -c $@


clean:
	rm -f $(OBJECTS)
