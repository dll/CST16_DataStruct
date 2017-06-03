/*
*文件：Global.h
*PFWDSA 全局头文件，存放全局变量、插件接口和PFWDSA的插件结构定义。
*作者：刘东良
*日期: 2012-09-10
*/

#ifndef PFWDSA_H
#define PFWDSA_H

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

//静态全局变量
//PFWDSA.C中使用的全局变量，在PFWDSA.exe和BaseServices.lib,PluginManager.lib模块间使用
extern int nPlugins;//插件总数
extern char pluginFolder[]; //插件文件夹
extern char dataFolder[]; //数据文件夹
extern char tempFolder[]; //临时文件夹
extern int PFWDSAruntimes; //PFWDSA运行次数,1首次使用

//接口(契约)设计
//通过PFUNC类型的函数指针加载插件
typedef void (*PFUNC)(void);
//通过PFUNCPlugInfo类型的函数指针获取插件信息（插件接口和插件版本）。设计意图是由DLL传递全局变量
typedef char * (*PFUNCPlugInfo)(void);

//插件结构
struct tagPLUGIN{
	unsigned id;  //插件编号:使用插件的编号,0,1,2（window下的句柄）
	char iPlugin[100]; //插件接口:插件接口,DSAInterface
	char name[100]; //插件名称:插件名称,线性表
	char nameDLL[100]; //插件库名称:动态链接库全名,DSA00.dll
	char nameTXT[100]; //插件配置名称:插件配置信息文本文件全名,DSA00.txt
	char path[100]; //插件路径：插件所在的路径
	char version[20]; //插件版本：版本号1.0.0
	char author[40]; //插件作者: 学号加姓名，206004刘东良
	char date[20]; //插件发布日期：2012-09-19
	char url[100]; //插件url：插件相关的网络资源
	char description[200]; //插件描述：详细介绍插件功能，如猜数游戏
}DSAPlugin[200];//PFWDSA初始容纳为200个插件

#endif

