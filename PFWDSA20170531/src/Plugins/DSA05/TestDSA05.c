/*
*�ļ���TestDSA05.C
*����ļ�������Ӧ�ã�ʵ��Josephus��Ϸ�����DSAInterface�ǲ���Ĺ��ص�
*���ߣ�������
*����: 2012-09-10
*/

#include"DSA05.h"

const int StudN=49;//ѧ����
const int CityN=626;//������

char gVersion[20];
char gInterface[20];
//�����Ϣ
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
//�����ܵĽӿ�
void DSAInterface(void){
	int i=0;
	while(i!=3){
		printf("����������ѡ��:\n1 Jose�㷨���\n2 LBSJose��Ϸ\n3 �˳�\n");
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
	printf("�����й����е���λ�õ�Josephus��Ϸ\n\n");
	printf("��ȡѧ���ͳ�������...\n\n");
	system("Data\\DSA052.dat");
	system(".\\Data\\DSA053.dat");
	studArray = ReadStudents("Data\\DSA052.dat");
	cityArray = ReadCities("Data\\DSA053.dat");

	printf("���������ȡѧ��...\n\n");
	Sleep(1000);
	confusionStud = ConfusionStudents(studArray);

	printf("���������ȡ���в���������ת��...\n\n");
	Sleep(1000);
	confusionCity = ConfusionCities(cityArray);
	s=50;
	while(s>=49){
		printf("���������μ���Ϸ������(<%d):\t",  StudN);
		scanf("%d", &s);
	}

	LBSJoseGameBefore = IntiLBSJosepusGame(confusionStud, s, confusionCity);
	printf("������ y ��ѧ������, �����������!\n");flushall();
	if(getchar()=='y')
		SelectSortStudID(LBSJoseGameBefore);
	
	OutPutLBSJoseGame("Temp\\DSA054.tmp", LBSJoseGameBefore);
	printf("������ y �鿴Josephus��Ϸѧ�������ڳ���, ��������!\n");flushall();
	if(getchar()=='y')
		system("Temp\\DSA054.tmp");
	Sleep(1000);
	printf("������Ϸ��...\n\n");
	i=s+1;
	while(i>s){
		printf("�����뱨�����(<%d):\t", s);flushall();
		scanf("%d", &i);
	}
	LBSJoseGameAfter = LBSJosepusGame(LBSJoseGameBefore, s, i);
	OutPutLBSJoseGame("Temp\\DSA055.tmp", LBSJoseGameAfter);

	Sleep(1000);
	printf("������ y �鿴Josephus��Ϸ���, ��������!\n");flushall();
	if(getchar()=='y')
		system("Temp\\DSA055.tmp");
	OutPutLBSJoseGameScreen(LBSJoseGameAfter);

	printf("�ط���Ϸ����!\n");
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
	printf("����Josephus�㷨����ԴGIS���γ�������ʵ��С����\n\n");

	studArray = ReadStudents("Data\\DSA052.dat");
	subArray = ReadSubjects("Data\\DSA051.dat");	
	testPaperBefore = JosepusTestPaper(studArray, subArray);
	OutPutTestPaper("Temp\\DSA056.tmp", testPaperBefore);
	printf("�����ַ� y �鿴Jose���ǰ����, ���򲻴��ļ�!\n");
	flushall();
	if(getchar()=='y')
		system("Temp\\DSA056.tmp");
	flushall();

	printf("���ڻ���ѧ�����ݼ�...\n\n");
	Sleep(1000);
	confusionStud = ConfusionStudents(studArray);

	printf("���������ȡ�������ݼ�...\n\n");
	Sleep(1000);
	confusionSub = ConfusionSubjects(subArray);
	testPaperAfter = JosepusTestPaper(confusionStud, confusionSub);
	OutPutTestPaper("Temp\\DSA057.tmp", testPaperAfter);

	printf("�����ַ� y �鿴Jose�����, ��������!\n");
	if(getchar()=='y')
		system("Temp\\DSA057.tmp");

	printf("������������Ծ�...\n\n");
	Sleep(1000);
	SelectSortPolyStudID(testPaperAfter);
	OutPutTestPaper("Temp\\DSA058.tmp", testPaperAfter);
	system("Temp\\DSA058.tmp");

	printf("����˳������Ծ�...\n\n");
	Sleep(1000);
	SelectSortPolySubID(testPaperAfter);
	OutPutTestPaperDP("Temp\\DSA059.tmp", testPaperAfter);
	system("Temp\\DSA059.tmp");

	DestroyPolyStud(confusionStud);
	DestroyPolySubject(confusionSub);
	DestroyPolyJose(testPaperAfter);
	system("CLS");
}