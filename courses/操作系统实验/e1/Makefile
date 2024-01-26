obj-m:=my_mh.o
my_mh-objs:=mhn.o
KDIR:=/lib/modules/$(shell uname -r)/build
PWD:=$(shell pwd)
default:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean
CONFIG_MODULE_SIG=n