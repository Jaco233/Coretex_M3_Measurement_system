################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MicroSemi_Code/hal/CortexM3/cortex_nvic.c 

OBJS += \
./MicroSemi_Code/hal/CortexM3/cortex_nvic.o 

C_DEPS += \
./MicroSemi_Code/hal/CortexM3/cortex_nvic.d 


# Each subdirectory must supply rules for building sources it contributes
MicroSemi_Code/hal/CortexM3/%.o: ../MicroSemi_Code/hal/CortexM3/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU C Compiler'
	arm-none-eabi-gcc -mthumb -mcpu=cortex-m3 -DACTEL_STDIO_THRU_UART -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\FreeTCPIP\net" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\MicroSemi_Code\drivers\mss_ace" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\MicroSemi_Code\drivers_config\mss_ace" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\MicroSemi_Code\drivers\mss_timer" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\MicroSemi_Code\drivers\mss_ethernet_mac" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\FreeTCPIP\apps\httpd" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\WebServer" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\FreeTCPIP" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\FreeRTOS_Source\include" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\FreeRTOS_Source\portable\GCC\ARM_CM3" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\MicroSemi_Code\drivers\mss_gpio" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\MicroSemi_Code\drivers\mss_uart" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\MicroSemi_Code\hal" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\MicroSemi_Code\hal\CortexM3" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\MicroSemi_Code\hal\CortexM3\GNU" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\MicroSemi_Code\CMSIS" -I"C:\Users\Jaco\Desktop\Skripsie\FreeRTOS\New\FreeRTOSv10.1.1\FreeRTOS\Demo\CORTEX_A2F200_SoftConsole\MicroSemi_Code\CMSIS\startup_gcc" -O0 -g3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


