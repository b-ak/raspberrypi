################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

EMPTY := 
SPACE := $(EMPTY) $(EMPTY)

ORDERED_OBJS += \
$(GEN_CMDS_QUOTED) \
"./src/vectors.obj" \
"./src/usbstk5505_spi.obj" \
"./src/usbstk5505_led.obj" \
"./src/usbstk5505_intr.obj" \
"./src/usbstk5505_i2c.obj" \
"./src/usbstk5505_gpio.obj" \
"./src/usbstk5505.obj" \
"./src/main.obj" \
"./src/aic3204_init.obj" \
"./src/aic3204.obj" \
"./src/PLL.obj" \
"./src/IIR_filters_fourth_order.obj" \
-l"rts55x.lib" \
"../cslVC5505.lib" \
"../lnkx.cmd" \

-include ../makefile.init

RM := DEL /F

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: mpas.out

# Tool invocations
mpas.out: $(GEN_CMDS) $(CMD_SRCS) $(LIB_SRCS) $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Linker'
	"C:/Texas Instruments/C5500 Code Generation Tools 4.3.9/bin/cl55" -v5505 --symdebug:none -O3 --diag_warning=225 --large_memory_model --algebraic --memory_model=large --asm_source=algebraic -z -m"mpas.map" --warn_sections -i"C:/Texas Instruments/C5500 Code Generation Tools 4.3.9/lib" -i"C:/Texas Instruments/C5500 Code Generation Tools 4.3.9/include" --reread_libs --rom_model -o "mpas.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C5500_EXECUTABLE_OUTPUTS__QTD) "mpas.out"
	-$(RM) ".\src\IIR_filters_fourth_order.obj" ".\src\PLL.obj" ".\src\aic3204.obj" ".\src\aic3204_init.obj" ".\src\main.obj" ".\src\usbstk5505.obj" ".\src\usbstk5505_gpio.obj" ".\src\usbstk5505_i2c.obj" ".\src\usbstk5505_intr.obj" ".\src\usbstk5505_led.obj" ".\src\usbstk5505_spi.obj" ".\src\vectors.obj" 
	-$(RM) ".\src\vectors.pp" 
	-$(RM) ".\src\IIR_filters_fourth_order.pp" ".\src\PLL.pp" ".\src\aic3204.pp" ".\src\aic3204_init.pp" ".\src\main.pp" ".\src\usbstk5505.pp" ".\src\usbstk5505_gpio.pp" ".\src\usbstk5505_i2c.pp" ".\src\usbstk5505_intr.pp" ".\src\usbstk5505_led.pp" ".\src\usbstk5505_spi.pp" 
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
