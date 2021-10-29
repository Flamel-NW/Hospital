#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Data.h"
#define  leapyear(y) (((y%4==0)&&(y%100!=0))||(y%400==0))


typedef struct doctor Doctor;
typedef struct department
{
	int name;
	Doctor* head;//��������ҽ����Ϣ����
	Doctor* top;
	Doctor* rear;
	//�Һ���Ϣ ����
	Heallog* Otop;
	Heallog* Orear;
	Heallog* Ohead;
	double sumprofit;
	int sumregistercount;//�����ܹҺ���

}Department;

typedef Department* PDepartment;

extern time_t FIRST;

void outputdepartmenttofile(Department** p);
void outputtoFile(Doctor* p);
void storeinfile(Patient* p);
void HoutputheallogtoFile(Heallog* p);
Heallog* loadheallog();
void loaddoctor();
void loadpatient();
void loaddepartment();
void loadheallogofdoctor(Doctor* p, Heallog* head);
void loadheallogofpatient(Patient* p, Heallog* q);
void checkiffirst();
void wheatherload();
void initFile();
void loadheallogofdepartment(Heallog* p);
int  wheatherwork(Doctor* p);
long long calculatestaydays(long long  m, long long  n);
void chargestaypay();