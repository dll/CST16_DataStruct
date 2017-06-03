/*
*�ļ���DSA09.C
*����ļ�, ��, DSAInterface�ǲ���Ĺ��ص�
*���ߣ�������
*����: 2012-09-10
*/

#include"DSA09.h"

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

void TestSeqBinTree(void);
void TestLinkBinTree(void);
void TestLinkBinTreeX(void);
void TestHuffmanTreeCoding(void);
void TestCSTree(void);

void DSAInterface(void){
	int i=0;
	while(i!=6){
		printf("\n\t���Ͷ������㷨��ʾ\
			\n����������ѡ��:\n1 TestSeqBinTree\n2 TestLinkBinTree\
			\n3 TestLinkBinTreeX\n4 TestHuffmanTreeCoding\n5 TestCSTree \n6�˳�\n");
		flushall();
		scanf("%d", &i);
		switch(i){
			case 1:
				TestSeqBinTree();break;
			case 2:
				TestLinkBinTree();break;
			case 3:
				TestLinkBinTreeX();break;
			case 4:
				TestHuffmanTreeCoding();break;
			case 5:
				TestCSTree();break;
			case 6:
				return;
		}
		system("PAUSE");
	}
}

void TestSeqBinTree(void){

	int n;
	SeqBinTree SeqBinTree;
	printf("��������򴴽��������Ľ����(����������):��6\n");
	scanf("%d", &n);flushall();
	printf("��������򴴽�������������:��ABCD0E00000F000\n");
	CreateSeqBinTree(SeqBinTree,n);
	LevelTraverseTree(SeqBinTree);

	system("PAUSE");
	printf("���ļ��ж�ȡ������������������\n");
	CreateSeqBinTreeFromFile(SeqBinTree);
	LevelTraverseTree(SeqBinTree);system("PAUSE");
	LevelPrintTree(SeqBinTree);system("PAUSE");
	LevelPrintTree1(SeqBinTree);system("PAUSE");
	LevelPrintTree2(SeqBinTree);system("PAUSE");
	LevelPrintTree3(SeqBinTree);system("PAUSE");
	printf("\n�������ĸ߶�Ϊ:%d\n", GetSBTreeHigh(SeqBinTree));
	system("PAUSE");

}


void TestLinkBinTree(void){

	LinkBinTree *lbTree;
	char DLR[]={'4','2','1','3','6','5','7'};
	char LDR[]={'1','2','3','4','5','6','7'};

	printf("�����ַ����д���������!\n");
	lbTree = CreateLinkBinTree();
	PreOrderTree(lbTree);
	printf("\n�������ĸ߶�Ϊ:%d\n", GetLBTreeHigh(lbTree));
	DestroyLinkBinTree(lbTree);

	printf("������������д���������!\n");
	lbTree=CreateDLRLDR(DLR, LDR, 7);
	PreOrderTree(lbTree);

	printf("\n�ǵݹ�ǰ�������������\t");
	PreOrderNuReserveTraverse(lbTree);

	DestroyLinkBinTree(lbTree);
}

void TestLinkBinTreeX(void){
	int TreeWidth,TreeHeight,LogicalHeight,RootX,RootY,Choice;
	BintreeNode *pRoot=NULL;
	while(1)
	{
		printf("\t��������ʾ\n\n");
		printf("�ӹ��Ͳ���	1.�������봴��������\n");
		printf("\t	2.�ļ���������������\n");
		printf("\t	11.��������\n");
		printf("\t	12.�����ҽ��\n");
		printf("\t	13.ɾ�����\n\n");
		printf("�����Ͳ���	3.��������������ļ�\n");
		printf("\t	4.ǰ�����������\n");
		printf("\t	5.�������������\n");
		printf("\t	6.�������������\n");
		printf("\t	7.��ʾҶ�ӽ��\n");
		printf("\t	8.��ʾ�������ṹ\n");
		printf("\t	10.����\n");
		printf("\t	14.���Ҳ���ʾ�ӽ��\n\n");
		printf("�����Ͳ���	9.�������������\n");
		printf("\t	0.�˳�\n\n");
		printf("��ѡ�����ֽ��в���...:");
		scanf("%d",&Choice);
		switch(Choice)
		{
			case 1:
				if(pRoot)
					DeleteBintree(pRoot);
				printf("#��������, ����#�㹻��ʱ���Զ�����,������������!\n");
				CreateBintree(&pRoot,InputFromKeyboard);
				printf("�ɹ�����������!\n");
				break;
			case 2:
				printf("�����������ļ�:");
				scanf("%s",FileName);
				fp=fopen(FileName,"rt");
				if(!fp)
				{
					printf("���ļ�ʧ��!\n");
					break;
				}
				if(pRoot)
					DeleteBintree(pRoot);
				CreateBintree(&pRoot,InputFromFile);
				fclose(fp);
				printf("�ɹ��������ļ�!\n");
				break;
			case 3:
				if(!pRoot)
				{
					printf("������û�д���!\n");
					break;
				}
				printf("�����뱣�������ļ�:");
				scanf("%s",FileName);
				fp=fopen(FileName,"wt");
				if(!fp)
				{
					printf("���ܴ������ļ�\n");
					break;
				}
				WriteDataToFile(pRoot);
				fclose(fp);
				printf("�ɹ����������ļ�!\n");
				break;
			case 4:
				if(!pRoot)
				{
					printf("������û�д���!\n");
					break;
				}
				PreOrder(pRoot,Visit);
				break;
			case 5:
				if(!pRoot)
				{
					printf("������û�д���!\n");
					break;
				}
				InOrder(pRoot,Visit);
				break;
			case 6:
				if(!pRoot)
				{
					printf("������û�д���!\n");
					break;
				}
				PostOrder(pRoot,Visit);
				break;
			case 7:
				if(!pRoot)
				{
					printf("������û�д���!\n");
					break;
				}
				ShowLeavesNode(pRoot,Visit);
				break;
			case 8:
				if(!pRoot)
				{
					printf("������û�д���!!\n");
					break;
				}
				PrintBinTree(pRoot, Depth(pRoot));

				PrintTree(pRoot,0);
				
				PrintBinTreeGL(pRoot);
				
				system("PAUSE");
				system("CLS");
				LogicalHeight=GetBintreeHeight(pRoot);
				TreeWidth=2*R*((int)pow(2,LogicalHeight-1)*2-1);
				TreeHeight=2*R*(2*LogicalHeight-1);
				if(TreeWidth>639||TreeHeight>479)
				{
					printf("�Բ��𣬶�����̫�󣬲�����ʾ!\n");
					break;
				}
				RootX=(GetMaxX()+1)/2;
				RootY=(GetMaxY()+1-TreeHeight)/10;
				DrawTree(pRoot,TreeWidth,RootX,RootY);

				break;
			case 9:
				if(!pRoot)
				{
					printf("������û�д���!\n");
					break;
				}
				DeleteBintree(pRoot);
				pRoot=NULL;
				break;
			case 10:
				{//��case��������������Ҫ��{}!
				char x;
				BintreeNode *p, *f;
				printf("������Ҫ���ҵĽ��(char x):\n");flushall();
				scanf("%c", &x);
				SearchNode(pRoot, x, &p, &f);
				if(p==NULL)
				{
					printf("û���ҵ�%c!\n", x);
					break;
				}
				printf("�ҵ�%c!\n", p->Data);
				p=NULL;
				break;
				}
			case 11:
				{
					char x;
					BintreeNode *p, *f;
					if(!pRoot)
					{
						printf("������û�д���!\n");
						break;
					}
					printf("������Ҫ�������ӽ���λ�ý��(char x):\n");flushall();
					scanf("%c", &x);
					SearchNode(pRoot, x, &p, &f);
					if(p==NULL)
					{
						printf("û���ҵ�%c!\n", x);
						break;
					}
					printf("������Ҫ�������ӽ��(char x):\n");flushall();
					scanf("%c", &x);
					p=InsertLeftNode(p, x);
					PrintBinTree(p, Depth(p));

					p=NULL;f=NULL;
					break;
				}
			case 12:
				{
					char x;
					BintreeNode *p, *f;
					if(!pRoot)
					{
						printf("������û�д���!\n");
						break;
					}
					printf("������Ҫ�����Һ��ӽ���λ�ý��(char x):\n");flushall();
					scanf("%c", &x);
					SearchNode(pRoot, x, &p, &f);
					if(p==NULL)
					{
						printf("û���ҵ�%c!\n", x);
						break;
					}
					printf("������Ҫ�����Һ��ӽ��(char x):\n");flushall();
					scanf("%c", &x);
					p=InsertRightNode(p, x);
					PrintBinTree(p, Depth(p));

					p=NULL;f=NULL;
					break;
				}
			case 13:
				{//��case��������������Ҫ��{}!
				char x;
				if(!pRoot)
				{
					printf("������û�д���!\n");
					break;
				}
				printf("������Ҫɾ���Ľ��(char x):\n");flushall();
				scanf("%c", &x);
				DeleteNodeX(&pRoot, x);
				break;
				}
			case 14:
				{
					char x;
					BintreeNode *p, *f;
					if(!pRoot)
					{
						printf("������û�д���!\n");
						break;
					}
					printf("������Ҫ�������ӽ���λ�ý��(char x):\n");flushall();
					scanf("%c", &x);
					SearchNode(pRoot, x, &p, &f);
					if(p==NULL)
					{
						printf("û���ҵ�%c!\n", x);
						break;
					}
					PrintBinTree(p, Depth(p));
					LogicalHeight=GetBintreeHeight(p);
					TreeWidth=2*R*((int)pow(2,LogicalHeight-1)*2-1);
					TreeHeight=2*R*(2*LogicalHeight-1);
					if(TreeWidth>639||TreeHeight>479)
					{
						printf("�Բ��𣬶�����̫�󣬲�����ʾ!\n");
						break;
					}
					RootX=(GetMaxX()+1)/2;
					RootY=(GetMaxY()+1-TreeHeight)/10;
					DrawTree(p,TreeWidth,RootX,RootY);

					p=NULL;f=NULL;
					break;
				}

			case 0:
				if(pRoot!=NULL) DeleteBintree(pRoot);
				//exit(0);
				return;
			default:
				printf("��������Ч����ѡ��˵�!\n");
				break;
		}
		flushall();
		printf("\n");
		system("PAUSE");
		system("CLS");
	}
	DestroyBinTree(pRoot);

}

void TestHuffmanTreeCoding(void)
{
	HuffmanTree htree=NULL;
	HuffmanCode hcode=NULL;
	int n=8;
	double w[9]={0, 0.05, 0.29, 0.07, 0.08, 0.14, 0.23, 0.03, 0.11};//w[0]δ�ã�DSA�����飬λ�����
	
	double EngChar[27] = {0, 8.19, 1.47, 3.83, 3.91, 12.25, 2.26, 1.71,\
		4.57, 7.10, 0.14, 0.41, 3.77, 3.34, 7.06, 7.26, 2.89, 0.09,\
		6.85, 6.36, 9.41, 2.58, 1.09, 1.59, 0.21, 1.58, 0.08};
	
	char * hiDSA="HiDSA";

	void HuffmanCoding4(HuffmanTree *HT, double *w, int n);

	/**/
	printf("\n���ڹ��������ı���ͽ���\n");
	HuffmanCoding(htree, hcode, w, n);
	
	system("PAUSE");
	system("CLS");
	HuffmanCoding2(htree, hcode, w, n);
	
	system("PAUSE");
	system("CLS");
	
	HuffmanCoding3(htree, hcode, EngChar, 26);
	HuffmanCoding4(&htree, EngChar, 26);

	printf("\n���ڹ��������ı���ͽ���,����������в���, 0->�˳�\n");
	while(getchar()!='0'){
		EncodeHC();
		DecodeHC(htree);flushall();
		printf("\n���ڹ��������ı���ͽ���,����������в���, 0->�˳�\n");
	}
}

void TestCSTree(void){
	CSTree  cstree;
	cstree=(CSTree)malloc(sizeof(CSTree));
	//��ʼ����
	InitCSTree(&cstree);
	//������
	CreateCSTree(&cstree);
	//�����
	PrintCSTree(&cstree);
	//������
	DestroyCSTree(&cstree);
}