################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../board/board.c \
../board/clock_config.c \
../board/peripherals.c \
../board/pin_mux.c 

C_DEPS += \
./board/board.d \
./board/clock_config.d \
./board/peripherals.d \
./board/pin_mux.d 

OBJS += \
./board/board.o \
./board/clock_config.o \
./board/peripherals.o \
./board/pin_mux.o 


# Each subdirectory must supply rules for building sources it contributes
board/%.o: ../board/%.c board/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKE16Z64VLF4 -DCPU_MKE16Z64VLF4_cm0plus -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\nguye\Documents\MCUXpressoIDE_11.9.1_2170\workspace\MKE16Z4_Project\board" -I"C:\Users\nguye\Documents\MCUXpressoIDE_11.9.1_2170\workspace\MKE16Z4_Project\source" -I"C:\Users\nguye\Documents\MCUXpressoIDE_11.9.1_2170\workspace\MKE16Z4_Project\drivers" -I"C:\Users\nguye\Documents\MCUXpressoIDE_11.9.1_2170\workspace\MKE16Z4_Project\device" -I"C:\Users\nguye\Documents\MCUXpressoIDE_11.9.1_2170\workspace\MKE16Z4_Project\CMSIS" -I"C:\Users\nguye\Documents\MCUXpressoIDE_11.9.1_2170\workspace\MKE16Z4_Project\component\uart" -I"C:\Users\nguye\Documents\MCUXpressoIDE_11.9.1_2170\workspace\MKE16Z4_Project\component\serial_manager" -I"C:\Users\nguye\Documents\MCUXpressoIDE_11.9.1_2170\workspace\MKE16Z4_Project\utilities" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-board

clean-board:
	-$(RM) ./board/board.d ./board/board.o ./board/clock_config.d ./board/clock_config.o ./board/peripherals.d ./board/peripherals.o ./board/pin_mux.d ./board/pin_mux.o

.PHONY: clean-board

