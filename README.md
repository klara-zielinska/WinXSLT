## Description

WinXSLT is a GUI based tool for performing XSLT transformations. It
can perform a transformation on one file or on a set of files given by
a path (possibly with wildcards).

## Requirements

To build WinXSLT you need
* Qt 5       (tested 5.6.3)
* Xalan-C++  (tested 1.11  compiled with MS VC++ 2010 for Win64)
* Xerces-C++ (tested 3.1.1 compiled with MS VC++ 2010 for Win64)
* MS VC++    (tested 2015 for Win64)

The system variables XERCESCROOT, XALANCROOT needs to be set. E.g.
* XERCESCROOT = C:\Libs\xerces-c-3.1.1
* XALANCROOT  = C:\Libs\xalan-c-1.11

To run WinXSLT you need appropriate Qt, Xalan and Xerces .dll files to be
available in a search path.