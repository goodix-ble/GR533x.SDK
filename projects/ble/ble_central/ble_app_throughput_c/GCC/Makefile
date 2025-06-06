#########################################################################################################
# GNU Compiler makefile for Goodix BLE Application Project
# Copyright(C) 2023, Shenzhen Goodix Technology Co., Ltd
#
# Default Location of GCC Compile Ref Files
#
#   {APP_ROOT_DIR} is root directory in GR55xx SDK
#
#   1. sdk lib for gcc          : {APP_ROOT_DIR}/platform/soc/linker/gcc/libble_sdk.a
#   2. symbol file for gcc      : {APP_ROOT_DIR}/platform/soc/linker/gcc/rom_symbol_gcc.txt
#   3. link file for gcc        : {APP_ROOT_DIR}/platform/soc/linker/gcc/gcc_linker.lds
#   4. startup asemmbly file    : (APP_ROOT_DIR)/platform/arch/arm/cortex-m/gcc/startup_gr55xx.s
#########################################################################################################


#########################################################################################################
###                                Different Configuration For Different Project
#########################################################################################################

## Set Vars by Input Value
# target name
    
MAKE_TARGET_NAME :=  ble_app_throughput_c

PRJ_C_SRC_FILES:=   \
../../../../../platform/soc/common/gr_system.c  \
../../../../../platform/soc/common/gr_interrupt.c  \
../../../../../platform/soc/common/gr_platform.c  \
../../../../../platform/soc/src/gr_soc.c  \
../../../../../platform/boards/board_SK.c  \
../../../../../drivers/src/app_dma.c  \
../../../../../drivers/src/app_gpiote.c  \
../../../../../drivers/src/app_io.c  \
../../../../../drivers/src/app_pwr_mgmt.c  \
../../../../../drivers/src/app_uart.c  \
../../../../../drivers/src/app_spi.c  \
../../../../../drivers/src/app_uart_dma.c  \
../../../../../components/libraries/ble/ble_scanner/ble_scanner.c  \
../../../../../components/libraries/app_key/app_key.c  \
../../../../../components/libraries/app_key/app_key_core.c  \
../../../../../components/libraries/ring_buffer/ring_buffer.c  \
../../../../../components/libraries/utility/utility.c  \
../../../../../components/libraries/sensorsim/sensorsim.c  \
../../../../../components/libraries/app_timer/app_timer.c  \
../../../../../components/libraries/pmu_calibration/pmu_calibration.c  \
../../../../../components/libraries/app_assert/app_assert.c  \
../../../../../components/libraries/app_error/app_error.c  \
../../../../../components/libraries/app_log/app_log.c  \
../../../../../components/sdk/ble.c  \
../../../../../components/profiles/common/ble_prf_utils.c  \
../../../../../components/profiles/ths_c/ths_c.c  \
../../../../../external/segger_rtt/SEGGER_RTT.c  \
../Src/platform/user_periph_setup.c  \
../Src/user/main.c  \
../Src/user/user_app.c  \
../Src/user/throughput_c.c  \


PRJ_ASM_SRC_FILES :=   \


PRJ_C_INCLUDE_PATH :=   \
../Src/config  \
../Src/platform  \
../Src/user  \
../Src/config  \
../../../../../components/boards  \
../../../../../components/drivers_ext/gr55xx  \
../../../../../components/drivers_ext/st7735  \
../../../../../components/drivers_ext/vs1005  \
../../../../../components/libraries/app_alarm  \
../../../../../components/libraries/app_assert  \
../../../../../components/libraries/app_error  \
../../../../../components/libraries/app_key  \
../../../../../components/libraries/app_log  \
../../../../../components/libraries/app_queue  \
../../../../../components/libraries/app_timer  \
../../../../../components/libraries/at_cmd  \
../../../../../components/libraries/bsp  \
../../../../../components/libraries/dfu_master  \
../../../../../components/libraries/dfu_port  \
../../../../../components/libraries/gui  \
../../../../../components/libraries/gui/gui_config  \
../../../../../components/libraries/hal_flash  \
../../../../../components/libraries/hci_uart  \
../../../../../components/libraries/pmu_calibration  \
../../../../../components/libraries/ring_buffer  \
../../../../../components/libraries/sensorsim  \
../../../../../components/libraries/utility  \
../../../../../components/libraries/ble/ble_scanner  \
../../../../../components/patch/ind  \
../../../../../components/profiles/ams_c  \
../../../../../components/profiles/ancs_c  \
../../../../../components/profiles/ans  \
../../../../../components/profiles/ans_c  \
../../../../../components/profiles/bas  \
../../../../../components/profiles/bas_c  \
../../../../../components/profiles/bcs  \
../../../../../components/profiles/bps  \
../../../../../components/profiles/common  \
../../../../../components/profiles/cscs  \
../../../../../components/profiles/cts  \
../../../../../components/profiles/cts_c  \
../../../../../components/profiles/dis  \
../../../../../components/profiles/dis_c  \
../../../../../components/profiles/gls  \
../../../../../components/profiles/gus  \
../../../../../components/profiles/gus_c  \
../../../../../components/profiles/hids  \
../../../../../components/profiles/hrrcps  \
../../../../../components/profiles/hrs  \
../../../../../components/profiles/hrs_c  \
../../../../../components/profiles/hts  \
../../../../../components/profiles/ias  \
../../../../../components/profiles/lls  \
../../../../../components/profiles/ndcs  \
../../../../../components/profiles/otas  \
../../../../../components/profiles/otas_c  \
../../../../../components/profiles/pass  \
../../../../../components/profiles/pass_c  \
../../../../../components/profiles/pcs  \
../../../../../components/profiles/rscs  \
../../../../../components/profiles/rscs_c  \
../../../../../components/profiles/rtus  \
../../../../../components/profiles/sample  \
../../../../../components/profiles/ths  \
../../../../../components/profiles/ths_c  \
../../../../../components/profiles/thscps  \
../../../../../components/profiles/tps  \
../../../../../components/profiles/wechat  \
../../../../../components/sdk/  \
../../../../../drivers/inc  \
../../../../../drivers/inc/hal  \
../../../../../external/freertos/include  \
../../../../../external/segger_rtt  \
../../../../../platform/include  \
../../../../../platform/soc/include  \
../../../../../platform/arch/arm/cortex-m/cmsis/core/include  \
../../../../../platform/soc/linker/keil  \
../../../../../platform/boards  \


PRJ_C_MICRO_DEFINES :=   \


PRJ_ASM_INCLUDE_PATH :=   \


PRJ_ASM_MICRO_DEFINES :=   \


IS_WIN_OS :=  true
LINKER_SCRIPT_TMPL = ../../../../../platform/soc/linker/gcc/gcc_linker.lds

# Set echo cmd
ECHO = @echo

#########################################################################################################
###                                   Common Configuration Area, Change carefully
#########################################################################################################

## Set Compiler (CC/ASM use same compile cmd for now)
CROSS_COMPILE 	= arm-none-eabi-
CC 				= $(CROSS_COMPILE)gcc
ASM				= $(CROSS_COMPILE)gcc
CPP 			= $(CROSS_COMPILE)cpp
LINK			= $(CROSS_COMPILE)gcc
OBJCOPY 		= $(CROSS_COMPILE)objcopy

## Set Common Flags for C/ASM
COMMON_COMPILE_FLAGS += -std=gnu99 --inline
COMMON_COMPILE_FLAGS += -ggdb3
COMMON_COMPILE_FLAGS += -ffunction-sections -fdata-sections
COMMON_COMPILE_FLAGS += -mfloat-abi=softfp -mfpu=fpv4-sp-d16  -mapcs-frame -mthumb-interwork -mthumb -mcpu=cortex-m4
COMMON_COMPILE_FLAGS += -gdwarf-2 -MD

## Set CFLAGS
# Set include path
CFLAGS += $(foreach inc,$(PRJ_C_INCLUDE_PATH),-I $(inc))
# Set macro-defines Flags
CFLAGS += $(foreach md,$(PRJ_C_MICRO_DEFINES),-D$(md))
CFLAGS += $(COMMON_COMPILE_FLAGS)
CFLAGS += -O2

## Set CPPFLAGS
CPPFLAGS += $(foreach inc,$(PRJ_C_INCLUDE_PATH),-I $(inc))
CPPFLAGS += $(foreach md,$(PRJ_C_MICRO_DEFINES),-D$(md))

## Set ASMFLAGS
ASMFLAGS += $(foreach inc,$(PRJ_ASM_INCLUDE_PATH),-I $(inc))
# Set macro-defines Flags
ASMFLAGS += $(foreach md,$(PRJ_ASM_MICRO_DEFINES),-D$(md))
ASMFLAGS += $(COMMON_COMPILE_FLAGS)

## Set default compile ref files
PATCH_FILE  		= ../../../../../platform/soc/linker/gcc/rom_symbol_gcc.txt

GCC_STARTUP_ASM_FILE 	= ../../../../../platform/arch/arm/cortex-m/gcc/startup_gr55xx.s

ifeq ($(IS_WIN_OS),true)
	BLE_TOOL_BIN		= ..\..\..\..\..\build\binaries\ble_tools\Keil\ble_tools.exe
else
	BLE_TOOL_BIN		= ..\..\..\..\..\build\binaries\ble_tools\GCC\ble_tools.gcc
endif


## Set LDFLAGS
LDFLAGS += -Wl,--gc-sections
# LDFLAGS += -specs=nano.specs
LDFLAGS += -L../../../../../components/libraries/app_crypto/gcc/ -lapp_crypto
LDFLAGS += -Wl,--start-group -L../../../../../components/mesh/lib/gcc/ -lmesh -L../../../../../platform/soc/linker/gcc/ -lble_sdk -Wl,--end-group

## Set compile output directory
BUILD 		?= out
BUILD_OBJ	?= $(BUILD)/obj
BUILD_LST	?= $(BUILD)/lst


## Set source files and objects
SRC_C	:= $(PRJ_C_SRC_FILES)
SRC_ASM := $(GCC_STARTUP_ASM_FILE) $(PRJ_ASM_SRC_FILES)
OBJ_C 	:= $(SRC_C:.c=.o)
OBJ_ASM := $(SRC_ASM:.s=.o)

OBJ 	:= $(OBJ_C) $(OBJ_ASM)
OBJ_ADJUST 	= $(patsubst %.o,$(BUILD_OBJ)/%.o,$(notdir $(OBJ)))

LINKER_SCRIPT := $(BUILD)/gcc_linker.lds

## verbosity switch
V ?= 0
ifeq ($(V),0)
	V_CC = @echo " $(CC) " $<;
	V_ASM = @echo " $(ASM) " $<;
	V_CPP = @echo " $(CPP) " $<;
	V_LINK = @echo " $(LINK) " $<;
	V_OBJCOPY = @echo " $(OBJCOPY) " $<;
else
	V_OPT = '-v'
endif


SRC_PATH += $(dir $(SRC_C))
SRC_PATH += $(dir $(SRC_ASM))
MAKE_PATH = $(foreach n,$(SRC_PATH),:$(n))
vpath %.c ./$(MAKE_PATH)
vpath %.s ./$(MAKE_PATH)
## default make goal
all: mk_path $(BUILD)/$(MAKE_TARGET_NAME).bin $(BUILD)/$(MAKE_TARGET_NAME).hex

## preprocess link-script
$(LINKER_SCRIPT): $(LINKER_SCRIPT_TMPL)
	$(V_CPP) $(CPP) $(CPPFLAGS) -E $< -o $@ -P

##  compile C & asm files
$(BUILD_OBJ)/%.o : %.c
	$(V_CC) $(CC) $(CFLAGS) -c $< -o $@

## how to compile assembly files
$(BUILD_OBJ)/%.o : %.s
	$(V_ASM) $(ASM) $(ASMFLAGS) -c $< -o $@

## make depends
$(BUILD)/$(MAKE_TARGET_NAME).hex: $(BUILD_LST)/$(MAKE_TARGET_NAME).elf
	$(ECHO) "compile hex file ..."
	$(V_OBJCOPY) $(OBJCOPY) -O ihex $< $@

$(BUILD)/$(MAKE_TARGET_NAME).bin: $(BUILD_LST)/$(MAKE_TARGET_NAME).elf
	$(ECHO) "compile binary file ..."
	$(V_OBJCOPY) $(OBJCOPY) -O binary $< $@

$(BUILD_LST)/$(MAKE_TARGET_NAME).elf: $(OBJ_ADJUST) $(LINKER_SCRIPT)
	$(ECHO) "compile .elf file ..."
	$(V_LINK) $(LINK) $(CFLAGS) -T $(LINKER_SCRIPT) $(PATCH_FILE) $(OBJ_ADJUST) $(LDFLAGS) -Wl,-Map=$(BUILD_LST)/$(MAKE_TARGET_NAME).map -o $@


mk_path :
	mkdir -p  $(BUILD)
	mkdir -p  $(BUILD_OBJ)
	mkdir -p  $(BUILD_LST)

flash: $(BUILD)/$(MAKE_TARGET_NAME).bin
	$(ECHO) "Writing $< to the GR55xx-SK board"
	GR5xxx_console.exe eraseall 2 0
	GR5xxx_console.exe program $(BUILD)/$(MAKE_TARGET_NAME).bin 'y' 0x200000 512 2 0

clean:
	rm -rf $(BUILD)

