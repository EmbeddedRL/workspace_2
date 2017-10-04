################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/CMSIS/Infineon/Lib/System_LibcStubs.c 

O_SRCS += \
../system/CMSIS/Infineon/Lib/System_LibcStubs.o 

OBJS += \
./system/CMSIS/Infineon/Lib/System_LibcStubs.o 

C_DEPS += \
./system/CMSIS/Infineon/Lib/System_LibcStubs.d 


# Each subdirectory must supply rules for building sources it contributes
system/CMSIS/Infineon/Lib/%.o: ../system/CMSIS/Infineon/Lib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DARM_MATH_CM4 -I"D:\Software\workspace_2\XMC4500_IO_Flat\system\CMSIS\Include" -I"D:\Software\workspace_2\XMC4500_IO_Flat\system" -I"D:\Software\workspace_2\XMC4500_IO_Flat\system\CMSIS\Infineon\Include" -I"D:\Software\workspace_2\XMC4500_IO_Flat\system\CMSIS\Infineon\XMC4500_series\Include" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


