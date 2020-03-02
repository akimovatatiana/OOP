@echo off

set Program="%~1"
set OutputFile="output.txt"

%Program% "6" > %OutputFile% 
fc %OutputFile% "out-6.txt" > nul || goto err
echo Test passed: everything is right

rem If there is no byte number
%Program% > %OutputFile%
fc %OutputFile% error-argc.txt > nul || goto err
echo Test passed: if there is no byte number

rem If there is more than one argument
%Program% "6" "8"> %OutputFile%
fc %OutputFile% error-argc.txt > nul || goto err
echo Test passed: if there is more than one argument

rem If byte number < 0
%Program% "-6"> %OutputFile%
fc %OutputFile% "error-range.txt" > nul || goto err
echo Test passed: if byte number less than 0

rem If byte number > 255
%Program% "256" > %OutputFile%
fc %OutputFile% "error-range.txt" > nul || goto err
echo Test passed: if byte number more than 255

rem If there is no number entered
%Program% "" > %OutputFile%
fc %OutputFile% "error-no-byte.txt" > nul || goto err
echo Test passed: if there is no number entered

rem If byte number = 0
%Program% "0" > %OutputFile%
fc %OutputFile% out-0.txt > nul || goto err
echo Test passed: if byte number = 0

rem If byte number = 255
%Program% "255" > %OutputFile%
fc %OutputFile% out-255.txt > nul || goto err
echo Test passed: if byte number = 255

rem If the input is string
%Program% "gjkr" > %OutputFile%
fc %OutputFile% error-byte.txt > nul || goto err
echo Test passed: if the input is string

rem If the input is not decimal number
%Program% "15ghd" > %OutputFile%
fc %OutputFile% error-byte.txt > nul || goto err
echo Test passed: if the input is not decimal number

echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1