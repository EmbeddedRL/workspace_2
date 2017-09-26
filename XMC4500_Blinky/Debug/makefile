################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
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
XMC4500_USIC_UART.bin \

SECONDARY_LIST += \
XMC4500_USIC_UART.lst \

SECONDARY_SIZE += \
XMC4500_USIC_UART.siz \


# All Target
all: XMC4500_USIC_UART.elf secondary-outputs

# Tool invocations
XMC4500_USIC_UART.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -T "D:\Studium_FH\2017_WS\Embedded_Systems_Software_Design\XMC4500_USIC_UART\Linker\xmc4500-1024.ld" -nostartfiles -L"D:\Studium_FH\2017_WS\Embedded_Systems_Software_Design\XMC4500_USIC_UART\Linker" -Wl,-Map,"XMC4500_USIC_UART.map" -o "XMC4500_USIC_UART.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

XMC4500_USIC_UART.bin: XMC4500_USIC_UART.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O binary "XMC4500_USIC_UART.elf"  "XMC4500_USIC_UART.bin"
	@echo 'Finished building: $@'
	@echo ' '

XMC4500_USIC_UART.lst: XMC4500_USIC_UART.elf
	@echo 'Invoking: Cross ARM GNU Create Listing'
	arm-none-eabi-objdump --source --all-headers --demangle --line-numbers --wide "XMC4500_USIC_UART.elf" > "XMC4500_USIC_UART.lst"
	@echo 'Finished building: $@'
	@echo ' '

XMC4500_USIC_UART.siz: XMC4500_USIC_UART.elf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-eabi-size --format=berkeley --totals "XMC4500_USIC_UART.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) XMC4500_USIC_UART.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
