################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/SpaceX/STM32Cube_FW_U0_V1.2.0/Projects/STM32U083HCY6/USBX/App/app_usbx_device.c \
C:/SpaceX/STM32Cube_FW_U0_V1.2.0/Projects/STM32U083HCY6/USBX/App/ux_device_descriptors.c \
C:/SpaceX/STM32Cube_FW_U0_V1.2.0/Projects/STM32U083HCY6/USBX/App/ux_device_keyboard.c 

OBJS += \
./Application/User/USBX/App/app_usbx_device.o \
./Application/User/USBX/App/ux_device_descriptors.o \
./Application/User/USBX/App/ux_device_keyboard.o 

C_DEPS += \
./Application/User/USBX/App/app_usbx_device.d \
./Application/User/USBX/App/ux_device_descriptors.d \
./Application/User/USBX/App/ux_device_keyboard.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/USBX/App/app_usbx_device.o: C:/SpaceX/STM32Cube_FW_U0_V1.2.0/Projects/STM32U083HCY6/USBX/App/app_usbx_device.c Application/User/USBX/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U083xx -DUX_INCLUDE_USER_DEFINE_FILE -c -I../../Core/Inc -I../../Drivers/STM32U0xx_HAL_Driver/Inc -I../../Drivers/STM32U0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32U0xx/Include -I../../Drivers/CMSIS/Include -I../../USBX/App -I../../USBX/Target -I../../Middlewares/ST/usbx/common/core/inc -I../../Middlewares/ST/usbx/ports/generic/inc -I../../Middlewares/ST/usbx/common/usbx_stm32_device_controllers -I../../Middlewares/ST/usbx/common/usbx_device_classes/inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/USBX/App/ux_device_descriptors.o: C:/SpaceX/STM32Cube_FW_U0_V1.2.0/Projects/STM32U083HCY6/USBX/App/ux_device_descriptors.c Application/User/USBX/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U083xx -DUX_INCLUDE_USER_DEFINE_FILE -c -I../../Core/Inc -I../../Drivers/STM32U0xx_HAL_Driver/Inc -I../../Drivers/STM32U0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32U0xx/Include -I../../Drivers/CMSIS/Include -I../../USBX/App -I../../USBX/Target -I../../Middlewares/ST/usbx/common/core/inc -I../../Middlewares/ST/usbx/ports/generic/inc -I../../Middlewares/ST/usbx/common/usbx_stm32_device_controllers -I../../Middlewares/ST/usbx/common/usbx_device_classes/inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/USBX/App/ux_device_keyboard.o: C:/SpaceX/STM32Cube_FW_U0_V1.2.0/Projects/STM32U083HCY6/USBX/App/ux_device_keyboard.c Application/User/USBX/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U083xx -DUX_INCLUDE_USER_DEFINE_FILE -c -I../../Core/Inc -I../../Drivers/STM32U0xx_HAL_Driver/Inc -I../../Drivers/STM32U0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32U0xx/Include -I../../Drivers/CMSIS/Include -I../../USBX/App -I../../USBX/Target -I../../Middlewares/ST/usbx/common/core/inc -I../../Middlewares/ST/usbx/ports/generic/inc -I../../Middlewares/ST/usbx/common/usbx_stm32_device_controllers -I../../Middlewares/ST/usbx/common/usbx_device_classes/inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Application-2f-User-2f-USBX-2f-App

clean-Application-2f-User-2f-USBX-2f-App:
	-$(RM) ./Application/User/USBX/App/app_usbx_device.cyclo ./Application/User/USBX/App/app_usbx_device.d ./Application/User/USBX/App/app_usbx_device.o ./Application/User/USBX/App/app_usbx_device.su ./Application/User/USBX/App/ux_device_descriptors.cyclo ./Application/User/USBX/App/ux_device_descriptors.d ./Application/User/USBX/App/ux_device_descriptors.o ./Application/User/USBX/App/ux_device_descriptors.su ./Application/User/USBX/App/ux_device_keyboard.cyclo ./Application/User/USBX/App/ux_device_keyboard.d ./Application/User/USBX/App/ux_device_keyboard.o ./Application/User/USBX/App/ux_device_keyboard.su

.PHONY: clean-Application-2f-User-2f-USBX-2f-App

