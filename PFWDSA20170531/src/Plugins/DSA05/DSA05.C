/*
*文件：DSA05.C
*插件文件，链表应用：josephus游戏及组卷设计
*作者：刘东良
*日期: 2012-09-10
*/

#include"DSA05.h"

extern int StudN;//学生数
extern int CityN;//城市数

int RandInt(int min, int max){
	int minValue=min, maxValue=max;
	srand((unsigned) time(NULL));
	return  minValue+(int)(rand() % (maxValue-minValue+1));
}
Student * ReadStudents(char * fnameStud){
	Student *h, *p, * s;
	FILE * pf;
	// 先建立无头结点的单循环链表
	pf=fopen(fnameStud, "r");
	if(!pf){printf("打开%s文件失败!\n", fnameStud);exit(0);}
	p=h = (Student *) malloc (sizeof (Student));
	fscanf(pf, "%d\t%s\n", &p->StudID, p->StudName);

	while (!feof(pf)) {//正序建表法
		s = (Student*) malloc (sizeof (Student));
		fscanf(pf, "%d\t%s", &s->StudID, s->StudName);    // 输入元素值
		
		p->next = s;//插入操作的1，入链
		p = s;  // 2，断链，3，拉链
	}
	p->next = h; 
	fclose(pf);
	return h;
}
City * ReadCities(char * fnameCity){
	City *h, *p, * s;
	FILE * pf;
	// 先建立无头结点的单循环链表
	pf=fopen(fnameCity, "r");
	if(!pf){printf("打开%s文件失败!\n", fnameCity);exit(0);}
	p= h = (City *) malloc (sizeof (City));
	fscanf(pf, "%s %s %f %f\n", p->province, p->city, \
		&p->latitude, &p->longtitude);
	while (!feof(pf)) {//正序建表法
		s = (City*) malloc (sizeof (City));
		fscanf(pf, "%s %s %f %f\n", s->province, s->city, \
			&p->latitude, &p->longtitude);
		
		p->next = s;//插入操作的1，入链
		p = s;  // 2，断链，3，拉链
	}
	p->next = h; 
	fclose(pf);
	return h;
}
Student *  ConfusionStudents(Student *stud){
	int m, k, c;
	Student * h, *p, *q, *n, *s;
	n=h = (Student *) malloc (sizeof (Student));
	p=stud;m=0;
	h=NULL;
	c=RandInt(1, StudN);

	while(m<StudN){
		k=1;
		while(k<c){
			k++;
			q=p;
			p=p->next;
		}	
		q->next = p->next;
		s=(Student *) malloc (sizeof (Student));
		s->StudID=p->StudID;
		strcpy(s->StudName, p->StudName);
		if(!h){
			h=s; n=h;
		}
		else{
			n->next=s;
			n=n->next;
		}
		free(p);
		p=q;
		m++;
	}
	n->next = h;
	return h;
}

City * ConfusionCities(City *city){
	int m, k, c;
	City * h, *p, *q, *n, *s;
	n=h = (City *) malloc (sizeof (City));
	p=city;m=0;
	h=NULL;
	c=RandInt(1, CityN);

	while(m<CityN){
		k=1;
		while(k<c){
			k++;
			q=p;
			p=p->next;
		}	
		q->next = p->next;
		s=(City *) malloc (sizeof (City));
		strcpy(s->province, p->province);
		strcpy(s->city, p->city);
		s->longtitude = p->longtitude-70;
		s->latitude = 70 - p->latitude;
		if(!h){
			h=s; n=h;
		}
		else{
			n->next=s;
			n=n->next;
		}
		free(p);
		p=q;
		m++;
	}
	n->next = h;
	return h;
}

LBSJoseGame * IntiLBSJosepusGame(Student * stud, int nStud, City * city){
	LBSJoseGame * h, *p, *n; int i;
	Student * st=stud; City * su=city;
	h = (LBSJoseGame *) malloc (sizeof (LBSJoseGame));
	h->student = *st;
	h->city = *su;
	h->next = NULL;
	p=h;
	st = st->next;
	su = su->next;
	i=1;
	while(i< nStud){
		n = (LBSJoseGame *) malloc (sizeof (LBSJoseGame));
		n->student = *st;
		n->city = *su;
		p->next = n;
		p = p->next;

		st = st->next;
		su = su->next;
		i++;
	}
	p->next = h;
	return h;
}
LBSJoseGame * LBSJosepusGame(LBSJoseGame * head,int total, int inter){
	int m, k, c;
	LBSJoseGame * h, *p, *q, *n, *s;
	n=h = (LBSJoseGame *) malloc (sizeof (LBSJoseGame));
	p=head;m=0;
	h=NULL;
	c=RandInt(1, CityN);

	while(m<total){
		k=1;
		while(k<inter){
			k++;
			q=p;
			p=p->next;
		}	
		q->next = p->next;
		s=(LBSJoseGame *) malloc (sizeof (LBSJoseGame));
		s->student.StudID = p->student.StudID;
		strcpy(s->student.StudName, p->student.StudName);
		strcpy(s->city.province, p->city.province);
		strcpy(s->city.city, p->city.city);
		s->city.longtitude = p->city.longtitude;
		s->city.latitude = p->city.latitude;
		if(!h){
			h=s; n=h;
		}
		else{
			n->next=s;
			n=n->next;
		}
		free(p);
		p=q;
		m++;
	}
	n->next = h;
	return h;
}
void OutPutLBSJoseGame(char * fname, LBSJoseGame * head){
	int i=1;
	FILE *pf=fopen(fname, "w");
	LBSJoseGame * p = head;
	fprintf(pf, "\t\t\t基于中国城市地理位置的Josephus游戏\n\n");
	fprintf(pf, "%2s  %2s %10s\t%10s\t%10s\t%10s%10s\n",\
		"序号","学号","学名","省份","城市","经度","纬度");

	fprintf(pf, "%2d\t%2d\t%-10s\t%-10s\t%-10s\t%.2f\t%.2f\n",\
		i++, p->student.StudID, p->student.StudName,\
		p->city.province, p->city.city, p->city.longtitude, \
		p->city.latitude);
	p=p->next;
	while (p!=head) {
		fprintf(pf, "%2d\t%2d\t%-10s\t%-10s\t%-10s\t%.2f\t%.2f\n",\
			i++, p->student.StudID, p->student.StudName,\
			p->city.province, p->city.city, p->city.longtitude, \
			p->city.latitude);

		p=p->next;
	}
	printf("\n");
	fclose(pf);
}

void OutPutLBSJoseGameScreen(LBSJoseGame * head){
	HANDLE hOut;//标准输出句柄	
	int i=1;
	LBSJoseGame * p = head;
	system("CLS");
	printf("\t\t\t基于中国城市地理位置的Josephus游戏\n\n");
	printf("%2s\t%2s\t%-10s\t%-10s\t%-10s%10s%10s\n",\
		"序号","学号","学名","省份","城市","经度","纬度");

	printf("%2d\t%2d\t%-10s\t%-10s\t%-10s\t%.2f\t%.2f\n",\
		i++,p->student.StudID, p->student.StudName,\
		p->city.province, p->city.city, p->city.longtitude, \
		p->city.latitude);
	p=p->next;
	while (p!=head) {
		if(p->next==head){
			hOut = GetStdHandle(STD_OUTPUT_HANDLE); // 获取标准输出设备句柄
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);//按省份着色
			printf("%2d\t%2d\t%-10s\t%-10s\t%-10s\t%.2f\t%.2f\n",\
			i++,p->student.StudID, p->student.StudName,\
			p->city.province, p->city.city, p->city.longtitude, \
			p->city.latitude);
			SetConsoleTextAttribute(hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE );//WHITE
		}
		else
			printf("%2d\t%2d\t%-10s\t%-10s\t%-10s\t%.2f\t%.2f\n",\
			i++,p->student.StudID, p->student.StudName,\
			p->city.province, p->city.city, p->city.longtitude, \
			p->city.latitude);

		p=p->next;
	}
	printf("\n");

}

//定位函数，行列屏幕坐标，单位像素
void gotoxy(int x, int y) //x为列坐标,y为行坐标
{
	COORD pos = {x,y};//定义坐标
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//设置一个句柄
	SetConsoleCursorPosition(hOut, pos);
}

void RePlayLBSJoseGame(LBSJoseGame * head){
	HANDLE hOut;//标准输出句柄
	int i=1;
	LBSJoseGame * p = head;
	system("CLS");
	system("MODE CON:COLS=120 LINES=70"); 
	gotoxy(0,20);
	printf("回放游戏过程!\n");
	Sleep(1000);

	gotoxy((int)p->city.longtitude, (int)p->city.latitude);
	printf("%d%4s", i, p->student.StudName);
	gotoxy((int)p->city.longtitude, (int)p->city.latitude+1);
	printf("@%-8s", p->city.city);
	p=p->next;
	while (p!=head) {
		Sleep(1000);
		if(p->next==head){
			hOut = GetStdHandle(STD_OUTPUT_HANDLE); // 获取标准输出设备句柄
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);//按省份着色
			gotoxy((int)p->city.longtitude, (int)p->city.latitude);
			printf("%d%4s", i++ ,p->student.StudName);
			gotoxy((int)p->city.longtitude, (int)p->city.latitude+1);
			printf("@%-8s", p->city.city);
			SetConsoleTextAttribute(hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE );//WHITE
		}	
		else{
			gotoxy((int)p->city.longtitude, (int)p->city.latitude);
			printf("%d%4s", i++, p->student.StudName);
			gotoxy((int)p->city.longtitude, (int)p->city.latitude+1);
			printf("@%-8s", p->city.city);
		}

		p=p->next;
	}
	printf("\n");

}
void SelectSortStudID(LBSJoseGame *p){
	Student s;
	City c;
	LBSJoseGame * tmp1, *tmp2, *least;
	if (p)
        for (tmp1 = p;tmp1->next!=p; tmp1 = tmp1->next) {
            for (tmp2 = tmp1->next, least = tmp1; tmp2!=p; tmp2 = tmp2->next)
                if (tmp2->student.StudID < least->student.StudID)
                    least = tmp2;
				if (tmp1 != least){
					s = tmp1->student;
					c = tmp1->city;
					tmp1 ->student = least->student;
					tmp1->city = least->city;
					least->student = s;
					least->city = c;
				}
        }	
}
//销毁函数，许多时候都被忽略了！
void DestroyPolyStud(Student *p){
	Student *q = p;
	Student *t = p;
	while(t->next!=p){
		q = t->next;
		t->next=q->next;
		free(q);
	}
	free(p);
}
void DestroyPolyCity(City *p){
	City *q = p;
	City *t = p;
	while(t->next!=p){
		q = t->next;
		t->next=q->next;
		free(q);
	}
	free(p);
}
void DestroyPolyJoseGame(LBSJoseGame *p){
	LBSJoseGame *q = p;
	LBSJoseGame *t = p;
	while(t->next!=p){
		q = t->next;
		t->next=q->next;
		free(q);
	}
	free(p);
}

Subject * ReadSubjects(char * fnameSub){
	Subject *h, *p, * s;
	FILE * pf;
	// 先建立无头结点的单循环链表
	pf=fopen(fnameSub, "r");
	if(!pf){printf("打开%s文件失败!\n", fnameSub);exit(0);}
	p= h = (Subject *) malloc (sizeof (Subject));
	fscanf(pf, "%d\t%s\t%s\t%d\t%s\t%s\t%s\n", &p->SubID, p->SubTitle, \
		p->SubContent, &p->SubScore, p->SubGrade, p->SubDate, p->SubPlace);
	while (!feof(pf)) {//正序建表法
		s = (Subject*) malloc (sizeof (Subject));
		fscanf(pf, "%d\t%s\t%s\t%d\t%s\t%s\t%s\n", &s->SubID, s->SubTitle, \
			s->SubContent, &s->SubScore, s->SubGrade, s->SubDate, s->SubPlace);
		
		p->next = s;//插入操作的1，入链
		p = s;  // 2，断链，3，拉链
	}
	p->next = h; 
	fclose(pf);
	return h;
}

Subject * ConfusionSubjects(Subject *sub){
	int m, k, c;
	Subject * h, *p, *q, *n, *s;
	n=h = (Subject *) malloc (sizeof (Subject));
	p=sub;m=0;
	h=NULL;
	c=RandInt(1, StudN);

	while(m<StudN){
		k=1;
		while(k<c){
			k++;
			q=p;
			p=p->next;
		}	
		q->next = p->next;
		s=(Subject *) malloc (sizeof (Subject));
		s->SubID = p->SubID;
		strcpy(s->SubTitle, p->SubTitle);
		strcpy(s->SubContent, p->SubContent);
		s->SubScore = p->SubScore;
		strcpy(s->SubGrade, p->SubGrade);
		strcpy(s->SubDate, p->SubDate);
		strcpy(s->SubPlace, p->SubPlace);
		if(!h){
			h=s; n=h;
		}
		else{
			n->next=s;
			n=n->next;
		}
		free(p);
		p=q;
		m++;
	}
	n->next = h;
	return h;
}

JoseTestPaper * JosepusTestPaper(Student * stud, Subject * sub){
	JoseTestPaper * h, *p, *n;
	Student * st=stud; Subject * su=sub;
	h = (JoseTestPaper *) malloc (sizeof (JoseTestPaper));
	h->student = *st;
	h->subject = *su;
	h->next = NULL;
	p=h;
	st = st->next;
	su = su->next;
	while(st!=stud){
		n = (JoseTestPaper *) malloc (sizeof (JoseTestPaper));
		n->student = *st;
		n->subject = *su;
		p->next = n;
		p = p->next;

		st = st->next;
		su = su->next;
	}
	p->next = h;
	return h;
}
void OutPutTestPaper(char * fname, JoseTestPaper * testPaper){
	FILE *pf=fopen(fname, "w");
	JoseTestPaper * p = testPaper;
	fprintf(pf, "\t\t\t基于Josephus算法《开源GIS》课程设计组卷实用小工具\n\n");
	fprintf(pf, "%4s\t%-6s\t%4s\t\t%-20s\t\t%-20s\t\t\t\t%4s\t%5s\n",\
		"学号","学名","题号","标题","内容","分值","成绩");

	fprintf(pf, "%2d\t%-6s\t%2d\t%-30s\t%-45s\t\t%2d\t%5s\n",\
		p->student.StudID, p->student.StudName,\
		p->subject.SubID, p->subject.SubTitle, p->subject.SubContent, \
		p->subject.SubScore, p->subject.SubGrade);
	p=p->next;
	while (p!=testPaper) {
		fprintf(pf, "%2d\t%-6s\t%2d\t%-30s\t%-45s\t\t%2d\t%5s\n",\
		p->student.StudID, p->student.StudName,\
		p->subject.SubID, p->subject.SubTitle, p->subject.SubContent, \
		p->subject.SubScore, p->subject.SubGrade);

		p=p->next;
	}
	printf("\n");
	fclose(pf);
}

void OutPutTestPaperDP(char * fname, JoseTestPaper * testPaper){
	FILE *pf=fopen(fname, "w");
	JoseTestPaper * p = testPaper;
	fprintf(pf, "\t\t\t基于Josephus算法《开源GIS》课程设计组卷实用小工具\n\n");
	fprintf(pf, "%4s\t%-6s\t%4s\t\t%-20s\t%2s\t%5s\t%8s\t%6s\n",\
		"学号","学名","题号","标题","分值","成绩","日期","地点");

	fprintf(pf, "%2d\t%-6s\t%2d\t%-30s\t%2d\t%5s\t%8s\t%6s\n",\
		p->student.StudID, p->student.StudName,\
		p->subject.SubID, p->subject.SubTitle, \
		p->subject.SubScore, p->subject.SubGrade, p->subject.SubDate, p->subject.SubPlace);
	p=p->next;
	while (p!=testPaper) {
		fprintf(pf, "%2d\t%-6s\t%2d\t%-30s\t%2d\t%5s\t%8s\t%6s\n",\
		p->student.StudID, p->student.StudName,\
		p->subject.SubID, p->subject.SubTitle,\
		p->subject.SubScore, p->subject.SubGrade, p->subject.SubDate, p->subject.SubPlace);

		p=p->next;
	}
	printf("\n");
	fclose(pf);
}

void SelectSortPolyStudID(JoseTestPaper *p){
	Student stu;Subject sub;
	JoseTestPaper * tmp1, *tmp2, *least;
	
	if (p)
        for (tmp1 = p; tmp1->next!=p; tmp1 = tmp1->next) {
            for (tmp2 = tmp1->next, least = tmp1; tmp2!=p; tmp2 = tmp2->next)
                if (tmp2->student.StudID < least->student.StudID)
                    least = tmp2;
				if (tmp1 != least){
					stu = tmp1->student;
					sub = tmp1->subject;
					tmp1 ->student = least->student;
					tmp1 ->subject = least->subject;
					least->student = stu;
					least->subject = sub;
				}
        }	
}
void SelectSortPolySubID(JoseTestPaper *p){
	Student stu;Subject sub;
	JoseTestPaper * tmp1, *tmp2, *least;
	
	if (p)
        for (tmp1 = p; tmp1->next!=p; tmp1 = tmp1->next) {
            for (tmp2 = tmp1->next, least = tmp1; tmp2!=p; tmp2 = tmp2->next)
                if (tmp2->subject.SubID < least->subject.SubID)
                    least = tmp2;
				if (tmp1 != least){
					stu = tmp1->student;
					sub = tmp1->subject;
					tmp1 ->student = least->student;
					tmp1 ->subject = least->subject;
					least->student = stu;
					least->subject = sub;
				}
        }	
}
//销毁函数，许多时候都被忽略!
void DestroyPolyJose(JoseTestPaper *p){
	JoseTestPaper *t, *q = p;
	t=p;
	while(t->next!=p){
		q = t->next;
		t->next=q->next;
		free(q);
	}
	free(p);
}
void DestroyPolySubject(Subject *p){
	Subject * q = p;
	Subject * t = p;
	while(t->next!=p){
		q = t->next;
		t->next=q->next;
		free(q);
	}
	free(p);
}