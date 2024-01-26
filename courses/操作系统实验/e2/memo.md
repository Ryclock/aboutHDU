## pre
```bash
wget https://cdn.kernel.org/pub/linux/kernel/v5.x/linux-5.4.260.tar.xz
sudo tar -xvf linux-5.4.260.tar.xz
mv linux-5.4.260 /usr/src/
cd /usr/src/linux-5.4.260/
apt-get install libncurses5-dev bison flex libssl-dev libelf-dev dwarves
```

## add syscall
```bash
vi arch/x86/entry/syscalls/syscall_64.tbl
vi include/linux/syscalls.h
vi kernel/sys.c
vi ~/test.c
```

## check
```bash
df -h # disk space must be greater than 30G
```

## make && install
```bash
make mrproper
make menuconfig
scripts/config --disable SYSTEM_TRUSTED_KEYS
nohup make -j8 1>/tmp/log.make.$(date +%s) 2>&1 &
nohup make -j8 modules 1>/tmp/log.make_modules.$(date +%s) 2>&1 &
nohup make modules_install 1>/tmp/log.make_modules_install.$(date +%s) 2>&1 &
nohup make install 1>/tmp/log.make_install.$(date +%s) 2>&1 &
```

## update && reboot
```bash
update-grub2
reboot
```

## result
```bash
gcc -o test.o test.c
./test.o
dmesg
```