################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../keyb/src/array_exec.cpp \
../keyb/src/matrix.cpp \
../keyb/src/sender.cpp 

OBJS += \
./keyb/src/array_exec.o \
./keyb/src/matrix.o \
./keyb/src/sender.o 

CPP_DEPS += \
./keyb/src/array_exec.d \
./keyb/src/matrix.d \
./keyb/src/sender.d 


# Each subdirectory must supply rules for building sources it contributes
keyb/src/%.o: ../keyb/src/%.cpp keyb/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra -g3 -DDEBUG -DUSE_FULL_ASSERT -DSTM32F103xB -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"D:\Projects\EclipceWorkspace\bt_keyboard\keyb\inc" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1-hal" -std=gnu++20 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


