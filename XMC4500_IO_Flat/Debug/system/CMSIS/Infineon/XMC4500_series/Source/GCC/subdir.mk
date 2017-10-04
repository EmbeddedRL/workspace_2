################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
../system/CMSIS/Infineon/XMC4500_series/Source/GCC/startup_XMC4500.asm 

OBJS += \
./system/CMSIS/Infineon/XMC4500_series/Source/GCC/startup_XMC4500.o 

ASM_DEPS += \
./system/CMSIS/Infineon/XMC4500_series/Source/GCC/startup_XMC4500.d 


# Each subdirectory must supply rules for building sources it contributes
system/CMSIS/Infineon/XMC4500_series/Source/GCC/%.o: ../system/CMSIS/Infineon/XMC4500_series/Source/GCC/%.asm
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -x assembler-with-cpp -I"D:\Software\workspace_2\XMC4500_IO_Flat\system\CMSIS\Infineon\Include" -DUC_ID=4503 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


