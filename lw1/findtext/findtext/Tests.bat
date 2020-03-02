@echo off

set MyProgram="%~1"
set OutputFile="out.txt"
set STRING="traveler"
set STRING_SMTH="something"
set STRING_REGISTER="Traveler"

%MyProgram% input.txt %STRING% > %OutputFile%
fc %OutputFile% "output.txt" > nul || goto err
echo Test passed: search for string in input file 

rem If the string has another register 
%MyProgram% input.txt %STRING_REGISTER% > %OutputFile%
fc %OutputFile% "not-found-out.txt" > nul || goto err
echo Test passed: if the string has another register

rem If there is no string in input file 
%MyProgram% input.txt %STRING_SMTH% > %OutputFile%
fc %OutputFile% "not-found-out.txt" > nul || goto err
echo Test passed: if there is no string in input file 

rem If there is no string
%MyProgram% input.txt > %OutputFile%
fc %OutputFile% "error-argc.txt" > nul || goto err 
echo Test passed: if there is no string

rem If there is an empty string
%MyProgram% input.txt "" > %OutputFile%
fc %OutputFile% "error-empty-string.txt" > nul || goto err 
echo Test passed: if there is an empty string

rem If there is no input file
%MyProgram% %STRING% > %OutputFile%
fc %OutputFile% "error-argc.txt" > nul || goto err 
echo Test passed: if there is no input file

rem If input file is empty
%MyProgram% empty.txt %STRING% > %OutputFile%
fc "not-found-out.txt" %OutputFile% > nul || goto err
echo Test passed: if input file is empty

rem If input file is missing
%MyProgram% MissingFile.txt %STRING% > %OutputFile%
fc "error-open.txt" %OutputFile% > nul || goto err
echo Test passed: if input file is missing

echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1