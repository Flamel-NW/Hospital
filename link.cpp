#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Data.h"
#include "others.h"

Patient* Ptop=NULL;
Patient *Prear=NULL;//患者信息链表头尾指针
Doctor *Dtop=NULL;
Doctor *Drear=NULL;
Heallog *Hrear=NULL;
Heallog *Htop=NULL;
PDepartment dep[4];//4个科室
int heallogcount=0;//诊疗记录编号
int doctornum = 0;
int patientnum = 0;
time_t FIRST = 0LL;

void initData()
{
	wheatherload();
	initFile();
	loaddepartment();
	if (FIRST)
	{
		loaddepartment();
		if (heallogcount != 0)
		{
			loadheallog();
		}
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
		for (int i = 0; i < 4; i++)
			if (flag) dep[i]->sumregistercount = 0;
		int a1, a2;
		FILE* f1;
		fopen_s(&f1, "医生个人信息.txt", "r");
		fscanf_s(f1, "%d", &a1);
		fclose(f1);
		FILE* f2;
		fopen_s(&f2, "全部病人信息.txt", "r");
		fscanf_s(f2, "%d", &a2);
		fclose(f2);
		if (a1 != 0)
		{
			loaddoctor();
			loadheallogofdoctor(Dtop, Htop);
			loadheallogofdepartment(Htop);
		}
		if (a2 != 0)
		{
			loadpatient();
			loadheallogofpatient(Ptop, Htop);
			chargestaypay();
		}

	}
}

void saveData()
{
	checkiffirst();
	HoutputheallogtoFile(Htop);
	outputdepartmenttofile(dep);
	outputtoFile(Dtop);
	storeinfile(Ptop);

}

int getDoctors(int department, int doctors[])
{
	int i = 0;
	if (department > -1 && department < 4)
	{
		Doctor* p = dep[department]->top;
		while (p != NULL)
		{
			doctors[i++] = p->worknum;
			p = p->next;
		}
	}
	else
	{
		Doctor* p;
		for (int j = 0; j < 4; j++)
		{
			p = dep[j]->top;
			while (p != NULL)
			{
				doctors[i++] = p->worknum;
				p = p->next;
			}
		}
	}
	return i;
}

int getPatients(int patients[])
{
	Patient *p = Ptop;
	int i = 0;
	if (p == NULL) return 0;//没有病人返回0
	while (p != NULL)
	{
		patients[i++] = p->systemID;
		p = p->next;
	}
	return i;

}

int addPatient(char name[], int age, int sex,char passwd[ ])
{
	if (patientnum > 100) return -1;
    Patient* p;
    p=(Patient*)malloc(sizeof(Patient));
    strcpy_s(p->name, name);
	strcpy_s(p->password, passwd);
    p->age=age;
    p->sex=sex;
    p->ifstay=-1;
    p->money=0;
    p->registercount=0;
	p->in = 0;
	p->out = 0;
    p->head=p->top=p->rear=NULL;
	p->next = NULL;
    for(int i=0;i<4;i++) p->ifregister[i]=0;
	p->systemID = ++patientnum;
    if(Ptop==NULL)
    {
        Ptop=Prear=p;
    }
    else
    {
        Prear->next=p;
        Prear=p;
    }
    return p->systemID;//返回患者编号
}


bool registration(int patientId, int doctorId)
{
	time_t t;
	struct tm m;
	time(&t);
	gmtime_s(&m, &t);
	Heallog* p;
	p = (Heallog*)malloc(sizeof(Heallog));
	p->doctornum = doctorId;
	p->patientnum = patientId;
	p->intime = t;
	p->allnext = NULL;
	p->Depnext = NULL;
	p->Docnext = NULL;
	p->Patnext = NULL;
	p->heallognum = ++heallogcount;//生成诊疗记录编号
	for (int i = 0; i < 4; i++)
	{
		p->usemedicine[i] = 0;
		p->usetest[i] = 0;
	}
	Patient* q = Ptop;
	while (q != NULL)
	{
		if (q->systemID == patientId)
		{
			p->patient = q;
			break;
		}
		q = q->next;
	}
	if ((Prear->systemID != patientId) && (q == Prear->next)) { free(p); heallogcount--; return 0; }
	if (q->top == NULL)
	{
		q->top = q->rear = q->head = p;
	}
	else
	{
		q->rear->Patnext = p;
		q->rear = p;
	}
	Doctor* s = Dtop;
	while (s != NULL)
	{
		if (s->worknum == doctorId)
		{
			p->doctor = s;
			break;
		}
		s = s->Dnext;
	}
	if (s->registernum >= 20 || q->ifregister[s->office] == 1) { heallogcount--; return 0; }
	q->ifregister[s->office] = 1;
	q->registercount++;
	s->registernum++;
	if ((Drear->worknum != doctorId) && (s == Drear->Dnext)) { free(p); heallogcount--; return 0; }
	if (s->top == NULL)
	{
		s->top = s->rear = s->head = p;
	}
	else
	{
		s->rear->Docnext = p;
		s->rear = p;
	}
	if (dep[s->office]->Otop == NULL)
	{
		dep[s->office]->Otop = dep[s->office]->Ohead = dep[s->office]->Orear = p;
	}
	else
	{
		dep[s->office]->Orear->Depnext = p;
		dep[s->office]->Orear = p;
	}
	if (Htop == NULL)
	{
		Htop = Hrear = p;
	}
	else
	{
		Hrear->allnext = p;
		Hrear = p;
	}
	return 1;
}


Patient* getPatient(int id)//根据id找患者
{
    Patient* q=Ptop;
    while(q!=NULL)
    {
        if(q->systemID==id) return q;
        q=q->next;
    }
    return NULL;//未找到返回空
}



int patientCheck(int id, char passwd[])
{
    Patient* p=getPatient(id);
    if(p==NULL) return 1;
    if(strcmp(p->password,passwd)==0) return 0;
    return 2;

}


Doctor* getDoctor(int id)
{
    Doctor* q = Dtop;
    while(q!=NULL)
    {
        if(q->worknum==id) return q;
        q=q->Dnext;
    }
    return NULL;//未找到返回空
}



int doctorCheck(int id, char passwd[])
{
    Doctor* p;
    p=getDoctor(id);
    if(p==NULL) return 1;
    if(strcmp(p->password,passwd)==0) return 0;
    return 2;
}


int addDoctor(char name[], int department, int pos, int workdays[], char passwd[])
{
	if (doctornum > 100) return -1;
    Doctor* p;
    p=(Doctor*)malloc(sizeof(Doctor));
    strcpy_s(p->name, name);
	strcpy_s(p->password, passwd);
    p->office=department;
	p->pos = pos;
	p->Dnext = NULL;
	p->next = NULL;
	for (int i = 0; i < 7; i++) p->days[i] = 0;
    if(dep[department]->top==NULL)
    {
        dep[department]->top=dep[department]->head=dep[department]->rear=p;
    }
    else
    {
        dep[department]->rear->next=p;
        dep[department]->rear=p;
    }
    for(int i=0;i<7;i++)
    {
        p->days[i]=workdays[i];
    }
    p->registernum=0;
    p->top=p->head=p->rear=NULL;
	p->worknum = ++doctornum;
    if(Dtop==NULL)
    {
        Dtop=Drear=p;
    }
    else
    {
        Drear->Dnext=p;
        Drear=p;
    }
    return p->worknum;
}


void deleteHeallog(Heallog* h)
{
	/*Heallog *move1, *move2, *move3, *move4, *temp1, *temp2, *temp3, *temp4;
	Heallog *q1, *q2, *q3, *q4;
	Heallog *t1, *t2;*/
	Heallog* move1 = NULL;
	Heallog* move2 = NULL;
	Heallog* move3 = NULL;
	Heallog* move4 = NULL;
	Heallog* temp1 = NULL;
	Heallog* temp2 = NULL;
	Heallog* temp3 = NULL;
	Heallog* temp4 = NULL;
	Heallog* q1 = NULL;
	Heallog* q2 = NULL;
	Heallog* q3 = NULL;
	Heallog* q4 = NULL;
	Heallog* t1 = NULL;
	Heallog* t2 = NULL;
	move1 = Htop;
	while (move1!= NULL)
	{
		q1 = move1;
		if (move1->heallognum == h->heallognum)
		{
			temp1 = move1;
			break;
		}
		move1 = move1->allnext;
	}

	move2 = dep[move1->doctor->office]->Otop;
	while (move2!= NULL)
	{
		q2 = move2;
		if (move2->heallognum == h->heallognum)
		{
			temp2= move2;
			break;
		}
		move2 = move2->Depnext;
	}
	Doctor* d1 = move1->doctor;
	Patient* d2 = move1->patient;
	move3= t1 = move1->doctor->top;
	move4= t2 = move1->patient->top;
	while (move3 != NULL)
	{
		q3 = move3;
		if (move2->heallognum == h->heallognum)
		{
			temp3 = move3;
			break;
		}
		move3 = move3->Docnext;
	}
	while (move4 != NULL)
	{
		q4 = move4;
		if (move4->heallognum == h->heallognum)
		{
			temp4 = move4;
			break;
		}
		move4 = move4->Patnext;
	}
	if (move1 == dep[move1->doctor->office]->Otop)
	{
		if (dep[move1->doctor->office]->Otop == dep[move1->doctor->office]->Orear)
		{
			dep[move1->doctor->office]->Otop = dep[move1->doctor->office]->Orear = dep[move1->doctor->office]->Ohead = NULL;
		}
		else
		{
           dep[move1->doctor->office]->Otop = move1->Depnext;
		}
		
	}
	else
	{
		q1->Depnext = move1->Depnext;
	}
	if (move2 == t1)
	{
		if (d1->top == d1->rear)
		{
			d1->top = d1->rear = d1->head = NULL;
		}
		else
		{
            t1->Docnext = move2->Docnext;
		}
		
	}
	else
	{
		q2->Docnext = move2->Docnext;
	}
	if (move3 == t2)
	{
		if (d2->top == d2->rear)
		{
			d2->top = d2->rear = d2->head = NULL;
		}
		else
		{
            t2->Patnext = move3->Patnext;
		}
		
	}
	else
	{
		q3->Patnext = move3->Patnext;
	}
	if (move4 == Htop)
	{
		if (Htop == Hrear)
		{
			Htop=Hrear = NULL;
		}
		else
		{
            Htop->allnext = move4->allnext;
		}
		
	}
	else
	{
		q4->allnext = move4->allnext;
	}
	free(temp1);
}


/*int getDoctorHeallogs(int doctor, int heallogs[])
{
	Doctor* p=Dtop;
	while (p != NULL)
	{
		if (p->worknum == doctor) break;
		p = p->Dnext;
	}
	Heallog *q=p->top;
	int i = 0;
	while (q != NULL)
	{
		heallogs[i++] = q->heallognum;
		q = q->Docnext;
	}
	return i;
}


int getPatientHeallogs(int patient, int heallogs[])
{
	Patient *p=Ptop;
	while (p != NULL)
	{
		if (p->systemID == patient) break;
		p = p->next;
	}
	Heallog *q = p->top;
	int i = 0;
	while (q != NULL)
	{
		heallogs[i++] = q->heallognum;
		q = q->Patnext;
	}
	return i;
}*/

Heallog* getHeallog(int id)
{
	Heallog* p = Htop;
	while (p != NULL)
	{
		if (p->heallognum == id) return p;

		p = p->allnext;
	}
	return NULL;//未找到返回空
}

int getNowHeallogs(int doctor, int heallogs[])
{
	time_t t;
	struct tm c1;
	struct tm c2;
	time(&t);
	gmtime_s(&c1, &t);
	int i = 0;
	Heallog* p;
	Doctor* d=Dtop;
	while (d != NULL)
	{
		if (d->worknum == doctor) break;
		d = d->Dnext;
	}
	p = d->top;
	while (p != NULL)
	{
		gmtime_s(&c2, &(p->intime));
		if ((p->patient->ifstay != -1) || (c1.tm_mday == c2.tm_mday)) heallogs[i++] = p->heallognum;

		p = p->Docnext;
	}
	return i;//返回数组元素个数

}


void addExamination(Heallog* h, int exam)
{
	h->usetest[exam] ++;
	dep[h->doctor->office]->sumprofit +=  EXAMPRICES[exam];

}


void addMedicine(Heallog* h, int medi, int num)
{
	h->usemedicine[medi] = num;
	dep[h->doctor->office]->sumprofit += (double)MEDICINEPRICES[medi] * num;
}

int inHospital(Heallog* h, int year, int month, int date)
{
	long long t1 = year * 10000LL + month * 100LL + date;
	struct tm t;
	int m=0;
	gmtime_s(&t, &(h->intime));
	long long  t2 = (t.tm_year + 1900LL) * 10000LL + (t.tm_mon + 1LL) * 100LL + t.tm_mday;
	if (t2 > t1) return -1;
	int day = (int)calculatestaydays(t1, t2);
	h->patient->ifstay = h->doctor->office;
	h->patient->in = time(NULL);
	h->patient->out = h->patient->in + 3600LL * 24 * day;
	m=200 * day;
	if (m > 1000)
	{
		h->patient->money = m;
	}
	else
	{
		h->patient->money = 1000;
	}
	return h->patient->money;
}

int outHospital(Heallog* h)
{
	int n = h->patient->money;
	h->patient->ifstay = -1;
	h->patient->money = 0;
	h->patient->out = time(NULL);
	return n;
}

int  getDoctorHeallogs(int doctor, int heallogs[])
{
	Doctor*  p = Dtop;
	while (p != NULL)
	{
		if (p->worknum == doctor) break;
		p = p->Dnext;
	}
	Heallog* h=p->top;
	int i = 0;
	while (h != NULL)
	{
		heallogs[i++] = h->heallognum;
		h = h->Docnext;
	}
	return i;
}



int  getPatientHeallogs(int patient, int heallogs[])
{
	Patient *p = Ptop;
	while (p!=NULL)
	{
		if (p->systemID == patient) break;
		p = p->next;
	}
	Heallog *h = p->top;
	int i = 0;
	while (h != NULL)
	{
		heallogs[i++] = h->heallognum;
		h = h->Patnext;
	}
	return i;
}
int  getTimeHeallogs(int year1, int month1, int date1, int year2, int month2, int date2, int heallogs[])
{
	long long front, back,symbol;
	struct tm t;
	int i = 0;
	front = year1 * 10000LL + month1 * 100LL + date1;
	back = year2 * 10000LL + month2 * 100LL + date2;
	Heallog *h = Htop;
	while (h != NULL)
	{
		gmtime_s(&t, &(h->intime));
		symbol = ((t.tm_year + 1900LL) * 10000LL) + (t.tm_mon + 1LL) * 100LL + t.tm_mday;
		if (symbol >= front && symbol <= back)
		{
			heallogs[i++] = h->heallognum;
		}
		h = h->allnext;
	}
	return i;
}


void virtualDeleteHeallog(Heallog* h)
{
	for (int i = 0; i < 4; i++)
	{
		dep[h->doctor->office]->sumprofit -= (double)h->usetest[i] * EXAMPRICES[i];
		dep[h->doctor->office]->sumprofit -= (double)h->usemedicine[i] * MEDICINEPRICES[i];
	}
	for (int i = 0; i < 4; i++)
	{
		h->usemedicine[i] = 0;
		h->usetest[i] = 0;
	}

}

double getIncomes(double incomes[])
{
	double sum=0;
	for (int i = 0; i < 4; i++)
	{
		incomes[i] = dep[i]->sumprofit;
		sum += dep[i]->sumprofit;
	}
	return sum;
}

int getInPatients(int patients[])
{
	Patient* p = Ptop;
	int i = 0;
	while (p != NULL)
	{
		if (p->ifstay != -1)
		{
			patients[i++] = p->systemID;
		}
		p = p->next;
	}
	return i;
}

int getBusyness(Doctor* d)
{
	if (d->registernum >= 0 && d->registernum <= 5) return 0;
	if (d->registernum > 5 && d->registernum <= 10) return 1;
	if (d->registernum > 10 && d->registernum <= 15) return 2;
	if (d->registernum > 15 && d->registernum <= 20) return 3;
	return -1;//其他情况返回-1
}

int getNowDoctors(int department, int doctors[])
{
	Doctor* p = dep[department]->top;
	int i = 0;
	while (p != NULL)
	{
		if (wheatherwork(p)) doctors[i++] = p->worknum;
		p = p->next;
	}
	return i;
}