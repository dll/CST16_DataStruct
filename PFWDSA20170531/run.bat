cd bin

IF exist "PFWDSA.exe" (
	start PFWDSA.exe
 ) ELSE (
	cd..
	start make.bat
	cd bin
	start PFWDSA.exe
)