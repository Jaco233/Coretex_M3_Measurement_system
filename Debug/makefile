################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include WebServer/subdir.mk
-include MicroSemi_Code/hal/CortexM3/subdir.mk
-include MicroSemi_Code/hal/CortexM3/GNU/subdir.mk
-include MicroSemi_Code/drivers_config/mss_ace/subdir.mk
-include MicroSemi_Code/drivers/mss_uart/subdir.mk
-include MicroSemi_Code/drivers/mss_i2c/subdir.mk
-include MicroSemi_Code/drivers/mss_gpio/subdir.mk
-include MicroSemi_Code/drivers/mss_ethernet_mac/subdir.mk
-include MicroSemi_Code/drivers/mss_ace/subdir.mk
-include MicroSemi_Code/CMSIS/subdir.mk
-include MicroSemi_Code/CMSIS/startup_gcc/subdir.mk
-include FreeTCPIP/subdir.mk
-include FreeTCPIP/http_Common/subdir.mk
-include FreeRTOS_Source/subdir.mk
-include FreeRTOS_Source/portable/MemMang/subdir.mk
-include FreeRTOS_Source/portable/GCC/ARM_CM3/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
MEMORYMAP += \
memory-map.xml \

IHEXFILES += \
Measurement_System.hex \

SRECFILES += \
Measurement_System.srec \

LISTINGS += \
Measurement_System.lst \


# All Target
all: Measurement_System secondary-outputs

# Tool invocations
Measurement_System: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU C Linker'
	arm-none-eabi-gcc -mthumb -mcpu=cortex-m3 -specs=bare.specs -T ../MicroSemi_Code/CMSIS/startup_gcc/debug-in-actel-smartfusion-envm.ld --gc-sections -Wl,-Map=$(EXECUTABLE).map -o"Measurement_System" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

memory-map.xml: $(EXECUTABLE)
	@echo 'Invoking: Memory map generator'
	actel-map -o "memory-map.xml" $(EXECUTABLE) $(BUILDCMD)
	@echo 'Finished building: $@'
	@echo ' '

Measurement_System.hex: $(EXECUTABLE)
	@echo 'Invoking: GNU Intel Hex File Generator'
	arm-none-eabi-objcopy -O ihex $(EXECUTABLE) "Measurement_System.hex"
	@echo 'Finished building: $@'
	@echo ' '

Measurement_System.srec: $(EXECUTABLE)
	@echo 'Invoking: GNU S-Record Generator'
	arm-none-eabi-objcopy -O srec $(EXECUTABLE) "Measurement_System.srec"
	@echo 'Finished building: $@'
	@echo ' '

Measurement_System.lst: $(EXECUTABLE)
	@echo 'Invoking: GNU Listing Generator'
	arm-none-eabi-objdump -h -S $(EXECUTABLE) > "Measurement_System.lst"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean::
	-$(RM) $(MEMORYMAP)$(OBJS)$(C_DEPS)$(SRECFILES)$(IHEXFILES)$(LISTINGS)$(EXECUTABLE) Measurement_System
	-@echo ' '

secondary-outputs: $(MEMORYMAP) $(IHEXFILES) $(SRECFILES) $(LISTINGS)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
