#include "Data.h"
#include "Auxiliary.h"
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>

void init();
void menu();
void patient();
void doctor();
void admin();
void patientRegister();
void patientLogin();
void patientChoose(Patient* p);
void showPatient(Patient* p);
void showStayInfo(Patient* p);
void doctorLogin();
void doctorInfo(Doctor* d);
void diagnose(Doctor* d);
void showHeallog(Heallog* h);
void showExamination(Heallog* h);
void showMedicine(Heallog* h);
void doctorRegister();
void inquireDepartment(int Department);
void inquireDoctor(int id);
void inquirePatient(int id);
void inquireTime();
void showAdminHeallog(Heallog* h);
void statistics();
void showIncome();
void showInPatients();
void showAdminStayInfo(Patient* p);
void showDoctorsCondition();

int main()
{
    initData();
    init();
    saveData();
    return 0;
}

void init()
{
    MOUSEMSG m;
    initgraph(1024, 755, NOCLOSE);
    IMAGE bk;
    loadimage(&bk, _T("img\\bk.jpg"));
    putimage(0, 0, &bk);

    settextstyle(100, 0, L"楷体");
    setbkmode(TRANSPARENT);
    settextcolor(LIGHTRED);
    outtextxy(150, 100, L"欢迎使用XX医院");
    outtextxy(200, 250, L"诊疗管理系统");

    while (true)
    {
        m = GetMouseMsg();
        if (m.uMsg == WM_LBUTTONDOWN)
        {
            menu();
            break;
        }
    }
    closegraph();
}

void menu()
{   
    while (true)
    {
        cleardevice();
        MOUSEMSG m;
        IMAGE bk;
        loadimage(&bk, _T("img\\bk.jpg"));
        putimage(0, 0, &bk);

        setfillcolor(LIGHTBLUE);
        fillrectangle(312, 225, 712, 325);
        fillrectangle(312, 400, 712, 500);
        fillrectangle(312, 575, 712, 675);

        selectBox(302, 215, 722, 335, false);
        selectBox(302, 390, 722, 510, false);
        selectBox(302, 565, 722, 685, false);

        settextstyle(150, 0, L"楷体");
        setbkmode(TRANSPARENT);
        settextcolor(BLACK);
        outtextxy(212, 25, L"主 菜 单");

        settextstyle(50, 0, L"楷体");
        outtextxy(440, 250, L"患  者");
        outtextxy(440, 425, L"医  生");
        outtextxy(440, 600, L"管理员");
        selectExit(false);

        while (true)
        {
            m = GetMouseMsg();
            if (m.x >= 312 && m.x <= 712 && m.y >= 225 && m.y <= 325)
            {
                selectBox(302, 215, 722, 335, true);
                if (m.uMsg == WM_LBUTTONDOWN)
                {
                    patient();
                    break;
                }
            }
            else if (m.x >= 312 && m.x <= 712 && m.y >= 400 && m.y <= 500)
            {
                selectBox(302, 390, 722, 510, true);
                if (m.uMsg == WM_LBUTTONDOWN)
                {
                    doctor();
                    break;
                }
            }
            else if (m.x >= 312 && m.x <= 712 && m.y >= 575 && m.y <= 675)
            {
                selectBox(302, 565, 722, 685, true);
                if (m.uMsg == WM_LBUTTONDOWN)
                {
                    admin();
                    break;
                }
            }
            else if (m.x >= 20 && m.x <= 120 && m.y >= 690 && m.y <= 735)
            {
                selectExit(true);
                if (m.uMsg == WM_LBUTTONDOWN)
                    return;
            }
            else
            {
                selectExit(false);
                selectBox(302, 215, 722, 335, false);
                selectBox(302, 390, 722, 510, false);
                selectBox(302, 565, 722, 685, false);
            }
        }
    }
}

void patient()
{
    while (true)
    {
        cleardevice();
        MOUSEMSG m;
        IMAGE bk;
        loadimage(&bk, _T("img\\bk.jpg"));
        putimage(0, 0, &bk);

        setfillcolor(LIGHTBLUE);
        fillrectangle(312, 275, 712, 375);
        fillrectangle(312, 450, 712, 550);

        selectBox(302, 265, 722, 385, false);
        selectBox(302, 440, 722, 560, false);
        selectBack(false);

        settextstyle(120, 0, L"楷体");
        setbkmode(TRANSPARENT);
        settextcolor(BLACK);
        outtextxy(330, 50, L"患  者");

        settextstyle(50, 0, L"楷体");
        outtextxy(440, 300, L"注  册");
        outtextxy(440, 475, L"登  录");

        while (true)
        {
            m = GetMouseMsg();
            if (m.x >= 312 && m.x <= 712 && m.y >= 275 && m.y <= 375)
            {
                selectBox(302, 265, 722, 385, true);
                if (m.uMsg == WM_LBUTTONDOWN)
                {
                    patientRegister();
                    break;
                }
            }
            else if (m.x >= 312 && m.x <= 712 && m.y >= 450 && m.y <= 550)
            {
                selectBox(302, 440, 722, 560, true);
                if (m.uMsg == WM_LBUTTONDOWN)
                {
                    patientLogin();
                    break;
                }
            }
            else if (m.x >= 20 && m.x <= 120 && m.y >= 690 && m.y <= 735)
            {
                selectBack(true);
                if (m.uMsg == WM_LBUTTONDOWN)
                    return;
            }
            else
            {
                selectBack(false);
                selectBox(302, 265, 722, 385, false);
                selectBox(302, 440, 722, 560, false);
            }
        }
    }
}

void patientRegister()
{
    while (true)
    {
        cleardevice();
        MOUSEMSG m;
        IMAGE bk;
        loadimage(&bk, _T("img\\bk.jpg"));
        putimage(0, 0, &bk);

        setfillcolor(WHITE);
        setlinecolor(BLACK);
        fillrectangle(392, 225, 792, 275);
        fillrectangle(392, 375, 792, 425);

        setlinecolor(WHITE);
        setfillcolor(LIGHTBLUE);
        fillrectangle(462, 625, 562, 675);
        selectBox(452, 615, 572, 685, false);
        selectText(492, 525, 542, 575, 0, L"男");
        selectText(642, 525, 692, 575, 0, L"女");
        selectBack(false);

        settextstyle(120, 0, L"楷体");
        setbkmode(TRANSPARENT);
        settextcolor(BLACK);
        outtextxy(270, 50, L"患者注册");

        settextstyle(25, 0, L"楷体");
        outtextxy(475, 637, L"下一步");

        settextstyle(50, 0, L"楷体");
        outtextxy(242, 225, L"姓 名");
        outtextxy(242, 375, L"年 龄");
        outtextxy(242, 525, L"性 别");

        bool get = false;
        int i = 0;
        int j = 0;
        int sex = 0;
        const int maxi = 14;
        const int maxj = 5;
        char name[maxi + 1];
        char age_str[maxj + 1];
        while (true)
        {
            if (!get)
                m = GetMouseMsg();
            else
                get = false;
            if (m.x >= 392 && m.x <= 792 && m.y >= 225 && m.y <= 275)
            {
                setMouse(1);
                if (m.uMsg == WM_LBUTTONDOWN)
                {
                    setlinecolor(BLACK);
                    line(402 + 25 * i, 235, 402 + 25 * i, 265);
                    setlinecolor(WHITE);
                    line(402 + 25 * j, 385, 402 + 25 * j, 415);

                    while (_kbhit())
                        _getch();

                    while (true)
                    {
                        if (MouseHit())
                        {
                            m = GetMouseMsg();
                            if (m.x < 392 || m.x > 792 || m.y < 225 || m.y > 275)
                            {
                                if (sex != 1)
                                    selectText(492, 525, 542, 575, 0, L"男");
                                if (sex != 2)
                                    selectText(642, 525, 692, 575, 0, L"女");
                                setMouse(0);
                                selectBox(452, 615, 572, 685, false);
                                selectBack(false);
                                if (m.x >= 392 && m.x <= 792 && m.y >= 375 && m.y <= 425)
                                    setMouse(1);
                                if (m.x >= 492 && m.x <= 542 && m.y >= 525 && m.y <= 575)
                                    if (sex != 1)
                                        selectText(492, 525, 542, 575, 1, L"男");
                                if (m.x >= 642 && m.x <= 692 && m.y >= 525 && m.y <= 575)
                                    if (sex != 2)
                                        selectText(642, 525, 692, 575, 3, L"女");
                                if (m.x >= 462 && m.x <= 562 && m.y >= 625 && m.y <= 675)
                                    selectBox(452, 615, 572, 685, true);
                                if (m.x >= 20 && m.x <= 120 && m.y >= 690 && m.y <= 735)
                                    selectBack(true);
                                if (m.uMsg == WM_LBUTTONDOWN)
                                {
                                    get = true;
                                    break;
                                }
                            }
                            else
                                setMouse(1);
                        }
                        if (_kbhit())
                        {
                            char ch = _getch();
                            if (ch == '\b' && i > 0)
                            {
                                i--;
                                setfillcolor(WHITE);
                                setlinecolor(WHITE);
                                fillrectangle(402 + 25 * i, 226, 402 + 25 * (i + 1), 274);
                                setlinecolor(BLACK);
                                line(402 + 25 * i, 235, 402 + 25 * i, 265);
                                setlinecolor(WHITE);
                                setfillcolor(LIGHTBLUE);
                                continue;
                            }
                            if (ch == 13)
                            {
                                get = true;
                                m.x = 462;
                                m.y = 625;
                                m.uMsg = WM_LBUTTONDOWN;
                                break;
                            }
                            if (!isalnum(ch) || i == maxi)
                                continue;
                            settextstyle(50, 0, L"楷体");
                            outtextxy(402 + 25 * i, 225, ch);
                            name[i++] = ch;

                            setlinecolor(BLACK);
                            line(402 + 25 * i, 235, 402 + 25 * i, 265);
                            setlinecolor(WHITE);
                            line(402 + 25 * (i - 1), 235, 402 + 25 * (i - 1), 265);
                        }
                    }
                }
            }
            else if (m.x >= 392 && m.x <= 792 && m.y >= 375 && m.y <= 425)
            {
                setMouse(1);
                if (m.uMsg == WM_LBUTTONDOWN)
                {
                    setlinecolor(BLACK);
                    line(402 + 25 * j, 385, 402 + 25 * j, 415);
                    setlinecolor(WHITE);
                    line(402 + 25 * i, 235, 402 + 25 * i, 265);

                    while (_kbhit())
                        _getch();

                    while (true)
                    {
                        if (MouseHit())
                        {
                            m = GetMouseMsg();
                            if (m.x < 392 || m.x > 792 || m.y < 375 || m.y > 425)
                            {
                                if (sex != 1)
                                    selectText(492, 525, 542, 575, 0, L"男");
                                if (sex != 2)
                                    selectText(642, 525, 692, 575, 0, L"女");
                                setMouse(0);
                                selectBox(452, 615, 572, 685, false);
                                selectBack(false);
                                if (m.x >= 392 && m.x <= 792 && m.y >= 225 && m.y <= 275)
                                    setMouse(1);
                                if (m.x >= 492 && m.x <= 542 && m.y >= 525 && m.y <= 575)
                                    if (sex != 1)
                                        selectText(492, 525, 542, 575, 1, L"男");
                                if (m.x >= 642 && m.x <= 692 && m.y >= 525 && m.y <= 575)
                                    if (sex != 2)
                                        selectText(642, 525, 692, 575, 3, L"女");
                                if (m.x >= 462 && m.x <= 562 && m.y >= 625 && m.y <= 675)
                                    selectBox(452, 615, 572, 685, true);
                                if (m.x >= 20 && m.x <= 120 && m.y >= 690 && m.y <= 735)
                                    selectBack(true);
                                if (m.uMsg == WM_LBUTTONDOWN)
                                {
                                    get = true;
                                    break;
                                }
                            }
                            else
                                setMouse(1);
                        }
                        if (_kbhit())
                        {
                            char ch = _getch();
                            if (ch == '\b' && j > 0)
                            {
                                j--;
                                setfillcolor(WHITE);
                                setlinecolor(WHITE);
                                fillrectangle(402 + 25 * j, 376, 402 + 25 * (j + 1), 424);
                                setlinecolor(BLACK);
                                line(402 + 25 * j, 385, 402 + 25 * j, 415);
                                setlinecolor(WHITE);
                                setfillcolor(LIGHTBLUE);
                                continue;
                            }
                            if (ch == 13)
                            {
                                get = true;
                                m.x = 462;
                                m.y = 625;
                                m.uMsg = WM_LBUTTONDOWN;
                                break;
                            }
                            if (!isdigit(ch) || j == maxj)
                                continue;
                            settextstyle(50, 0, L"楷体");
                            outtextxy(402 + 25 * j, 375, ch);
                            age_str[j++] = ch;

                            setlinecolor(BLACK);
                            line(402 + 25 * j, 385, 402 + 25 * j, 415);
                            setlinecolor(WHITE);
                            line(402 + 25 * (j - 1), 385, 402 + 25 * (j - 1), 415);
                        }
                    }
                }
            }
            else if (m.x >= 492 && m.x <= 542 && m.y >= 525 && m.y <= 575)
            {
                if (sex != 1)
                    selectText(492, 525, 542, 575, 1, L"男");
                if (m.uMsg == WM_LBUTTONDOWN)
                {
                    setlinecolor(WHITE);
                    line(402 + 25 * i, 235, 402 + 25 * i, 265);
                    line(402 + 25 * j, 385, 402 + 25 * j, 415);

                    sex = 1;
                    selectText(492, 525, 542, 575, 2, L"男");
                    selectText(642, 525, 692, 575, 0, L"女");
                }
            }
            else if (m.x >= 642 && m.x <= 692 && m.y >= 525 && m.y <= 575)
            {
                if (sex != 2)
                    selectText(642, 525, 692, 575, 3, L"女");
                if (m.uMsg == WM_LBUTTONDOWN)
                {
                    setlinecolor(WHITE);
                    line(402 + 25 * i, 235, 402 + 25 * i, 265);
                    line(402 + 25 * j, 385, 402 + 25 * j, 415);

                    sex = 2;
                    selectText(642, 525, 692, 575, 4, L"女");
                    selectText(492, 525, 542, 575, 0, L"男");
                }
            }
            else if (m.x >= 462 && m.x <= 562 && m.y >= 625 && m.y <= 675)
            {
                selectBox(452, 615, 572, 685, true);
                if (m.uMsg == WM_LBUTTONDOWN)
                {
                    setlinecolor(WHITE);
                    line(402 + 25 * i, 235, 402 + 25 * i, 265);
                    line(402 + 25 * j, 385, 402 + 25 * j, 415);

                    name[i] = '\0';
                    age_str[j] = '\0';

                    if (!strlen(name))
                    {
                        showMessage(L"请输入姓名");
                        continue;
                    }
                    if (!strlen(age_str))
                    {
                        showMessage(L"请输入年龄");
                        continue;
                    }
                    if (!sex)
                    {
                        showMessage(L"请选择性别");
                        continue;
                    }

                    int age = atoi(age_str);

                    char passwd[maxi + 1];
                    memset(passwd, 0, sizeof(passwd));
                    if (!setPasswd(passwd))
                        break;

                    int id = addPatient(name, age, sex % 2, passwd);
                    char id_str[maxi + 1];
                    _itoa_s(id, id_str, 10);
                    wchar_t message[100];
                    wchar_t* temp = char2wchar(id_str);
                    wcscpy_s(message, L"注册成功，您的账号是");
                    wcscat_s(message, temp);
                    delete[] temp;
                    showMessage(message);

                    int department = chooseDepartment();
                    if (department == -1)
                        break;
                    int doctor = chooseDoctor(department);
                    if (doctor == -1)
                        break;

                    if (registration(id, doctor))
                        showMessage(L"挂号成功");
                    else
                        showMessage(L"挂号失败");

                    return;
                }
            }
            else if (m.x >= 20 && m.x <= 120 && m.y >= 690 && m.y <= 735)
            {
                selectBack(true);
                if (m.uMsg == WM_LBUTTONDOWN)
                    return;
            }
            else
            {
                if (m.uMsg == WM_LBUTTONDOWN)
                {
                    setlinecolor(WHITE);
                    line(402 + 25 * i, 235, 402 + 25 * i, 265);
                    line(402 + 25 * j, 385, 402 + 25 * j, 415);
                }

                if (sex != 1)
                    selectText(492, 525, 542, 575, 0, L"男"); 
                if (sex != 2)
                    selectText(642, 525, 692, 575, 0, L"女");

                setMouse(0);
                selectBox(452, 615, 572, 685, false);
                selectBack(false);
            }
        }
    }
}

void patientLogin()
{
    while (true)
    {
        cleardevice();
        MOUSEMSG m;
        IMAGE bk;
        loadimage(&bk, _T("img\\bk.jpg"));
        putimage(0, 0, &bk);

        setfillcolor(WHITE);
        setlinecolor(BLACK);
        fillrectangle(392, 275, 792, 325);
        fillrectangle(392, 450, 792, 500);

        setlinecolor(WHITE);
        setfillcolor(LIGHTBLUE);
        fillrectangle(462, 600, 562, 650);
        selectBox(452, 590, 572, 660, false);
        selectBack(false);

        settextstyle(120, 0, L"楷体");
        setbkmode(TRANSPARENT);
        settextcolor(BLACK);
        outtextxy(270, 50, L"患者登录");

        settextstyle(25, 0, L"楷体");
        outtextxy(480, 612, L"登 录");

        settextstyle(50, 0, L"楷体");
        outtextxy(242, 275, L"账 号");
        outtextxy(242, 450, L"密 码");

        bool get = false;
        int i = 0;
        int j = 0;
        const int maxi = 14;
        const int maxj = 14;
        char id_str[maxi + 1];
        char passwd[maxj + 1];
        while (true)
        {
            if (!get)
                m = GetMouseMsg();
            else
                get = false;
            if (m.x >= 392 && m.x <= 792 && m.y >= 275 && m.y <= 325)
            {
                setMouse(1);
                if (m.uMsg == WM_LBUTTONDOWN)
                {
                    setlinecolor(BLACK);
                    line(402 + 25 * i, 285, 402 + 25 * i, 315);
                    setlinecolor(WHITE);
                    line(402 + 25 * j, 460, 402 + 25 * j, 490);

                    while (_kbhit())
                        _getch();

                    while (true)
                    {
                        if (MouseHit())
                        {
                            m = GetMouseMsg();
                            if (m.x < 392 || m.x > 792 || m.y < 275 || m.y > 325)
                            {
                                setMouse(0);
                                selectBox(452, 590, 572, 660, false);
                                selectBack(false);
                                if (m.x >= 392 && m.x <= 792 && m.y >= 450 && m.y <= 500)
                                    setMouse(1);
                                if (m.x >= 462 && m.x <= 562 && m.y >= 600 && m.y <= 650)
                                    selectBox(452, 590, 572, 660, true);
                                if (m.x >= 20 && m.x <= 120 && m.y >= 690 && m.y <= 735)
                                    selectBack(true);
                                if (m.uMsg == WM_LBUTTONDOWN)
                                {
                                    get = true;
                                    break;
                                }
                            }
                            else
                                setMouse(1);
                        }
                        if (_kbhit())
                        {
                            char ch = _getch();
                            if (ch == '\b' && i > 0)
                            {
                                i--;
                                setfillcolor(WHITE);
                                setlinecolor(WHITE);
                                fillrectangle(402 + 25 * i, 276, 402 + 25 * (i + 1), 324);
                                setlinecolor(BLACK);
                                line(402 + 25 * i, 285, 402 + 25 * i, 315);
                                setlinecolor(WHITE);
                                setfillcolor(LIGHTBLUE);
                                continue;
                            }
                            if (ch == 13)
                            {
                                get = true;
                                m.x = 462;
                                m.y = 600;
                                m.uMsg = WM_LBUTTONDOWN;
                                break;
                            }
                            if (!isdigit(ch) || i == maxi)
                                continue;
                            settextstyle(50, 0, L"楷体");
                            outtextxy(402 + 25 * i, 275, ch);
                            id_str[i++] = ch;

                            setlinecolor(BLACK);
                            line(402 + 25 * i, 285, 402 + 25 * i, 315);
                            setlinecolor(WHITE);
                            line(402 + 25 * (i - 1), 285, 402 + 25 * (i - 1), 315);
                        }
                    }
                }
            }
            else if (m.x >= 392 && m.x <= 792 && m.y >= 450 && m.y <= 500)
            {
                setMouse(1);
                if (m.uMsg == WM_LBUTTONDOWN)
                {
                    setlinecolor(BLACK);
                    line(402 + 25 * j, 460, 402 + 25 * j, 490);
                    setlinecolor(WHITE);
                    line(402 + 25 * i, 285, 402 + 25 * i, 315);

                    while (_kbhit())
                        _getch();

                    while (true)
                    {
                        if (MouseHit())
                        {
                            m = GetMouseMsg();
                            if (m.x < 392 || m.x > 792 || m.y < 450 || m.y > 500)
                            {
                                setMouse(0);
                                selectBox(452, 590, 572, 660, false);
                                selectBack(false);
                                if (m.x >= 392 && m.x <= 792 && m.y >= 275 && m.y <= 325)
                                    setMouse(1);
                                if (m.x >= 462 && m.x <= 562 && m.y >= 600 && m.y <= 650)
                                    selectBox(452, 590, 572, 660, true);
                                if (m.x >= 20 && m.x <= 120 && m.y >= 690 && m.y <= 735)
                                    selectBack(true);
                                if (m.uMsg == WM_LBUTTONDOWN)
                                {
                                    get = true;
                                    break;
                                }
                            }
                            else
                                setMouse(1);
                        }
                        if (_kbhit())
                        {
                            char ch = _getch();
                            if (ch == '\b' && j > 0)
                            {
                                j--;
                                setfillcolor(WHITE);
                                setlinecolor(WHITE);
                                fillrectangle(402 + 25 * j, 451, 402 + 25 * (j + 1), 499);
                                setlinecolor(BLACK);
                                line(402 + 25 * j, 460, 402 + 25 * j, 490);
                                setlinecolor(WHITE);
                                setfillcolor(LIGHTBLUE);
                                continue;
                            }
                            if (ch == 13)
                            {
                                get = true;
                                m.x = 462;
                                m.y = 600;
                                m.uMsg = WM_LBUTTONDOWN;
                                break;
                            }
                            if (!isalnum(ch) || j == maxj)
                                continue;
                            settextstyle(50, 0, L"楷体");
                            outtextxy(402 + 25 * j, 450, '*');
                            passwd[j++] = ch;

                            setlinecolor(BLACK);
                            line(402 + 25 * j, 460, 402 + 25 * j, 490);
                            setlinecolor(WHITE);
                            line(402 + 25 * (j - 1), 460, 402 + 25 * (j - 1), 490);
                        }
                    }
                }
            }
            else if (m.x >= 462 && m.x <= 562 && m.y >= 600 && m.y <= 650)
            {
                selectBox(452, 590, 572, 660, true);
                if (m.uMsg == WM_LBUTTONDOWN)
                {
                    setlinecolor(WHITE);
                    line(402 + 25 * i, 285, 402 + 25 * i, 315);
                    line(402 + 25 * j, 460, 402 + 25 * j, 490);

                    id_str[i] = '\0';
                    passwd[j] = '\0';

                    if (!strlen(id_str))
                    {
                        showMessage(L"请输入账号");
                        continue;
                    }
                    if (!strlen(passwd))
                    {
                        showMessage(L"请输入密码");
                        continue;
                    }

                    int id = atoi(id_str);
                    Patient* p;
                    bool flag = false;
                    switch (patientCheck(id, passwd))
                    {
                    case 0:
                        p = getPatient(id);
                        patientChoose(p);
                        flag = true;
                        break;
                    case 1:
                        showMessage(L"查无此人");
                        break;
                    case 2:
                        showMessage(L"密码错误");
                        break;
                    default:
                        break;
                    }
                    if (flag)
                        break;
                }
            }
            else if (m.x >= 20 && m.x <= 120 && m.y >= 690 && m.y <= 735)
            {
                selectBack(true);
                if (m.uMsg == WM_LBUTTONDOWN)
                    return;
            }
            else
            {
                if (m.uMsg == WM_LBUTTONDOWN)
                {
                    setlinecolor(WHITE);
                    line(402 + 25 * i, 285, 402 + 25 * i, 315);
                    line(402 + 25 * j, 460, 402 + 25 * j, 490);
                }
                setMouse(0);
                selectBox(452, 590, 572, 660, false);
                selectBack(false);
            }
        }
    }
}

void patientChoose(Patient* p)
{
    while (true)
    {
        cleardevice();
        MOUSEMSG m;
        IMAGE bk;
        loadimage(&bk, _T("img\\bk.jpg"));
        putimage(0, 0, &bk);

        setfillcolor(LIGHTBLUE);
        fillrectangle(312, 275, 712, 375);
        fillrectangle(312, 450, 712, 550);

        selectBox(302, 265, 722, 385, false);
        selectBox(302, 440, 722, 560, false);
        selectBack(false);

        settextstyle(120, 0, L"楷体");
        setbkmode(TRANSPARENT);
        settextcolor(BLACK);
        outtextxy(330, 50, L"请选择");

        settextstyle(50, 0, L"楷体");
        outtextxy(412, 300, L"信息查询");
        outtextxy(412, 475, L"再次挂号");

        while (true)
        {
            m = GetMouseMsg();
            if (m.x >= 312 && m.x <= 712 && m.y >= 275 && m.y <= 375)
            {
                selectBox(302, 265, 722, 385, true);
                if (m.uMsg == WM_LBUTTONDOWN)
                {
                    showPatient(p);
                    break;
                }
            }
            else if (m.x >= 312 && m.x <= 712 && m.y >= 450 && m.y <= 550)
            {
                selectBox(302, 440, 722, 560, true);
                if (m.uMsg == WM_LBUTTONDOWN)
                {
                    if (p->ifstay != -1)
                    {
                        showMessage(L"您已住院，无法再次挂号");
                        break;
                    }

                    int department = chooseDepartment();
                    if (department == -1)
                        break;
                    int doctor = chooseDoctor(department);
                    if (doctor == -1)
                        break;

                    if (registration(p->systemID, doctor))
                        showMessage(L"挂号成功");
                    else
                        showMessage(L"挂号失败");

                    break;
                }
            }
            else if (m.x >= 20 && m.x <= 120 && m.y >= 690 && m.y <= 735)
            {
                selectBack(true);
                if (m.uMsg == WM_LBUTTONDOWN)
                    return;
            }
            else
            {
                selectBack(false);
                selectBox(302, 265, 722, 385, false);
                selectBox(302, 440, 722, 560, false);
            }
        }
    }
}

void showPatient(Patient* p)
{
    while (true)
    {
        cleardevice();
        MOUSEMSG m;
        IMAGE bk;
        loadimage(&bk, _T("img\\bk.jpg"));
        putimage(0, 0, &bk);

        settextstyle(120, 0, L"楷体");
        setbkmode(TRANSPARENT);
        settextcolor(BLACK);
        outtextxy(270, 50, L"患者信息");

        settextstyle(50, 0, L"楷体");
        outtextxy(250, 225, L"账 号：");
        outtextxy(250, 300, L"姓 名：");
        outtextxy(250, 375, L"性 别：");
        outtextxy(250, 450, L"年 龄：");

        char temp[100];
        wchar_t* wtemp;
        _itoa_s(p->systemID, temp, 10);

        wtemp = char2wchar(temp);
        outtextxy(450, 225, wtemp);
        delete[] wtemp;

        wtemp = char2wchar(p->name);
        outtextxy(450, 300, wtemp);
        delete[] wtemp;

        outtextxy(450, 375, p->sex ? L"男" : L"女");
        _itoa_s(p->age, temp, 10);

        wtemp = char2wchar(temp);
        outtextxy(450, 450, wtemp);
        delete[] wtemp;

        selectText(422, 600, 602, 650, 0, L"住院信息");
        selectBack(false);

        while (true)
        {
            m = GetMouseMsg();
            if (m.x >= 422 && m.x <= 602 && m.y >= 600 && m.y <= 650)
            {
                selectText(422, 600, 602, 650, (p->ifstay != -1) ? 1 : 0, L"住院信息");
                if (m.uMsg == WM_LBUTTONDOWN && (p->ifstay != -1))
                {
                    selectText(422, 600, 602, 650, 2, L"住院信息");
                    showStayInfo(p);
                    break;
                }
            }
            else if (m.x >= 20 && m.x <= 120 && m.y >= 690 && m.y <= 735)
            {
                selectBack(true);
                if (m.uMsg == WM_LBUTTONDOWN)
                    return;
            }
            else
            {
                selectText(422, 600, 602, 650, 0, L"住院信息");
                selectBack(false);
            }
        }
    }
}

void showStayInfo(Patient* p)
{
    while (true)
    {   
        cleardevice();
        MOUSEMSG m;
        IMAGE bk;
        loadimage(&bk, _T("img\\bk.jpg"));
        putimage(0, 0, &bk);

        setlinecolor(WHITE);
        setfillcolor(LIGHTBLUE);
        fillrectangle(462, 600, 562, 650);
        selectBox(452, 590, 572, 660, false);
        selectBack(false);

        settextstyle(120, 0, L"楷体");
        setbkmode(TRANSPARENT);
        settextcolor(BLACK);
        outtextxy(270, 50, L"住院信息");

        settextstyle(25, 0, L"楷体");
        outtextxy(480, 612, L"充 值");

        settextstyle(50, 0, L"楷体");
        outtextxy(250, 250, L"押金余额：");
        outtextxy(150, 350, L"预计出院时间：");

        char temp[100];
        wchar_t* wtemp;
        _itoa_s(p->money, temp, 10);
        wtemp = char2wchar(temp);
        outtextxy(500, 250, wtemp);
        delete[] wtemp;

        wchar_t str[100];
        struct tm outtime;
        gmtime_s(&outtime, &(p->out));
        _itoa_s(outtime.tm_year + 1900, temp, 10);
        wtemp = char2wchar(temp);
        wcscpy_s(str, wtemp);
        delete[] wtemp;
        wcscat_s(str, L".");
        _itoa_s(outtime.tm_mon + 1, temp, 10);
        wtemp = char2wchar(temp);
        wcscat_s(str, wtemp);
        delete[] wtemp;
        wcscat_s(str, L".");
        _itoa_s(outtime.tm_mday, temp, 10);
        wtemp = char2wchar(temp);
        wcscat_s(str, wtemp);
        delete[] wtemp;
        outtextxy(500, 350, str);

        if (p->money < 1000)
        {
            wchar_t str[100] = L"押金余额不足，请立刻充值至少";
            char temp[100];
            _itoa_s(1000 - p->money, temp, 10);
            wchar_t* wtemp = char2wchar(temp);
            wcscat_s(str, wtemp);
            delete[] wtemp;
            showMessage(str);
            int add = recharge();
            p->money += (add == -1) ? 0 : add;
            continue;
        }

        while (true)
        {
            m = GetMouseMsg();
            if (m.x >= 462 && m.x <= 562 && m.y >= 600 && m.y <= 650)
            {
                selectBox(452, 590, 572, 660, true);
                if (m.uMsg == WM_LBUTTONDOWN)
                {
                    int add = recharge();
                    p->money += (add == -1) ? 0 : add;
                    break;
                }
            }
            else if (m.x >= 20 && m.x <= 120 && m.y >= 690 && m.y <= 735)
            {
                selectBack(true);
                if (m.uMsg == WM_LBUTTONDOWN)
                    return;
            }
            else
            {
                selectBox(452, 590, 572, 660, false);
                selectBack(false);
            }
        }
    }
}

void doctor()
{
    while (true)
    {
        cleardevice();
        MOUSEMSG m;
        IMAGE bk;
        loadimage(&bk, _T("img\\bk.jpg"));
        putimage(0, 0, &bk);

        setfillcolor(LIGHTBLUE);
        fillrectangle(312, 275, 712, 375);
        fillrectangle(312, 450, 712, 550);

        selectBox(302, 265, 722, 385, false);
        selectBox(302, 440, 722, 560, false);
        selectBack(false);

        settextstyle(120, 0, L"楷体");
        setbkmode(TRANSPARENT);
        settextcolor(BLACK);
        outtextxy(330, 50, L"医  生");

        settextstyle(50, 0, L"楷体");
        outtextxy(440, 300, L"登  录");
        outtextxy(440, 475, L"注  册");

        while (true)
        {
            m = GetMouseMsg();
            if (m.x >= 312 && m.x <= 712 && m.y >= 275 && m.y <= 375)
            {
                selectBox(302, 265, 722, 385, true);
                if (m.uMsg == WM_LBUTTONDOWN)
                {
                    doctorLogin();
                    break;
                }
            }
            else if (m.x >= 312 && m.x <= 712 && m.y >= 450 && m.y <= 550)
            {
                selectBox(302, 440, 722, 560, true);
                if (m.uMsg == WM_LBUTTONDOWN)
                {
                    doctorRegister();
                    break;
                }
            }
            else if (m.x >= 20 && m.x <= 120 && m.y >= 690 && m.y <= 735)
            {
                selectBack(true);
                if (m.uMsg == WM_LBUTTONDOWN)
                    return;
            }
            else
            {
                selectBack(false);
                selectBox(302, 265, 722, 385, false);
                selectBox(302, 440, 722, 560, false);
            }
        }
    }
}

void doctorLogin()
{
    while (true)
    {
        cleardevice();
        MOUSEMSG m;
        IMAGE bk;
        loadimage(&bk, _T("img\\bk.jpg"));
        putimage(0, 0, &bk);

        setfillcolor(WHITE);
        setlinecolor(BLACK);
        fillrectangle(392, 275, 792, 325);
        fillrectangle(392, 450, 792, 500);

        setlinecolor(WHITE);
        setfillcolor(LIGHTBLUE);
        fillrectangle(462, 600, 562, 650);
        selectBox(452, 590, 572, 660, false);
        selectBack(false);

        settextstyle(120, 0, L"楷体");
        setbkmode(TRANSPARENT);
        settextcolor(BLACK);
        outtextxy(270, 50, L"医生登录");

        settextstyle(25, 0, L"楷体");
        outtextxy(480, 612, L"登 录");

        settextstyle(50, 0, L"楷体");
        outtextxy(242, 275, L"工 号");
        outtextxy(242, 450, L"密 码");

        bool get = false;
        int i = 0;
        int j = 0;
        const int maxi = 14;
        const int maxj = 14;
        char id_str[maxi + 1];
        char passwd[maxj + 1];
        while (true)
        {
            if (!get)
                m = GetMouseMsg();
            else
                get = false;
            if (m.x >= 392 && m.x <= 792 && m.y >= 275 && m.y <= 325)
            {
                setMouse(1);
                if (m.uMsg == WM_LBUTTONDOWN)
                {
                    setlinecolor(BLACK);
                    line(402 + 25 * i, 285, 402 + 25 * i, 315);
                    setlinecolor(WHITE);
                    line(402 + 25 * j, 460, 402 + 25 * j, 490);

                    while (_kbhit())
                        _getch();

                    while (true)
                    {
                        if (MouseHit())
                        {
                            m = GetMouseMsg();
                            if (m.x < 392 || m.x > 792 || m.y < 275 || m.y > 325)
                            {
                                setMouse(0);
                                selectBox(452, 590, 572, 660, false);
                                selectBack(false);
                                if (m.x >= 392 && m.x <= 792 && m.y >= 450 && m.y <= 500)
                                    setMouse(1);
                                if (m.x >= 462 && m.x <= 562 && m.y >= 600 && m.y <= 650)
                                    selectBox(452, 590, 572, 660, true);
                                if (m.x >= 20 && m.x <= 120 && m.y >= 690 && m.y <= 735)
                                    selectBack(true);
                                if (m.uMsg == WM_LBUTTONDOWN)
                                {
                                    get = true;
                                    break;
                                }
                            }
                            else
                                setMouse(1);
                        }
                        if (_kbhit())
                        {
                            char ch = _getch();
                            if (ch == '\b' && i > 0)
                            {
                                i--;
                                setfillcolor(WHITE);
                                setlinecolor(WHITE);
                                fillrectangle(402 + 25 * i, 276, 402 + 25 * (i + 1), 324);
                                setlinecolor(BLACK);
                                line(402 + 25 * i, 285, 402 + 25 * i, 315);
                                setlinecolor(WHITE);
                                setfillcolor(LIGHTBLUE);
                                continue;
                            }
                            if (ch == 13)
                            {
                                get = true;
                                m.x = 462;
                                m.y = 600;
                                m.uMsg = WM_LBUTTONDOWN;
                                break;
                            }
                            if (!isdigit(ch) || i == maxi)
                                continue;
                            settextstyle(50, 0, L"楷体");
                            outtextxy(402 + 25 * i, 275, ch);
                            id_str[i++] = ch;

                            setlinecolor(BLACK);
                            line(402 + 25 * i, 285, 402 + 25 * i, 315);
                            setlinecolor(WHITE);
                            line(402 + 25 * (i - 1), 285, 402 + 25 * (i - 1), 315);
                        }
                    }
                }
            }
            else if (m.x >= 392 && m.x <= 792 && m.y >= 450 && m.y <= 500)
            {
                setMouse(1);
                if (m.uMsg == WM_LBUTTONDOWN)
                {
                    setlinecolor(BLACK);
                    line(402 + 25 * j, 460, 402 + 25 * j, 490);
                    setlinecolor(WHITE);
                    line(402 + 25 * i, 285, 402 + 25 * i, 315);

                    while (_kbhit())
                        _getch();

                    while (true)
                    {
                        if (MouseHit())
                        {
                            m = GetMouseMsg();
                            if (m.x < 392 || m.x > 792 || m.y < 450 || m.y > 500)
                            {
                                setMouse(0);
                                selectBox(452, 590, 572, 660, false);
                                selectBack(false);
                                if (m.x >= 392 && m.x <= 792 && m.y >= 275 && m.y <= 325)
                                    setMouse(1);
                                if (m.x >= 462 && m.x <= 562 && m.y >= 600 && m.y <= 650)
                                    selectBox(452, 590, 572, 660, true);
                                if (m.x >= 20 && m.x <= 120 && m.y >= 690 && m.y <= 735)
                                    selectBack(true);
                                if (m.uMsg == WM_LBUTTONDOWN)
                                {
                                    get = true;
                                    break;
                                }
                            }
                            else
                                setMouse(1);
                        }
                        if (_kbhit())
                        {
                            char ch = _getch();
                            if (ch == '\b' && j > 0)
                            {
                                j--;
                                setfillcolor(WHITE);
                                setlinecolor(WHITE);
                                fillrectangle(402 + 25 * j, 451, 402 + 25 * (j + 1), 499);
                                setlinecolor(BLACK);
                                line(402 + 25 * j, 460, 402 + 25 * j, 490);
                                setlinecolor(WHITE);
                                setfillcolor(LIGHTBLUE);
                                continue;
                            }
                            if (ch == 13)
                            {
                                get = true;
                                m.x = 462;
                                m.y = 600;
                                m.uMsg = WM_LBUTTONDOWN;
                                break;
                            }
                            if (!isalnum(ch) || j == maxj)
                                continue;
                            settextstyle(50, 0, L"楷体");
                            outtextxy(402 + 25 * j, 450, '*');
                            passwd[j++] = ch;

                            setlinecolor(BLACK);
                            line(402 + 25 * j, 460, 402 + 25 * j, 490);
                            setlinecolor(WHITE);
                            line(402 + 25 * (j - 1), 460, 402 + 25 * (j - 1), 490);
                        }
                    }
                }
            }
            else if (m.x >= 462 && m.x <= 562 && m.y >= 600 && m.y <= 650)
            {
                selectBox(452, 590, 572, 660, true);
                if (m.uMsg == WM_LBUTTONDOWN)
                {
                    setlinecolor(WHITE);
                    line(402 + 25 * i, 285, 402 + 25 * i, 315);
                    line(402 + 25 * j, 460, 402 + 25 * j, 490);

                    id_str[i] = '\0';
                    passwd[j] = '\0';

                    if (!strlen(id_str))
                    {
                        showMessage(L"请输入工号");
                        continue;
                    }
                    if (!strlen(passwd))
                    {
                        showMessage(L"请输入工号");
                        continue;
                    }

                    int id = atoi(id_str);
                    bool flag = false;
                    Doctor* d;
                    switch (doctorCheck(id, passwd))
                    {
                    case 0:
                        d = getDoctor(id);
                        doctorInfo(d);
                        flag = true;
                        break;
                    case 1:
                        showMessage(L"查无此人");
                        break;
                    case 2:
                        showMessage(L"密码错误");
                        break;
                    default:
                        break;
                    }
                    if (flag)
                        break;
                }
            }
            else if (m.x >= 20 && m.x <= 120 && m.y >= 690 && m.y <= 735)
            {
                selectBack(true);
                if (m.uMsg == WM_LBUTTONDOWN)
                    return;
            }
            else
            {
                if (m.uMsg == WM_LBUTTONDOWN)
                {
                    setlinecolor(WHITE);
                    line(402 + 25 * i, 285, 402 + 25 * i, 315);
                    line(402 + 25 * j, 460, 402 + 25 * j, 490);
                }
                setMouse(0);
                selectBox(452, 590, 572, 660, false);
                selectBack(false);
            }
        }
    }
}

void doctorInfo(Doctor* d)
{
    while (true)
    {
        cleardevice();
        MOUSEMSG m;
        IMAGE bk;
        loadimage(&bk, _T("img\\bk.jpg"));
        putimage(0, 0, &bk);

        settextstyle(120, 0, L"楷体");
        setbkmode(TRANSPARENT);
        settextcolor(BLACK);
        outtextxy(270, 50, L"医生信息");

        settextstyle(50, 0, L"楷体");
        outtextxy(250, 225, L"工 号：");
        outtextxy(250, 300, L"姓 名：");
        outtextxy(250, 375, L"科 室：");
        outtextxy(250, 450, L"职 位：");

        char temp[100];
        wchar_t* wtemp;
        _itoa_s(d->worknum, temp, 10);

        wtemp = char2wchar(temp);
        outtextxy(450, 225, wtemp);
        delete[] wtemp;

        wtemp = char2wchar(d->name);
        outtextxy(450, 300, wtemp);
        delete[] wtemp;

        outtextxy(450, 375, DEPARTMENTS[d->office]);
        outtextxy(450, 450, POSITIONS[d->pos]);

        selectText(422, 600, 602, 650, 0, L" 接  诊");
        selectBack(false);

        while (true)
        {
            m = GetMouseMsg();
            if (m.x >= 422 && m.x <= 602 && m.y >= 600 && m.y <= 650)
            {
                selectText(422, 600, 602, 650, 1, L" 接  诊");
                if (m.uMsg == WM_LBUTTONDOWN)
                {
                    selectText(422, 600, 602, 650, 2, L" 接  诊");
                    diagnose(d);
                    break;
                }
            }
            else if (m.x >= 20 && m.x <= 120 && m.y >= 690 && m.y <= 735)
            {
                selectBack(true);
                if (m.uMsg == WM_LBUTTONDOWN)
                    return;
            }
            else
            {
                selectText(422, 600, 602, 650, 0, L" 接  诊");
                selectBack(false);
            }
        }
    }
}

void diagnose(Doctor* d)
{
    while (true)
    {
        cleardevice();
        IMAGE bk;
        loadimage(&bk, _T("img\\bk.jpg"));
        putimage(0, 0, &bk);

        settextstyle(120, 0, L"楷体");
        setbkmode(TRANSPARENT);
        settextcolor(BLACK);
        outtextxy(270, 50, L"选择患者");
        settextstyle(50, 0, L"楷体");

        wchar_t strs[100][50];
        Heallog* hs[100];
        
        int heallogs[100];
        int num_log = getNowHeallogs(d->worknum, heallogs);
        for (int i = 0; i < num_log; i++)
        {
            hs[i] = getHeallog(heallogs[i]);
            wchar_t* wtemp = char2wchar(hs[i]->patient->name);
            wcscpy_s(strs[i], wtemp);
            delete[] wtemp;
        }
        
        LPCTSTR temp_strs[100];
        for (int i = 0; i < 100; i++)
            temp_strs[i] = strs[i];
        int select = selectForm(262, 200, 762, temp_strs, num_log, false);
        
        if (select == -1)
            return;
        else
            showHeallog(hs[select]);
    }
}

void showHeallog(Heallog* h)
{
    while (true)
    {
        cleardevice();
        IMAGE bk;
        loadimage(&bk, _T("img\\bk.jpg"));
        putimage(0, 0, &bk);

        settextstyle(120, 0, L"楷体");
        setbkmode(TRANSPARENT);
        settextcolor(BLACK);
        outtextxy(270, 50, L"诊疗记录");

        settextstyle(50, 0, L"楷体");
        outtextxy(250, 225, L"医 生：");
        outtextxy(250, 300, L"患 者：");

        wchar_t* wtemp = char2wchar(h->doctor->name);
        outtextxy(450, 225, wtemp);
        delete[] wtemp;

        wtemp = char2wchar(h->patient->name);
        outtextxy(450, 300, wtemp);
        delete[] wtemp;

        LPCTSTR temp1[] =
        {
            L"检 查",
            L"开 药",
            L"出 院"
        };
        LPCTSTR temp2[] =
        {
            L"检 查",
            L"开 药",
            L"住 院"
        };

        int select = selectForm(262, 375, 762, (h->patient->ifstay != -1) ? temp1 : temp2, 3, false);
        switch (select)
        {
        case 0:
            showExamination(h);
            break;
        case 1:
            showMedicine(h);
            break;
        case 2:
            if (h->patient->ifstay != -1)
            {
                int ret = outHospital(h);
                char ret_str[100];
                _itoa_s(ret, ret_str, 10);
                wchar_t* temp = char2wchar(ret_str);
                wchar_t message[100];
                wcscpy_s(message, L"患者已出院，退还押金");
                wcscat_s(message, temp);
                wcscat_s(message, L"元");
                delete[] temp;
                showMessage(message);
            }
            else
            {
                showMessage(L"请选择预计出院时间");
                int year = chooseYear();
                if (year == 1999)
                    break;
                int month = chooseMonth();
                if (month == 0)
                    break;
                int date = chooseDate(year, month);
                if (date == 0)
                    break;
                int money = inHospital(h, year, month, date);
                if (money == -1)
                {
                    showMessage(L"选择日期不合法");
                    break;
                }
                char money_str[100];
                _itoa_s(money, money_str, 10);
                wchar_t* temp = char2wchar(money_str);
                wchar_t message[100];
                wcscpy_s(message, L"请缴纳押金至少");
                wcscat_s(message, temp);
                wcscat_s(message, L"元");
                showMessage(message);
                while (true)
                {
                    int add = recharge();
                    if (add == -1)
                    {
                        showMessage(L"未缴费！");
                        outHospital(h);
                        break;
                    }
                    if (add < money)
                    {
                        wcscpy_s(message, L"充值金额不足，请缴纳押金至少");
                        wcscat_s(message, temp);
                        wcscat_s(message, L"元");
                        showMessage(message);
                    }
                    else
                    {
                        h->patient->money = add;
                        showMessage(L"缴费成功，患者已住院");
                        break;
                    }
                }
                delete[] temp;
            }
            break;
        case -1:
            return;
        default:
            break;
        }
    }
}

void showExamination(Heallog* h)
{
    while (true)
    {
        cleardevice();
        IMAGE bk;
        loadimage(&bk, _T("img\\bk.jpg"));
        putimage(0, 0, &bk);

        settextstyle(120, 0, L"楷体");
        setbkmode(TRANSPARENT);
        settextcolor(BLACK);
        outtextxy(270, 50, L"检查记录");
        settextstyle(50, 0, L"楷体");

        wchar_t strs[4][100];
        LPCTSTR temp_strs[4];
        for (int i = 0; i < 4; i++)
        {
            wcscpy_s(strs[i], EXAMINATIONS[i]);
            wcscat_s(strs[i], L"：");
            char temp[100];
            _itoa_s(h->usetest[i], temp, 10);
            wchar_t* wtemp = char2wchar(temp);
            wcscat_s(strs[i], wtemp);
            delete[] wtemp;
            wcscat_s(strs[i], L"次");
            temp_strs[i] = strs[i];
        }
        int select = select4Form(262, 200, 762, temp_strs, false);
        if (select == -1)
            return;
        else
        {
            addExamination(h, select);
            continue;
        }
    }
}

void showMedicine(Heallog* h)
{
    while (true)
    {
        cleardevice();
        IMAGE bk;
        loadimage(&bk, _T("img\\bk.jpg"));
        putimage(0, 0, &bk);

        settextstyle(120, 0, L"楷体");
        setbkmode(TRANSPARENT);
        settextcolor(BLACK);
        outtextxy(270, 50, L"药品记录");
        settextstyle(50, 0, L"楷体");

        wchar_t strs[4][100];
        LPCTSTR temp_strs[4];
        for (int i = 0; i < 4; i++)
        {
            wcscpy_s(strs[i], MEDICINE[i]);
            wcscat_s(strs[i], L"：");
            char temp[100];
            _itoa_s(h->usemedicine[i], temp, 10);
            wchar_t* wtemp = char2wchar(temp);
            wcscat_s(strs[i], wtemp);
            delete[] wtemp;
            wcscat_s(strs[i], L"盒");
            temp_strs[i] = strs[i];
        }
        int select = select4Form(262, 200, 762, temp_strs, false);
        if (select == -1)
            return;
        else
        {
            int add_num = enterNumber();
            if (add_num > 100)
            {
                showMessage(L"单次开药过多");
                continue;
            }
            addMedicine(h, select, add_num);
        }
    }
}

void doctorRegister()
{
    if (adminLogin())
    {
        while (true)
        {
            cleardevice();
            MOUSEMSG m;
            IMAGE bk;
            loadimage(&bk, _T("img\\bk.jpg"));
            putimage(0, 0, &bk);

            setfillcolor(WHITE);
            setlinecolor(BLACK);
            fillrectangle(392, 350, 792, 400);

            setlinecolor(WHITE);
            setfillcolor(LIGHTBLUE);
            fillrectangle(462, 600, 562, 650);
            selectBox(452, 590, 572, 660, false);
            selectBack(false);

            settextstyle(120, 0, L"楷体");
            setbkmode(TRANSPARENT);
            settextcolor(BLACK);
            outtextxy(270, 50, L"医生信息");

            settextstyle(25, 0, L"楷体");
            outtextxy(480, 612, L"确 定");

            settextstyle(50, 0, L"楷体");
            outtextxy(242, 350, L"姓 名");

            bool get = false;
            int i = 0;
            const int maxi = 14;
            char name[maxi + 1];
            while (true)
            {
                if (!get)
                    m = GetMouseMsg();
                else
                    get = false;
                if (m.x >= 392 && m.x <= 792 && m.y >= 350 && m.y <= 400)
                {
                    setMouse(1);
                    if (m.uMsg == WM_LBUTTONDOWN)
                    {
                        setlinecolor(BLACK);
                        line(402 + 25 * i, 360, 402 + 25 * i, 390);
                        setlinecolor(WHITE);

                        while (_kbhit())
                            _getch();

                        while (true)
                        {
                            if (MouseHit())
                            {
                                m = GetMouseMsg();
                                if (m.x < 392 || m.x > 792 || m.y < 360 || m.y > 390)
                                {
                                    setMouse(0);
                                    selectBox(452, 590, 572, 660, false);
                                    selectBack(false);
                                    if (m.x >= 462 && m.x <= 562 && m.y >= 600 && m.y <= 650)
                                        selectBox(452, 590, 572, 660, true);
                                    if (m.x >= 20 && m.x <= 120 && m.y >= 690 && m.y <= 735)
                                        selectBack(true);
                                    if (m.uMsg == WM_LBUTTONDOWN)
                                    {
                                        get = true;
                                        break;
                                    }
                                }
                                else
                                    setMouse(1);
                            }
                            if (_kbhit())
                            {
                                char ch = _getch();
                                if (ch == '\b' && i > 0)
                                {
                                    i--;
                                    setfillcolor(WHITE);
                                    setlinecolor(WHITE);
                                    fillrectangle(402 + 25 * i, 351, 402 + 25 * (i + 1), 399);
                                    setlinecolor(BLACK);
                                    line(402 + 25 * i, 360, 402 + 25 * i, 390);
                                    setlinecolor(WHITE);
                                    setfillcolor(LIGHTBLUE);
                                    continue;
                                }
                                if (ch == 13)
                                {
                                    get = true;
                                    m.x = 462;
                                    m.y = 600;
                                    m.uMsg = WM_LBUTTONDOWN;
                                    break;
                                }
                                if (!isalnum(ch) || i == maxi)
                                    continue;
                                settextstyle(50, 0, L"楷体");
                                outtextxy(402 + 25 * i, 350, ch);
                                name[i++] = ch;

                                setlinecolor(BLACK);
                                line(402 + 25 * i, 360, 402 + 25 * i, 390);
                                setlinecolor(WHITE);
                                line(402 + 25 * (i - 1), 360, 402 + 25 * (i - 1), 390);
                            }
                        }
                    }
                }
                else if (m.x >= 462 && m.x <= 562 && m.y >= 600 && m.y <= 650)
                {
                    selectBox(452, 590, 572, 660, true);
                    if (m.uMsg == WM_LBUTTONDOWN)
                    {
                        setlinecolor(WHITE);
                        line(402 + 25 * i, 360, 402 + 25 * i, 390);

                        name[i] = '\0';

                        if (!strlen(name))
                        {
                            showMessage(L"请输入姓名");
                            continue;
                        }

                        int department = chooseDepartment();
                        if (department == -1)
                            break;

                        int position = choosePositions();
                        if (position == -1)
                            break;

                        int workdays[7];
                        if (!chooseWorkdays(workdays))
                            break;

                        char passwd[maxi + 1];
                        if (!setPasswd(passwd))
                            break;

                        int id = addDoctor(name, department, position, workdays, passwd);
                        char id_str[maxi + 1];
                        _itoa_s(id, id_str, 10);
                        wchar_t message[100];
                        wchar_t* wtemp = char2wchar(id_str);
                        wcscpy_s(message, L"注册成功，您的工号是");
                        wcscat_s(message, wtemp);
                        delete[] wtemp;
                        showMessage(message);

                        return;
                    }
                }
                else if (m.x >= 20 && m.x <= 120 && m.y >= 690 && m.y <= 735)
                {
                    selectBack(true);
                    if (m.uMsg == WM_LBUTTONDOWN)
                        return;
                }
                else
                {
                    if (m.uMsg == WM_LBUTTONDOWN)
                    {
                        setlinecolor(WHITE);
                        line(402 + 25 * i, 360, 402 + 25 * i, 390);
                    }
                    setMouse(0);
                    selectBox(452, 590, 572, 660, false);
                    selectBack(false);
                }
            }
        }
    }
}

void admin()
{
    if (adminLogin())
    {
        while (true)
        {
            cleardevice();
            MOUSEMSG m;
            IMAGE bk;
            loadimage(&bk, _T("img\\bk.jpg"));
            putimage(0, 0, &bk);

            setfillcolor(LIGHTBLUE);
            fillrectangle(312, 275, 712, 375);
            fillrectangle(312, 450, 712, 550);

            selectBox(302, 265, 722, 385, false);
            selectBox(302, 440, 722, 560, false);
            selectBack(false);

            settextstyle(120, 0, L"楷体");
            setbkmode(TRANSPARENT);
            settextcolor(BLACK);
            outtextxy(330, 50, L"管理员");

            settextstyle(50, 0, L"楷体");
            outtextxy(412, 300, L" 查  询");
            outtextxy(412, 475, L" 统  计");

            while (true)
            {
                m = GetMouseMsg();
                if (m.x >= 312 && m.x <= 712 && m.y >= 275 && m.y <= 375)
                {
                    selectBox(302, 265, 722, 385, true);
                    if (m.uMsg == WM_LBUTTONDOWN)
                    {
                        switch (chooseInquire())
                        {
                        case 0:
                            inquireDepartment(chooseDepartment());
                            break;
                        case 1:
                            inquireDoctor(chooseDoctor(4));
                            break;
                        case 2:
                            inquirePatient(choosePatient());
                            break;
                        case 3:
                            inquireTime();
                            break;
                        }
                        break;
                    }
                }
                else if (m.x >= 312 && m.x <= 712 && m.y >= 450 && m.y <= 550)
                {
                    selectBox(302, 440, 722, 560, true);
                    if (m.uMsg == WM_LBUTTONDOWN)
                    {
                        statistics();
                        break;
                    }
                }
                else if (m.x >= 20 && m.x <= 120 && m.y >= 690 && m.y <= 735)
                {
                    selectBack(true);
                    if (m.uMsg == WM_LBUTTONDOWN)
                        return;
                }
                else
                {
                    selectBack(false);
                    selectBox(302, 265, 722, 385, false);
                    selectBox(302, 440, 722, 560, false);
                }
            }
        }
    }
}

void inquireDepartment(int department)
{
    while (department != -1)
    {
        cleardevice();
        IMAGE bk;
        loadimage(&bk, _T("img\\bk.jpg"));
        putimage(0, 0, &bk);

        settextstyle(120, 0, L"楷体");
        setbkmode(TRANSPARENT);
        settextcolor(BLACK);
        outtextxy(270, 50, L"诊疗记录");

        wchar_t strs[100][50];
        for (int i = 0; i < 100; i++)
            wcscpy_s(strs[i], L"  医生：");
        Heallog* hs[100];
        int k = 0;

        int doctors[100];
        int num_doc = getDoctors(department, doctors);
        
        for (int i = 0; i < num_doc; i++)
        {
            int heallogs[100];
            int num_log = getDoctorHeallogs(doctors[i], heallogs);
            for (int j = 0; j < num_log; j++)
            {
                hs[k] = getHeallog(heallogs[j]);
                wchar_t* wtemp = char2wchar(hs[k]->doctor->name);
                wcscat_s(strs[k], wtemp);
                delete[] wtemp;
                wcscat_s(strs[k], L"  患者：");
                wtemp = char2wchar(hs[k]->patient->name);
                wcscat_s(strs[k], wtemp);
                delete[] wtemp;
                k++;
            }
        }

        LPCTSTR temp_strs[100];
        for (int i = 0; i < 100; i++)
            temp_strs[i] = strs[i];
        int select = selectForm(262, 200, 762, temp_strs, k, false);

        if (select == -1)
            return;
        else
            showAdminHeallog(hs[select]);
    }
}

void inquireDoctor(int id)
{
    while (id != -1)
    {
        cleardevice();
        IMAGE bk;
        loadimage(&bk, _T("img\\bk.jpg"));
        putimage(0, 0, &bk);

        settextstyle(120, 0, L"楷体");
        setbkmode(TRANSPARENT);
        settextcolor(BLACK);
        outtextxy(270, 50, L"诊疗记录");

        wchar_t strs[100][50];
        for (int i = 0; i < 100; i++)
            wcscpy_s(strs[i], L"  医生：");
        Heallog* hs[100];

        int heallogs[100];
        int num_log = getDoctorHeallogs(id, heallogs);
        for (int i = 0; i < num_log; i++)
        {
            hs[i] = getHeallog(heallogs[i]);
            wchar_t* wtemp = char2wchar(hs[i]->doctor->name);
            wcscat_s(strs[i], wtemp);
            delete[] wtemp;
            wcscat_s(strs[i], L"  患者：");
            wtemp = char2wchar(hs[i]->patient->name);
            wcscat_s(strs[i], wtemp);
            delete[] wtemp;
        }

        LPCTSTR temp_strs[100];
        for (int i = 0; i < 100; i++)
            temp_strs[i] = strs[i];
        int select = selectForm(262, 200, 762, temp_strs, num_log, false);

        if (select == -1)
            return;
        else
            showAdminHeallog(hs[select]);
    }
}

void inquirePatient(int id)
{
    while (id != -1)
    {
        cleardevice();
        IMAGE bk;
        loadimage(&bk, _T("img\\bk.jpg"));
        putimage(0, 0, &bk);

        settextstyle(120, 0, L"楷体");
        setbkmode(TRANSPARENT);
        settextcolor(BLACK);
        outtextxy(270, 50, L"诊疗记录");

        wchar_t strs[100][50];
        for (int i = 0; i < 100; i++)
            wcscpy_s(strs[i], L"  医生：");
        Heallog* hs[100];

        int heallogs[100];
        int num_log = getPatientHeallogs(id, heallogs);
        for (int i = 0; i < num_log; i++)
        {
            hs[i] = getHeallog(heallogs[i]);
            wchar_t* wtemp = char2wchar(hs[i]->doctor->name);
            wcscat_s(strs[i], wtemp);
            delete[] wtemp;
            wcscat_s(strs[i], L"  患者：");
            wtemp = char2wchar(hs[i]->patient->name);
            wcscat_s(strs[i], wtemp);
            delete[] wtemp;
        }

        LPCTSTR temp_strs[100];
        for (int i = 0; i < 100; i++)
            temp_strs[i] = strs[i];
        int select = selectForm(262, 200, 762, temp_strs, num_log, false);

        if (select == -1)
            return;
        else
            showAdminHeallog(hs[select]);
    }
}

void inquireTime()
{
    while (true)
    {
        int year1 = chooseYear();
        if (year1 == 1999)
            break;
        int month1 = chooseMonth();
        if (month1 == 0)
            break;
        int date1 = chooseDate(year1, month1);
        if (date1 == 0)
            break;

        int year2 = chooseYear();
        if (year2 == 1999)
            break;
        int month2 = chooseMonth();
        if (month2 == 0)
            break;
        int date2 = chooseDate(year2, month2);
        if (date2 == 0)
            break;

        cleardevice();
        IMAGE bk;
        loadimage(&bk, _T("img\\bk.jpg"));
        putimage(0, 0, &bk);

        settextstyle(120, 0, L"楷体");
        setbkmode(TRANSPARENT);
        settextcolor(BLACK);
        outtextxy(270, 50, L"诊疗记录");

        wchar_t strs[100][50];
        for (int i = 0; i < 100; i++)
            wcscpy_s(strs[i], L"  医生：");
        Heallog* hs[100];

        int heallogs[100];
        int num_log = getTimeHeallogs(year1, month1, date1, year2, month2, date2, heallogs);
        for (int i = 0; i < num_log; i++)
        {
            hs[i] = getHeallog(heallogs[i]);
            wchar_t* wtemp = char2wchar(hs[i]->doctor->name);
            wcscat_s(strs[i], wtemp);
            delete[] wtemp;
            wcscat_s(strs[i], L"  患者：");
            wtemp = char2wchar(hs[i]->patient->name);
            wcscat_s(strs[i], wtemp);
            delete[] wtemp;
        }

        LPCTSTR temp_strs[100];
        for (int i = 0; i < 100; i++)
            temp_strs[i] = strs[i];
        int select = selectForm(262, 200, 762, temp_strs, num_log, false);

        if (select == -1)
            return;
        else
            showAdminHeallog(hs[select]);
    }
}

void showAdminHeallog(Heallog* h)
{
    while (true)
    {
        cleardevice();
        IMAGE bk;
        loadimage(&bk, _T("img\\bk.jpg"));
        putimage(0, 0, &bk);

        settextstyle(120, 0, L"楷体");
        setbkmode(TRANSPARENT);
        settextcolor(BLACK);
        outtextxy(270, 50, L"诊疗记录");

        settextstyle(50, 0, L"楷体");
        outtextxy(250, 225, L"医 生：");
        outtextxy(250, 300, L"患 者：");

        wchar_t* wtemp = char2wchar(h->doctor->name);
        outtextxy(450, 225, wtemp);
        delete[] wtemp;

        wtemp = char2wchar(h->patient->name);
        outtextxy(450, 300, wtemp);
        delete[] wtemp;

        LPCTSTR temp[] =
        {
            L"检 查",
            L"药 品",
            L"修 改",
            L"删 除"
        };

        int select = select4Form(262, 375, 762, temp, false);
        switch (select)
        {
        case 0:
            showExamination(h);
            break;
        case 1:
            showMedicine(h);
            break;
        case 2:
            virtualDeleteHeallog(h);
            showMessage(L"诊疗记录已清空，请添加新内容");
            break;
        case 3:
            deleteHeallog(h);
            return;
        case -1:
            return;
        default:
            break;
        }
    }
}

void statistics()
{
    while (true)
    {
        cleardevice();
        MOUSEMSG m;
        IMAGE bk;
        loadimage(&bk, _T("img\\bk.jpg"));
        putimage(0, 0, &bk);

        setfillcolor(LIGHTBLUE);
        fillrectangle(312, 225, 712, 325);
        fillrectangle(312, 400, 712, 500);
        fillrectangle(312, 575, 712, 675);

        selectBox(302, 215, 722, 335, false);
        selectBox(302, 390, 722, 510, false);
        selectBox(302, 565, 722, 685, false);

        settextstyle(150, 0, L"楷体");
        setbkmode(TRANSPARENT);
        settextcolor(BLACK);
        outtextxy(287, 25, L"统  计");

        settextstyle(50, 0, L"楷体");
        outtextxy(440, 250, L"营业额");
        outtextxy(365, 425, L"住院患者报表");
        outtextxy(365, 600, L"医生出诊情况");
        selectBack(false);

        while (true)
        {
            m = GetMouseMsg();
            if (m.x >= 312 && m.x <= 712 && m.y >= 225 && m.y <= 325)
            {
                selectBox(302, 215, 722, 335, true);
                if (m.uMsg == WM_LBUTTONDOWN)
                {
                    showIncome();
                    break;
                }
            }
            else if (m.x >= 312 && m.x <= 712 && m.y >= 400 && m.y <= 500)
            {
                selectBox(302, 390, 722, 510, true);
                if (m.uMsg == WM_LBUTTONDOWN)
                {
                    showInPatients();
                    break;
                }
            }
            else if (m.x >= 312 && m.x <= 712 && m.y >= 575 && m.y <= 675)
            {
                selectBox(302, 565, 722, 685, true);
                if (m.uMsg == WM_LBUTTONDOWN)
                {
                    showDoctorsCondition();
                    break;
                }
            }
            else if (m.x >= 20 && m.x <= 120 && m.y >= 690 && m.y <= 735)
            {
                selectBack(true);
                if (m.uMsg == WM_LBUTTONDOWN)
                    return;
            }
            else
            {
                selectBack(false);
                selectBox(302, 215, 722, 335, false);
                selectBox(302, 390, 722, 510, false);
                selectBox(302, 565, 722, 685, false);
            }
        }
    }
}

void showIncome()
{
    while (true)
    {
        cleardevice();
        IMAGE bk;
        loadimage(&bk, _T("img\\bk.jpg"));
        putimage(0, 0, &bk);

        settextstyle(150, 0, L"楷体");
        setbkmode(TRANSPARENT);
        settextcolor(BLACK);
        outtextxy(287, 25, L"营业额");
        settextstyle(50, 0, L"楷体");

        double incomes[5];
        double all = getIncomes(incomes);
        incomes[4] = all;
        
        wchar_t strs[5][100];
        for (int i = 0; i < 4; i++)
        {
            wcscpy_s(strs[i], DEPARTMENTS[i]);
            char income_str[100];
            sprintf_s(income_str, ": %.2lf", incomes[i]);
            wchar_t* wtemp = char2wchar(income_str);
            wcscat_s(strs[i], wtemp);
            delete[] wtemp;
            wcscat_s(strs[i], L"元");
        }
        wcscpy_s(strs[4], L"总计");
        char income_str[100];
        sprintf_s(income_str, ": %.2lf", incomes[4]);
        wchar_t* wtemp = char2wchar(income_str);
        wcscat_s(strs[4], wtemp);
        delete[] wtemp;
        wcscat_s(strs[4], L"元");

        LPCTSTR temp_strs[5];
        for (int i = 0; i < 5; i++)
            temp_strs[i] = strs[i];
        selectForm(262, 200, 762, temp_strs, 5, true);
        return;
    }
}

void showInPatients()
{
    while (true)
    {
        cleardevice();
        IMAGE bk;
        loadimage(&bk, _T("img\\bk.jpg"));
        putimage(0, 0, &bk);

        settextstyle(80, 0, L"楷体");
        setbkmode(TRANSPARENT);
        settextcolor(BLACK);
        outtextxy(272, 25, L"住院患者报表");
        settextstyle(50, 0, L"楷体");

        int patients[120];
        int num_pat = getInPatients(patients);

        wchar_t strs[120][50];
        for (int i = 0; i < num_pat; i++)
        {
            Patient* p = getPatient(patients[i]);
            char temp[100];
            _itoa_s(p->systemID, temp, 10);
            wchar_t* wtemp = char2wchar(temp);
            wcscpy_s(strs[i], wtemp);
            delete[] wtemp;

            wcscat_s(strs[i], L"/");
            wtemp = char2wchar(p->name);
            wcscat_s(strs[i], wtemp);
            delete[] wtemp;

            wcscat_s(strs[i], L"/入院时间：");
            struct tm intime;
            gmtime_s(&intime, &(p->in));
            _itoa_s(intime.tm_year + 1900, temp, 10);
            wtemp = char2wchar(temp);
            wcscat_s(strs[i], wtemp);
            delete[] wtemp;
            wcscat_s(strs[i], L".");
            _itoa_s(intime.tm_mon + 1, temp, 10);
            wtemp = char2wchar(temp);
            wcscat_s(strs[i], wtemp);
            delete[] wtemp;
            wcscat_s(strs[i], L".");
            _itoa_s(intime.tm_mday, temp, 10);
            wtemp = char2wchar(temp);
            wcscat_s(strs[i], wtemp);
            delete[] wtemp;
        }

        LPCTSTR temp_strs[120];
        for (int i = 0; i < 120; i++)
            temp_strs[i] = strs[i];
        int select = selectForm(212, 200, 812, temp_strs, num_pat, false);
        if (select == -1)
            return;
        else
            showAdminStayInfo(getPatient(patients[select]));
    }
}

void showAdminStayInfo(Patient* p)
{
    while (true)
    {
        cleardevice();
        MOUSEMSG m;
        IMAGE bk;
        loadimage(&bk, _T("img\\bk.jpg"));
        putimage(0, 0, &bk);

        selectBack(false);
        settextstyle(120, 0, L"楷体");
        setbkmode(TRANSPARENT);
        settextcolor(BLACK);
        outtextxy(270, 50, L"住院信息");

        settextstyle(50, 0, L"楷体");
        outtextxy(250, 250, L"押金余额：");
        outtextxy(150, 350, L"预计出院时间：");

        char temp[100];
        wchar_t* wtemp;
        _itoa_s(p->money, temp, 10);
        wtemp = char2wchar(temp);
        outtextxy(500, 250, wtemp);
        delete[] wtemp;

        wchar_t str[100];
        struct tm outtime;
        gmtime_s(&outtime, &(p->out));
        _itoa_s(outtime.tm_year + 1900, temp, 10);
        wtemp = char2wchar(temp);
        wcscpy_s(str, wtemp);
        delete[] wtemp;
        wcscat_s(str, L".");
        _itoa_s(outtime.tm_mon + 1, temp, 10);
        wtemp = char2wchar(temp);
        wcscat_s(str, wtemp);
        delete[] wtemp;
        wcscat_s(str, L".");
        _itoa_s(outtime.tm_mday, temp, 10);
        wtemp = char2wchar(temp);
        wcscat_s(str, wtemp);
        delete[] wtemp;
        outtextxy(500, 350, str);

        while (true)
        {
            m = GetMouseMsg();
            if (m.x >= 20 && m.x <= 120 && m.y >= 690 && m.y <= 735)
            {
                selectBack(true);
                if (m.uMsg == WM_LBUTTONDOWN)
                    return;
            }
            else
                selectBack(false);
        }
    }
}

void showDoctorsCondition()
{
    while (true)
    {
        cleardevice();
        IMAGE bk;
        loadimage(&bk, _T("img\\bk.jpg"));
        putimage(0, 0, &bk);

        settextstyle(80, 0, L"楷体");
        setbkmode(TRANSPARENT);
        settextcolor(BLACK);
        outtextxy(272, 25, L"医生出诊情况");
        settextstyle(50, 0, L"楷体");
        outtextxy(80, 150, L"工号/姓名/出诊时间/繁忙程度");

        int doctors[50];
        int num_doc = getDoctors(4, doctors);

        wchar_t strs[100][50];
        for (int i = 0; i < num_doc; i++)
        {
            Doctor* d = getDoctor(doctors[i]);
            char temp[100];
            _itoa_s(d->worknum, temp, 10);
            wchar_t* wtemp = char2wchar(temp);
            wcscpy_s(strs[i], wtemp);
            delete[] wtemp;
            wcscat_s(strs[i], L"/");
            wtemp = char2wchar(d->name);
            wcscat_s(strs[i], wtemp);
            delete[] wtemp;

            wcscat_s(strs[i], L"/周");
            bool flag = false;
            for (int j = 1; j <= 7; j++)
                if (d->days[j % 7])
                {
                    if (flag)
                        wcscat_s(strs[i], L",");
                    else
                        flag = true;
                    switch (j)
                    {
                    case 1:
                        wcscat_s(strs[i], L"一");
                        break;
                    case 2:
                        wcscat_s(strs[i], L"二");
                        break;
                    case 3:
                        wcscat_s(strs[i], L"三");
                        break;
                    case 4:
                        wcscat_s(strs[i], L"四");
                        break;
                    case 5:
                        wcscat_s(strs[i], L"五");
                        break;
                    case 6:
                        wcscat_s(strs[i], L"六");
                        break;
                    case 7:
                        wcscat_s(strs[i], L"日");
                        break;
                    }
                }
            wcscat_s(strs[i], L"/");
            switch (getBusyness(d))
            {
            case 0:
                wcscat_s(strs[i], L"低");
                break;
            case 1:
                wcscat_s(strs[i], L"较低");
                break;
            case 2:
                wcscat_s(strs[i], L"较高");
                break;
            case 3:
                wcscat_s(strs[i], L"高");
                break;
            }
        }

        LPCTSTR temp_strs[50];
        for (int i = 0; i < 50; i++)
            temp_strs[i] = strs[i];
        if (selectForm(112, 200, 912, temp_strs, num_doc, true) == -1)
            return;
    }
}
