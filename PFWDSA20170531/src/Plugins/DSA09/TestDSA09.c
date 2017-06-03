/*
*文件：DSA09.C
*插件文件, 树, DSAInterface是插件的挂载点
*作者：刘东良
*日期: 2012-09-10
*/

#include"DSA09.h"

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

void TestSeqBinTree(void);
void TestLinkBinTree(void);
void TestLinkBinTreeX(void);
void TestHuffmanTreeCoding(void);
void TestCSTree(void);

void DSAInterface(void){
	int i=0;
	while(i!=6){
		printf("\n\t树和二叉树算法演示\
			\n请输入数字选择:\n1 TestSeqBinTree\n2 TestLinkBinTree\
			\n3 TestLinkBinTreeX\n4 TestHuffmanTreeCoding\n5 TestCSTree \n6退出\n");
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
	printf("请输入层序创建二叉树的结点数(不包括虚结点):如6\n");
	scanf("%d", &n);flushall();
	printf("请输入层序创建二叉树的序列:如ABCD0E00000F000\n");
	CreateSeqBinTree(SeqBinTree,n);
	LevelTraverseTree(SeqBinTree);

	system("PAUSE");
	printf("从文件中读取（满）二叉树的序列\n");
	CreateSeqBinTreeFromFile(SeqBinTree);
	LevelTraverseTree(SeqBinTree);system("PAUSE");
	LevelPrintTree(SeqBinTree);system("PAUSE");
	LevelPrintTree1(SeqBinTree);system("PAUSE");
	LevelPrintTree2(SeqBinTree);system("PAUSE");
	LevelPrintTree3(SeqBinTree);system("PAUSE");
	printf("\n二叉树的高度为:%d\n", GetSBTreeHigh(SeqBinTree));
	system("PAUSE");

}


void TestLinkBinTree(void){

	LinkBinTree *lbTree;
	char DLR[]={'4','2','1','3','6','5','7'};
	char LDR[]={'1','2','3','4','5','6','7'};

	printf("输入字符序列创建二叉树!\n");
	lbTree = CreateLinkBinTree();
	PreOrderTree(lbTree);
	printf("\n二叉树的高度为:%d\n", GetLBTreeHigh(lbTree));
	DestroyLinkBinTree(lbTree);

	printf("先序和中序序列创建二叉树!\n");
	lbTree=CreateDLRLDR(DLR, LDR, 7);
	PreOrderTree(lbTree);

	printf("\n非递归前序遍历二叉树：\t");
	PreOrderNuReserveTraverse(lbTree);

	DestroyLinkBinTree(lbTree);
}

void TestLinkBinTreeX(void){
	int TreeWidth,TreeHeight,LogicalHeight,RootX,RootY,Choice;
	BintreeNode *pRoot=NULL;
	while(1)
	{
		printf("\t二叉树演示\n\n");
		printf("加工型操作	1.键盘输入创建二叉树\n");
		printf("\t	2.文件读数创建二叉树\n");
		printf("\t	11.插入左结点\n");
		printf("\t	12.插入右结点\n");
		printf("\t	13.删除结点\n\n");
		printf("引用型操作	3.保存二叉树数据文件\n");
		printf("\t	4.前序遍历二叉树\n");
		printf("\t	5.中序遍历二叉树\n");
		printf("\t	6.后序遍历二叉树\n");
		printf("\t	7.显示叶子结点\n");
		printf("\t	8.显示二叉树结构\n");
		printf("\t	10.查找\n");
		printf("\t	14.查找并显示子结点\n\n");
		printf("销毁型操作	9.清除二叉树数据\n");
		printf("\t	0.退出\n\n");
		printf("请选择数字进行操作...:");
		scanf("%d",&Choice);
		switch(Choice)
		{
			case 1:
				if(pRoot)
					DeleteBintree(pRoot);
				printf("#代表虚结点, 输入#足够多时会自动结束,并创建二叉树!\n");
				CreateBintree(&pRoot,InputFromKeyboard);
				printf("成功创建二叉树!\n");
				break;
			case 2:
				printf("请输入数据文件:");
				scanf("%s",FileName);
				fp=fopen(FileName,"rt");
				if(!fp)
				{
					printf("打开文件失败!\n");
					break;
				}
				if(pRoot)
					DeleteBintree(pRoot);
				CreateBintree(&pRoot,InputFromFile);
				fclose(fp);
				printf("成功读数据文件!\n");
				break;
			case 3:
				if(!pRoot)
				{
					printf("二叉树没有创建!\n");
					break;
				}
				printf("请输入保存数据文件:");
				scanf("%s",FileName);
				fp=fopen(FileName,"wt");
				if(!fp)
				{
					printf("不能打开数据文件\n");
					break;
				}
				WriteDataToFile(pRoot);
				fclose(fp);
				printf("成功保存数据文件!\n");
				break;
			case 4:
				if(!pRoot)
				{
					printf("二叉树没有创建!\n");
					break;
				}
				PreOrder(pRoot,Visit);
				break;
			case 5:
				if(!pRoot)
				{
					printf("二叉树没有创建!\n");
					break;
				}
				InOrder(pRoot,Visit);
				break;
			case 6:
				if(!pRoot)
				{
					printf("二叉树没有创建!\n");
					break;
				}
				PostOrder(pRoot,Visit);
				break;
			case 7:
				if(!pRoot)
				{
					printf("二叉树没有创建!\n");
					break;
				}
				ShowLeavesNode(pRoot,Visit);
				break;
			case 8:
				if(!pRoot)
				{
					printf("二叉树没有创建!!\n");
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
					printf("对不起，二叉树太大，不能显示!\n");
					break;
				}
				RootX=(GetMaxX()+1)/2;
				RootY=(GetMaxY()+1-TreeHeight)/10;
				DrawTree(pRoot,TreeWidth,RootX,RootY);

				break;
			case 9:
				if(!pRoot)
				{
					printf("二叉树没有创建!\n");
					break;
				}
				DeleteBintree(pRoot);
				pRoot=NULL;
				break;
			case 10:
				{//在case中声明变量，需要加{}!
				char x;
				BintreeNode *p, *f;
				printf("请输入要查找的结点(char x):\n");flushall();
				scanf("%c", &x);
				SearchNode(pRoot, x, &p, &f);
				if(p==NULL)
				{
					printf("没有找到%c!\n", x);
					break;
				}
				printf("找到%c!\n", p->Data);
				p=NULL;
				break;
				}
			case 11:
				{
					char x;
					BintreeNode *p, *f;
					if(!pRoot)
					{
						printf("二叉树没有创建!\n");
						break;
					}
					printf("请输入要插入左孩子结点的位置结点(char x):\n");flushall();
					scanf("%c", &x);
					SearchNode(pRoot, x, &p, &f);
					if(p==NULL)
					{
						printf("没有找到%c!\n", x);
						break;
					}
					printf("请输入要插入左孩子结点(char x):\n");flushall();
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
						printf("二叉树没有创建!\n");
						break;
					}
					printf("请输入要插入右孩子结点的位置结点(char x):\n");flushall();
					scanf("%c", &x);
					SearchNode(pRoot, x, &p, &f);
					if(p==NULL)
					{
						printf("没有找到%c!\n", x);
						break;
					}
					printf("请输入要插入右孩子结点(char x):\n");flushall();
					scanf("%c", &x);
					p=InsertRightNode(p, x);
					PrintBinTree(p, Depth(p));

					p=NULL;f=NULL;
					break;
				}
			case 13:
				{//在case中声明变量，需要加{}!
				char x;
				if(!pRoot)
				{
					printf("二叉树没有创建!\n");
					break;
				}
				printf("请输入要删除的结点(char x):\n");flushall();
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
						printf("二叉树没有创建!\n");
						break;
					}
					printf("请输入要插入左孩子结点的位置结点(char x):\n");flushall();
					scanf("%c", &x);
					SearchNode(pRoot, x, &p, &f);
					if(p==NULL)
					{
						printf("没有找到%c!\n", x);
						break;
					}
					PrintBinTree(p, Depth(p));
					LogicalHeight=GetBintreeHeight(p);
					TreeWidth=2*R*((int)pow(2,LogicalHeight-1)*2-1);
					TreeHeight=2*R*(2*LogicalHeight-1);
					if(TreeWidth>639||TreeHeight>479)
					{
						printf("对不起，二叉树太大，不能显示!\n");
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
				printf("请输入有效数字选择菜单!\n");
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
	double w[9]={0, 0.05, 0.29, 0.07, 0.08, 0.14, 0.23, 0.03, 0.11};//w[0]未用，DSA中数组，位序概念
	
	double EngChar[27] = {0, 8.19, 1.47, 3.83, 3.91, 12.25, 2.26, 1.71,\
		4.57, 7.10, 0.14, 0.41, 3.77, 3.34, 7.06, 7.26, 2.89, 0.09,\
		6.85, 6.36, 9.41, 2.58, 1.09, 1.59, 0.21, 1.58, 0.08};
	
	char * hiDSA="HiDSA";

	void HuffmanCoding4(HuffmanTree *HT, double *w, int n);

	/**/
	printf("\n基于哈夫曼树的编码和解码\n");
	HuffmanCoding(htree, hcode, w, n);
	
	system("PAUSE");
	system("CLS");
	HuffmanCoding2(htree, hcode, w, n);
	
	system("PAUSE");
	system("CLS");
	
	HuffmanCoding3(htree, hcode, EngChar, 26);
	HuffmanCoding4(&htree, EngChar, 26);

	printf("\n基于哈夫曼树的编码和解码,按任意键进行测试, 0->退出\n");
	while(getchar()!='0'){
		EncodeHC();
		DecodeHC(htree);flushall();
		printf("\n基于哈夫曼树的编码和解码,按任意键进行测试, 0->退出\n");
	}
}

void TestCSTree(void){
	CSTree  cstree;
	cstree=(CSTree)malloc(sizeof(CSTree));
	//初始化树
	InitCSTree(&cstree);
	//创建树
	CreateCSTree(&cstree);
	//输出树
	PrintCSTree(&cstree);
	//销毁树
	DestroyCSTree(&cstree);
}