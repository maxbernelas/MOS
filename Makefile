################################################################################
# Customizable variables
################################################################################
# Directories that need to be built
MODULES := src/cpu src/kernel

# Name of the output binary
OUT := mos

# Build options
CFLAGS := -Iinclude -Wall -Wextra -Werror -mcpu=cortex-m3 -nostdinc -mthumb    \
	  -ggdb -fomit-frame-pointer
LDFLAGS := -nostdlib
CROSS := arm-none-eabi-

################################################################################
# Build instructions, nothing should be customized under this line
################################################################################
CC := $(CROSS)gcc
LD := $(CROSS)ld
AS := $(CROSS)as
GDB := $(CROSS)gdb
OBJCOPY := $(CROSS)objcopy
SIZE := $(CROSS)size
OBJ :=

# Include all subdirectries makefiles, they will add their object files to the
# OBJ variable
include $(foreach module, $(MODULES), $(wildcard $(module)/*.mk))

# Default target (build the OS !)
all: $(OUT).bin

# Flat binary output
$(OUT).bin: $(OUT).elf
	$(OBJCOPY) -O binary $< $@
	$(SIZE) $<

# ELF binary output
$(OUT).elf: $(OBJ)
	$(LD) $(LDFLAGS) -T linker.lds -o $@ $^

# Cleanup target, remove generated object files and binaries
clean:
	rm -f $(OBJ) $(OUT).bin $(OUT).elf

debug: $(OUT).elf $(OUT).bin
	$(GDB) $<
