@echo off

set MyProgram="%~1"
set OutputFile="output.txt"

REM Защита от запуска без аргумента, задающего путь к программе
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

rem If there are not input files
%MyProgram% > %OutputFile%
fc %OutputFile% "error-argc.txt" > nul || goto err 
echo Test passed: if there are not input files

rem If there is one input file
%MyProgram% input.txt > %OutputFile%
fc %OutputFile% "error-argc.txt" > nul || goto err 
echo Test passed: if there is one input file

rem If input files are missing
%MyProgram% MissingFile1.txt MissingFile2.txt > %OutputFile%
fc "error-open.txt" %OutputFile% > nul || goto err
echo Test passed: if input files are missing

rem If first input file is missing
%MyProgram% MissingFile1.txt matrix2.txt > %OutputFile%
fc "error-open.txt" %OutputFile% > nul || goto err
echo Test passed: if first input file is missing

rem If second input file is missing
%MyProgram% matrix1.txt MissingFile2.txt > %OutputFile%
fc "error-open.txt" %OutputFile% > nul || goto err
echo Test passed: if second input file is missing

rem Result of product Matrix1 x zero matrix
%MyProgram% matrix1.txt matrix0.txt > %OutputFile%
fc "output0.txt" %OutputFile% > nul || goto err
echo Test passed: result of product Matrix1 x zero matrix

rem Result of product Matrix1 x unit matrix
%MyProgram% matrix1.txt matrixUnit.txt > %OutputFile%
fc "output1.txt" %OutputFile% > nul || goto err
echo Test passed: result of product Matrix1 x unit matrix

rem Result of product Matrix1 x Matrix2
%MyProgram% matrix1.txt matrix2.txt > %OutputFile%
fc "output12.txt" %OutputFile% > nul || goto err
echo Test passed: result of product Matrix1 x Matrix2

rem Result of product Matrix1 x Matrix2
%MyProgram% matrix2.txt matrix1.txt > %OutputFile%
fc "output21.txt" %OutputFile% > nul || goto err
echo Test passed: result of product Matrix2 x Matrix1

echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1