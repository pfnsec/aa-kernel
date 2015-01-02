export ARCH=ARMv7
export PREFIX=arm-linux-gnu-
#export PREFIX=aarch64-linux-gnu-

export CC=$(PREFIX)gcc
export LD=$(PREFIX)ld
export AS=$(PREFIX)gcc

export CFLAGS=-Wall -g -nostdlib -ffreestanding -Isrc/include \
	-mcpu='cortex-a8' -mfpu='neon' -fdiagnostics-color=always #-funsafe-math-optimizations	
#	-march='armv8-a'  -funsafe-math-optimizations\

export LDFLAGS=-Tlink.ld -nostdlib #-lgcc
#export ASFLAGS=-march='armv8-a' -Isrc/include -ffreestanding -nostdlib\
	-fdiagnostics-color=always
export ASFLAGS=-mcpu='cortex-a8' -Isrc/include #-fdiagnostics-color=always

export KERNEL_BINARY=kernel.elf

export SOURCES:=$(shell find src/ -type f -name '*.c' -o -name '*.S')
export OBJECTS:=$(patsubst %.c,%.o,$(patsubst %.S,%.o,$(SOURCES)))

export CONFIG=config
export INCLUDE_DIR:=src/include

all: $(KERNEL_BINARY)

$(KERNEL_BINARY): $(OBJECTS) src/include/config.h 
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@

%.c: src/include/config.h

src/include/config.h: $(CONFIG)
	INCLUDE_DIR=src/include ./scripts/make_config.pl $(CONFIG)

clean:
	rm -f $(OBJECTS)
