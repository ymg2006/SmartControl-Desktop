@echo off
setlocal
if exist out\build\debug rmdir /s /q out\build\debug
if exist build rmdir /s /q build
cmake --preset Qt-Debug
cmake --build out/build/debug --verbose
