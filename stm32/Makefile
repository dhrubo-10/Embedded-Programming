TARGET  = blink
CC      = arm-none-eabi-gcc
AS      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
FLASH   = st-flash

CPU     = -mcpu=cortex-m3 -mthumb
CFLAGS  = $(CPU) -O2 -Wall -ffreestanding -nostdlib
LDFLAGS = $(CPU) -T linker.ld -nostdlib

SRCS    = startup.s main.c
OBJS    = startup.o main.o

all: $(TARGET).bin

startup.o: startup.s
	$(AS) $(CPU) -c $< -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).elf: $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

flash: $(TARGET).bin
	$(FLASH) write $(TARGET).bin 0x08000000

clean:
	rm -f *.o *.elf *.bin