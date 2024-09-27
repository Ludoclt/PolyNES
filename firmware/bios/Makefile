PREFIX := arm-none-eabi-

CC := $(PREFIX)gcc
AS := $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

TARGET := bios

BUILD_DIR := ../build/bios
OBJ_DIR := $(BUILD_DIR)/obj
LIB_DIR := ../lib

ASM_SRC := startup_stm32h750xx.s
C_SRC := $(wildcard *.c)

CPU = -mcpu=cortex-m7
FPU = -mfpu=fpv5-d16
FLOAT-ABI = -mfloat-abi=hard
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

DEFINES := -DSTM32H750xx

ifeq ($(DEBUG),1)
	DEFINES += -DDEBUG
endif

INCLUDES := -I./ \
			-I$(LIB_DIR)/cmsis_core/Include \
			-I$(LIB_DIR)/stm32h7xx_cmsis/Include

CFLAGS += $(MCU) $(DEFINES) $(INCLUDES) -Og -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG),1)
	CFLAGS += -g -gdwarf-2
endif

# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

LDSCRIPT = stm32h750xbhx_flash.ld

LIBS = -lc -lm -lnosys
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin

OBJ = $(addprefix $(OBJ_DIR)/,$(notdir $(C_SRC:.c=.o)))
vpath %.c $(sort $(dir $(C_SRC)))
OBJ += $(addprefix $(OBJ_DIR)/,$(notdir $(ASM_SRC:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SRC)))

$(OBJ_DIR)/%.o: %.c Makefile | $(OBJ_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(OBJ_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(OBJ_DIR)/%.o: %.s Makefile | $(OBJ_DIR)
	$(AS) -c $(CFLAGS) $< -o $@
$(OBJ_DIR)/%.o: %.S Makefile | $(OBJ_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJ) Makefile
	$(CC) $(OBJ) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	-rm -rf $(BUILD_DIR)
  
-include $(wildcard $(OBJ_DIR)/*.d)
