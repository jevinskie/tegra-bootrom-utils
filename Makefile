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
	_start.o \
	main.o \
	usb.o \
	hello.o \
)

OBJS += $(addprefix $(BUILD)/$(TARGET)/, \
)

ENTRY_POINT_ADDRESS := 0x4000A000

ARCH := -mcpu=arm7tdmi -mthumb -mthumb-interwork -masm-syntax-unified
CUSTOMDEFINES := -DBLVERSIONMJ=$(BLVERSION_MAJOR) -DBLVERSIONMN=$(BLVERSION_MINOR) -DENTRY_POINT_ADDRESS=$(ENTRY_POINT_ADDRESS)
CUSTOMDEFINES += -DDEBUG
CFLAGS = $(ARCH) -Os -g -nostdlib -ffunction-sections -fdata-sections -fomit-frame-pointer -fno-inline -std=gnu11 -Wall $(CUSTOMDEFINES)
LDFLAGS = $(ARCH) -nostartfiles -lgcc -Wl,--nmagic,--gc-sections,--defsym,LOAD_ADDR=$(ENTRY_POINT_ADDRESS) 

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
	$(CC) $(LDFLAGS) -T $(SOURCEDIR)/link.ld $^ -o $@

$(BUILD)/$(TARGET)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/$(TARGET)/%.o: %.S
	@mkdir -p "$(BUILD)"
	@mkdir -p "$(BUILD)/$(TARGET)"
	@mkdir -p "$(OUTPUT)"
	$(CC) $(CFLAGS) -c $< -o $@
