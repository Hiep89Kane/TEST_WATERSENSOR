################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/INA219/Adafruit_INA219.c 

OBJS += \
./Core/Src/INA219/Adafruit_INA219.o 

C_DEPS += \
./Core/Src/INA219/Adafruit_INA219.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/INA219/%.o Core/Src/INA219/%.su: ../Core/Src/INA219/%.c Core/Src/INA219/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G070xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I../Core/Src/INA219 -I../Core/Src/LCD_i2c -I../Core/Src/INIT -I../Core/Src/TEST_SENSOR -I"D:/1_NGUYEN_VAN_HIEP/25_STM32CubeIDE_Workspace/0_2H1T_Library" -I../Core/Src/PUTCHAR -I../Core/Src/CAP_SENSOR -I../Core/Src/COMMON -I../Core/Src/testDcMotor -I../Core/Src/FLASH -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-INA219

clean-Core-2f-Src-2f-INA219:
	-$(RM) ./Core/Src/INA219/Adafruit_INA219.d ./Core/Src/INA219/Adafruit_INA219.o ./Core/Src/INA219/Adafruit_INA219.su

.PHONY: clean-Core-2f-Src-2f-INA219

