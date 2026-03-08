################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/IIR_filters_fourth_order.c \
../src/PLL.c \
../src/aic3204.c \
../src/aic3204_init.c \
../src/main.c \
../src/usbstk5505.c \
../src/usbstk5505_gpio.c \
../src/usbstk5505_i2c.c \
../src/usbstk5505_intr.c \
../src/usbstk5505_led.c \
../src/usbstk5505_spi.c 

ASM_SRCS += \
../src/vectors.asm 

ASM_DEPS += \
./src/vectors.pp 

OBJS += \
./src/IIR_filters_fourth_order.obj \
./src/PLL.obj \
./src/aic3204.obj \
./src/aic3204_init.obj \
./src/main.obj \
./src/usbstk5505.obj \
./src/usbstk5505_gpio.obj \
./src/usbstk5505_i2c.obj \
./src/usbstk5505_intr.obj \
./src/usbstk5505_led.obj \
./src/usbstk5505_spi.obj \
./src/vectors.obj 

C_DEPS += \
./src/IIR_filters_fourth_order.pp \
./src/PLL.pp \
./src/aic3204.pp \
./src/aic3204_init.pp \
./src/main.pp \
./src/usbstk5505.pp \
./src/usbstk5505_gpio.pp \
./src/usbstk5505_i2c.pp \
./src/usbstk5505_intr.pp \
./src/usbstk5505_led.pp \
./src/usbstk5505_spi.pp 

OBJS__QTD += \
".\src\IIR_filters_fourth_order.obj" \
".\src\PLL.obj" \
".\src\aic3204.obj" \
".\src\aic3204_init.obj" \
".\src\main.obj" \
".\src\usbstk5505.obj" \
".\src\usbstk5505_gpio.obj" \
".\src\usbstk5505_i2c.obj" \
".\src\usbstk5505_intr.obj" \
".\src\usbstk5505_led.obj" \
".\src\usbstk5505_spi.obj" \
".\src\vectors.obj" 

ASM_DEPS__QTD += \
".\src\vectors.pp" 

C_DEPS__QTD += \
".\src\IIR_filters_fourth_order.pp" \
".\src\PLL.pp" \
".\src\aic3204.pp" \
".\src\aic3204_init.pp" \
".\src\main.pp" \
".\src\usbstk5505.pp" \
".\src\usbstk5505_gpio.pp" \
".\src\usbstk5505_i2c.pp" \
".\src\usbstk5505_intr.pp" \
".\src\usbstk5505_led.pp" \
".\src\usbstk5505_spi.pp" 

C_SRCS_QUOTED += \
"../src/IIR_filters_fourth_order.c" \
"../src/PLL.c" \
"../src/aic3204.c" \
"../src/aic3204_init.c" \
"../src/main.c" \
"../src/usbstk5505.c" \
"../src/usbstk5505_gpio.c" \
"../src/usbstk5505_i2c.c" \
"../src/usbstk5505_intr.c" \
"../src/usbstk5505_led.c" \
"../src/usbstk5505_spi.c" 

ASM_SRCS_QUOTED += \
"../src/vectors.asm" 


# Each subdirectory must supply rules for building sources it contributes
src/IIR_filters_fourth_order.obj: ../src/IIR_filters_fourth_order.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Texas Instruments/C5500 Code Generation Tools 4.3.9/bin/cl55" -v5505 --symdebug:none -O3 --include_path="C:/Texas Instruments/C5500 Code Generation Tools 4.3.9/include" --include_path="D:/vmshare/mpas/workspace/ccs_v4/inc" --diag_warning=225 --large_memory_model --algebraic --memory_model=large --asm_source=algebraic --preproc_with_compile --preproc_dependency="src/IIR_filters_fourth_order.pp" --obj_directory="src" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

src/PLL.obj: ../src/PLL.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Texas Instruments/C5500 Code Generation Tools 4.3.9/bin/cl55" -v5505 --symdebug:none -O3 --include_path="C:/Texas Instruments/C5500 Code Generation Tools 4.3.9/include" --include_path="D:/vmshare/mpas/workspace/ccs_v4/inc" --diag_warning=225 --large_memory_model --algebraic --memory_model=large --asm_source=algebraic --preproc_with_compile --preproc_dependency="src/PLL.pp" --obj_directory="src" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

src/aic3204.obj: ../src/aic3204.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Texas Instruments/C5500 Code Generation Tools 4.3.9/bin/cl55" -v5505 --symdebug:none -O3 --include_path="C:/Texas Instruments/C5500 Code Generation Tools 4.3.9/include" --include_path="D:/vmshare/mpas/workspace/ccs_v4/inc" --diag_warning=225 --large_memory_model --algebraic --memory_model=large --asm_source=algebraic --preproc_with_compile --preproc_dependency="src/aic3204.pp" --obj_directory="src" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

src/aic3204_init.obj: ../src/aic3204_init.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Texas Instruments/C5500 Code Generation Tools 4.3.9/bin/cl55" -v5505 --symdebug:none -O3 --include_path="C:/Texas Instruments/C5500 Code Generation Tools 4.3.9/include" --include_path="D:/vmshare/mpas/workspace/ccs_v4/inc" --diag_warning=225 --large_memory_model --algebraic --memory_model=large --asm_source=algebraic --preproc_with_compile --preproc_dependency="src/aic3204_init.pp" --obj_directory="src" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

src/main.obj: ../src/main.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Texas Instruments/C5500 Code Generation Tools 4.3.9/bin/cl55" -v5505 --symdebug:none -O3 --include_path="C:/Texas Instruments/C5500 Code Generation Tools 4.3.9/include" --include_path="D:/vmshare/mpas/workspace/ccs_v4/inc" --diag_warning=225 --large_memory_model --algebraic --memory_model=large --asm_source=algebraic --preproc_with_compile --preproc_dependency="src/main.pp" --obj_directory="src" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

src/usbstk5505.obj: ../src/usbstk5505.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Texas Instruments/C5500 Code Generation Tools 4.3.9/bin/cl55" -v5505 --symdebug:none -O3 --include_path="C:/Texas Instruments/C5500 Code Generation Tools 4.3.9/include" --include_path="D:/vmshare/mpas/workspace/ccs_v4/inc" --diag_warning=225 --large_memory_model --algebraic --memory_model=large --asm_source=algebraic --preproc_with_compile --preproc_dependency="src/usbstk5505.pp" --obj_directory="src" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

src/usbstk5505_gpio.obj: ../src/usbstk5505_gpio.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Texas Instruments/C5500 Code Generation Tools 4.3.9/bin/cl55" -v5505 --symdebug:none -O3 --include_path="C:/Texas Instruments/C5500 Code Generation Tools 4.3.9/include" --include_path="D:/vmshare/mpas/workspace/ccs_v4/inc" --diag_warning=225 --large_memory_model --algebraic --memory_model=large --asm_source=algebraic --preproc_with_compile --preproc_dependency="src/usbstk5505_gpio.pp" --obj_directory="src" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

src/usbstk5505_i2c.obj: ../src/usbstk5505_i2c.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Texas Instruments/C5500 Code Generation Tools 4.3.9/bin/cl55" -v5505 --symdebug:none -O3 --include_path="C:/Texas Instruments/C5500 Code Generation Tools 4.3.9/include" --include_path="D:/vmshare/mpas/workspace/ccs_v4/inc" --diag_warning=225 --large_memory_model --algebraic --memory_model=large --asm_source=algebraic --preproc_with_compile --preproc_dependency="src/usbstk5505_i2c.pp" --obj_directory="src" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

src/usbstk5505_intr.obj: ../src/usbstk5505_intr.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Texas Instruments/C5500 Code Generation Tools 4.3.9/bin/cl55" -v5505 --symdebug:none -O3 --include_path="C:/Texas Instruments/C5500 Code Generation Tools 4.3.9/include" --include_path="D:/vmshare/mpas/workspace/ccs_v4/inc" --diag_warning=225 --large_memory_model --algebraic --memory_model=large --asm_source=algebraic --preproc_with_compile --preproc_dependency="src/usbstk5505_intr.pp" --obj_directory="src" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

src/usbstk5505_led.obj: ../src/usbstk5505_led.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Texas Instruments/C5500 Code Generation Tools 4.3.9/bin/cl55" -v5505 --symdebug:none -O3 --include_path="C:/Texas Instruments/C5500 Code Generation Tools 4.3.9/include" --include_path="D:/vmshare/mpas/workspace/ccs_v4/inc" --diag_warning=225 --large_memory_model --algebraic --memory_model=large --asm_source=algebraic --preproc_with_compile --preproc_dependency="src/usbstk5505_led.pp" --obj_directory="src" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

src/usbstk5505_spi.obj: ../src/usbstk5505_spi.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Texas Instruments/C5500 Code Generation Tools 4.3.9/bin/cl55" -v5505 --symdebug:none -O3 --include_path="C:/Texas Instruments/C5500 Code Generation Tools 4.3.9/include" --include_path="D:/vmshare/mpas/workspace/ccs_v4/inc" --diag_warning=225 --large_memory_model --algebraic --memory_model=large --asm_source=algebraic --preproc_with_compile --preproc_dependency="src/usbstk5505_spi.pp" --obj_directory="src" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

src/vectors.obj: ../src/vectors.asm $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Texas Instruments/C5500 Code Generation Tools 4.3.9/bin/cl55" -v5505 --symdebug:none -O3 --include_path="C:/Texas Instruments/C5500 Code Generation Tools 4.3.9/include" --include_path="D:/vmshare/mpas/workspace/ccs_v4/inc" --diag_warning=225 --large_memory_model --algebraic --memory_model=large --asm_source=algebraic --preproc_with_compile --preproc_dependency="src/vectors.pp" --obj_directory="src" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


