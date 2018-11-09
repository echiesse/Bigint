@echo off
rem Opção de build com o Visual C++:
rem Visual C++ 19.00.23506 (Visual Studio 2015)
rem Built originally on Windows 10
cl test.cpp /EHsc

rem Opção de build com MinGW
rem g++ (GCC) 4.9.3
rem g++ -std=c++14 test.cpp -o test_gcc.exe
