/*
*文件：TestDSA05.C
*插件文件，链表应用：实现Josephus游戏及组卷，DSAInterface是插件的挂载点
*作者：刘东良
*日期: 2012-09-10
*/

#include"DSA05.h"

const int StudN=49;//学生数
const int CityN=626;//城市数

char gVersion[20];
char gInterface[20];
//插件信息
BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call){
		case DLL_PROCESS_ATTACH:
			strcpy(gVersion,"1.0.0");
			strcpy(gInterface,"DSAInterface");
			break;
		case DLL_THREAD_ATTACH:	
		case DLL_THREAD_DETACH:		
		case DLL_PROCESS_DETACH:	
			break;
    }
    return TRUE;
}
char* GetPluginVersion(){
	return gVersion;
}
char* GetPluginInterface(){
	return gInterface;
}
//插件框架的接口
void DSAInterface(void){
	int i=0;
	while(i!=3){
		printf("请输入数字选择:\n1 Jose算法组卷\n2 LBSJose游戏\n3 退出\n");
		flushall();
		scanf("%d", &i);
		if(i==1)
			JoseTestPaperApp();
		if(i==2)
			LBSJoseGameApp();
	}
}

void LBSJoseGameApp(void){
	int i,s;
	Student * studArray, * confusionStud;
	City * cityArray, * confusionCity;
	LBSJoseGame * LBSJoseGameBefore, * LBSJoseGameAfter;
	system("CLS");
	printf("基于中国城市地理位置的Josephus游戏\n\n");
	printf("读取学生和城市数据...\n\n");
	system("Data\\DSA052.dat");
	system(".\\Data\\DSA053.dat");
	studArray = ReadStudents("Data\\DSA052.dat");
	cityArray = ReadCities("Data\\DSA053.dat");

	printf("正在整理抽取学生...\n\n");
	Sleep(1000);
	confusionStud = ConfusionStudents(studArray);

	printf("正在整理抽取城市并进行坐标转换...\n\n");
	Sleep(1000);
	confusionCity = ConfusionCities(cityArray);
	s=50;
	while(s>=49){
		printf("请随机输入参加游戏的人数(<%d):\t",  StudN);
		scanf("%d", &s);
	}

	LBSJoseGameBefore = IntiLBSJosepusGame(confusionStud, s, confusionCity);
	printf("请输入 y 按学号排序, 否则随机排序!\n");flushall();
	if(getchar()=='y')
		SelectSortStudID(LBSJoseGameBefore);
	
	OutPutLBSJoseGame("Temp\\DSA054.tmp", LBSJoseGameBefore);
	printf("请输入 y 查看Josephus游戏学生和所在城市, 否则跳过!\n");flushall();
	if(getchar()=='y')
		system("Temp\\DSA054.tmp");
	Sleep(1000);
	printf("正在游戏中...\n\n");
	i=s+1;
	while(i>s){
		printf("请输入报数间隔(<%d):\t", s);flushall();
		scanf("%d", &i);
	}
	LBSJoseGameAfter = LBSJosepusGame(LBSJoseGameBefore, s, i);
	OutPutLBSJoseGame("Temp\\DSA055.tmp", LBSJoseGameAfter);

	Sleep(1000);
	printf("请输入 y 查看Josephus游戏结果, 否则跳过!\n");flushall();
	if(getchar()=='y')
		system("Temp\\DSA055.tmp");
	OutPutLBSJoseGameScreen(LBSJoseGameAfter);

	printf("回放游戏过程!\n");
	system("PAUSE");
	RePlayLBSJoseGame(LBSJoseGameAfter);
	
	DestroyPolyStud(confusionStud);
	DestroyPolyCity(confusionCity);
	DestroyPolyJoseGame(LBSJoseGameAfter);
	system("CLS");
}

void JoseTestPaperApp(void){
	
	Student * studArray, * confusionStud;
	Subject * subArray, * confusionSub;
	JoseTestPaper * testPaperBefore, * testPaperAfter;
	system("CLS");	
	printf("基于Josephus算法《开源GIS》课程设计组卷实用小工具\n\n");

	studArray = ReadStudents("Data\\DSA052.dat");
	subArray = ReadSubjects("Data\\DSA051.dat");	
	testPaperBefore = JosepusTestPaper(studArray, subArray);
	OutPutTestPaper("Temp\\DSA056.tmp", testPaperBefore);
	printf("输入字符 y 查看Jose组卷前数据, 否则不打开文件!\n");
	flushall();
	if(getchar()=='y')
		system("Temp\\DSA056.tmp");
	flushall();

	printf("正在混乱学生数据集...\n\n");
	Sleep(1000);
	confusionStud = ConfusionStudents(studArray);

	printf("正在随机抽取试题数据集...\n\n");
	Sleep(1000);
	confusionSub = ConfusionSubjects(subArray);
	testPaperAfter = JosepusTestPaper(confusionStud, confusionSub);
	OutPutTestPaper("Temp\\DSA057.tmp", testPaperAfter);

	printf("输入字符 y 查看Jose组卷结果, 否则跳过!\n");
	if(getchar()=='y')
		system("Temp\\DSA057.tmp");

	printf("正在排序输出试卷...\n\n");
	Sleep(1000);
	SelectSortPolyStudID(testPaperAfter);
	OutPutTestPaper("Temp\\DSA058.tmp", testPaperAfter);
	system("Temp\\DSA058.tmp");

	printf("考核顺序输出试卷...\n\n");
	Sleep(1000);
	SelectSortPolySubID(testPaperAfter);
	OutPutTestPaperDP("Temp\\DSA059.tmp", testPaperAfter);
	system("Temp\\DSA059.tmp");

	DestroyPolyStud(confusionStud);
	DestroyPolySubject(confusionSub);
	DestroyPolyJose(testPaperAfter);
	system("CLS");
}