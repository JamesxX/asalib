@echo off
echo Version tool.
set /P version="What version is being coupled? "
mkdir __%version%
mkdir __%version%\x86
@echo off
mkdir __%version%\x64
mkdir __%version%\asalib\public
mkdir __%version%\Docs

xcopy /s asalib\public __%version%\asalib\public
( type Doxyfile & echo PROJECT_NUMBER=%version% ) | doxygen.exe -
xcopy /s Docs __%version%\Docs
rmdir /S /Q Docs\


call:CopyFilexXX AbelianSquaresAnalysis.bat
call:CopyFilexXX Analysis.exe
call:CopyFilexXX asalib.dll
call:CopyFilexXX asalib.lib
call:CopyFilexXX ExampleMorphism.morph
call:CopyFilexXX Morphism.exe
call:CopyFilexXX SingleWord.exe
call:CopyFilexXX RawSquaresByBlock.exe
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