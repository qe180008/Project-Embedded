################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../board/board.c \
../board/clock_config.c \
../board/pin_mux.c 

C_DEPS += \
./board/board.d \
./board/clock_config.d \
./board/pin_mux.d 

OBJS += \
./board/board.o \
./board/clock_config.o \
./board/pin_mux.o 


# Each subdirectory must supply rules for building sources it contributes
board/%.o: ../board/%.c board/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MKL82Z128VLK7 -DCPU_MKL82Z128VLK7_cm0plus -DFRDM_KL82Z -DFREEDOM -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master\source" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master\drivers" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master\device" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master\utilities" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master\component\uart" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master\component\serial_manager" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master\component\lists" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master\CMSIS" -I"C:\Users\trieu\Desktop\lap_trinh_nhung\frdmkl82z_i2c_polling_b2b_transfer_master\frdmkl82z_i2c_polling_b2b_transfer_master\board" -O0 -fno-common -g3 -gdwarf-4 -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-board

clean-board:
	-$(RM) ./board/board.d ./board/board.o ./board/clock_config.d ./board/clock_config.o ./board/pin_mux.d ./board/pin_mux.o

.PHONY: clean-board

