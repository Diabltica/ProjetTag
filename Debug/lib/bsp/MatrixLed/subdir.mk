################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../lib/bsp/MatrixLed/WS2812S_asm.s 

C_SRCS += \
../lib/bsp/MatrixLed/WS2812S.c 

OBJS += \
./lib/bsp/MatrixLed/WS2812S.o \
./lib/bsp/MatrixLed/WS2812S_asm.o 

S_DEPS += \
./lib/bsp/MatrixLed/WS2812S_asm.d 

C_DEPS += \
./lib/bsp/MatrixLed/WS2812S.d 


# Each subdirectory must supply rules for building sources it contributes
lib/bsp/MatrixLed/%.o: ../lib/bsp/MatrixLed/%.c lib/bsp/MatrixLed/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F1 -DNUCLEO_F103RB -DSTM32F103RBTx -DSTM32 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../lib/hal/inc -I../lib/bsp -I../lib/CMSIS/core -I../lib/CMSIS/device -I../appli -O0 -ffunction-sections -fdata-sections -Wall -Wextra -Wconversion -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
lib/bsp/MatrixLed/%.o: ../lib/bsp/MatrixLed/%.s lib/bsp/MatrixLed/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m3 -g3 -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@" "$<"

