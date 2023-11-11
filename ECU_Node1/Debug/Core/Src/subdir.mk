################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/FPEC_program.c \
../Core/Src/GPIO_program.c \
../Core/Src/Parse.c \
../Core/Src/RCC_program.c \
../Core/Src/SYSTICK_program.c \
../Core/Src/UART_program.c \
../Core/Src/main.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c 

OBJS += \
./Core/Src/FPEC_program.o \
./Core/Src/GPIO_program.o \
./Core/Src/Parse.o \
./Core/Src/RCC_program.o \
./Core/Src/SYSTICK_program.o \
./Core/Src/UART_program.o \
./Core/Src/main.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o 

C_DEPS += \
./Core/Src/FPEC_program.d \
./Core/Src/GPIO_program.d \
./Core/Src/Parse.d \
./Core/Src/RCC_program.d \
./Core/Src/SYSTICK_program.d \
./Core/Src/UART_program.d \
./Core/Src/main.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/FPEC_program.cyclo ./Core/Src/FPEC_program.d ./Core/Src/FPEC_program.o ./Core/Src/FPEC_program.su ./Core/Src/GPIO_program.cyclo ./Core/Src/GPIO_program.d ./Core/Src/GPIO_program.o ./Core/Src/GPIO_program.su ./Core/Src/Parse.cyclo ./Core/Src/Parse.d ./Core/Src/Parse.o ./Core/Src/Parse.su ./Core/Src/RCC_program.cyclo ./Core/Src/RCC_program.d ./Core/Src/RCC_program.o ./Core/Src/RCC_program.su ./Core/Src/SYSTICK_program.cyclo ./Core/Src/SYSTICK_program.d ./Core/Src/SYSTICK_program.o ./Core/Src/SYSTICK_program.su ./Core/Src/UART_program.cyclo ./Core/Src/UART_program.d ./Core/Src/UART_program.o ./Core/Src/UART_program.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32f1xx_hal_msp.cyclo ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.cyclo ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.cyclo ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su

.PHONY: clean-Core-2f-Src

