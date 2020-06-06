@echo off
move CMakeLists.txt cmake
cd cmake

cmake -G "MinGW Makefiles" .
mingw32-make -j6
move CMakeLists.txt ..
pause
