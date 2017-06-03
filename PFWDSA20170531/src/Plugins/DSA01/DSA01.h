
#ifndef DSA01_H
#define DSA01_H

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>

#include<limits.h>
#include "..\..\HostApp\include\DSATestServices.h"

#define mcmp(x,y) ((*x)>(*y)?(1):(-1)) 

typedef double ElementType;
extern char gVersion[20];
extern char* GetPluginVersion(void);
extern char gInterface[20];
extern char* GetPluginInterface(void);

void swap(int *a, int *b);

void SelectSort(int a[], int n) ;

void BubbleSort(int a[], int n);

/////////////////////////////////////////////////
int SelectMin(ElementType e[], int i, int n);

/* ºÚµ•—°‘Ò≈≈–Ú */
void DATSelectSort(ElementType e[], int n);

void DSA_SelectSort(void* *a, int n, char * typeName, int(*Cmp)(void *, void *));
void DSASelectSort(void* *a, int n, int size, int(*FCmp)(void *, void *)) ;

void DSABubbleSort(void* *a, int n, int size, int(*FCmp)(void *, void *));

static int Partition(void* arr, int(*cmp)(void*, void*), int left, int right, int size) ;
  
static void QSort(void* arr, int(*cmp)(void*, void*), int left, int right, int size);
  
void DSAQuickSort(void* arr, int n, int size, int(*cmp)(void*, void*)) ;

#endif
