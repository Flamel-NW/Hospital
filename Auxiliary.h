#pragma once
#include <graphics.h>

extern const char ROOT_PASSWD[9];
extern LPCTSTR DEPARTMENTS[4];
extern LPCTSTR POSITIONS[4];
extern LPCTSTR EXAMINATIONS[4];
extern LPCTSTR MEDICINE[4];

int recharge();
int chooseDepartment();
int choosePositions();
int chooseDoctor(int department);
int choosePatient();
bool chooseWorkdays(int workdays[]);
int chooseInquire();
int enterNumber();
int chooseYear();
int chooseMonth();
int chooseDate(int year, int month);
bool setPasswd(char passwd[]);
bool adminLogin();

void setMouse(int mouse);
void selectBox(int left, int top, int right, int bottom, bool select);
void selectText(int left, int top, int right, int bottom, int mouse, LPCTSTR str);
int selectForm(int left, int top, int right, LPCTSTR strs[], int layers, bool read);
int select4Form(int left, int top, int right, LPCTSTR strs[], bool read);
void selectBack(bool select);
void selectExit(bool select);
void showMessage(LPCTSTR str);
wchar_t* char2wchar(const char* cchar);
char* wchar2char(const wchar_t* wchar);
