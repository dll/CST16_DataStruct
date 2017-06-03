/*
*文件：PluginManager.C
*内容：
* 向BaseServices提供插件管理功能。具体包括InsertPlugin、GetPluginTxt、SetPluginTxt、DeletePlugin、RetrievePlugin等5个函数。
* 各函数具体功能见具体实现
*作者：刘东良
*日期: 2012-09-10
*/
#include "../include/Global.h"
#include "../include/PluginManager.h"

//1 向PFWDSA框架中插入新的插件，准确地讲是向DSAPlugin数组中添加插件
//2 执行时，提示输入插件文件完整的路径名称。如果输入插件路径或者名称错误则返回
//3 判断插件是否已经存在DSAPlugin数组中
//4   如果插入的插件已经存在，则flag标志为1，并询问是否覆盖此插件文件（包括dll和txt两个文件）
//5   如果覆盖则首先调用FreeLibrary函数释放该插件，再重新加载dll和txt文件，类似BaseServices模块中LoadPlugin函数
//6   GetPluginTxt和SetPluginTxt函数分别是读写插件的txt文件获取插件信息
//8 新插入的插件不存在DSAPlugin数组中，flag标志为0，首先根据Win32API函数CopyFile的返回值判断是否有Plugins文件夹
//9   没有则调用system("MD Plugins");创建，然后再次调用CopyFile拷贝dll文件
//10  同样分别拷贝或输入新插件的配置txt文件
//11  调用LoadLibrary函数添加插件到DSAPlugin数组中
void InsertPlugin(void){
	HMODULE hm;
	PFUNCPlugInfo pluginfo;
	char tname[200]={0},fname[200]={0},pname[200]={0};
	int i=0, flag=0;

	printf("\t请输入完整的插件dll文件名称,包括文件名及扩展名(如,E:\\DSA00.dll)\n");
	scanf("%s",pname);
	if(!strrchr(pname,'\\') || -1==access(pname,0) ){//access函数判断pname是否存在，0只判断是否存在
		printf("\t输入[%s]插件dll文件路径或名称错误或文件不存在!\n", pname);
		return;
	}
	strcpy(tname,strrchr(pname,'\\'));
	for(i=0;tname[i]!='\0';i++)
		tname[i]=tname[i+1];
	strcpy(fname,pluginFolder);
	strcat(fname, tname);
	//遍历DSAPlugin数组中已有插件
	for(i=0;i<nPlugins;i++){
      		//判断插件是否已存在, 忽略大小写的字符串比较
		if(stricmp(tname,DSAPlugin[i].nameDLL)==0){
			flag=1;
			printf("\t插件[%s]已存在! 是否覆盖此插件[y/n]?(回车不覆盖):", tname);
			flushall();
			if('y' == getchar()){
				FreeLibrary((HMODULE)DSAPlugin[i].id);
				//CopyFile参数：源文件;目标文件;如目标文件存在, True: 失败, False: 覆盖
				if(!CopyFile(pname,fname,FALSE))
					printf("\t复制[%s]文件到[%s]失败!\n", pname, fname);//GetLastError()
				else{
					hm=LoadLibrary(fname);
					DSAPlugin[i].id=(DWORD)hm;
					//GetProcAddress函数Win32API，获得插件导出的插件接口名称
					pluginfo = (PFUNCPlugInfo)GetProcAddress(hm, "GetPluginInterface");
					if (pluginfo != NULL)
						strcpy(DSAPlugin[i].iPlugin,pluginfo());
					else{
						printf("\t插件接口的致命错误!该插件不是PFWDSA的插件!\n");
						break;
					}
					//获得插件导出的插件版本
					pluginfo = (PFUNCPlugInfo)GetProcAddress(hm, "GetPluginVersion");
					if (pluginfo != NULL)
						strcpy(DSAPlugin[i].version,pluginfo());
					else{
						printf("\t插件版本的致命错误!该插件版本不被PFWDSA兼容!\n");
						break;
					}
					if(GetPluginTxt(pname,i)==-1){
						if(SetPluginTxt(pname,i)==-1){
							printf("\t输入[%s]插件配置txt文件失败!\n",pname);
							FreeLibrary((HMODULE)DSAPlugin[i].id);
							return;
						}
					}
					printf("\t成功插入新插件!\n");
				}
			}
			else
				return;				
		}
	}
	//新插入的插件不存在DSAPlugin数组中
	if(flag==0){
 		if(!CopyFile(pname,fname,TRUE)){
			printf("\t复制新插件文件失败:可能bin目录下没有Plugins文件夹!\n");
			printf("\t创建Plugins文件[y/n]?(回车退出系统):\n");
			flushall();
			if('y'==getchar()){
				system("MD Plugins");//使用system函数执行DOS命令MD，创建文件夹Plugins
				if(!CopyFile(pname,fname,TRUE)){
					printf("\t复制新插件[%s]文件失败!\n", pname);
					system("PAUSE");
					return;
				}
				else{
					printf("\t成功复制新插件[%s]文件!", pname);
				}
			}
			else{
				printf("\tPFWDSA退出，必须创建Plugins文件夹!\n");
				system("PAUSE");
				exit(0);
			}
			
		}
		else{
			printf("\t成功复制新插件dll文件!\n");
		}
		
		if(GetPluginTxt(pname,i)==0){
			printf("\t成功复制新插件配置txt文件!\n");
		}
		else if(SetPluginTxt(pname,i)==0){
				printf("\t成功输入新插件配置txt文件!\n");
			}
			else{
				printf("\t复制或输入新插件的配置txt文件失败!\n");
				return;
			}
		nPlugins++;
		hm=LoadLibrary(pname);
		DSAPlugin[i].id=(DWORD)hm;
		pluginfo = (PFUNCPlugInfo)GetProcAddress(hm, "GetPluginInterface");
		if (pluginfo != NULL)
			strcpy(DSAPlugin[i].iPlugin,pluginfo());
		else{
			printf("\t插件接口的致命错误!该插件不是PFWDSA的插件!\n");
		}
		pluginfo = (PFUNCPlugInfo)GetProcAddress(hm, "GetPluginVersion");
		if (pluginfo != NULL)
			strcpy(DSAPlugin[i].version,pluginfo());
		else{
			printf("\t插件版本的致命错误!该插件版本不被PFWDSA兼容!\n");
		}
		printf("\t成功插入新插件!\n");
	}
}
//1 读id插件的txt文件获取插件信息
//2 该函数是获取id插件信息即txt文本数据
//3 参数pname可能指向任意位置
//4 如果Plugins文件夹不存在pname文件，则要将该文件拷贝至Plugins文件夹中
//5 否则，不拷贝文件
//6 获取成功返回0；否则返回-1并报告读取插件的配置文件失败
int GetPluginTxt(char pname[],int id){
	char fname[20],path[50], tmp[20];
	int i;
	FILE *pFile;

	for(i=0;pname[i]!= '\0';i++)
		fname[i]=pname[i];
	fname[i]='\0';fname[i-1]='t';fname[i-2]='x';fname[i-3]='t';
	pFile=fopen(fname,"r");
	strcpy(path,pluginFolder);
	strcpy(tmp,strrchr(fname,'\\'));
	strcat(path, tmp);

	if(pFile!=NULL){
		fscanf(pFile, "%s", DSAPlugin[id].iPlugin);
		fscanf(pFile, "%s", DSAPlugin[id].name);
		fscanf(pFile, "%s", DSAPlugin[id].nameDLL);
		fscanf(pFile, "%s", DSAPlugin[id].nameTXT);
		fscanf(pFile, "%s", DSAPlugin[id].path);
		fscanf(pFile, "%s", DSAPlugin[id].version);
		fscanf(pFile, "%s", DSAPlugin[id].author);
		fscanf(pFile, "%s", DSAPlugin[id].date);
		fscanf(pFile, "%s", DSAPlugin[id].url);
		fscanf(pFile, "%s", DSAPlugin[id].description);
		fclose(pFile);
		if(-1==access(pname,0) )
			CopyFile(fname,path,TRUE);
		return 0;//成功
	}	
	else{
		printf("\t读取[%s]插件的配置txt文件失败! \n",fname);
		return -1;//失败
	}
}
//1 输入id插件信息生成插件的txt文件
//2 该函数输入10项插件信息:接口、名称、DLL、TXT、路径、版本、作者、日期、网址、描述
//3 输入、保存文件成功返回0;否则返回-1并报告输入保存插件的配置文件失败
int SetPluginTxt(char pname[],int id){
	char fname[20],path[50], tmp[20];
	int i;
	FILE *pFile;

	for(i=0;pname[i]!= '\0';i++)
		fname[i]=pname[i];
	fname[i]='\0';fname[i-1]='t';fname[i-2]='x';fname[i-3]='t';
	pFile=fopen(fname,"w");
	strcpy(path,pluginFolder);
	strcpy(tmp,strrchr(fname,'\\'));
	strcat(path, tmp);
	printf("\t请输入新插件的配置信息(10项):\n");
	printf("iPlugin name nameDLL nameTXT path version author date url description\n");
	printf(" 接口   名称    DLL     TXT  路径   版本   作者  日期 网址    描述\n");
	scanf("%s %s %s %s %s %s %s %s %s %s", &DSAPlugin[id].iPlugin,&DSAPlugin[id].name,\
		&DSAPlugin[id].nameDLL, &DSAPlugin[id].nameTXT,&DSAPlugin[id].path, &DSAPlugin[id].version,\
		&DSAPlugin[id].author, &DSAPlugin[id].date, &DSAPlugin[id].url,&DSAPlugin[id].description);
	if(pFile!=NULL){
		fprintf(pFile, "%s\n", &DSAPlugin[id].iPlugin);
		fprintf(pFile, "%s\n", &DSAPlugin[id].name);
		fprintf(pFile, "%s\n", &DSAPlugin[id].nameDLL);
		fprintf(pFile, "%s\n", &DSAPlugin[id].nameTXT);
		fprintf(pFile, "%s\n", &DSAPlugin[id].path);
		fprintf(pFile, "%s\n", &DSAPlugin[id].version);
		fprintf(pFile, "%s\n", &DSAPlugin[id].author);
		fprintf(pFile, "%s\n", &DSAPlugin[id].date);
		fprintf(pFile, "%s\n", &DSAPlugin[id].url);
		fprintf(pFile, "%s\n", &DSAPlugin[id].description);
		fclose(pFile);
		if(0==access(pname,0) )
			CopyFile(fname,path,TRUE);
		return 0;
	}	
	else{
		printf("\t输入[%s]插件的配置txt文件失败!\n",fname);
		return -1;
	}
}

//1 删除插件
//2 如果输入插件序号无效则返回
//3 否则，调用FreeLibrary函数释放该插件以便可以删除插件（否则插件dll被锁将不可访问）
//4 如果彻底删除，从Plugins文件夹中删除该插件的dll和txt文件，不可恢复且不可用
//5 删除功能由system函数完成。实际执行shell指令del并使用通配符*删除多个文件
//6    删除Plugins文件夹下的插件的dll、exe和txt等多个文件
//7    删除Data文件夹下的数据dat多个文件
//8    删除Temp文件夹下的临时生成的数据tmp多个文件
//9 DSAPlugin数组要前移，插件数目nPlugins减1
//10  这是仅仅从DSAPlugin数组中减少一个插件，系统重启会恢复显示并可用
void DeletePlugin(void){
	int i, j, k, id;
	char d, pname[100], pnameDLL[100], ptemp[100], dtemp[100], ttemp[100], temp[100];
	HANDLE hFile;
	WIN32_FIND_DATA FileData;
	char pdir[100], ddir[100], tdir[100], pdll[100];
	
	printf("\t请输入插件序号[0,%2d]: ", nPlugins-1);
	scanf("%d",&id);
	if(id<0 || id>=nPlugins){
		printf("\t输入插件序号[%d]不在有效范围[0,%d]!\n", id, nPlugins-1);
		return;
	}
	//覆盖删除插件，并为删除提供可能，否则"拒绝访问"（因为插件被写入进程啦）
	FreeLibrary((HMODULE)DSAPlugin[id].id);
	
	strcpy(pname, DSAPlugin[id].name);
	strcpy(pnameDLL, DSAPlugin[id].nameDLL);
	for(i=0;pnameDLL[i]!='\0';i++){
		temp[i]=pnameDLL[i];
	}
	temp[i-1]='\0';temp[i-2]='*';temp[i-3]='.';temp[i-4]='*';
	strcpy(pdir, pluginFolder);strcpy(ptemp,pluginFolder);strcpy(pdll, pluginFolder);
	strcpy(ddir, dataFolder);strcpy(dtemp, dataFolder);
	strcpy(tdir, tempFolder);strcpy(ttemp, tempFolder);	
	strcat(pdir, temp);strcat(pdll, pnameDLL);
	strcat(ddir, temp);
	strcat(tdir, temp);

	for(i=id;i<nPlugins-1;i++)
		DSAPlugin[i]=DSAPlugin[i+1];
	nPlugins--;

	printf("\t删除[%s]插件不可恢复吗[y/n]?(回车不删除):", pname);
	flushall();
	if((d=getchar())=='y'){
		//删除Plugins文件夹下的插件文件，可能是dll，exe，txt等格式多个文件
		if(remove(pdll))
		//if(!DeleteFile(pdll))
			printf("\t删除[%s]插件[%s]文件失败[%d]!\n", pname,pnameDLL,GetLastError());
		else{
			printf("\t成功删除[%s]插件[%s]文件!\n", pname,pnameDLL);
		}
		hFile = FindFirstFile(pdir,  &FileData);//搜索第一个插件文件
		if (hFile==INVALID_HANDLE_VALUE) {
        		;//printf("\t[%s]插件[%s]文件不存在!\n", pname, pdir);//空语句
		}
		else{
			while(1){
				strcat(ptemp, FileData.cFileName);
				if(remove(ptemp)){
					printf("\t删除[%s]插件[%s]文件失败!\n",pname, ptemp);
					return;
				}
				else{
					printf("\t成功删除[%s]插件[%s]文件!\n",pname, ptemp);
				}
				//获得下一个dll插件文件
				if (!FindNextFile(hFile, &FileData)) 
                			break;
				strcpy(ptemp,pluginFolder);
			}
			FindClose(hFile);//释放查找文件句柄
		}
		//删除Data文件夹下的插件数据文件，是插件文件名+序号，扩展名为dat的多个文件
		hFile = FindFirstFile(ddir,  &FileData);//搜索第一个数据文件
		if (hFile==INVALID_HANDLE_VALUE) {
        		;//printf("\t[%s]插件的数据[%s]文件不存在!\n", pname, ddir);//空语句
		}
		else{
			while(1){
				strcat(dtemp, FileData.cFileName);
				if(remove(dtemp)){
					printf("\t删除[%s]插件[%s]数据文件失败!\n",pname, dtemp);
					return;
				}
				else{
					printf("\t成功删除[%s]插件[%s]数据文件!\n",pname, dtemp);
				}
				//获得下一个插件的数据文件
				if (!FindNextFile(hFile, &FileData)) 
                			break;
				strcpy(dtemp,dataFolder);
			}
			FindClose(hFile);//释放查找文件句柄
		}
		//删除Temp文件夹下的插件演示临时生成的数据文件，扩展名为tmp的多个文件
		hFile = FindFirstFile(tdir,  &FileData);//搜索第一个临时文件
		if (hFile==INVALID_HANDLE_VALUE) {
        		;//printf("\t[%s]插件的临时生成的数据[%s]文件不存在!\n", pname, tdir);//空语句
		}
		else{
			while(1){
				strcat(ttemp, FileData.cFileName);
				if(remove(ttemp)){
					printf("\t删除[%s]插件[%s]临时生成的数据文件失败!\n", pname, ttemp);
					return;
				}
				else{
					printf("\t成功删除[%s]插件临时生成[%s]数据文件!\n", pname, ttemp);
				}
				//获得下一个插件的临时文件
				if (!FindNextFile(hFile, &FileData)) 
                			break;
				strcpy(ttemp,tempFolder);
			}
			FindClose(hFile);//释放查找文件句柄
		}
	}
	else
		printf("\t成功从插件列表中删除[%s]插件,重启系统将恢复且可用!\n", pname);

}
//1 提取插件的信息
//2 如果查询插件序号无效则返回
//3 否则打印插件的配置文件txt中的所有信息
void RetrievePlugin(void){
	int id;
	
	printf("\t请输入插件序号[0,%2d]: ", nPlugins-1);
	scanf("%d",&id);
	if(id<0 || id>=nPlugins){
		printf("\t输入插件序号[%d]不在有效范围[0,%d]!\n", id, nPlugins-1);
		return;
	}
	printf("\n\t插件编号为: %d \n", id);
	printf("\t插件接口为: %s \n", DSAPlugin[id].iPlugin);
	printf("\t插件名称为: %s \n", DSAPlugin[id].name);
	printf("\t插件DLL为 : %s \n", DSAPlugin[id].nameDLL);
	printf("\t插件TXT为 : %s \n", DSAPlugin[id].nameTXT);
	printf("\t插件路径为: %s \n", DSAPlugin[id].path);
	printf("\t插件版本为: %s \n", DSAPlugin[id].version);
	printf("\t插件作者为: %s \n", DSAPlugin[id].author);	
	printf("\t插件日期为: %s \n", DSAPlugin[id].date);
	printf("\t插件url为:  %s \n", DSAPlugin[id].url);
	printf("\t插件描述为: %s \n", DSAPlugin[id].description);
}