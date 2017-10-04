################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include system/CMSIS/Infineon/XMC4500_series/Source/GCC/subdir.mk
-include system/CMSIS/Infineon/XMC4500_series/Source/subdir.mk
-include system/CMSIS/Infineon/Lib/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
XMC4500_IO_Flat.hex \

SECONDARY_LIST += \
XMC4500_IO_Flat.lst \

SECONDARY_SIZE += \
XMC4500_IO_Flat.siz \


# All Target
all: XMC4500_IO_Flat.elf secondary-outputs

# Tool invocations
XMC4500_IO_Flat.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -T "D:\Software\workspace_2\XMC4500_IO_Flat\system\CMSIS\Infineon\XMC4500_series\Source\GCC\XMC4500.ld" -nostartfiles -L"D:\Software\workspace_2\XMC4500_IO_Flat\system" -L"D:\Software\workspace_2\XMC4500_IO_Flat\system\CMSIS\Lib\GCC" -L"D:\Software\workspace_2\XMC4500_IO_Flat\system\CMSIS\Infineon\Lib" -Wl,-Map,"XMC4500_IO_Flat.map" -o "XMC4500_IO_Flat.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

XMC4500_IO_Flat.hex: XMC4500_IO_Flat.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex "XMC4500_IO_Flat.elf"  "XMC4500_IO_Flat.hex"
	@echo 'Finished building: $@'
	@echo ' '

XMC4500_IO_Flat.lst: XMC4500_IO_Flat.elf
	@echo 'Invoking: Cross ARM GNU Create Listing'
	arm-none-eabi-objdump --source --all-headers --demangle --line-numbers --wide "XMC4500_IO_Flat.elf" > "XMC4500_IO_Flat.lst"
	@echo 'Finished building: $@'
	@echo ' '

XMC4500_IO_Flat.siz: XMC4500_IO_Flat.elf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-eabi-size --format=berkeley "XMC4500_IO_Flat.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) XMC4500_IO_Flat.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
