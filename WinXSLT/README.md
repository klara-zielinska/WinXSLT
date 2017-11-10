## Requirements

WinXSLT requires Xalan 1.11 and Xerces 3.1.1 libraries.

The system variables XERCESCROOT, XALANCINCLUDE, XALANCNLS, XALANCLIB needs 
to be set. E.g.

XERCESCROOT    = C:\Libs\xerces-c
XALANCINCLUDE  = %XALANCROOT%\src
XALANCNLS      = %XALANCROOT%\Build\Win64\VC10\Release\Nls
XALANCLIB      = %XALANCROOT%\Build\Win64\VC10\Release
XALANCROOT     = C:\Libs\xalan-c-1.11\c