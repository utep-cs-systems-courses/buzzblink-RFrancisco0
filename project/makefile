COMMON_OBJECTS  =
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include


CC              = msp430-elf-gcc
AS              = msp430-elf-as
AR              = msp430-elf-ar

all: button.elf

button.elf: ${COMMON_OBJECTS} wdInterruptHandler.o p2_interrupt_handler.o buzzer.o led.o led_dim_statemachine.o switches.o main.o statemachine.a ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

statemachine.a: statemachine.o
	$(AR) crs $@ $^

load: button.elf
	mspdebug rf2500 "runing button.elf"

clean:
	rm -f *.o *.elf *.h~ *.c~ *.s~
