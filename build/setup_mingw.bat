@echo off

mkdir ga1-win64
cd ga1-win64
cmake -G "MinGW Makefiles" -DVIDEO_OPENGLES=0 ../../src/engine
cd ..
