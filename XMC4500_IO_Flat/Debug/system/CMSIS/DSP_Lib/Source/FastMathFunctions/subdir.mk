################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_cos_f32.c \
../system/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_cos_q15.c \
../system/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_cos_q31.c \
../system/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sin_f32.c \
../system/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sin_q15.c \
../system/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sin_q31.c \
../system/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sqrt_q15.c \
../system/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sqrt_q31.c 

OBJS += \
./system/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_cos_f32.o \
./system/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_cos_q15.o \
./system/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_cos_q31.o \
./system/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sin_f32.o \
./system/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sin_q15.o \
./system/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sin_q31.o \
./system/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sqrt_q15.o \
./system/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sqrt_q31.o 

C_DEPS += \
./system/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_cos_f32.d \
./system/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_cos_q15.d \
./system/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_cos_q31.d \
./system/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sin_f32.d \
./system/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sin_q15.d \
./system/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sin_q31.d \
./system/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sqrt_q15.d \
./system/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sqrt_q31.d 


# Each subdirectory must supply rules for building sources it contributes
system/CMSIS/DSP_Lib/Source/FastMathFunctions/%.o: ../system/CMSIS/DSP_Lib/Source/FastMathFunctions/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DARM_MATH_CM4 -I"/home/horauer/workspace/io_simplistic/system/CMSIS/Include" -I"/home/horauer/workspace/io_simplistic/system" -I"/home/horauer/workspace/io_simplistic/system/CMSIS/DSP_Lib/Examples_M4/arm_signal_converge_example/Common/Include" -I"/home/horauer/workspace/io_simplistic/system/CMSIS/Infineon/Include" -I"/home/horauer/workspace/io_simplistic/system/CMSIS/Infineon/XMC4500_series/Include" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


