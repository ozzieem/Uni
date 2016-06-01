################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../main.c \
../lcd4.c \
../counter.c \
../delay_loop.c \
../time.c \
../io_usart.c \
../task_tc.c \
../relay.c \
../sensor_smt160.c \
../task_dice.c \
../task_ring.c \
../io_di.c \
../io_do.c \
../help_functions.c


PREPROCESSING_SRCS +=  \
../wait_milliseconds.s


ASM_SRCS += 


OBJS +=  \
main.o \
wait_milliseconds.o \
lcd4.o \
counter.o \
delay_loop.o \
time.o \
io_usart.o \
task_tc.o \
relay.o \
sensor_smt160.o \
task_dice.o \
task_ring.o \
io_di.o \
io_do.o \
help_functions.o

OBJS_AS_ARGS +=  \
main.o \
wait_milliseconds.o \
lcd4.o \
counter.o \
delay_loop.o \
time.o \
io_usart.o \
task_tc.o \
relay.o \
sensor_smt160.o \
task_dice.o \
task_ring.o \
io_di.o \
io_do.o \
help_functions.o

C_DEPS +=  \
main.d \
wait_milliseconds.d \
lcd4.d \
counter.d \
delay_loop.d \
time.d \
io_usart.d \
task_tc.d \
relay.d \
sensor_smt160.d \
task_dice.d \
task_ring.d \
io_di.d \
io_do.d \
help_functions.d

C_DEPS_AS_ARGS +=  \
main.d \
wait_milliseconds.d \
lcd4.d \
counter.d \
delay_loop.d \
time.d \
io_usart.d \
task_tc.d \
relay.d \
sensor_smt160.d \
task_dice.d \
task_ring.d \
io_di.d \
io_do.d \
help_functions.d

OUTPUT_FILE_PATH +=main.elf

OUTPUT_FILE_PATH_AS_ARGS +=main.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

# AVR32/GNU C Compiler





























./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 3.4.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.1002\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -DF_CPU=8000000UL  -Os -ffunction-sections -fdata-sections -Wall -mmcu=atmega32 -c -gdwarf-2 -fsigned-char -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<"
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler
./wait_milliseconds.o: .././wait_milliseconds.s
	@echo Building file: $<
	@echo Invoking: AVR32/GNU Assembler : 3.4.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.1002\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -Wa,-gdwarf2 -x assembler-with-cpp -c -mmcu=atmega32 -Wall -gdwarf-2      -DF_CPU=8000000UL -Os -fsigned-char -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<"
	@echo Finished building: $<
	


./%.o: .././%.s
	@echo Building file: $<
	@echo Invoking: AVR32/GNU Assembler : 3.4.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.1002\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -Wa,-gdwarf2 -x assembler-with-cpp -c -mmcu=atmega32 -Wall -gdwarf-2      -DF_CPU=8000000UL -Os -fsigned-char -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<"
	@echo Finished building: $<
	




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 3.4.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.1002\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="main.map" -Wl,--start-group  -Wl,--end-group -Wl,--gc-sections -mmcu=atmega32 
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.1002\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  "main.elf" "main.hex"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.1002\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "main.elf" "main.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.1002\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "main.elf" > "main.lss"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.1002\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature  "main.elf" "main.srec"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.1002\avr8-gnu-toolchain\bin\avr-size.exe" "main.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "main.elf" "main.a" "main.hex" "main.lss" "main.eep" "main.map" "main.srec"
	