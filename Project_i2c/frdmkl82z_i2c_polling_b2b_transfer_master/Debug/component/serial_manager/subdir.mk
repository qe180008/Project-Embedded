################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../component/serial_manager/serial_manager.c \
../component/serial_manager/serial_port_uart.c 

C_DEPS += \
./component/serial_manager/serial_manager.d \
./component/serial_manager/serial_port_uart.d 

OBJS += \
./component/serial_manager/serial_manager.o \
./component/serial_manager/serial_port_uart.o 


# Each subdirectory must supply rules for building sources it contributes
component/serial_manager/%.o: ../component/serial_manager/%.c component/serial_manager/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MKL82Z128VLK7 -DCPU_MKL82Z128VLK7_cm0plus -DFRDM_KL82Z -DFREEDOM -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master\source" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master\drivers" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master\device" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master\utilities" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master\component\uart" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master\component\serial_manager" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master\component\lists" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master\CMSIS" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master\board" -O0 -fno-common -g3 -gdwarf-4 -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-component-2f-serial_manager

clean-component-2f-serial_manager:
	-$(RM) ./component/serial_manager/serial_manager.d ./component/serial_manager/serial_manager.o ./component/serial_manager/serial_port_uart.d ./component/serial_manager/serial_port_uart.o

.PHONY: clean-component-2f-serial_manager

