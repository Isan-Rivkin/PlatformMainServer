################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/BusyManagerModule/BusyManager.cpp \
../src/BusyManagerModule/HighScoresLogic.cpp 

OBJS += \
./src/BusyManagerModule/BusyManager.o \
./src/BusyManagerModule/HighScoresLogic.o 

CPP_DEPS += \
./src/BusyManagerModule/BusyManager.d \
./src/BusyManagerModule/HighScoresLogic.d 


# Each subdirectory must supply rules for building sources it contributes
src/BusyManagerModule/%.o: ../src/BusyManagerModule/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/user/Desktop/eclipse_ws_eliav/lab32/Utils/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


