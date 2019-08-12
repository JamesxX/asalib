@echo off
echo Version tool.
set /P version="What version is being coupled? "
mkdir __%version%
mkdir __%version%\x86
@echo off
mkdir __%version%\x64
mkdir __%version%\asalib2\public
mkdir __%version%\Docs

xcopy /s asalib2\public __%version%\asalib2\public
( type Doxyfile & echo PROJECT_NUMBER=%version% ) | doxygen.exe -
xcopy /s Docs __%version%\Docs
rmdir /S /Q Docs\

call:CopyFilexXX asalib2.dll
call:CopyFilexXX asalib2.lib
call:CopyFilexXX singleword2.exe
call:CopyFilexXX generateForBlocksAndLength.exe
call:CopyFilexXX rawSquareByBlock.exe
call:CopyFilexXX morphism.exe
echo.&pause&goto:eof

:CopyFilexXX
call:CopyFilex86 %~1
call:CopyFilex64 %~1
goto:eof

:CopyFilex86
copy build\Win32\Release\%~1 __%version%\x86\%~1
goto:eof

:CopyFilex64
copy build\x64\Release\%~1 __%version%\x64\%~1
goto:eof