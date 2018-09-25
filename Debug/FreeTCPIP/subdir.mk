################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeTCPIP/psock.c \
../FreeTCPIP/timer.c \
../FreeTCPIP/uip.c \
../FreeTCPIP/uip_arp.c 

OBJS += \
./FreeTCPIP/psock.o \
./FreeTCPIP/timer.o \
./FreeTCPIP/uip.o \
./FreeTCPIP/uip_arp.o 

C_DEPS += \
./FreeTCPIP/psock.d \
./FreeTCPIP/timer.d \
./FreeTCPIP/uip.d \
./FreeTCPIP/uip_arp.d 


# Each subdirectory must supply rules for building sources it contributes
FreeTCPIP/%.o: ../FreeTCPIP/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU C Compiler'
	arm-none-eabi-gcc -mthumb -mcpu=cortex-m3 -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\FreeTCPIP\net" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\MicroSemi_Code\drivers\mss_ace" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\MicroSemi_Code\drivers_config\mss_ace" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\MicroSemi_Code\drivers\mss_timer" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\MicroSemi_Code\drivers\mss_ethernet_mac" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\MicroSemi_Code\drivers\I2C" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\FreeTCPIP\apps\httpd" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\WebServer" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\FreeTCPIP" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\FreeRTOS_Source\include" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\FreeRTOS_Source\portable\GCC\ARM_CM3" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\MicroSemi_Code\drivers\mss_gpio" -O0 -g3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


