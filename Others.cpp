#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Data.h"
#include "others.h"

extern PDepartment dep[4];
extern int heallogcount;
extern int doctornum;
extern int patientnum;
extern Patient *Ptop;
extern Patient *Prear;
extern Heallog* Hrear;
extern Heallog* Htop;
extern Doctor *Dtop;
extern Doctor *Drear;
time_t NOW = 0LL;

void  checkiffirst()
{
	FILE* file;
	fopen_s(&file, "first.txt", "w");
	fprintf(file, "%lld", NOW);
	fclose(file);
}

void wheatherload()
{
	FILE* file;
	fopen_s(&file, "first.txt", "r");
	fscanf_s(file, "%lld", &FIRST);
	NOW = time(NULL);
	fclose(file);
}


void outputdepartmenttofile(Department** p)
{
	FILE* file;
	fopen_s(&file, "科室基本信息.txt", "w");
	if (file == NULL) { return; }
	fprintf(file, "%d", heallogcount);
	for (int i = 0; i < 4; i++)
	{

		fprintf(file, "\n%d\t%d\t%.2f", p[i]->name, p[i]->sumregistercount, p[i]->sumprofit);
	}
	fclose(file);
	for (int i = 0; i < 4; i++)
	{
		free(dep[i]);
		dep[i] = NULL;
	}
}


void outputtoFile(Doctor* p)
{
	Doctor* q = p;
	Doctor* s=NULL;
	FILE* file;
	fopen_s(&file, "医生个人信息.txt", "w");
	if (file == NULL) {  return; }
	//fprintf(file,"姓名\t工号\t科室\t职位\t当前挂号数\t工作日期\n");
	fprintf(file, "%d", doctornum);
	while (q != NULL)
	{
		s = q;
		fprintf(file, "\n%s\t", q->name);
		fprintf(file, "%d\t", q->worknum);
		fprintf(file, "%s\t", q->password);
		fprintf(file, "%d\t", q->office);
		fprintf(file, "%d\t", q->pos);
		fprintf(file, "%d\t", q->registernum);
		for (int i = 0; i < 6; i++) fprintf(file, "%d ", q->days[i]);
		fprintf(file, "%d", q->days[6]);
		q = q->Dnext;
		free(s);
	}
	fclose(file);
	Dtop = NULL;
	Drear = NULL;
}

void storeinfile(Patient* p)
{
	FILE* file;
	fopen_s(&file, "全部病人信息.txt", "w");
	//fprintf(file,"患者姓名\t患者年龄\t患者性别\t患者编号\t是否住院\t当前挂号数\t挂号情况\n");
	fprintf(file, "%d", patientnum);
	Patient* q = p;
	Patient* s = NULL;
	while (q != NULL)
	{
		s = q;
		fprintf(file, "\n%s\t%d\t%d\t%d\t%d\t%d\t", q->name, q->age, q->sex, q->systemID, q->ifstay, q->registercount);
		fprintf(file, "%d\t", q->money);
		fprintf(file, "%s\t", q->password);
		fprintf(file, "%lld\t%lld\t", q->in, q->out);
		for (int i = 0; i < 3; i++)
			fprintf(file, "%d ", q->ifregister[i]);
		fprintf(file, "%d", q->ifregister[3]);

		q = q->next;
		free(s);
	}
	fclose(file);
	Ptop = NULL;
	Prear = NULL;
}

void HoutputheallogtoFile(Heallog* p)//输出诊疗记录到文件
{
	FILE* file;
	fopen_s(&file, "全部诊疗记录顺序信息.txt", "w");
	Heallog* q;
	q = p;
	Heallog* s = NULL;
	if (file == NULL) {  return; }
	while (q != NULL)
	{
		fprintf(file, "\n");
		s = q;
		fprintf(file, "%d %d %d %lld ", q->heallognum, q->doctornum, q->patientnum, q->intime);
		for (int i = 0; i < 4; i++)
		{
			fprintf(file, "%d ", q->usemedicine[i]);
		}
		for (int i = 0; i < 3; i++)
		{
			fprintf(file, "%d ", q->usetest[i]);
		}
		fprintf(file, "%d", q->usetest[3]);
		q = q->allnext;
		free(s);
	}

	fclose(file);
	Htop = NULL;
	Hrear = NULL;
}


Heallog* loadheallog()
{
	Heallog* p1;
	FILE* file;
	if ((fopen_s(&file, "全部诊疗记录顺序信息.txt", "r")) != 0)
	{
		fopen_s(&file, "全部诊疗记录顺序信息.txt", "wb+");
	}

	for (int i = 0; i < heallogcount; i++)
	{
		p1 = (Heallog*)malloc(sizeof(Heallog));
		p1->allnext = NULL;
		p1->Depnext = NULL;
		p1->Docnext = NULL;
		p1->Patnext = NULL;
		fscanf_s(file, "%d%d%d%lld", &(p1->heallognum), &(p1->doctornum), &(p1->patientnum), &(p1->intime));
		for (int i = 0; i < 4; i++)
		{
			fscanf_s(file, "%d", &(p1->usemedicine[i]));
		}
		for (int i = 0; i < 4; i++)
		{
			fscanf_s(file, "%d", &(p1->usetest[i]));
		}
		if (Htop == NULL)
		{
			Htop = Hrear  = p1;
		}
		else
		{
			Hrear->allnext = p1;
			Hrear = p1;
		}
	}

	fclose(file);
	return Htop;
}

void loaddoctor()
{
	int flag = 0;
	if (Hrear != NULL) 
	{
		time_t date;
		struct tm today;
		time(&date);
		gmtime_s(&today, &date);
		struct tm l;
		gmtime_s(&l, &(Hrear->intime));
	    if (today.tm_mday != l.tm_mday)  
			flag = 1;
	}
	Doctor* p;
	FILE* file;
	fopen_s(&file, "医生个人信息.txt", "r");
	if (file == NULL) { return; }
	fscanf_s(file, "%d\n", &doctornum);
	while (doctornum)
	{
		p = (Doctor*)malloc(sizeof(Doctor));
		fscanf_s(file, "%s", p->name, sizeof(p->name));
		fscanf_s(file, "%d", &(p->worknum));
		fscanf_s(file, "%s", p->password, sizeof(p->password));
		fscanf_s(file, "%d", &(p->office));
		fscanf_s(file, "%d", &(p->pos));
		fscanf_s(file, "%d", &(p->registernum));
		p->Dnext = NULL;
		p->head = NULL;
		p->next = NULL;
		p->top = NULL;
		p->rear = NULL;
		if (flag) p->registernum = 0;
		for (int i = 0; i < 7; i++)
		{
			fscanf_s(file, "%d", &(p->days[i]));
		}
		if (Dtop == NULL)
		{
			Dtop = Drear = p;
		}
		else
		{
			Drear->Dnext = p;
			Drear = p;
		}
		for (int i = 0; i < 4; i++)
		{
			if (p->office == i)
			{
				if (dep[i]->top == NULL)
				{
					dep[i]->top = dep[i]->head = dep[i]->rear = p;
				}
				else
				{
					dep[i]->rear->next = p;
					dep[i]->rear = p;
				}
				break;
			}
		}
		if (fgetc(file) == EOF)
			break;
	}

	fclose(file);

}

void loadpatient()
{
	int flag = 0;
	if (Hrear != NULL)
	{
		time_t date;
		struct tm today;
		time(&date);
		gmtime_s(&today, &date);
		struct tm l;
		gmtime_s(&l, &(Hrear->intime));
		if (today.tm_mday != l.tm_mday)  flag = 1;
	}

	Patient* p;
	//Patient* head=NULL;
	FILE* file;
	fopen_s(&file, "全部病人信息.txt", "r");
	fscanf_s(file, "%d", &patientnum);
	while (patientnum)
	{
		p = (Patient*)malloc(sizeof(Patient));
		fscanf_s(file, "%s%d%d%d%d%d", p->name, sizeof(p->name), &(p->age), &(p->sex), &(p->systemID), &(p->ifstay), &(p->registercount));
		p->top = NULL;
		p->rear = NULL;
		p->head = NULL;
		p->next = NULL;
		fscanf_s(file, "%d", &(p->money));
		fscanf_s(file, "%s", p->password, sizeof(p->password));
		fscanf_s(file, "%lld%lld", &(p->in), &(p->out));
		for (int i = 0; i < 4; i++)
		{
			fscanf_s(file, "%d", &(p->ifregister[i]));
		}
		if (flag)
		{
			p->registercount = 0;
			for (int i = 0; i < 4; i++)
			{
				p->ifregister[i] = 0;
			}
		}
		if (Ptop == NULL)
		{
			Ptop = Prear = p;
		}
		else
		{
			Prear->next = p;
			Prear = p;
		}
		if (fgetc(file) == EOF)
			break;
	}

	fclose(file);

}

void loaddepartment()
{

	FILE* file;
	fopen_s(&file, "科室基本信息.txt", "r");
	if (file == NULL) { return; }
	fscanf_s(file, "%d\n", &heallogcount);
	for (int i = 0; i < 4; i++)
	{
		dep[i] = (Department*)malloc(sizeof(Department));
		fscanf_s(file, "%d%d%lf", &(dep[i]->name), &(dep[i]->sumregistercount), &(dep[i]->sumprofit));
		dep[i]->top = NULL;
		dep[i]->head = NULL;
		dep[i]->rear = NULL;
		dep[i]->Otop = NULL;
		dep[i]->Ohead = NULL;
		dep[i]->Ohead = NULL;

	}
	fclose(file);


}

void loadheallogofdoctor(Doctor* p, Heallog* head)
{
	Heallog *q, *temp;
	q = head;
	Doctor* d = p;
	while (d != NULL)
	{
		while (q != NULL)
		{
			if (q->doctornum == d->worknum)
			{
				q->doctor = d;
				temp = q;
				if (d->top == NULL)
				{
					d->top = d->rear = d->head = temp;
				}
				else
				{
					d->rear->Docnext = temp;
					d->rear = temp;
				}
			}
			q = q->allnext;
		}
		d = d->Dnext;
		q = head;
	}

}

void loadheallogofpatient(Patient* p, Heallog* q)
{
	Heallog *temp, *head;
	head = q;
	Patient *s = p;
	while (s!= NULL)
	{
		while (head != NULL)
		{
			if (head->patientnum == s->systemID)
			{
				head->patient = s;
				temp = head;
				if (s->top == NULL)
				{
					s->top = s->rear = s->head = temp;
				}
				else
				{
					s->rear->Patnext = temp;
					s->rear = temp;
				}
			}
			head = head->allnext;
		}
		s = s->next;
		head = q;
	}

}


void loadheallogofdepartment(Heallog* p)
{
	Heallog* q = p;
	for (int i = 0; i < 4; i++)
	{
		while (q != NULL)
		{
			if (q->doctor->office == i)
			{
				if (dep[i]->Otop == NULL)
				{
					dep[i]->Otop = dep[i]->Ohead = dep[i]->Orear = q;
				}
				else
				{
					dep[i]->Orear->Depnext = q;

				}
			}
			q = q->allnext;
		}
		q = p;
	}

}

void initFile()
{
	if (!FIRST)
	{
		FILE* file;
		fopen_s(&file, "科室基本信息.txt", "w");
		fprintf(file, "%d\n", heallogcount);
		fprintf(file, "0\t0\t0.00\n");
		fprintf(file, "1\t0\t0.00\n");
		fprintf(file, "2\t0\t0.00\n");
		fprintf(file, "3\t0\t0.00\n");
		fclose(file);

		FILE* f1;
		fopen_s(&f1, "全部病人信息.txt", "w");
		fclose(f1);

		FILE* f2;
		fopen_s(&f2, "医生个人信息.txt", "w");
		fclose(f2);

		FILE* f3;
		fopen_s(&f3, "全部诊疗记录顺序信息.txt", "w");
		fclose(f3);
	}

}

int  wheatherwork(Doctor* p)
{
	time_t m;
	time(&m);
	char d[50];
	ctime_s(d, sizeof(d), &m);
	char w[4];
	strncpy_s(w, d, 3);
	w[3] = '\0';
	if ((strcmp(w, "Mon") == 0) && (p->days[1] == 1)) return 1;

	if ((strcmp(w, "Tue") == 0) && (p->days[2] == 1)) return 1;

	if ((strcmp(w, "Wed") == 0) && (p->days[3] == 1)) return 1;

	if ((strcmp(w, "Thu") == 0) && (p->days[4] == 1)) return 1;

	if ((strcmp(w, "Fri") == 0) && (p->days[5] == 1)) return 1;

	if ((strcmp(w, "Sat") == 0) && (p->days[6] == 1)) return 1;

	if ((strcmp(w, "Sun") == 0) && (p->days[0] == 1)) return 1;

	return 0;
}

long long  calculatestaydays(long long  m, long long  n)
{
	int month[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	long long y1, y2, m1, m2, d1, d2;
	y1 = m / 10000; m1 = (m % 10000) / 100; d1 = m % 100;
	y2 = n / 10000; m2 = (n % 10000) / 100; d2 = n % 100;
	long long ans = 0;
	long long sum1 = 0, sum2 = 0;
	for (int i = 0; i < y1; i++)
	{
		if (leapyear(i)) sum1 += 366;
		else sum1 += 365;
	}
	if (leapyear(y1)) month[2] = 29;
	else month[2] = 28;
	for (int j = 0; j < m1; j++)
	{
		sum1 += month[j];
	}
	sum1 += d1;
	for (int i = 0; i < y2; i++)
	{
		if (leapyear(i)) sum2 += 366;
		else sum2 += 365;
	}
	if (leapyear(y2)) month[2] = 29;
	else month[2] = 28;
	for (int j = 0; j < m2; j++)
	{
		sum2 += month[j];
	}
	sum2 += d2;
	ans = sum1 - sum2;
	return ans;

}

void chargestaypay()
{
	Patient *p=Ptop;
	while (p!=NULL)
	{
		if (p->ifstay != -1)
		{
			long long day = (NOW - FIRST) / (3600 * 24);
			if (day == 0)
			{
				p = p->next;
				continue;
			}

			p->money -= 200 * day;
			dep[p->ifstay]->sumprofit += 200 * day;
		}
		p = p->next;
	}

}