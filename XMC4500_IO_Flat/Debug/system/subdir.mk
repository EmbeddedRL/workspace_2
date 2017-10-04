################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/XMC4500_startup.c 

OBJS += \
./system/XMC4500_startup.o 

C_DEPS += \
./system/XMC4500_startup.d 


# Each subdirectory must supply rules for building sources it contributes
system/%.o: ../system/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DARM_MATH_CM4 -I"/home/horauer/workspace/XMC4500_IO_Flat/system/CMSIS/Include" -I"/home/horauer/workspace/XMC4500_IO_Flat/system" -I"/home/horauer/workspace/XMC4500_IO_Flat/system/CMSIS/Infineon/Include" -I"/home/horauer/workspace/XMC4500_IO_Flat/system/CMSIS/Infineon/XMC4500_series/Include" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


