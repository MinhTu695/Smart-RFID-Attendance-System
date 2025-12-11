################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSP/bsp_button.c \
../BSP/bsp_eeprom.c \
../BSP/bsp_lcd.c \
../BSP/bsp_led.c \
../BSP/bsp_rfid.c \
../BSP/bsp_wifi.c 

OBJS += \
./BSP/bsp_button.o \
./BSP/bsp_eeprom.o \
./BSP/bsp_lcd.o \
./BSP/bsp_led.o \
./BSP/bsp_rfid.o \
./BSP/bsp_wifi.o 

C_DEPS += \
./BSP/bsp_button.d \
./BSP/bsp_eeprom.d \
./BSP/bsp_lcd.d \
./BSP/bsp_led.d \
./BSP/bsp_rfid.d \
./BSP/bsp_wifi.d 


# Each subdirectory must supply rules for building sources it contributes
BSP/%.o: ../BSP/%.c BSP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"C:/Users/ADMIN/STM32CubeIDE/workspace_1.7.0/BluePill_Attendance/Driver/Component" -I"C:/Users/ADMIN/STM32CubeIDE/workspace_1.7.0/BluePill_Attendance/Driver/Device" -I"C:/Users/ADMIN/STM32CubeIDE/workspace_1.7.0/BluePill_Attendance/App" -I"C:/Users/ADMIN/STM32CubeIDE/workspace_1.7.0/BluePill_Attendance/BSP" -I"C:/Users/ADMIN/STM32CubeIDE/workspace_1.7.0/BluePill_Attendance/Common" -I"C:/Users/ADMIN/STM32CubeIDE/workspace_1.7.0/BluePill_Attendance/Driver" -I"C:/Users/ADMIN/STM32CubeIDE/workspace_1.7.0/BluePill_Attendance/MiddleWare" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

