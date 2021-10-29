#pragma once
#include <time.h>

const int EXAMPRICES[] = { 100, 180, 20, 100 };
const int MEDICINEPRICES[] = { 15, 20, 50, 12 };

typedef struct doctor Doctor;
typedef struct patient Patient;

typedef struct heallog
{
    Doctor* doctor;
    Patient* patient;
    int doctornum;
    int patientnum;
    time_t intime;
    int heallognum;
    int usemedicine[4];
    int usetest[4];
    struct heallog* Docnext;
    struct heallog* Patnext;
    struct heallog* Depnext;
    struct heallog* allnext;
}Heallog;

typedef struct doctor
{
    char name[21];
    char password[15];
    int worknum;//����
    int registernum;
    int pos;
    int office;
    int days[7];
    Heallog* head;
    Heallog* top;
    Heallog* rear;
    struct doctor* next;
    struct doctor* Dnext;
}Doctor;


typedef struct patient
{
    char name[20];
    char password[15];//��¼����
    int sex;
    int age;
    int ifstay;
    int systemID;
    int registercount;
    int money;
    int ifregister[4];//Ĭ�ϲ�������ʮ������
    time_t in;
    time_t out;
    Heallog* top;
    Heallog* rear;
    Heallog* head;
    struct patient* next;
}Patient;


void initData();                                                // ��ʼ������
void saveData();                                                // ��������

// ���룺����ֵ�����⸾�� <-> 0123, doctors��һ�������飬����Ϊ100���㽫�����������ҽ���Ĺ��Ŵ洢��ȥ
//      ���Department��ֵΪ4���򷵻�����ҽ�����������洢����ҽ���Ĺ���
// ������������ҽ��������
int getDoctors(int department, int doctors[]);

// ���룺����ֵ�����⸾�� <-> 0123, doctors��һ�������飬����Ϊ100���㽫������ҳ���ҽ���Ĺ��Ŵ洢��ȥ
// �����������ҳ���ҽ��������
int getNowDoctors(int department, int doctors[]);

// ���룺һ�����飬�����в��˵��˺Ŵ洢��ȥ
// ��������в��˵�����
int getPatients(int patients[]);

// ���룺һ�����飬������סԺ���˵��˺Ŵ洢��ȥ
// ��������в��˵�����
int getInPatients(int patients[]);

// ���룺�˺�/���ţ�heallogs��һ�������飬����Ϊ100���㽫���ҽ��������ʷ���Ƽ�¼�ı�Ŵ洢��ȥ
// ��������Ƽ�¼������
int getDoctorHeallogs(int doctor, int heallogs[]);
int getPatientHeallogs(int patient, int heallogs[]);
// ��������[time1, time2]���������Ƽ�¼������������id����time1 > time2������0
int getTimeHeallogs(int year1, int month1, int date1, int year2, int month2, int date2, int heallogs[]);

// ����������������������ǰ���ҽ�����ڽ�������Ƽ�¼
int getNowHeallogs(int doctor, int heallogs[]);

// ���룺���������䣬�Ա�, ����
// ����������˺�
int addPatient(char name[], int age, int sex, char passwd[]);

// ���룺���˱�ţ�ҽ������
// ������Һ��Ƿ�ɹ�
bool registration(int patientId, int doctorId);

// ���룺���˱�ţ�����
// ������ɹ�Ϊ0�����˺�Ϊ1���������Ϊ2
int patientCheck(int id, char passwd[]);

// ���룺ҽ�����ţ�����
// ������ɹ�Ϊ0�����˺�Ϊ1���������Ϊ2
int doctorCheck(int id, char passwd[]);

// ���룺���������ң�������
// �����ҽ������
int addDoctor(char name[], int department, int position, int workdays[], char passwd[]);

// ���룺���Ƽ�¼ָ�룬ɾ����
void deleteHeallog(Heallog* h);

// ���룺���Ƽ�¼ָ�룬��������������
void virtualDeleteHeallog(Heallog* h);

// ���룺���鳤��Ϊ4������ÿ�����ҵ�Ӫҵ�������Ӫҵ��
double getIncomes(double incomes[]);

// ���룺ҽ����æ�̶ȣ����صȼ�
int getBusyness(Doctor* d);

void addExamination(Heallog* h, int exam);
void addMedicine(Heallog* h, int medi, int num);

// ���룺���˵����Ƽ�¼��Ԥ�Ƴ�Ժ������
// ������轻Ѻ����
int inHospital(Heallog* h, int year, int month, int date);

// ���룺���˵����Ƽ�¼
// �����Ӧ��Ѻ����
int outHospital(Heallog* h);

Patient* getPatient(int id);
Doctor* getDoctor(int id);
Heallog* getHeallog(int id);
