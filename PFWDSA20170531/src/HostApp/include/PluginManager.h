/*
*�ļ���PluginManager.h
*PFWDSA ����ܵĹ�����ͷ�ļ�������PFWDSAƽ̨�������ĺ�����
*���ߣ�������
*����: 2012-09-10
*/

#ifndef PLUGMANAGER_H
#define PLUGMANAGER_H

extern int nPlugins;

//PFWDSAƽ̨��ò���ı���Ϣ���ַ��������pnameΪ�����dll�ļ�·�������ƣ����Ͳ���idΪ������
//����������ֵ��0Ϊ�ɹ���-1Ϊʧ��
int GetPluginTxt(char pname[],int id);
//PFWDSAƽ̨�������ı���Ϣ���ַ��������pnameΪ�����dll�ļ�·�������ƣ����Ͳ���idΪ������
//����������ֵ��0Ϊ�ɹ���-1Ϊʧ��
int SetPluginTxt(char pname[],int id);
//PFWDSAƽ̨����µĲ�����޲Σ��޷���ֵ
void InsertPlugin(void);
//PFWDSAƽ̨ɾ�����,���ڴ�ɾ���ͳ��״����ļ�ɾ�����޲Σ��޷���ֵ
void DeletePlugin(void);
//PFWDSAƽ̨��ѯ������޲Σ��޷���ֵ
void RetrievePlugin(void);

#endif