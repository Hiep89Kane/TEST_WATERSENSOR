cls
@echo off
	@ECHO *********************************************************
	@ECHO  Batch file for programming STM32
	@ECHO  - Programming FLASH 
	@ECHO  - Support Windows 7 32-bit or 64-bit
	@ECHO *********************************************************
:Start_Programming 
	@ECHO   ** S T A R T   P R O G R A M M I N G **
@ECHO ---------------------------------------------------------

@SET TOOL="C:\Program Files\STMicroelectronics\st_toolset\stvp\STVP_CmdLine.exe"
@SET CUSTOMERCODE="TEST_WATERSENSOR.hex"

@ECHO.
@ECHO Hex File: %CUSTOMERCODE%	
@ECHO.

%TOOL% -c ID=0 SWD -rOB -ME w32 -P %CUSTOMERCODE% -V  "after_programming" -OB RDP=0 -Rst

@IF ERRORLEVEL ==1 (
	@ECHO.
    @ECHO Not Windows 32-bit, Switching to Windows 64-bit
    @ECHO.
	@SET TOOL="C:\Program Files (x86)\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility\ST-LINK_CLI.exe"
) ELSE GOTO CHECKING_ERROR

%TOOL% -c ID=0 SWD -rOB -ME w32 -P %CUSTOMERCODE% -V  "after_programming" -OB RDP=0 -Rst

@PAUSE
@GOTO Start_Programming