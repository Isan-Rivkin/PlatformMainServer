################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/HandlerManager.cpp \
../src/Listener.cpp \
../src/MainController.cpp \
../src/PlatformMainServer.cpp \
../src/User.cpp 

OBJS += \
./src/HandlerManager.o \
./src/Listener.o \
./src/MainController.o \
./src/PlatformMainServer.o \
./src/User.o 

CPP_DEPS += \
./src/HandlerManager.d \
./src/Listener.d \
./src/MainController.d \
./src/PlatformMainServer.d \
./src/User.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/user/Desktop/eclipse_ws_eliav/lab32/Utils/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


