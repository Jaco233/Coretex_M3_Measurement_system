################################################################################
# Automatically-generated file. Do not edit!
################################################################################

O_SRCS := 
C_SRCS := 
S_UPPER_SRCS := 
S_SRCS := 
OBJ_SRCS := 
MEMORYMAP := 
OBJS := 
C_DEPS := 
SRECFILES := 
IHEXFILES := 
LISTINGS := 
EXECUTABLE := 

# Every subdirectory with source files must be described here
SUBDIRS := \
. \
WebServer \
MicroSemi_Code/hal/CortexM3 \
MicroSemi_Code/hal/CortexM3/GNU \
MicroSemi_Code/drivers_config/mss_ace \
MicroSemi_Code/drivers/mss_uart \
MicroSemi_Code/drivers/mss_i2c \
MicroSemi_Code/drivers/mss_gpio \
MicroSemi_Code/drivers/mss_ethernet_mac \
MicroSemi_Code/drivers/mss_ace \
MicroSemi_Code/CMSIS \
MicroSemi_Code/CMSIS/startup_gcc \
FreeTCPIP \
FreeTCPIP/http_Common \
FreeRTOS_Source \
FreeRTOS_Source/portable/MemMang \
FreeRTOS_Source/portable/GCC/ARM_CM3 \

################################################################################
# Microsemi SoftConsole IDE Variables
################################################################################

BUILDCMD = arm-none-eabi-gcc -mthumb -mcpu=cortex-m3 -specs=bare.specs -T ../MicroSemi_Code/CMSIS/startup_gcc/debug-in-actel-smartfusion-envm.ld --gc-sections -Wl,-Map=$(EXECUTABLE).map 
SHELL := cmd.exe
EXECUTABLE := Measurement_System

# Target-specific items to be cleaned up in the top directory.
clean::
	-$(RM) $(wildcard ./*.map) 
