################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/Device/button.c \
../Driver/Device/eeprom.c \
../Driver/Device/esp8266.c \
../Driver/Device/lcd.c \
../Driver/Device/rfid.c 

OBJS += \
./Driver/Device/button.o \
./Driver/Device/eeprom.o \
./Driver/Device/esp8266.o \
./Driver/Device/lcd.o \
./Driver/Device/rfid.o 

C_DEPS += \
./Driver/Device/button.d \
./Driver/Device/eeprom.d \
./Driver/Device/esp8266.d \
./Driver/Device/lcd.d \
./Driver/Device/rfid.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/Device/%.o: ../Driver/Device/%.c Driver/Device/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"C:/Users/ADMIN/STM32CubeIDE/workspace_1.7.0/BluePill_Attendance/Driver/Component" -I"C:/Users/ADMIN/STM32CubeIDE/workspace_1.7.0/BluePill_Attendance/Driver/Device" -I"C:/Users/ADMIN/STM32CubeIDE/workspace_1.7.0/BluePill_Attendance/App" -I"C:/Users/ADMIN/STM32CubeIDE/workspace_1.7.0/BluePill_Attendance/BSP" -I"C:/Users/ADMIN/STM32CubeIDE/workspace_1.7.0/BluePill_Attendance/Common" -I"C:/Users/ADMIN/STM32CubeIDE/workspace_1.7.0/BluePill_Attendance/Driver" -I"C:/Users/ADMIN/STM32CubeIDE/workspace_1.7.0/BluePill_Attendance/MiddleWare" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

