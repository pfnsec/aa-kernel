export PREFIX=arm-none-eabi-

export CC=$(PREFIX)gcc
export LD=$(PREFIX)ld
export AS=$(PREFIX)as

export CFLAGS=-Wall -nostdlib -ffreestanding -Isrc/include \
	-mcpu='cortex-a8' -mfpu='neon' -funsafe-math-optimizations\
	-fdiagnostics-color=always
export LDFLAGS=-Tlink.ld -nostdlib #-lgcc
export ASFLAGS=-mcpu='cortex-a8'

export KERNEL_BINARY=kernel.elf

export SOURCES:=$(shell find src/ -type f -name '*.c' -o -name '*.s')
export OBJECTS:=$(patsubst %.c,%.o,$(patsubst %.s,%.o,$(SOURCES)))

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
