/*
*�ļ���BaseServices.h
*PFWDSA ����ܵĻ�������ͷ�ļ�������PFWDSAƽ̨��Ҫ�Ļ������ܺ�����
*���ߣ�������
*����: 2012-09-10
*/

#ifndef BASESERVICES_H
#define BASESERVICES_H

//PFWDSA����PluginsĿ¼�µĲ�����ز���������޲Σ��޷���ֵ
void LoadPlugin(void);
//ѡ����������ʾ���޲Σ��޷���ֵ
void ChoicePlugin(void);
//����id���в�������Ͳ���Ϊ�����ţ��޷���ֵ
void RunPlugin(int id);
//�ͷ�ϵͳʹ�õ���Դ���޲Σ��޷���ֵ
void DestroyPlugin(void);
//PFWDSA���롢ɾ������ѯ������޲Σ��޷���ֵ
void ManagerPlugin(void);
//��PFWDSA.log��־�ļ��ж�ȡʹ�ô������޲Σ��޷���ֵ
void ReadSysRunTimes(void);
//������־(ʹ�ô�����ʱ��)��PFWDSA.log�ļ��У��޲Σ��޷���ֵ
void SaveSysRunTimes(void);
//����i��ӡPFWDSA���ı����棬���Ͳ�������4�ֲ�ͬ���棬�޷���ֵ
void PrintPFWDSATextUI(int i);
//��ӡ�����ź����ƣ��޲Σ��޷���ֵ
void ShowPluginsIDName(void);

#endif