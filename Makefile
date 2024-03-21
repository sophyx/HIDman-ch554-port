#BOARD_TYPE = BOARD_AXP
BOARD_TYPE = BOARD_MINI
#BOARD_TYPE = BOARD_MICRO

BOARD_OPTIONS = OPT_DEFAULT
#BOARD_OPTIONS = OPT_SWAP_KBD_MSC

CC = sdcc
OBJCOPY = sdobjcopy
PACK_HEX = packihx
WCHISP = wchisptool
OBJDIR = ./build

TARGET = hidman_ch554

OBJECTS = \
$(OBJDIR)/ch554.rel \
$(OBJDIR)/gpio.rel \
$(OBJDIR)/keyboardled.rel \
$(OBJDIR)/main.rel \
$(OBJDIR)/parsedescriptor.rel \
$(OBJDIR)/system.rel \
$(OBJDIR)/task.rel \
$(OBJDIR)/timer2.rel \
$(OBJDIR)/usbhost.rel \
$(OBJDIR)/recvbuffer.rel \
$(OBJDIR)/data.rel \
$(OBJDIR)/ps2protocol.rel \
$(OBJDIR)/ps2.rel \
$(OBJDIR)/andyalloc.rel \
$(OBJDIR)/pwm.rel \
$(OBJDIR)/mouse.rel

ifndef FREQ_SYS
FREQ_SYS = 24000000
endif

ifndef XRAM_SIZE
XRAM_SIZE = 0x0400
endif

ifndef XRAM_LOC
XRAM_LOC = 0x0000
endif

ifndef CODE_SIZE
CODE_SIZE = 0x37FF
endif

CFLAGS := -V -mmcs51 --model-large --stack-auto \
	--xram-size $(XRAM_SIZE) --xram-loc $(XRAM_LOC) \
	--code-size $(CODE_SIZE) \
	-I/ -DFREQ_SYS=$(FREQ_SYS) -D$(BOARD_TYPE) -D$(BOARD_OPTIONS) \
	$(EXTRA_FLAGS)

LFLAGS := $(CFLAGS)

print-%  : ; @echo $* = $($*)

$(OBJDIR)/%.rel : %.c
	$(CC) -c $(CFLAGS) -o $@ $<


$(OBJDIR)/$(TARGET).ihx: $(OBJECTS)
	$(CC) $(OBJECTS) $(LFLAGS) -o $(OBJDIR)/$(TARGET).ihx
	

$(OBJDIR)/$(TARGET).hex: $(OBJDIR)/$(TARGET).ihx
	$(PACK_HEX) $(OBJDIR)/$(TARGET).ihx > $(OBJDIR)/$(TARGET).hex

$(OBJDIR)/$(TARGET).bin: $(OBJDIR)/$(TARGET).ihx
	$(OBJCOPY) -I ihex -O binary $(OBJDIR)/$(TARGET).ihx $(OBJDIR)/$(TARGET).bin

size: $(OBJDIR)/$(TARGET).ihx
	@echo '---------- Segments ----------'
	@egrep '(ABS,CON)|(REL,CON)' $(OBJDIR)/$(TARGET).map | gawk --non-decimal-data '{dec = sprintf("%d","0x" $$2); print dec " " $$0}' | /usr/bin/sort -n -k1 | cut -f2- -d' ' | uniq
	@echo '---------- Memory ----------'
	@egrep 'available|EXTERNAL|FLASH' $(OBJDIR)/$(TARGET).mem

flash: $(OBJDIR)/$(TARGET).bin
	$(WCHISP) -f $(OBJDIR)/$(TARGET).bin -g

.DEFAULT_GOAL := all
all: $(OBJDIR)/$(TARGET).bin $(OBJDIR)/$(TARGET).hex

clean:
	rm -f $(OBJDIR)/*

test: $(OBJECTS) $(OBJDIR)/test.rel
	$(CC) build/test.rel build/parsedescriptor.rel build/andyalloc.rel build/data.rel build/uart.rel $(LFLAGS) -o $(OBJDIR)/test.ihx
	s51 build/test -s -