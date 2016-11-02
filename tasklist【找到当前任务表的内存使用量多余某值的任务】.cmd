@echo off
:: Exam 2 Script
:: Author: Adam Giacalone
:: Date: 11/1/2016
:: Purpose is to create a script that allows someone to search the windows task list by task memory usage

:main
cls
echo ------------
echo   Welcome
echo ------------
echo What would you like to do, SEARCH or QUIT?
echo Select 1 for SEARCH
echo Select 2 for QUIT
set /p answer=
IF %answer%==1 goto search
IF %answer%==2 goto END
set /p dummy=Please enter a valid imput!! Please ENTER to continue
goto main

:search
cls
echo Please enter the number of MB (megabytes) of memory usage you would like to search for:
set /p memory=
set /a kilobytes=%memory%*1024
echo You entered %memory% Megabytes! That is %kilobytes% Kilobytes!
tasklist /fi "memusage gt %kilobytes%"
GOTO   END

:USAGE
echo Usage: %0 dir_path file_size
GOTO   END

:END
pause
