HelloChina.exe : HelloChina.c
	cl HelloChina.c

ren  HelloChina.exe  DSA13.exe
copy DSA13.exe ..\..\..\..\bin\Plugins

del HelloChina.obj HelloChina.exe DSA13.exe

exit