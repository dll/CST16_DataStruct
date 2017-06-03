/*
*文件：PFWDSA.C
*内容：
* 主程序文件，实现PFWDSA系统功能的主入口。通过静态引入库lib方式链接两个静态库BaseServices.lib、PluginManager.lib
* 和一个动态库DSATestServices.dll构成主框架。
*作者：刘东良
*日期: 2012-09-10
*/


#include "include/Global.h"
#include "include/BaseServices.h"
#include "include/DSATestServices.h"

//使用DSATestServices.lib引入库隐式链接动态链接库DSATestServices.dll
//设置make.bat文件中的link选项，二者其一或都写
//#pragma comment(lib, "bin/DSATestServices.lib")
//#pragma comment(lib, "lib/BaseServices.lib")
//#pragma comment(lib, "lib/PluginManager.lib")

//模块间使用的全局变量(PluginManage.obj,BaseServices.obj和PFWDSA.obj。
//使用原则：源文件中定义，头文件中extern修饰声明)
int  nPlugins=0;//0表示没有插件
char pluginFolder[] = ".\\Plugins\\"; //插件文件夹
char dataFolder[] = ".\\Data\\"; //插件数据文件夹
char tempFolder[] = ".\\Temp\\"; //系统及插件临时文件夹
int  PFWDSAruntimes = 1; //PFWDSA运行次数,1首次使用

//自动随机选择插件进行演示
void AutoRandDemo(void);//使用函数三步骤：1步,声明

//1 main主函数：核心功能是ManagerPlugin、AutoRandDemo、ChoicePlugin实现的管理、随机、选择插件等操作
//2 读写系统运行次数函数ReadSysRunTimes和SaveSysRunTimes累计该系统运行次数，并写入日志文件PFWDSA.log中
//3 加载插件函数LoadPlugin列表显示插件，以供管理、随机、选择插件操作
//4 显示PFWDSA主菜单
//5 循环执行管理插件、自动随机演示、选择插件、重新启动系统和退出系统
//6 使用goto语句,恢复删除插件并列表显示且可用
//7 退出系统使用goto语句，销毁系统使用的资源

int main(void){	
	char m=' ';
	ReadSysRunTimes();//ReadSysRunTimes在BaseServices.lib模块内
	do{
		system("CLS");//清屏
		PrintPFWDSATextUI(3);//在BaseServices.lib模块内,显示主界面
		LoadPlugin();//在BaseServices.lib模块内,加载插件
		while(m!='Q' || m!='q'){
			PrintPFWDSATextUI(3);//显示主界面
			ShowPluginsIDName();//在BaseServices.lib模块内,显示插件列表
			printf("\n\t\t   ================== ");
			printf("\n\t\t   |  PFWDSA主菜单  | ");
			printf("\n\t\t   ------------------ ");
			printf("\n\t\t   | [M/m] 管理插件 | ");
			printf("\n\t\t   | [A/a] 随机演示 | ");
			printf("\n\t\t   | [C/c] 选择插件 | ");
			printf("\n\t\t   | [R/r] 重启系统 | ");
			printf("\n\t\t   | [Q/q] 退出系统 | ");
			printf("\n\t\t   ================== ");
			printf("\n\t\t\a   请输入菜单首字符:");
			flushall();//清理C流的垃圾—输出printf与输入scanf之间，且为字符输入时!
			m=getchar();
			switch(m){//switch语句
				case 'M':
				case 'm':
					ManagerPlugin();//ManagerPlugin在BaseServices.lib模块内
					break;
				case 'A':
				case 'a':
					AutoRandDemo();//使用函数三步骤：3步,调用,本源文件中
					break;
				case 'C':
				case 'c':
					ChoicePlugin();//ChoicePlugin在BaseServices.lib模块内
					break;
				case 'Q':
				case 'q':
					goto EXITPFWDSA;//使用goto语句，退出系统
				case 'R':
				case 'r':
					goto RESTART;//使用goto语句，重启系统
				default:
					system("CLS");
					PrintPFWDSATextUI(3);
					ShowPluginsIDName();
					printf("\n\t\a输入无效，请重新输入主菜单首字符!");
					system("PAUSE");
					break;		
			}
		}
		RESTART:
			DestroyPlugin();//DestroyPlugin在BaseServices.lib模块内
	}while(m == 'R' || m == 'r');
	EXITPFWDSA:
		DestroyPlugin();
	system("DEL /F /Q .\\Temp\\*.*");
	printf("\n\t\a 版权@刘东良2012 GPL许可 CZLDL@TOM.COM\n\n");
	SaveSysRunTimes();//SaveSysRunTimesBaseServices.lib模块内
	system("PAUSE");
	return 0;
}

//1 自动随机选择演示
//2 根据PFWDSA平台0个，1个，2个以上插件随机选择插件进行演示
//3 没有插件则退出
//4 1个插件，直接运行该插件，不需随机选择
//5 2个以上插件，则由RandInt随机选择一个插件演示，RandInt在DSATestServices.dll模块内
//6 按ESC键退出

void AutoRandDemo(void){ //使用函数三步骤：2步,定义
	while(1){//无限循环，直到用户按ESC键
		PrintPFWDSATextUI(1);
		ShowPluginsIDName();
		printf("\n\t1秒钟切换或回车立即执行,空格键分段计时!\n");
		if(nPlugins<=0){//没有插件
			printf("\tPFWDSA平台没有插件!\n");
			system("PAUSE");
			return;
		}
		else if(nPlugins==1){//1个插件，可以与else合并
			//TimeClock在DSATestServices.dll模块内，它可提供给插件用户使用(API)，
			//不同于BaseServices.lib为PFWDSA框架所专用
			if(TimeClock(100)==VK_ESCAPE){//10毫秒
				printf("\n\t退出随机演示!\n");
				break;//跳出while
			}
			RunPlugin(0);//RunPlugin在BaseServices.lib模块内
		}
		else{//2个以上插件
			if(TimeClock(1000)==VK_ESCAPE){//1000毫秒为1秒
				printf("\n\t退出随机演示!\n");
				break;
			}
			//RandInt在DSATestServices.dll模块内，返回[0,nPlugins-1)间的随机整数
			RunPlugin(RandInt(0,nPlugins));
		}
	}
}