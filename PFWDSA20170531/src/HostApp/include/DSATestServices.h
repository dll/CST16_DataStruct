/*
*文件：DSATestServices.h
*PFWDSA 主框架的数据结构与算法测试的头文件，声明测试需要的函数。
*  希望平台用户能扩展该动态链接库，增加它的测试功能
*作者：刘东良
*日期: 2012-12-21
*/

#ifndef DSATESTSERVICES_H
#define DSATESTSERVICES_H

#include<time.h>

//生成一个随机整型数
//const int参数分别是min和max值
//返回从[min,max)之间的一个随机整型数
int RandInt(const int min, const int max);
//生成n长度的随机整型数组
//const int参数分别是min和max值
//int n参数为数组长度
//int a参数为整型数组
//无返回值
void RandIntArray(const int min, const int max, int a[], int n);
//生成一个随机随机数
//const double参数分别是min和max值
//返回从[min,max)之间的一个随机浮点数
double RandDouble(const double min, const double max);
//生成n长度的随机浮点数组
//const double参数分别是min和max值
//int n参数为数组长度
//int a参数为浮点数组
//无返回值
void RandDoubleArray(const double min, const double max, double a[], int n);

//C库中tm定义,自己实现tms计时达毫秒级，也可以封装tm实现
struct tms     //定义时间结构体，包括时分秒和毫秒 
{ 
	int hours,minutes,seconds; 
	int milliseconds;//毫秒
}timec,tmpc,totalc;    //timec计时显示，tmpc存储上一阶段时间，totalc记总时间 
int cnt;//依据Sleep函数累计毫秒计数

//计时闹钟
//int mseconds参数为闹钟设定时长
//返回字符char类型,按键回车,返回'\r'计时结束;按键空格,返回' '显示此次计时,初始化计时器;
//按键'ESC',返回'ESC';否则提示按键错误。
//计时到mseconds时返回'm'
char TimeClock(int mseconds);


void RandCharArray(char min, char max, char a[], int n);
void PrintiArray(int a[], int n);
void PrintdArray(double a[], int n);
void PrintcArray(char a[], int n);
//通用比较函数
int ICmp(const void *a, const void *b);
int CCmp(const void *a , const void *b);
int DCmp(const void *a, const void *b);
int FCmp(const void *a, const void *b);
//通用交换函数
void VSwap(void * vp1, void *vp2, int size);



#endif