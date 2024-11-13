################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../component/serial_manager/fsl_component_serial_manager.c \
../component/serial_manager/fsl_component_serial_port_uart.c 

C_DEPS += \
./component/serial_manager/fsl_component_serial_manager.d \
./component/serial_manager/fsl_component_serial_port_uart.d 

OBJS += \
./component/serial_manager/fsl_component_serial_manager.o \
./component/serial_manager/fsl_component_serial_port_uart.o 


# Each subdirectory must supply rules for building sources it contributes
component/serial_manager/%.o: ../component/serial_manager/%.c component/serial_manager/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKE16Z64VLF4 -DCPU_MKE16Z64VLF4_cm0plus -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\trieu\Desktop\lap_trinh_nhung\MKE16Z4_Project_PWM\MKE16Z4_Project\board" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\MKE16Z4_Project_PWM\MKE16Z4_Project\source" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\MKE16Z4_Project_PWM\MKE16Z4_Project\drivers" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\MKE16Z4_Project_PWM\MKE16Z4_Project\device" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\MKE16Z4_Project_PWM\MKE16Z4_Project\CMSIS" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\MKE16Z4_Project_PWM\MKE16Z4_Project\component\uart" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\MKE16Z4_Project_PWM\MKE16Z4_Project\component\serial_manager" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\MKE16Z4_Project_PWM\MKE16Z4_Project\utilities" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-component-2f-serial_manager

clean-component-2f-serial_manager:
	-$(RM) ./component/serial_manager/fsl_component_serial_manager.d ./component/serial_manager/fsl_component_serial_manager.o ./component/serial_manager/fsl_component_serial_port_uart.d ./component/serial_manager/fsl_component_serial_port_uart.o

.PHONY: clean-component-2f-serial_manager

