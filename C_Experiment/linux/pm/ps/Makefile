
obj-m:=ps_exp.o

KDIR:=/lib/modules/$(shell uname -r)/build
PWD:=$(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	@rm -f Module.symvers ps_app

