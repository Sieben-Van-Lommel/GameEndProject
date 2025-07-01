@echo off
:: main compileren
c:\gbdk\bin\lcc -c -o main.o main.c
::charactercontroller compileren
c:\gbdk\bin\lcc -c -o characterController.o characterController.c
::alles
c:\gbdk\bin\lcc -o main.gb main.o characterController.o
pause
