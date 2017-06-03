/*
*文件：PluginManager.h
*PFWDSA 主框架的管理插件头文件，声明PFWDSA平台管理插件的函数。
*作者：刘东良
*日期: 2012-09-10
*/

#ifndef PLUGMANAGER_H
#define PLUGMANAGER_H

extern int nPlugins;

//PFWDSA平台获得插件文本信息，字符数组参数pname为插件的dll文件路径和名称，整型参数id为插件序号
//返回整型数值，0为成功，-1为失败
int GetPluginTxt(char pname[],int id);
//PFWDSA平台输入插件文本信息，字符数组参数pname为插件的dll文件路径和名称，整型参数id为插件序号
//返回整型数值，0为成功，-1为失败
int SetPluginTxt(char pname[],int id);
//PFWDSA平台添加新的插件，无参，无返回值
void InsertPlugin(void);
//PFWDSA平台删除插件,分内存删除和彻底磁盘文件删除，无参，无返回值
void DeletePlugin(void);
//PFWDSA平台查询插件，无参，无返回值
void RetrievePlugin(void);

#endif