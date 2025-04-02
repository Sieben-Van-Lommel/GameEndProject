@echo off
c:\gbdk\bin\lcc -c -o characterController.o characterController.c
c:\gbdk\bin\lcc -c -o main.o main.c
c:\gbdk\bin\lcc -o main.gb main.o characterController.o
pause
