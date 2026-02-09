@echo off

mkdir _build\haxe
swig.exe -xml -xmllite -c++ -o _build/haxe/steel.xml steel.i
haxe --run HaxeWrapperBuilder
del _build\haxe\steel.xml
