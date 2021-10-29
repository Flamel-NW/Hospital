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
    int worknum;//工号
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
    char password[15];//登录密码
    int sex;
    int age;
    int ifstay;
    int systemID;
    int registercount;
    int money;
    int ifregister[4];//默认不超过三十个科室
    time_t in;
    time_t out;
    Heallog* top;
    Heallog* rear;
    Heallog* head;
    struct patient* next;
}Patient;


void initData();                                                // 初始化数据
void saveData();                                                // 保存数据

// 输入：科室值，内外妇儿 <-> 0123, doctors是一个空数组，长度为100，你将这个科室所有医生的工号存储进去
//      如果Department的值为4，则返回所有医生的数量，存储所有医生的工号
// 输出：这个科室医生的数量
int getDoctors(int department, int doctors[]);

// 输入：科室值，内外妇儿 <-> 0123, doctors是一个空数组，长度为100，你将这个科室出诊医生的工号存储进去
// 输出：这个科室出诊医生的数量
int getNowDoctors(int department, int doctors[]);

// 输入：一个数组，你所有病人的账号存储进去
// 输出：所有病人的数量
int getPatients(int patients[]);

// 输入：一个数组，你所有住院病人的账号存储进去
// 输出：所有病人的数量
int getInPatients(int patients[]);

// 输入：账号/工号，heallogs是一个空数组，长度为100，你将这个医生所有历史诊疗记录的编号存储进去
// 输出：诊疗记录的数量
int getDoctorHeallogs(int doctor, int heallogs[]);
int getPatientHeallogs(int patient, int heallogs[]);
// 返回区间[time1, time2]中所有诊疗记录数，并保存其id，若time1 > time2，返回0
int getTimeHeallogs(int year1, int month1, int date1, int year2, int month2, int date2, int heallogs[]);

// 和上面的区别是这个搜索当前这个医生正在接诊的诊疗记录
int getNowHeallogs(int doctor, int heallogs[]);

// 输入：姓名，年龄，性别, 密码
// 输出：病人账号
int addPatient(char name[], int age, int sex, char passwd[]);

// 输入：病人编号，医生工号
// 输出：挂号是否成功
bool registration(int patientId, int doctorId);

// 输入：病人编号，密码
// 输出：成功为0，无账号为1，密码错误为2
int patientCheck(int id, char passwd[]);

// 输入：医生工号，密码
// 输出：成功为0，无账号为1，密码错误为2
int doctorCheck(int id, char passwd[]);

// 输入：姓名，科室，工作日
// 输出：医生工号
int addDoctor(char name[], int department, int position, int workdays[], char passwd[]);

// 输入：诊疗记录指针，删除它
void deleteHeallog(Heallog* h);

// 输入：诊疗记录指针，将里面的内容清空
void virtualDeleteHeallog(Heallog* h);

// 输入：数组长度为4，保存每个科室的营业额，返回总营业额
double getIncomes(double incomes[]);

// 输入：医生繁忙程度，返回等级
int getBusyness(Doctor* d);

void addExamination(Heallog* h, int exam);
void addMedicine(Heallog* h, int medi, int num);

// 输入：病人的诊疗记录，预计出院年月日
// 输出：需交押金金额
int inHospital(Heallog* h, int year, int month, int date);

// 输入：病人的诊疗记录
// 输出：应退押金金额
int outHospital(Heallog* h);

Patient* getPatient(int id);
Doctor* getDoctor(int id);
Heallog* getHeallog(int id);
