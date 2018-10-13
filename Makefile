ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

include $(DEVKITARM)/base_rules

TARGET := tegra-bootrom-utils
BLVERSION_MAJOR := 0
BLVERSION_MINOR := 1
BUILD := build
OUTPUT := output
SOURCEDIR = src
VPATH = $(dir $(wildcard ./$(SOURCEDIR)/*/)) $(dir $(wildcard ./$(SOURCEDIR)/*/*/))

OBJS = $(addprefix $(BUILD)/$(TARGET)/, \
	start.o \
	_exit.o \
	main.o \
	usb.o \
	stdio-bits.o \
	raise.o \
)

OBJS += $(addprefix $(BUILD)/$(TARGET)/, \
)

ENTRY_POINT_ADDRESS := 0x4000A000

ARCH := -mcpu=arm7tdmi -mthumb -mthumb-interwork -masm-syntax-unified
CUSTOMDEFINES := -DBLVERSIONMJ=$(BLVERSION_MAJOR) -DBLVERSIONMN=$(BLVERSION_MINOR) -DENTRY_POINT_ADDRESS=$(ENTRY_POINT_ADDRESS)
CUSTOMDEFINES += -DDEBUG
CFLAGS = $(ARCH) -flto-partition=none -flto -fuse-linker-plugin -fuse-ld=gold -Os -g -nostdinc -nostdlib -ffunction-sections -fdata-sections -fomit-frame-pointer -std=gnu11 -Wall -Wextra -isystem /opt/devkitpro/devkitARM/bin/../lib/gcc/arm-none-eabi/8.1.0/include -isystem /Users/jevin/code/tegra/libc/prefix-nolto/lib/newlib-nano/arm-none-eabi/include $(CUSTOMDEFINES)
LDFLAGS = $(ARCH) -flto-partition=none -flto -fuse-linker-plugin -fuse-ld=gold -Os -g -nostdinc -nostdlib -L/Users/jevin/code/tegra/libc/prefix-nolto/lib/newlib-nano/arm-none-eabi/lib/thumb -lc -lgcc -Wl,--nmagic,--gc-sections,--defsym,LOAD_ADDR=$(ENTRY_POINT_ADDRESS)

.PHONY: all clean

all: $(TARGET).bin
	@echo -n "Payload size is "
	@wc -c < $(OUTPUT)/$(TARGET).bin
	@echo "Max size is 126296 Bytes."

clean:
	@rm -rf $(OBJS)
	@rm -rf $(BUILD)
	@rm -rf $(OUTPUT)

$(TARGET).bin: $(BUILD)/$(TARGET)/$(TARGET).elf
	$(OBJCOPY) -S -O binary $< $(OUTPUT)/$@

$(BUILD)/$(TARGET)/$(TARGET).elf: $(OBJS)
	$(CC) -T $(SOURCEDIR)/link.ld $^ -o $@ $(LDFLAGS)

$(BUILD)/$(TARGET)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/$(TARGET)/%.o: %.S
	@mkdir -p "$(BUILD)"
	@mkdir -p "$(BUILD)/$(TARGET)"
	@mkdir -p "$(OUTPUT)"
	$(CC) $(CFLAGS) -c $< -o $@
