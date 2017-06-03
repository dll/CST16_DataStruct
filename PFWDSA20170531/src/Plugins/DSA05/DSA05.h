/*
*文件：DSA05.h
*插件文件，链表应用：Josephus游戏及组卷设计
*作者：刘东良
*日期: 2012-09-10
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
	unsigned StudID;//学生学号
	char StudName[10];//学生姓名
	struct tagStudent * next;
}Student;

typedef struct tagCHINACITY{
	char province[20],city[20];//省份，城市
	float longtitude, latitude;//经度，纬度
	struct tagCHINACITY *next;
}City;

//双重链表
typedef struct tagLBSJoseGame{
	Student student;//学生
	City city;//城市
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
void gotoxy(int x, int y); //x为列坐标,y为行坐标
void RePlayLBSJoseGame(LBSJoseGame * head);
void SelectSortStudID(LBSJoseGame *p);
void DestroyPolyStud(Student *p);
void DestroyPolyCity(City *p);
void DestroyPolyJoseGame(LBSJoseGame *p);
void LBSJoseGameApp(void);

typedef struct tagSubject{
	unsigned SubID;//试题序号
	char SubTitle[100];//试题标题
	char SubContent[200];//试题内容
	unsigned SubScore;//试题分值
	char SubGrade[100];//试题成绩
	char SubDate[10];//测试日期
	char SubPlace[10];//测试地点
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