@echo off
setlocal EnableDelayedExpansion

if exist proyecto.exe del /f /q proyecto.exe

set files=

for /r %%f in (*.cxx) do (
    set files=!files! "%%f"
)

g++ -I src -std=c++17 -O2 -Wall !files! src\main.cpp -o proyecto.exe

if exist proyecto.exe proyecto.exe