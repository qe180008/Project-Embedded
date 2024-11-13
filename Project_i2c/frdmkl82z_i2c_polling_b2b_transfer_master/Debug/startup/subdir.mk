################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../startup/startup_mkl82z7.c 

C_DEPS += \
./startup/startup_mkl82z7.d 

OBJS += \
./startup/startup_mkl82z7.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.c startup/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MKL82Z128VLK7 -DCPU_MKL82Z128VLK7_cm0plus -DFRDM_KL82Z -DFREEDOM -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master\source" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master\drivers" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master\device" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master\utilities" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master\component\uart" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master\component\serial_manager" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master\component\lists" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master\CMSIS" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master\board" -O0 -fno-common -g3 -gdwarf-4 -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-startup

clean-startup:
	-$(RM) ./startup/startup_mkl82z7.d ./startup/startup_mkl82z7.o

.PHONY: clean-startup

