@echo off
del bin\PFWDSA.exe

IF exist "bin\PFWDSA.exe" (goto exe ) ELSE (goto build)

:build
start make.bat

echo build PFWDSA.exe to succeed!

pause

goto exe

:exe
cd bin
start PFWDSA.exe
