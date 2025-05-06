#!/bin/bash
#file /home/m/Documents/src/clearcache/sandbox/ImageDir_d12x_20250326224333
#file -fi/home/m/Documents/src/clearcache/sandbox/ImageDir_d12x_20250326224333
#file -do/home/m/Documents/src/clearcache/sandbox/obrazec
#file -dc/home/m/Documents/src/clearcache/sandbox/cache
#gdb "./main.exe -fi/home/m/Documents/src/clearcache/sandbox/ImageDir_d12x_20250326224333 file -do/home/m/Documents/src/clearcache/sandbox/obrazec"

# haltura XXX TODO peredelat
cp ./main.exe ./sandbox/apt_cache
cp ./main.o ./sandbox/apt_cache
cp ./ClC.o ./sandbox/apt_cache


#/media/es/data1/Handy_Web_Cache/deb.debian.org
#/media/es/data1/Handy_Web_Cache/security.debian.org
  #-dc$HOME/Documents/src/clearcache/sandbox/apt_cache\
  #-dc/var/cache/apt/archives\
  #-dc/media/es/data1/Handy_Web_Cache/security.debian.org\
  #-dc/media/es/data1/Handy_Web_Cache/deb.debian.org\
gdb --args ./main.exe\
  -dc/media/es/data1/Handy_Web_Cache/security.debian.org\
  -dp$HOME/Documents/src/clearcache/sandbox/apt.list

