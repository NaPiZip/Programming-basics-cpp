cd build
del * /Q /S
rd . /S /Q
cmake .. -G "Visual Studio 16 2019"
pause -1
