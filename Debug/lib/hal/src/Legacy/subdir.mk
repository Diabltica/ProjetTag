################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/hal/src/Legacy/stm32f1xx_hal_can.c 

OBJS += \
./lib/hal/src/Legacy/stm32f1xx_hal_can.o 

C_DEPS += \
./lib/hal/src/Legacy/stm32f1xx_hal_can.d 


# Each subdirectory must supply rules for building sources it contributes
lib/hal/src/Legacy/%.o: ../lib/hal/src/Legacy/%.c lib/hal/src/Legacy/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32F1 -DNUCLEO_F103RB -DSTM32F103RBTx -DSTM32 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../lib/hal/inc -I../lib/bsp -I../lib/CMSIS/core -I../lib/CMSIS/device -I../appli -O0 -ffunction-sections -fdata-sections -Wall -Wextra -Wconversion -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
