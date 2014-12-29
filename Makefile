GCC := arm-eabi-gcc
LD := arm-eabi-ld
AS := arm-eabi-as
OBJCOPY := arm-eabi-objcopy
RM := rm -f
VBA := vba

.SUFFIXES : .cpp .c .s

CFLAGS  := -mthumb-interwork -c -g -O2 -Wall -fverbose-asm -I.
SFLAGS  := -mthumb-interwork 
LDFLAGS := -T LinkScript 

OBJS := boot.o function.o func.o script.o save.o minigame.o Demo.o

all : book.gba 

clean :
	$(RM) *.o *.elf *.gba

run : all
	$(VBA) book.gba

book.gba : book.elf
	$(OBJCOPY) -v -O binary book.elf book.gba
	
book.elf : $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(GCC) $(CFLAGS) -o $@ $< 

%.o: %.s
	$(AS) $(SFLAGS) -o $@ $< 
