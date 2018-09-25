################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS_Source/list.c \
../FreeRTOS_Source/queue.c \
../FreeRTOS_Source/tasks.c \
../FreeRTOS_Source/timers.c 

OBJS += \
./FreeRTOS_Source/list.o \
./FreeRTOS_Source/queue.o \
./FreeRTOS_Source/tasks.o \
./FreeRTOS_Source/timers.o 

C_DEPS += \
./FreeRTOS_Source/list.d \
./FreeRTOS_Source/queue.d \
./FreeRTOS_Source/tasks.d \
./FreeRTOS_Source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS_Source/%.o: ../FreeRTOS_Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU C Compiler'
	arm-none-eabi-gcc -mthumb -mcpu=cortex-m3 -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\FreeTCPIP\net" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\MicroSemi_Code\drivers\mss_ace" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\MicroSemi_Code\drivers_config\mss_ace" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\MicroSemi_Code\drivers\mss_timer" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\MicroSemi_Code\drivers\mss_ethernet_mac" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\MicroSemi_Code\drivers\I2C" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\FreeTCPIP\apps\httpd" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\WebServer" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\FreeTCPIP" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\FreeRTOS_Source\include" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\FreeRTOS_Source\portable\GCC\ARM_CM3" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\MicroSemi_Code\drivers\mss_gpio" -O0 -g3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


