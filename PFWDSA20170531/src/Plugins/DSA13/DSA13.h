//PFWDSA plugin head file DSA10.h
#ifndef DSA13_H
#define DSA13_H

#include<stdio.h> 
#include<stdlib.h> 
#include<windows.h> 
#include<time.h> 

void DSAInterface(void);
extern char gVersion[20];
extern char* GetPluginVersion(void);
extern char gInterface[20];
extern char* GetPluginInterface(void);

void gotoxy(int x, int y); //x为列坐标,y为行坐标
void NUProChinaCityMap(void);
void ProChinaCityMap(void);

#endif
