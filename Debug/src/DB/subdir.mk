################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DB/AbstractDB.cpp \
../src/DB/BasicDB.cpp \
../src/DB/Entity.cpp 

OBJS += \
./src/DB/AbstractDB.o \
./src/DB/BasicDB.o \
./src/DB/Entity.o 

CPP_DEPS += \
./src/DB/AbstractDB.d \
./src/DB/BasicDB.d \
./src/DB/Entity.d 


# Each subdirectory must supply rules for building sources it contributes
src/DB/%.o: ../src/DB/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/user/Desktop/eclipse_ws_eliav/lab32/Utils/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


