@echo off

set CCFLAGS=-O2 -MTd -nologo -fp:fast -fp:except- -Gm- -GR- -EHa- -Zo -Oi -WX -W4 -wd4100 -FC -Z7 -D_CRT_SECURE_NO_WARNINGS
set CLFLAGS=-incremental:no

if not exist ..\build\ mkdir ..\build
pushd ..\build

cl %CCFLAGS% ..\code\ray.cpp /link %CLFLAGS%
popd
