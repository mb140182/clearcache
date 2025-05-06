#!/bin/bash
#file /home/m/Documents/src/clearcache/sandbox/ImageDir_d12x_20250326224333
#file -fi/home/m/Documents/src/clearcache/sandbox/ImageDir_d12x_20250326224333
#file -do/home/m/Documents/src/clearcache/sandbox/obrazec
#file -dc/home/m/Documents/src/clearcache/sandbox/cache
#gdb "./main.exe -fi/home/m/Documents/src/clearcache/sandbox/ImageDir_d12x_20250326224333 file -do/home/m/Documents/src/clearcache/sandbox/obrazec"


cp ./main.exe ./sandbox/cache
cp ./main.o ./sandbox/cache
cp ./ClC.o ./sandbox/cache


gdb --args ./main.exe\
  -dc$HOME/Documents/src/clearcache/sandbox/cache\
  -do$HOME/Documents/src/clearcache/sandbox/ImageDir_d12x_20250326224333
  #-do$HOME/Documents/src/clearcache/sandbox/obrazec

