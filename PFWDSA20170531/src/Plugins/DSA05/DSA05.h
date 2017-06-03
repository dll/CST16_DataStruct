/*
*�ļ���DSA05.h
*����ļ�������Ӧ�ã�Josephus��Ϸ��������
*���ߣ�������
*����: 2012-09-10
*/

#ifndef JOSEGAME_H
#define JOSEGAME_H

#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

extern char gVersion[20];
extern char* GetPluginVersion(void);
extern char gInterface[20];
extern char* GetPluginInterface(void);

typedef struct tagStudent{
	unsigned StudID;//ѧ��ѧ��
	char StudName[10];//ѧ������
	struct tagStudent * next;
}Student;

typedef struct tagCHINACITY{
	char province[20],city[20];//ʡ�ݣ�����
	float longtitude, latitude;//���ȣ�γ��
	struct tagCHINACITY *next;
}City;

//˫������
typedef struct tagLBSJoseGame{
	Student student;//ѧ��
	City city;//����
	struct tagLBSJoseGame * next;
}LBSJoseGame;

int RandInt(int min, int max);
Student * ReadStudents(char * fnameStud);
City * ReadCities(char * fnameCity);
Student *  ConfusionStudents(Student *stud);
City * ConfusionCities(City *city);
LBSJoseGame * IntiLBSJosepusGame(Student * stud, int nStud, City * city);
LBSJoseGame * LBSJosepusGame(LBSJoseGame * head,int total, int inter);
void OutPutLBSJoseGame(char * fname, LBSJoseGame * head);
void OutPutLBSJoseGameScreen(LBSJoseGame * head);
void gotoxy(int x, int y); //xΪ������,yΪ������
void RePlayLBSJoseGame(LBSJoseGame * head);
void SelectSortStudID(LBSJoseGame *p);
void DestroyPolyStud(Student *p);
void DestroyPolyCity(City *p);
void DestroyPolyJoseGame(LBSJoseGame *p);
void LBSJoseGameApp(void);

typedef struct tagSubject{
	unsigned SubID;//�������
	char SubTitle[100];//�������
	char SubContent[200];//��������
	unsigned SubScore;//�����ֵ
	char SubGrade[100];//����ɼ�
	char SubDate[10];//��������
	char SubPlace[10];//���Եص�
	struct tagSubject * next;
}Subject;

typedef struct tagTestPaper{
	Student student;
	Subject subject;
	struct tagTestPaper * next;
}JoseTestPaper;
Subject * ReadSubjects(char * fnameSub);
Subject * ConfusionSubjects(Subject *sub);
JoseTestPaper * JosepusTestPaper(Student * stud, Subject * sub);
void OutPutTestPaper(char * fname, JoseTestPaper * testPaper);
void OutPutTestPaperDP(char * fname, JoseTestPaper * testPaper);
void SelectSortPolyStudID(JoseTestPaper *p);
void SelectSortPolySubID(JoseTestPaper *p);
void JoseTestPaperApp(void);
void DestroyPolyStud(Student * );
void DestroyPolySubject(Subject *);
void DestroyPolyJoseTest(JoseTestPaper * );


#endif