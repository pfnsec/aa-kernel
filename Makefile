TARGET   := armv7
PLATFORM := zynq


BINARY   := kernel.elf


include config/$(TARGET)-config.mk


CC=$(PREFIX)gcc
#CC=clang
CXX=clang++
LD=$(PREFIX)gcc


CFLAGS   := -std=c11 -g -O2 -ffreestanding -Isrc/include/ -Wall -Wno-unused -fdiagnostics-color=always $(TARGET_CFLAGS) -Wstrict-aliasing
ASFLAGS  := -Wall -g -ffreestanding  -fdiagnostics-color=always $(TARGET_ASFLAGS)
LDFLAGS  := -Wall -g -Tlink/$(LDSCRIPT) -nostdlib $(TARGET_LDFLAGS) -lgcc



# - Generic sources - #
SOURCES  := $(shell find src/                    \
                   -path src/arch     -prune -o  \
                   -path src/drivers  -prune -o  \
                   -path src/platform -prune -o  \
                   -type f -name *.c  -print)


# - Platform-specific drivers - #
SOURCES  += $(shell find src/platform/$(PLATFORM) \
                   -type f -name *.c  -print)


# - Generic drivers, as specified in <target>-config.mk - #
SOURCES  += $(shell find src/drivers -false      \
	    $(patsubst %, -o -name %.c ,  $(DRIVER_LIST)))


# - Architecture-specific code - #
SOURCES  += $(shell find src/arch/$(TARGET) -type f -name *.s)
SOURCES  += $(shell find src/arch/$(TARGET) -type f -name *.c)
SOURCES  += $(shell find src/arch/subarch/$(SUBARCH) -type f -name *.s)
SOURCES  += $(shell find src/arch/subarch/$(SUBARCH) -type f -name *.c)


OBJECTS  := $(patsubst %.s, %.o, \
            $(patsubst %.c, %.o, \
            $(SOURCES)))


all: $(BINARY) $(PLATFORM_BINARY)


$(PLATFORM_BINARY): $(BINARY)
	@$(PLATFORM_OBJCOPY)
	$(info Built $(PLATFORM_BINARY))


$(BINARY): $(OBJECTS)
	@$(LD) $(sort $(OBJECTS)) -o $(BINARY) $(LDFLAGS)
	$(info LD $(OBJECTS))
	$(info Built $(BINARY))

.c.o:
	@$(CC)  $(CFLAGS)  -c $< -o $@
	$(info CC $<)

.s.o:
	@$(CC)  $(ASFLAGS) -c $< -o $@
	$(info AS $<)
	

clean:
	rm -f $(OBJECTS)
