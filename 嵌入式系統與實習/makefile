CROSS_PATH = /cygdrive/c/Andestech/AndeSight201MCU/toolchains/nds32le-elf-mculib-v3m/bin
CROSS_COMPILE = $(CROSS_PATH)/nds32le-elf-gcc
CFLAGS = -c -g
LDFLAGS = -mvh -mcpu=n801 -mcmodel=medium -g
SRCS = hello.c message.c
OBJS = $(SRCS:.c=.o)

hello.adx : $(OBJS)
	$(CROSS_COMPILE) $(LDFLAGS) $^ -o $@
hello.o : hello.c
	$(CROSS_COMPILE) $(CFLAGS) $^ -o $@
message.o : message.c
	$(CROSS_COMPILE) $(CFLAGS) $< -o $@