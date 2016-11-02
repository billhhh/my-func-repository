@echo off

IF [%1]==[] GOTO USAGE
IF [%2]==[] GOTO USAGE

:START
for "%1\%%i" in (*)do if %%~zi lss %2 echo %%i %%~zi byte
GOTO   END

:USAGE
echo Usage: %0 dir_path file_size
GOTO   END

:END
pause