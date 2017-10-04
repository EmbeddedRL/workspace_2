################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/CMSIS/Infineon/XMC4500_series/Source/System_XMC4500.c 

OBJS += \
./system/CMSIS/Infineon/XMC4500_series/Source/System_XMC4500.o 

C_DEPS += \
./system/CMSIS/Infineon/XMC4500_series/Source/System_XMC4500.d 


# Each subdirectory must supply rules for building sources it contributes
system/CMSIS/Infineon/XMC4500_series/Source/%.o: ../system/CMSIS/Infineon/XMC4500_series/Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DARM_MATH_CM4 -I"D:\Software\workspace_2\XMC4500_IO_Flat\system\CMSIS\Include" -I"D:\Software\workspace_2\XMC4500_IO_Flat\system" -I"D:\Software\workspace_2\XMC4500_IO_Flat\system\CMSIS\Infineon\Include" -I"D:\Software\workspace_2\XMC4500_IO_Flat\system\CMSIS\Infineon\XMC4500_series\Include" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


