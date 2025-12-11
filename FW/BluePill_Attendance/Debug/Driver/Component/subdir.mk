################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/Component/gpio.c \
../Driver/Component/i2c.c \
../Driver/Component/spi.c 

OBJS += \
./Driver/Component/gpio.o \
./Driver/Component/i2c.o \
./Driver/Component/spi.o 

C_DEPS += \
./Driver/Component/gpio.d \
./Driver/Component/i2c.d \
./Driver/Component/spi.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/Component/%.o: ../Driver/Component/%.c Driver/Component/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"C:/Users/ADMIN/STM32CubeIDE/workspace_1.7.0/BluePill_Attendance/Driver/Component" -I"C:/Users/ADMIN/STM32CubeIDE/workspace_1.7.0/BluePill_Attendance/Driver/Device" -I"C:/Users/ADMIN/STM32CubeIDE/workspace_1.7.0/BluePill_Attendance/App" -I"C:/Users/ADMIN/STM32CubeIDE/workspace_1.7.0/BluePill_Attendance/BSP" -I"C:/Users/ADMIN/STM32CubeIDE/workspace_1.7.0/BluePill_Attendance/Common" -I"C:/Users/ADMIN/STM32CubeIDE/workspace_1.7.0/BluePill_Attendance/Driver" -I"C:/Users/ADMIN/STM32CubeIDE/workspace_1.7.0/BluePill_Attendance/MiddleWare" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

