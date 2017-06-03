/*
*�ļ���DSATestServices.h
*PFWDSA ����ܵ����ݽṹ���㷨���Ե�ͷ�ļ�������������Ҫ�ĺ�����
*  ϣ��ƽ̨�û�����չ�ö�̬���ӿ⣬�������Ĳ��Թ���
*���ߣ�������
*����: 2012-12-21
*/

#ifndef DSATESTSERVICES_H
#define DSATESTSERVICES_H

#include<time.h>

//����һ�����������
//const int�����ֱ���min��maxֵ
//���ش�[min,max)֮���һ�����������
int RandInt(const int min, const int max);
//����n���ȵ������������
//const int�����ֱ���min��maxֵ
//int n����Ϊ���鳤��
//int a����Ϊ��������
//�޷���ֵ
void RandIntArray(const int min, const int max, int a[], int n);
//����һ����������
//const double�����ֱ���min��maxֵ
//���ش�[min,max)֮���һ�����������
double RandDouble(const double min, const double max);
//����n���ȵ������������
//const double�����ֱ���min��maxֵ
//int n����Ϊ���鳤��
//int a����Ϊ��������
//�޷���ֵ
void RandDoubleArray(const double min, const double max, double a[], int n);

//C����tm����,�Լ�ʵ��tms��ʱ����뼶��Ҳ���Է�װtmʵ��
struct tms     //����ʱ��ṹ�壬����ʱ����ͺ��� 
{ 
	int hours,minutes,seconds; 
	int milliseconds;//����
}timec,tmpc,totalc;    //timec��ʱ��ʾ��tmpc�洢��һ�׶�ʱ�䣬totalc����ʱ�� 
int cnt;//����Sleep�����ۼƺ������

//��ʱ����
//int mseconds����Ϊ�����趨ʱ��
//�����ַ�char����,�����س�,����'\r'��ʱ����;�����ո�,����' '��ʾ�˴μ�ʱ,��ʼ����ʱ��;
//����'ESC',����'ESC';������ʾ��������
//��ʱ��msecondsʱ����'m'
char TimeClock(int mseconds);


void RandCharArray(char min, char max, char a[], int n);
void PrintiArray(int a[], int n);
void PrintdArray(double a[], int n);
void PrintcArray(char a[], int n);
//ͨ�ñȽϺ���
int ICmp(const void *a, const void *b);
int CCmp(const void *a , const void *b);
int DCmp(const void *a, const void *b);
int FCmp(const void *a, const void *b);
//ͨ�ý�������
void VSwap(void * vp1, void *vp2, int size);



#endif