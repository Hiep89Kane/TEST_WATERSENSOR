################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/TEST_SENSOR/testWaterSensor.c 

OBJS += \
./Core/Src/TEST_SENSOR/testWaterSensor.o 

C_DEPS += \
./Core/Src/TEST_SENSOR/testWaterSensor.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/TEST_SENSOR/%.o Core/Src/TEST_SENSOR/%.su: ../Core/Src/TEST_SENSOR/%.c Core/Src/TEST_SENSOR/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G070xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I../Core/Src/INA219 -I../Core/Src/LCD_i2c -I../Core/Src/INIT -I../Core/Src/TEST_SENSOR -I"D:/1_NGUYEN_VAN_HIEP/25_STM32CubeIDE_Workspace/0_2H1T_Library" -I../Core/Src/PUTCHAR -I../Core/Src/CAP_SENSOR -I../Core/Src/COMMON -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-TEST_SENSOR

clean-Core-2f-Src-2f-TEST_SENSOR:
	-$(RM) ./Core/Src/TEST_SENSOR/testWaterSensor.d ./Core/Src/TEST_SENSOR/testWaterSensor.o ./Core/Src/TEST_SENSOR/testWaterSensor.su

.PHONY: clean-Core-2f-Src-2f-TEST_SENSOR

