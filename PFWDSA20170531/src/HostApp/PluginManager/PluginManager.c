/*
*�ļ���PluginManager.C
*���ݣ�
* ��BaseServices�ṩ��������ܡ��������InsertPlugin��GetPluginTxt��SetPluginTxt��DeletePlugin��RetrievePlugin��5��������
* ���������幦�ܼ�����ʵ��
*���ߣ�������
*����: 2012-09-10
*/
#include "../include/Global.h"
#include "../include/PluginManager.h"

//1 ��PFWDSA����в����µĲ����׼ȷ�ؽ�����DSAPlugin��������Ӳ��
//2 ִ��ʱ����ʾ�������ļ�������·�����ơ����������·���������ƴ����򷵻�
//3 �жϲ���Ƿ��Ѿ�����DSAPlugin������
//4   �������Ĳ���Ѿ����ڣ���flag��־Ϊ1����ѯ���Ƿ񸲸Ǵ˲���ļ�������dll��txt�����ļ���
//5   ������������ȵ���FreeLibrary�����ͷŸò���������¼���dll��txt�ļ�������BaseServicesģ����LoadPlugin����
//6   GetPluginTxt��SetPluginTxt�����ֱ��Ƕ�д�����txt�ļ���ȡ�����Ϣ
//8 �²���Ĳ��������DSAPlugin�����У�flag��־Ϊ0�����ȸ���Win32API����CopyFile�ķ���ֵ�ж��Ƿ���Plugins�ļ���
//9   û�������system("MD Plugins");������Ȼ���ٴε���CopyFile����dll�ļ�
//10  ͬ���ֱ𿽱��������²��������txt�ļ�
//11  ����LoadLibrary������Ӳ����DSAPlugin������
void InsertPlugin(void){
	HMODULE hm;
	PFUNCPlugInfo pluginfo;
	char tname[200]={0},fname[200]={0},pname[200]={0};
	int i=0, flag=0;

	printf("\t�����������Ĳ��dll�ļ�����,�����ļ�������չ��(��,E:\\DSA00.dll)\n");
	scanf("%s",pname);
	if(!strrchr(pname,'\\') || -1==access(pname,0) ){//access�����ж�pname�Ƿ���ڣ�0ֻ�ж��Ƿ����
		printf("\t����[%s]���dll�ļ�·�������ƴ�����ļ�������!\n", pname);
		return;
	}
	strcpy(tname,strrchr(pname,'\\'));
	for(i=0;tname[i]!='\0';i++)
		tname[i]=tname[i+1];
	strcpy(fname,pluginFolder);
	strcat(fname, tname);
	//����DSAPlugin���������в��
	for(i=0;i<nPlugins;i++){
      		//�жϲ���Ƿ��Ѵ���, ���Դ�Сд���ַ����Ƚ�
		if(stricmp(tname,DSAPlugin[i].nameDLL)==0){
			flag=1;
			printf("\t���[%s]�Ѵ���! �Ƿ񸲸Ǵ˲��[y/n]?(�س�������):", tname);
			flushall();
			if('y' == getchar()){
				FreeLibrary((HMODULE)DSAPlugin[i].id);
				//CopyFile������Դ�ļ�;Ŀ���ļ�;��Ŀ���ļ�����, True: ʧ��, False: ����
				if(!CopyFile(pname,fname,FALSE))
					printf("\t����[%s]�ļ���[%s]ʧ��!\n", pname, fname);//GetLastError()
				else{
					hm=LoadLibrary(fname);
					DSAPlugin[i].id=(DWORD)hm;
					//GetProcAddress����Win32API����ò�������Ĳ���ӿ�����
					pluginfo = (PFUNCPlugInfo)GetProcAddress(hm, "GetPluginInterface");
					if (pluginfo != NULL)
						strcpy(DSAPlugin[i].iPlugin,pluginfo());
					else{
						printf("\t����ӿڵ���������!�ò������PFWDSA�Ĳ��!\n");
						break;
					}
					//��ò�������Ĳ���汾
					pluginfo = (PFUNCPlugInfo)GetProcAddress(hm, "GetPluginVersion");
					if (pluginfo != NULL)
						strcpy(DSAPlugin[i].version,pluginfo());
					else{
						printf("\t����汾����������!�ò���汾����PFWDSA����!\n");
						break;
					}
					if(GetPluginTxt(pname,i)==-1){
						if(SetPluginTxt(pname,i)==-1){
							printf("\t����[%s]�������txt�ļ�ʧ��!\n",pname);
							FreeLibrary((HMODULE)DSAPlugin[i].id);
							return;
						}
					}
					printf("\t�ɹ������²��!\n");
				}
			}
			else
				return;				
		}
	}
	//�²���Ĳ��������DSAPlugin������
	if(flag==0){
 		if(!CopyFile(pname,fname,TRUE)){
			printf("\t�����²���ļ�ʧ��:����binĿ¼��û��Plugins�ļ���!\n");
			printf("\t����Plugins�ļ�[y/n]?(�س��˳�ϵͳ):\n");
			flushall();
			if('y'==getchar()){
				system("MD Plugins");//ʹ��system����ִ��DOS����MD�������ļ���Plugins
				if(!CopyFile(pname,fname,TRUE)){
					printf("\t�����²��[%s]�ļ�ʧ��!\n", pname);
					system("PAUSE");
					return;
				}
				else{
					printf("\t�ɹ������²��[%s]�ļ�!", pname);
				}
			}
			else{
				printf("\tPFWDSA�˳������봴��Plugins�ļ���!\n");
				system("PAUSE");
				exit(0);
			}
			
		}
		else{
			printf("\t�ɹ������²��dll�ļ�!\n");
		}
		
		if(GetPluginTxt(pname,i)==0){
			printf("\t�ɹ������²������txt�ļ�!\n");
		}
		else if(SetPluginTxt(pname,i)==0){
				printf("\t�ɹ������²������txt�ļ�!\n");
			}
			else{
				printf("\t���ƻ������²��������txt�ļ�ʧ��!\n");
				return;
			}
		nPlugins++;
		hm=LoadLibrary(pname);
		DSAPlugin[i].id=(DWORD)hm;
		pluginfo = (PFUNCPlugInfo)GetProcAddress(hm, "GetPluginInterface");
		if (pluginfo != NULL)
			strcpy(DSAPlugin[i].iPlugin,pluginfo());
		else{
			printf("\t����ӿڵ���������!�ò������PFWDSA�Ĳ��!\n");
		}
		pluginfo = (PFUNCPlugInfo)GetProcAddress(hm, "GetPluginVersion");
		if (pluginfo != NULL)
			strcpy(DSAPlugin[i].version,pluginfo());
		else{
			printf("\t����汾����������!�ò���汾����PFWDSA����!\n");
		}
		printf("\t�ɹ������²��!\n");
	}
}
//1 ��id�����txt�ļ���ȡ�����Ϣ
//2 �ú����ǻ�ȡid�����Ϣ��txt�ı�����
//3 ����pname����ָ������λ��
//4 ���Plugins�ļ��в�����pname�ļ�����Ҫ�����ļ�������Plugins�ļ�����
//5 ���򣬲������ļ�
//6 ��ȡ�ɹ�����0�����򷵻�-1�������ȡ����������ļ�ʧ��
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
		return 0;//�ɹ�
	}	
	else{
		printf("\t��ȡ[%s]���������txt�ļ�ʧ��! \n",fname);
		return -1;//ʧ��
	}
}
//1 ����id�����Ϣ���ɲ����txt�ļ�
//2 �ú�������10������Ϣ:�ӿڡ����ơ�DLL��TXT��·�����汾�����ߡ����ڡ���ַ������
//3 ���롢�����ļ��ɹ�����0;���򷵻�-1���������뱣�����������ļ�ʧ��
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
	printf("\t�������²����������Ϣ(10��):\n");
	printf("iPlugin name nameDLL nameTXT path version author date url description\n");
	printf(" �ӿ�   ����    DLL     TXT  ·��   �汾   ����  ���� ��ַ    ����\n");
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
		printf("\t����[%s]���������txt�ļ�ʧ��!\n",fname);
		return -1;
	}
}

//1 ɾ�����
//2 ��������������Ч�򷵻�
//3 ���򣬵���FreeLibrary�����ͷŸò���Ա����ɾ�������������dll���������ɷ��ʣ�
//4 �������ɾ������Plugins�ļ�����ɾ���ò����dll��txt�ļ������ɻָ��Ҳ�����
//5 ɾ��������system������ɡ�ʵ��ִ��shellָ��del��ʹ��ͨ���*ɾ������ļ�
//6    ɾ��Plugins�ļ����µĲ����dll��exe��txt�ȶ���ļ�
//7    ɾ��Data�ļ����µ�����dat����ļ�
//8    ɾ��Temp�ļ����µ���ʱ���ɵ�����tmp����ļ�
//9 DSAPlugin����Ҫǰ�ƣ������ĿnPlugins��1
//10  ���ǽ�����DSAPlugin�����м���һ�������ϵͳ������ָ���ʾ������
void DeletePlugin(void){
	int i, j, k, id;
	char d, pname[100], pnameDLL[100], ptemp[100], dtemp[100], ttemp[100], temp[100];
	HANDLE hFile;
	WIN32_FIND_DATA FileData;
	char pdir[100], ddir[100], tdir[100], pdll[100];
	
	printf("\t�����������[0,%2d]: ", nPlugins-1);
	scanf("%d",&id);
	if(id<0 || id>=nPlugins){
		printf("\t���������[%d]������Ч��Χ[0,%d]!\n", id, nPlugins-1);
		return;
	}
	//����ɾ���������Ϊɾ���ṩ���ܣ�����"�ܾ�����"����Ϊ�����д���������
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

	printf("\tɾ��[%s]������ɻָ���[y/n]?(�س���ɾ��):", pname);
	flushall();
	if((d=getchar())=='y'){
		//ɾ��Plugins�ļ����µĲ���ļ���������dll��exe��txt�ȸ�ʽ����ļ�
		if(remove(pdll))
		//if(!DeleteFile(pdll))
			printf("\tɾ��[%s]���[%s]�ļ�ʧ��[%d]!\n", pname,pnameDLL,GetLastError());
		else{
			printf("\t�ɹ�ɾ��[%s]���[%s]�ļ�!\n", pname,pnameDLL);
		}
		hFile = FindFirstFile(pdir,  &FileData);//������һ������ļ�
		if (hFile==INVALID_HANDLE_VALUE) {
        		;//printf("\t[%s]���[%s]�ļ�������!\n", pname, pdir);//�����
		}
		else{
			while(1){
				strcat(ptemp, FileData.cFileName);
				if(remove(ptemp)){
					printf("\tɾ��[%s]���[%s]�ļ�ʧ��!\n",pname, ptemp);
					return;
				}
				else{
					printf("\t�ɹ�ɾ��[%s]���[%s]�ļ�!\n",pname, ptemp);
				}
				//�����һ��dll����ļ�
				if (!FindNextFile(hFile, &FileData)) 
                			break;
				strcpy(ptemp,pluginFolder);
			}
			FindClose(hFile);//�ͷŲ����ļ����
		}
		//ɾ��Data�ļ����µĲ�������ļ����ǲ���ļ���+��ţ���չ��Ϊdat�Ķ���ļ�
		hFile = FindFirstFile(ddir,  &FileData);//������һ�������ļ�
		if (hFile==INVALID_HANDLE_VALUE) {
        		;//printf("\t[%s]���������[%s]�ļ�������!\n", pname, ddir);//�����
		}
		else{
			while(1){
				strcat(dtemp, FileData.cFileName);
				if(remove(dtemp)){
					printf("\tɾ��[%s]���[%s]�����ļ�ʧ��!\n",pname, dtemp);
					return;
				}
				else{
					printf("\t�ɹ�ɾ��[%s]���[%s]�����ļ�!\n",pname, dtemp);
				}
				//�����һ������������ļ�
				if (!FindNextFile(hFile, &FileData)) 
                			break;
				strcpy(dtemp,dataFolder);
			}
			FindClose(hFile);//�ͷŲ����ļ����
		}
		//ɾ��Temp�ļ����µĲ����ʾ��ʱ���ɵ������ļ�����չ��Ϊtmp�Ķ���ļ�
		hFile = FindFirstFile(tdir,  &FileData);//������һ����ʱ�ļ�
		if (hFile==INVALID_HANDLE_VALUE) {
        		;//printf("\t[%s]�������ʱ���ɵ�����[%s]�ļ�������!\n", pname, tdir);//�����
		}
		else{
			while(1){
				strcat(ttemp, FileData.cFileName);
				if(remove(ttemp)){
					printf("\tɾ��[%s]���[%s]��ʱ���ɵ������ļ�ʧ��!\n", pname, ttemp);
					return;
				}
				else{
					printf("\t�ɹ�ɾ��[%s]�����ʱ����[%s]�����ļ�!\n", pname, ttemp);
				}
				//�����һ���������ʱ�ļ�
				if (!FindNextFile(hFile, &FileData)) 
                			break;
				strcpy(ttemp,tempFolder);
			}
			FindClose(hFile);//�ͷŲ����ļ����
		}
	}
	else
		printf("\t�ɹ��Ӳ���б���ɾ��[%s]���,����ϵͳ���ָ��ҿ���!\n", pname);

}
//1 ��ȡ�������Ϣ
//2 �����ѯ��������Ч�򷵻�
//3 �����ӡ����������ļ�txt�е�������Ϣ
void RetrievePlugin(void){
	int id;
	
	printf("\t�����������[0,%2d]: ", nPlugins-1);
	scanf("%d",&id);
	if(id<0 || id>=nPlugins){
		printf("\t���������[%d]������Ч��Χ[0,%d]!\n", id, nPlugins-1);
		return;
	}
	printf("\n\t������Ϊ: %d \n", id);
	printf("\t����ӿ�Ϊ: %s \n", DSAPlugin[id].iPlugin);
	printf("\t�������Ϊ: %s \n", DSAPlugin[id].name);
	printf("\t���DLLΪ : %s \n", DSAPlugin[id].nameDLL);
	printf("\t���TXTΪ : %s \n", DSAPlugin[id].nameTXT);
	printf("\t���·��Ϊ: %s \n", DSAPlugin[id].path);
	printf("\t����汾Ϊ: %s \n", DSAPlugin[id].version);
	printf("\t�������Ϊ: %s \n", DSAPlugin[id].author);	
	printf("\t�������Ϊ: %s \n", DSAPlugin[id].date);
	printf("\t���urlΪ:  %s \n", DSAPlugin[id].url);
	printf("\t�������Ϊ: %s \n", DSAPlugin[id].description);
}