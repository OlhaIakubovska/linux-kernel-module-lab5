# hello1.h lives in inc/, so *.c files include it as "hello1.h"
ccflags-y += -I$(src)/inc

obj-m := hello1.o hello2.o

KDIR ?= $(HOME)/repos/linux-stable

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
