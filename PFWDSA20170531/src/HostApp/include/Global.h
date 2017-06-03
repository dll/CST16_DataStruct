/*
*�ļ���Global.h
*PFWDSA ȫ��ͷ�ļ������ȫ�ֱ���������ӿں�PFWDSA�Ĳ���ṹ���塣
*���ߣ�������
*����: 2012-09-10
*/

#ifndef PFWDSA_H
#define PFWDSA_H

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

//��̬ȫ�ֱ���
//PFWDSA.C��ʹ�õ�ȫ�ֱ�������PFWDSA.exe��BaseServices.lib,PluginManager.libģ���ʹ��
extern int nPlugins;//�������
extern char pluginFolder[]; //����ļ���
extern char dataFolder[]; //�����ļ���
extern char tempFolder[]; //��ʱ�ļ���
extern int PFWDSAruntimes; //PFWDSA���д���,1�״�ʹ��

//�ӿ�(��Լ)���
//ͨ��PFUNC���͵ĺ���ָ����ز��
typedef void (*PFUNC)(void);
//ͨ��PFUNCPlugInfo���͵ĺ���ָ���ȡ�����Ϣ������ӿںͲ���汾���������ͼ����DLL����ȫ�ֱ���
typedef char * (*PFUNCPlugInfo)(void);

//����ṹ
struct tagPLUGIN{
	unsigned id;  //������:ʹ�ò���ı��,0,1,2��window�µľ����
	char iPlugin[100]; //����ӿ�:����ӿ�,DSAInterface
	char name[100]; //�������:�������,���Ա�
	char nameDLL[100]; //���������:��̬���ӿ�ȫ��,DSA00.dll
	char nameTXT[100]; //�����������:���������Ϣ�ı��ļ�ȫ��,DSA00.txt
	char path[100]; //���·����������ڵ�·��
	char version[20]; //����汾���汾��1.0.0
	char author[40]; //�������: ѧ�ż�������206004������
	char date[20]; //����������ڣ�2012-09-19
	char url[100]; //���url�������ص�������Դ
	char description[200]; //�����������ϸ���ܲ�����ܣ��������Ϸ
}DSAPlugin[200];//PFWDSA��ʼ����Ϊ200�����

#endif

