################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/SpaceX/STM32Cube_FW_U0_V1.2.0/Projects/STM32U083HCY6/Core/Src/system_stm32u0xx.c 

OBJS += \
./Drivers/CMSIS/system_stm32u0xx.o 

C_DEPS += \
./Drivers/CMSIS/system_stm32u0xx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/system_stm32u0xx.o: C:/SpaceX/STM32Cube_FW_U0_V1.2.0/Projects/STM32U083HCY6/Core/Src/system_stm32u0xx.c Drivers/CMSIS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DUSE_HAL_DRIVER -DSTM32U083xx -DUX_INCLUDE_USER_DEFINE_FILE -c -I../../Core/Inc -I../../Drivers/STM32U0xx_HAL_Driver/Inc -I../../Drivers/STM32U0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32U0xx/Include -I../../Drivers/CMSIS/Include -I../../USBX/App -I../../USBX/Target -I../../Middlewares/ST/usbx/common/core/inc -I../../Middlewares/ST/usbx/ports/generic/inc -I../../Middlewares/ST/usbx/common/usbx_stm32_device_controllers -I../../Middlewares/ST/usbx/common/usbx_device_classes/inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS

clean-Drivers-2f-CMSIS:
	-$(RM) ./Drivers/CMSIS/system_stm32u0xx.cyclo ./Drivers/CMSIS/system_stm32u0xx.d ./Drivers/CMSIS/system_stm32u0xx.o ./Drivers/CMSIS/system_stm32u0xx.su

.PHONY: clean-Drivers-2f-CMSIS

