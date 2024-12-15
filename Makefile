# === Configuration ===

# Directories
SRC_DIR := src
RUNTIME_DIR := runtime
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj

# Source files
C_SRC := $(shell find $(SRC_DIR) -name '*.c')
ASM_SRC := $(shell find $(SRC_DIR) -name '*.s')
SRC := $(C_SRC) $(ASM_SRC)

# Object files
C_OBJ := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(C_SRC))
ASM_OBJ := $(patsubst $(SRC_DIR)/%.s,$(OBJ_DIR)/%.o,$(ASM_SRC))
OBJ := $(C_OBJ) $(ASM_OBJ)

# Compiler and tools
CC := sdcc-sdcc
AS := z80-elf-as
LD := z80-elf-ld
OBJCOPY := z80-elf-objcopy

# Compiler flags
CFLAGS := -mz80 -I$(SRC_DIR)/include --opt-code-size
ASFLAGS :=
LDFLAGS := -T link.ld

# === Targets ===

.PHONY: all clean

all: $(BUILD_DIR)/pondbios.bin

clean:
	rm -rf $(BUILD_DIR)

$(BUILD_DIR) $(OBJ_DIR):
	mkdir -p $@

$(BUILD_DIR)/pondbios.bin: $(BUILD_DIR)/pondbios.elf
	$(OBJCOPY) -O binary $< $@

$(BUILD_DIR)/pondbios.elf: $(OBJ) $(BUILD_DIR)/runtime.o | $(BUILD_DIR)
	$(LD) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(OBJ_DIR)/%.s | $(OBJ_DIR)
	$(AS) $(ASFLAGS) -sdcc -o $@ $<

$(OBJ_DIR)/%.s: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -S -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s | $(OBJ_DIR)
	$(AS) $(ASFLAGS) -o $@ $<

$(BUILD_DIR)/runtime.o: | $(BUILD_DIR)
	$(AS) $(ASFLAGS) -sdcc -o $@ $(RUNTIME_DIR)/*.s
