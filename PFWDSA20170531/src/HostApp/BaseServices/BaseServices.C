/*
*文件：BaseServices.C
*内容：
*  向主程序文件PFWDSA.C提供基本服务。具体包括LoadPlugin、ChoicePlugin、RunPlugin、ManagerPlugin等9个函数
*  PFWDSA平台的插件必须实现导出DSAInterface函数及导出gVersion、gInterface全局变量
*  目前，gInterface用来展示DLL导出全局变量的技术，用它通过DLL内部携带的插件接口，验证该插件是否为PFWDSA的插件
*  而gVersion用它通过DLL内部携带的版本信息，验证该插件与PFWDSA要求的插件的版本是否兼容  
*  各函数具体功能见具体实现
*
*  另，实现模块化（BaseServices.lib，PluginManager.lib及PFWDSA.exe）的程序设计目的是理解和演示
*  static静态全局变量，extern全局变量等使用
*作者：刘东良
*日期: 2012-09-10
*/


#include "../include/Global.h"
#include "../include/BaseServices.h"
#include "../include/PluginManager.h"

//1 从日志文件中获取系统运行次数
//2 如果打开PFWDSA.log日志文件失败，则系统运行次数PFWDSAruntimes为0
//3 否则，获得实际值PFWDSAruntimes
void ReadSysRunTimes(void){
	char bufflog[50],tmplog[50];
	FILE *pf=fopen("PFWDSA.log", "r");//PFWDSA.log硬编码，但本程序无臭味
	if(!pf){
		PFWDSAruntimes=0;	
	}
	else{
		do{
			fgets(bufflog,50,pf);
			strcpy(tmplog,bufflog);
		}while(fgets(bufflog,50,pf));
		PFWDSAruntimes=atoi(tmplog);//运行次数
		fclose(pf);
	}
} 
//1 保存系统运行次数
//2 如果打开PFWDSA.log日志文件失败，则返回（不进一步处理失败）
//3 否则，保存运行次数，运行结束时的日期和时间
void SaveSysRunTimes(void){
	time_t datetime;
	FILE *pf=fopen("PFWDSA.log", "a");
	PFWDSAruntimes++;
	time(&datetime); 
	if(!pf){
		printf("保存系统运行次数[%d]失败! \n",PFWDSAruntimes);
		return;	
	}
	else{
		//将运行次数和运行结束时的日期和时间写入日志文件PFWDSA.log中
		fprintf(pf, "%d %s", PFWDSAruntimes, asctime(localtime(&datetime)));
		fclose(pf);
	}
}

//0 一个插件至少包括dll和txt两个文件，dll是二进制代码可执行体，txt是文本类型配置文件。没有txt文件插件可以使用，但系统要求
//  插件信息完备，便于操作插件，完成各项功能。如果没有获得插件配置信息，插件名称则为空，但输入序号仍可以查询和运行
//1 PFWDSA框架加载插件:核心函数。将系统预设Plugins文件夹中的每个插件
//  包括dll和txt文件两个文件遍历加入全局变量DSAPlugin数组，以供使用
//2 约定插件的扩展名为dll（不区分大小写）
//3 在系统指定的bin目录中Plugins文件夹遍历所有插件文件
//4 调用Win32API函数FindFirstFile搜索第一个插件文件
//5 如果FindFirstFile返回值为非法的，则认定PFWDSA平台没有插件，并调用PluginManage模块中InsertPlugin函数插入插件
//6 否则，打印PFWDSA的文本主界面3（PrintPFWDSATextUI）
//7       循环搜索其它dll插件文件
//8       调用Win32API函数LoadLibrary加载dll插件文件
//9       调用Win32API函数GetProcAddress传入PFUNCPlugTxt类型函数指针GetPluginInterface，获得插件导出的插件接口
//10      函数GetProcAddress传入PFUNCPlugTxt类型函数指针GetPluginVersion，获得插件导出的插件版本信息
//11	  通过GetPluginTxt函数获得插件信息txt文件内容（具体见插件同名的txt文件）	      
//12      如GetPluginTxt函数获得txt文件失败，则调用SetPluginTxt函数输入插件10项信息
//13      成功加载插件包括dll和txt文件后，nPlugins增加1
//14 每个插件的信息都存储在全局变量DSAPlugin数组中
void LoadPlugin(void){
	HANDLE hFile;
	HMODULE hm;
	PFUNCPlugInfo pluginfo;//PFUNCPlugInfo类型的插件信息变量
	WIN32_FIND_DATA FileData;
	int i;
	char dllname[100];
	char temp[100];
	strcpy(dllname,pluginFolder);
	strcpy(temp,pluginFolder);
	strcat(temp, "*.dll");//硬编码.dll
	i=0;
	//获得指定目录下指定格式即dll插件文件的第一个文件
	hFile = FindFirstFile(temp,  &FileData);

	if (hFile==INVALID_HANDLE_VALUE) {
        	printf("\n\tPFWDSA平台没有插件!\n");
		InsertPlugin();//插入新的插件
	}
	else{
		PrintPFWDSATextUI(3);//打印PFWDSA的文本主界面
		while (1){
			strcat(dllname, FileData.cFileName);
			hm = LoadLibrary(dllname);//Win32API加载dll插件文件
			if ( !hm )
				printf("\t加载插件失败!\n");
			else{
				DSAPlugin[i].id=(DWORD)hm;
				//GetProcAddress函数获得插件导出的插件接口名称
				pluginfo = (PFUNCPlugInfo)GetProcAddress(hm, "GetPluginInterface");
				if (pluginfo != NULL)
					strcpy(DSAPlugin[i].iPlugin,pluginfo());
				else{
					printf("\t插件接口的致命错误!该插件不是PFWDSA的插件,不被加载!\n");
					break;
				}
				//获得插件导出的插件版本
				pluginfo = (PFUNCPlugInfo)GetProcAddress(hm, "GetPluginVersion");
				if (pluginfo != NULL)
					strcpy(DSAPlugin[i].version,pluginfo());
				else{
					printf("\t插件版本的致命错误!该插件版本不被PFWDSA兼容,不被加载!\n");
					break;
				}
				if(GetPluginTxt(dllname,i)==-1){
					if(SetPluginTxt(dllname,i)==-1){
						printf("\t输入%s插件配置txt文件失败!\n",dllname);
						break;
					}
				}
				i++;
			}
			//获得下一个dll插件文件
			if (!FindNextFile(hFile, &FileData)) 
                		break;
			strcpy(dllname,pluginFolder);
		}
		nPlugins=i;
		FindClose(hFile);//释放查找文件句柄
	}
	ShowPluginsIDName();//显示插件序号和名称
}
//1 显示插件序号和名称
void ShowPluginsIDName(void){
	int i;
	printf("\n\n\t\t     PFWDSA插件列表[%2.2d]   \n", nPlugins);
	printf("\t\t===========================\n");
 	printf("\t\t| 序号       名称         |\n");
   	printf("\t\t---------------------------\n");
	for(i=0;i<nPlugins;i++){
		printf("\t\t| [%2d]    %-12s    |\n", i, DSAPlugin[i].name);
	}
  	printf("\t\t===========================\n");
}
//1 选择插件进行演示
//2 如果PFWDSA平台无插件则调用插入函数InsertPlugin加载插件
//3 否则，循环进行选择插件演示，直到按y或Y退出
//4    PFWDSA的文本主界面2，显示插件序号和名称
//5    输入序号选择插件
//6        序号为-1退出插件选择
//7        序号在[0，nPlugins)有效范围则调用RunPlugin函数演示id插件
//8        序号无效则报告并询问是否继续选择不同插件：输入y或Y继续，否则退出
void ChoicePlugin(void){
	char c = 'n';
	int id = 0;	
	if(nPlugins<=0){
		printf ("\n\tPFWDSA平台没有插件!\n");
		InsertPlugin();
	}
	else{
		do{	
			PrintPFWDSATextUI(2);
			ShowPluginsIDName();
			printf("\n\t请输入[序号]选择插件([-1]返回):");
			scanf("%d", &id);
			if(id==-1){
				printf("\n\t退出插件选择!\n");
				return;
			}
			else if(id>=0 && id < nPlugins){
					RunPlugin(id);
					printf("\n\t选择不同插件吗[y/n]?(回车返回):");
					flushall();
					scanf("%c", &c);	
				}
				else{
					printf("\t输入插件序号[%d]不在有效范围[0,%d]!\n", id, nPlugins-1);
					printf("\n\t重新选择不同插件吗[y/n]?(回车返回):");
					flushall();
					scanf("%c", &c);
				}

		}while(c == 'Y' || c == 'y');
	}
}
//1 运行插件
//2 循环运行插件，演示某个插件结束时询问输入y或Y则继续，否则退出
//3 PFWDSA的文本主界面2，调用Win32API函数GetProcAddress传入PFUNC类型函数指针DSAInterface即插件接口
//4 注意清除输入流的垃圾问题
void  RunPlugin(int id){
	char cont;
	PFUNC pFunc;
	do{
		pFunc = (PFUNC)GetProcAddress((HINSTANCE)DSAPlugin[id].id, DSAPlugin[id].iPlugin);		
		if (pFunc != NULL)
			pFunc();		
		printf("\n\t继续测试[%s]插件吗[y/n]?(回车返回):",DSAPlugin[id].name);
		while (getchar() != '\n')
			;//清除输入流的垃圾
		scanf("%c", &cont);
	}while(cont == 'Y' || cont == 'y');
}

//1 销毁插件：插件使用内存、资源等需释放
//2 相对于LoadLibrary函数，调用FreeLibrary释放插件dll资源
void DestroyPlugin(void){
	int i;
	for (i=0; DSAPlugin[i].id!=0; i++)
		FreeLibrary((HMODULE)DSAPlugin[i].id);
}
//1 管理插件（插入、删除、查询）
//2 PFWDSA的文本主界面0
//3 选择插入或删除或查询插件或退出进行操作
void ManagerPlugin(void){
	char m;
	while(1){
		system("CLS");
		PrintPFWDSATextUI(0);
		ShowPluginsIDName();
		printf("\n\t请输入[i]插入 [d]删除 [r]查询 [q]退出:");
		flushall();
		scanf("%c",&m);
		switch(m){
		case 'i':case 'I':
			InsertPlugin();
			break;
		case 'd':case 'D':
			DeletePlugin();
			break;
		case 'r':case 'R':
			RetrievePlugin();
			break;
		case 'q':case 'Q':
			printf("\n\t退出插件管理!\n");
			return;
		default:
			printf("\t输入无效，请重输入!", m);
			break;
		}
		system("PAUSE");
	}
}
//1 PFWDSA的文本主界面
//2 PFWDSA的界面分为0管理插件，1随机演示，2选择插件和其它情况等四种界面
void PrintPFWDSATextUI(int i){
	system("CLS");
	printf("\n\t=================================================");
	printf("\n\t|基于DLL插件框架的《数据结构与算法》实验演示平台|");
	printf("\n\t|         版本V1.0.0 共使用[%5.5d]次!           |",PFWDSAruntimes);
	printf("\n\t|    《数据结构》(C语言版)(第2版)教材参考代码   |");
	printf("\n\t| 秦玉平  马靖善 主编  清华大学出版社,2012年3月 |");
	printf("\n\t-------------------------------------------------");
	if(i==0)
		printf("\n\t|              PFWDSA管理插件模块               |");
	else if(i==1)
		printf("\n\t|              PFWDSA随机演示模块               |");
	else if(i==2)
		printf("\n\t|              PFWDSA选择插件模块               |");
	else 
		printf("\n\t|                PFWDSA主界面                   |");	
	printf("\n\t=================================================\n");	
}