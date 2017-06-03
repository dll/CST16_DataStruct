/*
*文件：BaseServices.h
*PFWDSA 主框架的基础服务头文件，声明PFWDSA平台需要的基础功能函数。
*作者：刘东良
*日期: 2012-09-10
*/

#ifndef BASESERVICES_H
#define BASESERVICES_H

//PFWDSA加载Plugins目录下的插件加载插件函数，无参，无返回值
void LoadPlugin(void);
//选择插件进行演示，无参，无返回值
void ChoicePlugin(void);
//依据id运行插件，整型参数为插件序号，无返回值
void RunPlugin(int id);
//释放系统使用的资源，无参，无返回值
void DestroyPlugin(void);
//PFWDSA插入、删除、查询插件，无参，无返回值
void ManagerPlugin(void);
//从PFWDSA.log日志文件中读取使用次数，无参，无返回值
void ReadSysRunTimes(void);
//保存日志(使用次数和时间)到PFWDSA.log文件中，无参，无返回值
void SaveSysRunTimes(void);
//依据i打印PFWDSA的文本界面，整型参数代表4种不同界面，无返回值
void PrintPFWDSATextUI(int i);
//打印插件序号和名称，无参，无返回值
void ShowPluginsIDName(void);

#endif