A budget tracking application design to run on the Institute of Computer Science Operating System.

Required files:
QEMU
Installation:
```
sudo apt-get install qemu
```
Check GCC version:
```
gcc -v
```

-if running GCC Version 5.x:
```
sudo apt-get install gcc-4.9-multilib
```

Edited something in the files and want to see the changes?

GOTO ics-os folder

```
make clean
sudo make install
```

HOW TO RUN THE ICS-OS:
```
cd ics-os
```
-for 32bit systems:
```
qemu-system-i386 -fda ics-os-floppy.img
```
-for 64bit systems:
```
qemu-system-x86_64 -fda ics-os-floppy.img
```
