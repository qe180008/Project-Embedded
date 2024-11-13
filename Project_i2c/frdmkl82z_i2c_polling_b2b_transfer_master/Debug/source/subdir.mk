################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/i2c_polling_b2b_transfer_master.c \
../source/mtb.c \
../source/semihost_hardfault.c 

C_DEPS += \
./source/i2c_polling_b2b_transfer_master.d \
./source/mtb.d \
./source/semihost_hardfault.d 

OBJS += \
./source/i2c_polling_b2b_transfer_master.o \
./source/mtb.o \
./source/semihost_hardfault.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MKL82Z128VLK7 -DCPU_MKL82Z128VLK7_cm0plus -DFRDM_KL82Z -DFREEDOM -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master\source" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master\drivers" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master\device" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master\utilities" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master\component\uart" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master\component\serial_manager" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master\component\lists" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master\CMSIS" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master\board" -O0 -fno-common -g3 -gdwarf-4 -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/i2c_polling_b2b_transfer_master.d ./source/i2c_polling_b2b_transfer_master.o ./source/mtb.d ./source/mtb.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o

.PHONY: clean-source

