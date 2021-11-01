#ifndef WINVER 
#define WINVER 0x0500 
#endif

#include "Data.h"
#include "Auxiliary.h"
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>

const char ROOT_PASSWD[9] = "1";
LPCTSTR DEPARTMENTS[] =
{
    L"内  科",
    L"外  科",
    L"妇产科",
    L"儿  科"
};
LPCTSTR POSITIONS[] =
{
    L"主任医师",
    L"副主任医师",
    L"主治医师",
    L"住院医师"
};
LPCTSTR EXAMINATIONS[4]
{
    L"X光",
    L"CT",
    L"血常规",
    L"B超"
};
LPCTSTR MEDICINE[4]
{
    L"999感冒灵",
    L"阿司匹林",
    L"云南白药",
    L"健胃消食片"
};

int recharge()
{
    cleardevice();
    ExMessage m;
    IMAGE bk;
    loadimage(&bk, _T("img\\bk.jpg"));
    putimage(0, 0, &bk);

    setfillcolor(WHITE);
    setlinecolor(BLACK);
    fillrectangle(312, 350, 712, 400);

    setlinecolor(WHITE);
    setfillcolor(LIGHTBLUE);
    fillrectangle(462, 600, 562, 650);
    selectBox(452, 590, 572, 660, false);
    selectBack(false);

    settextstyle(80, 0, L"楷体");
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);
    outtextxy(192, 50, L"充值金额（百元）");

    settextstyle(25, 0, L"楷体");
    outtextxy(480, 612, L"确 定");
    settextstyle(50, 0, L"楷体");

    bool get = false;
    int i = 0;
    const int maxi = 5;
    char money_str[maxi + 1];
    while (true)
    {
        if (!get)
            m = getmessage();
        else
            get = false;
        if (m.x >= 312 && m.x <= 712 && m.y >= 350 && m.y <= 400)
        {
            setMouse(1);
            if (m.message == WM_LBUTTONDOWN)
            {
                setlinecolor(BLACK);
                line(322 + 25 * i, 360, 322 + 25 * i, 390);
                setlinecolor(WHITE);

                while (_kbhit())
                    _getch();

                while (true)
                {
                    if (peekmessage(&m, -1, false))
                    {
                        m = getmessage();
                        if (m.x < 312 || m.x > 712 || m.y < 350 || m.y > 400)
                        {
                            setMouse(0);
                            selectBox(452, 590, 572, 660, false);
                            selectBack(false);
                            if (m.x >= 462 && m.x <= 562 && m.y >= 600 && m.y <= 650)
                                selectBox(452, 590, 572, 660, true);
                            if (m.x >= 20 && m.x <= 120 && m.y >= 690 && m.y <= 735)
                                selectBack(true);
                            if (m.message == WM_LBUTTONDOWN)
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
                            fillrectangle(322 + 25 * i, 351, 322 + 25 * (i + 1), 399);
                            setlinecolor(BLACK);
                            line(322 + 25 * i, 360, 322 + 25 * i, 390);
                            setlinecolor(WHITE);
                            setfillcolor(LIGHTBLUE);
                            continue;
                        }
                        if (ch == 13)
                        {
                            get = true;
                            m.x = 462;
                            m.y = 600;
                            m.message = WM_LBUTTONDOWN;
                            break;
                        }
                        if (!isdigit(ch) || i == maxi)
                            continue;
                        settextstyle(50, 0, L"楷体");
                        outtextxy(322 + 25 * i, 350, ch);
                        money_str[i++] = ch;

                        setlinecolor(BLACK);
                        line(322 + 25 * i, 360, 322 + 25 * i, 390);
                        setlinecolor(WHITE);
                        line(322 + 25 * (i - 1), 360, 322 + 25 * (i - 1), 390);
                    }
                }
            }
        }
        else if (m.x >= 462 && m.x <= 562 && m.y >= 600 && m.y <= 650)
        {
            selectBox(452, 590, 572, 660, true);
            if (m.message == WM_LBUTTONDOWN)
            {
                setlinecolor(WHITE);
                line(322 + 25 * i, 360, 322 + 25 * i, 390);

                money_str[i] = '\0';

                if (!strlen(money_str))
                {
                    showMessage(L"请输入金额");
                    continue;
                }

                return atoi(money_str) * 100;
            }
        }
        else if (m.x >= 20 && m.x <= 120 && m.y >= 690 && m.y <= 735)
        {
            selectBack(true);
            if (m.message == WM_LBUTTONDOWN)
                return -1;
        }
        else
        {
            if (m.message == WM_LBUTTONDOWN)
            {
                setlinecolor(WHITE);
                line(322 + 25 * i, 360, 322 + 25 * i, 390);
            }
            setMouse(0);
            selectBox(452, 590, 572, 660, false);
            selectBack(false);
        }
    }
}

int chooseDepartment()
{
    cleardevice();
    IMAGE bk;
    loadimage(&bk, _T("img\\bk.jpg"));
    putimage(0, 0, &bk);

    settextstyle(120, 0, L"楷体");
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);
    outtextxy(270, 50, L"选择科室");

    return select4Form(262, 200, 762, DEPARTMENTS, false);
}

int choosePositions()
{
    cleardevice();
    IMAGE bk;
    loadimage(&bk, _T("img\\bk.jpg"));
    putimage(0, 0, &bk);

    settextstyle(120, 0, L"楷体");
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);
    outtextxy(270, 50, L"选择级别");

    return select4Form(262, 200, 762, POSITIONS, false);
}

int chooseDoctor(int department)
{
    cleardevice();
    IMAGE bk;
    loadimage(&bk, _T("img\\bk.jpg"));
    putimage(0, 0, &bk);

    settextstyle(120, 0, L"楷体");
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);
    outtextxy(270, 50, L"选择医生");

    int ids[100];
    memset(ids, 0, sizeof(ids));
    int num_doc;
    if (department == 4)
        num_doc = getDoctors(department, ids);
    else
        num_doc = getNowDoctors(department, ids);

    wchar_t temp_names[100][15];
    LPCTSTR names[100];
    memset(names, 0, sizeof(names));
    for (int i = 0; i < num_doc; i++)
    {
        Doctor* d = getDoctor(ids[i]);
        wchar_t* wtemp = char2wchar(d->name);
        wcscpy_s(temp_names[i], wtemp);
        delete[] wtemp;
        names[i] = temp_names[i];
    }

    int temp = selectForm(262, 200, 762, names, num_doc, false);
    return (temp == -1) ? temp : ids[temp];
}

int choosePatient()
{
    cleardevice();
    IMAGE bk;
    loadimage(&bk, _T("img\\bk.jpg"));
    putimage(0, 0, &bk);

    settextstyle(120, 0, L"楷体");
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);
    outtextxy(270, 50, L"选择患者");

    int ids[120];
    memset(ids, 0, sizeof(ids));
    int num_doc = getPatients(ids);

    wchar_t temp_names[100][15];
    LPCTSTR names[100];
    memset(names, 0, sizeof(names));
    for (int i = 0; i < num_doc; i++)
    {
        Patient* d = getPatient(ids[i]);
        wchar_t* wtemp = char2wchar(d->name);
        wcscpy_s(temp_names[i], wtemp);
        delete[] wtemp;
        names[i] = temp_names[i];
    }

    int temp = selectForm(262, 200, 762, names, num_doc, false);
    return (temp == -1) ? temp : ids[temp];
}

bool chooseWorkdays(int workdays[])
{
    int tempdays[7];
    memset(workdays, 0, sizeof(workdays));
    memset(tempdays, 0, sizeof(tempdays));

    cleardevice();
    ExMessage m;
    IMAGE bk;
    loadimage(&bk, _T("img\\bk.jpg"));
    putimage(0, 0, &bk);

    settextstyle(120, 0, L"楷体");
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);
    outtextxy(270, 50, L"出诊时间");

    setlinecolor(WHITE);
    setfillcolor(LIGHTBLUE);
    fillrectangle(462, 600, 562, 650);
    selectBox(452, 590, 572, 660, false);
    selectBack(false);

    settextstyle(25, 0, L"楷体");
    outtextxy(480, 612, L"确 定");
    settextstyle(50, 0, L"楷体");

    LPCTSTR days[] =
    {
        L"一",
        L"二",
        L"三",
        L"四",
        L"五",
        L"六",
        L"日"
    };

    for (int i = 0; i < 7; i++)
        selectText(337 + 50 * i, 300, 387 + 50 * i, 350, 0, days[i]);

    while (true)
    {
        m = getmessage();
        for (int i = 0; i < 7; i++)
        {
            if (m.x >= 337 + 50 * i && m.x <= 387 + 50 * i && m.y >= 300 && m.y <= 350)
            {
                for (int j = 0; j < 7; j++)
                    if (j != i)
                        selectText(337 + 50 * j, 300, 387 + 50 * j, 350, tempdays[(j + 1) % 7] ? 2 : 0, days[j]);
                selectText(337 + 50 * i, 300, 387 + 50 * i, 350, tempdays[(i + 1) % 7] ? 2 : 1, days[i]);
                if (m.message == WM_LBUTTONDOWN)
                {
                    if (tempdays[(i + 1) % 7])
                    {
                        selectText(337 + 50 * i, 300, 387 + 50 * i, 350, 0, days[i]);
                        tempdays[(i + 1) % 7] = 0;
                    }
                    else
                    {
                        selectText(337 + 50 * i, 300, 387 + 50 * i, 350, 2, days[i]);
                        tempdays[(i + 1) % 7] = 1;
                    }
                }
            }
        }
        if (m.x >= 452 && m.x <= 572 && m.y >= 590 && m.y <= 660)
        {
            selectBox(452, 590, 572, 660, true);
            if (m.message == WM_LBUTTONDOWN)
            {
                int temp = 0;
                for (int i = 0; i < 7; i++)
                    temp += tempdays[i];
                if (!temp)
                {
                    showMessage(L"请选择工作时间");
                    continue;
                }

                for (int i = 0; i < 7; i++)
                    workdays[i] = tempdays[i];
                return true;
            }
        }
        else if (m.x >= 20 && m.x <= 120 && m.y >= 690 && m.y <= 735)
        {
            selectBack(true);
            if (m.message == WM_LBUTTONDOWN)
                return false;
        }
        else if (m.x < 337 || m.x > 687 || m.y < 300 || m.y > 350)
        {
            selectBack(false);
            selectBox(452, 590, 572, 660, false);
            for (int i = 0; i < 7; i++)
                selectText(337 + 50 * i, 300, 387 + 50 * i, 350, tempdays[(i + 1) % 7] ? 2 : 0, days[i]);
        }
    }
}

int chooseInquire()
{
    cleardevice();
    IMAGE bk;
    loadimage(&bk, _T("img\\bk.jpg"));
    putimage(0, 0, &bk);

    settextstyle(120, 0, L"楷体");
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);
    outtextxy(270, 50, L"查询方式");

    LPCTSTR ways[]
    {
        L" 按科室",
        L" 按医生",
        L" 按患者",
        L"按时间段"
    };

    return select4Form(362, 300, 662, ways, false);
}

int enterNumber()
{
    cleardevice();
    ExMessage m;
    IMAGE bk;
    loadimage(&bk, _T("img\\bk.jpg"));
    putimage(0, 0, &bk);

    setfillcolor(WHITE);
    setlinecolor(BLACK);
    fillrectangle(312, 350, 712, 400);

    setlinecolor(WHITE);
    setfillcolor(LIGHTBLUE);
    fillrectangle(462, 600, 562, 650);
    selectBox(452, 590, 572, 660, false);
    selectBack(false);

    settextstyle(120, 0, L"楷体");
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);
    outtextxy(270, 50, L"输入数量");

    settextstyle(25, 0, L"楷体");
    outtextxy(480, 612, L"确 定");
    settextstyle(50, 0, L"楷体");

    bool get = false;
    int i = 0;
    const int maxi = 5;
    char number[maxi + 1];
    while (true)
    {
        if (!get)
            m = getmessage();
        else
            get = false;
        if (m.x >= 312 && m.x <= 712 && m.y >= 350 && m.y <= 400)
        {
            setMouse(1);
            if (m.message == WM_LBUTTONDOWN)
            {
                setlinecolor(BLACK);
                line(322 + 25 * i, 360, 322 + 25 * i, 390);
                setlinecolor(WHITE);

                while (_kbhit())
                    _getch();

                while (true)
                {
                    if (peekmessage(&m, -1, false))
                    {
                        m = getmessage();
                        if (m.x < 312 || m.x > 712 || m.y < 350 || m.y > 400)
                        {
                            setMouse(0);
                            selectBox(452, 590, 572, 660, false);
                            selectBack(false);
                            if (m.x >= 462 && m.x <= 562 && m.y >= 600 && m.y <= 650)
                                selectBox(452, 590, 572, 660, true);
                            if (m.x >= 20 && m.x <= 120 && m.y >= 690 && m.y <= 735)
                                selectBack(true);
                            if (m.message == WM_LBUTTONDOWN)
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
                            fillrectangle(322 + 25 * i, 351, 322 + 25 * (i + 1), 399);
                            setlinecolor(BLACK);
                            line(322 + 25 * i, 360, 322 + 25 * i, 390);
                            setlinecolor(WHITE);
                            setfillcolor(LIGHTBLUE);
                            continue;
                        }
                        if (ch == 13)
                        {
                            get = true;
                            m.x = 462;
                            m.y = 600;
                            m.message = WM_LBUTTONDOWN;
                            break;
                        }
                        if (!isdigit(ch) || i == maxi)
                            continue;
                        settextstyle(50, 0, L"楷体");
                        outtextxy(322 + 25 * i, 350, ch);
                        number[i++] = ch;

                        setlinecolor(BLACK);
                        line(322 + 25 * i, 360, 322 + 25 * i, 390);
                        setlinecolor(WHITE);
                        line(322 + 25 * (i - 1), 360, 322 + 25 * (i - 1), 390);
                    }
                }
            }
        }
        else if (m.x >= 462 && m.x <= 562 && m.y >= 600 && m.y <= 650)
        {
            selectBox(452, 590, 572, 660, true);
            if (m.message == WM_LBUTTONDOWN)
            {
                setlinecolor(WHITE);
                line(322 + 25 * i, 360, 322 + 25 * i, 390);

                number[i] = '\0';

                if (!strlen(number))
                {
                    showMessage(L"请输入金额");
                    continue;
                }

                return atoi(number);
            }
        }
        else if (m.x >= 20 && m.x <= 120 && m.y >= 690 && m.y <= 735)
        {
            selectBack(true);
            if (m.message == WM_LBUTTONDOWN)
                return false;
        }
        else
        {
            if (m.message == WM_LBUTTONDOWN)
            {
                setlinecolor(WHITE);
                line(322 + 25 * i, 360, 322 + 25 * i, 390);
            }
            setMouse(0);
            selectBox(452, 590, 572, 660, false);
            selectBack(false);
        }
    }
}

int chooseYear()
{
    cleardevice();
    IMAGE bk;
    loadimage(&bk, _T("img\\bk.jpg"));
    putimage(0, 0, &bk);

    settextstyle(120, 0, L"楷体");
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);
    outtextxy(270, 50, L"选择年份");

    wchar_t years[50][15];
    char temp[10];
    for (int i = 0; i < 50; i++)
    {
        _itoa_s(i + 2000, temp, 10);
        wchar_t* wtemp = char2wchar(temp);
        wcscpy_s(years[i], wtemp);
        delete[] wtemp;
        wcscat_s(years[i], L" 年");
    }

    LPCTSTR temp_years[50];
    for (int i = 0; i < 50; i++)
        temp_years[i] = years[i];

    return selectForm(362, 200, 662, temp_years, 50, false) + 2000;
}

int chooseMonth()
{
    cleardevice();
    IMAGE bk;
    loadimage(&bk, _T("img\\bk.jpg"));
    putimage(0, 0, &bk);

    settextstyle(120, 0, L"楷体");
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);
    outtextxy(270, 50, L"选择月份");

    wchar_t months[12][15];
    char temp[10];
    for (int i = 0; i < 12; i++)
    {
        _itoa_s(i + 1, temp, 10);
        wchar_t* wtemp = char2wchar(temp);
        wcscpy_s(months[i], wtemp);
        delete[] wtemp;
        wcscat_s(months[i], L" 月");
    }

    LPCTSTR temp_mouths[12];
    for (int i = 0; i < 12; i++)
        temp_mouths[i] = months[i];

    return selectForm(362, 200, 662, temp_mouths, 12, false) + 1;
}

int chooseDate(int year, int month)
{
    cleardevice();
    IMAGE bk;
    loadimage(&bk, _T("img\\bk.jpg"));
    putimage(0, 0, &bk);

    settextstyle(120, 0, L"楷体");
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);
    outtextxy(270, 50, L"选择日期");

    wchar_t dates[31][15];
    char temp[10];
    for (int i = 0; i < 31; i++)
    {
        _itoa_s(i + 1, temp, 10);
        wchar_t* wtemp = char2wchar(temp);
        wcscpy_s(dates[i], wtemp);
        delete[] wtemp;
        wcscat_s(dates[i], L" 日");
    }

    LPCTSTR temp_dates[31];
    for (int i = 0; i < 31; i++)
        temp_dates[i] = dates[i];

    switch (month)
    {
    case 2:
        return selectForm(362, 200, 662, temp_dates, 
            ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 29 : 28, false) + 1;
    case 4:
    case 6:
    case 9:
    case 11:
        return selectForm(362, 200, 662, temp_dates, 30, false) + 1;
    default:
        return selectForm(362, 200, 662, temp_dates, 31, false) + 1;
    }
}

bool setPasswd(char passwd[])
{
    cleardevice();
    ExMessage m;
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
    outtextxy(270, 50, L"设置密码");

    settextstyle(25, 0, L"楷体");
    outtextxy(480, 612, L"登 录");

    settextstyle(50, 0, L"楷体");
    outtextxy(192, 275, L" 密  码 ");
    outtextxy(192, 450, L"确认密码");

    bool get = false;
    int i = 0;
    int j = 0;
    const int maxi = 14;
    const int maxj = 14;
    char passwd1[maxi + 1];
    char passwd2[maxj + 1];
    while (true)
    {
        if (!get)
            getmessage(&m);
        else
            get = false;
        if (m.x >= 392 && m.x <= 792 && m.y >= 275 && m.y <= 325)
        {
            setMouse(1);
            if (m.message == WM_LBUTTONDOWN)
            {
                setlinecolor(BLACK);
                line(402 + 25 * i, 285, 402 + 25 * i, 315);
                setlinecolor(WHITE);
                line(402 + 25 * j, 460, 402 + 25 * j, 490);

                while (_kbhit())
                    _getch();

                while (true)
                {
                    if (peekmessage(&m, -1, false))
                    {
                        m = getmessage();
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
                            if (m.message == WM_LBUTTONDOWN)
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
                            m.message = WM_LBUTTONDOWN;
                            break;
                        }
                        if (!isalnum(ch) || i == maxi)
                            continue;
                        settextstyle(50, 0, L"楷体");
                        outtextxy(402 + 25 * i, 275, '*');
                        passwd1[i++] = ch;

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
            if (m.message == WM_LBUTTONDOWN)
            {
                setlinecolor(BLACK);
                line(402 + 25 * j, 460, 402 + 25 * j, 490);
                setlinecolor(WHITE);
                line(402 + 25 * i, 285, 402 + 25 * i, 315);

                while (_kbhit())
                    _getch();

                while (true)
                {
                    if (peekmessage(&m, -1, false))
                    {
                        m = getmessage();
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
                            if (m.message == WM_LBUTTONDOWN)
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
                            m.message = WM_LBUTTONDOWN;
                            break;
                        }
                        if (!isalnum(ch) || j == maxj)
                            continue;
                        settextstyle(50, 0, L"楷体");
                        outtextxy(402 + 25 * j, 450, '*');
                        passwd2[j++] = ch;

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
            if (m.message == WM_LBUTTONDOWN)
            {
                setlinecolor(WHITE);
                line(402 + 25 * i, 285, 402 + 25 * i, 315);
                line(402 + 25 * j, 460, 402 + 25 * j, 490);

                passwd1[i] = '\0';
                passwd2[j] = '\0';

                if (strcmp(passwd1, passwd2))
                    showMessage(L"两次密码不一致");
                else if (!strlen(passwd1))
                {
                    showMessage(L"请输入密码");
                    continue;
                }
                else
                {
                    strcpy_s(passwd, 15, passwd1);
                    return true;
                }
            }
        }
        else if (m.x >= 20 && m.x <= 120 && m.y >= 690 && m.y <= 735)
        {
            selectBack(true);
            if (m.message == WM_LBUTTONDOWN)
                return false;
        }
        else
        {
            if (m.message == WM_LBUTTONDOWN)
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

bool adminLogin()
{
    cleardevice();
    ExMessage m;
    IMAGE bk;
    loadimage(&bk, _T("img\\bk.jpg"));
    putimage(0, 0, &bk);

    setfillcolor(WHITE);
    setlinecolor(BLACK);
    fillrectangle(312, 350, 712, 400);

    setlinecolor(WHITE);
    setfillcolor(LIGHTBLUE);
    fillrectangle(462, 600, 562, 650);
    selectBox(452, 590, 572, 660, false);
    selectBack(false);

    settextstyle(25, 0, L"楷体");
    outtextxy(480, 612, L"登 录");

    settextstyle(50, 0, L"楷体");
    outtextxy(382, 150, L"管理员密码");

    bool get = false;
    int i = 0;
    const int maxi = 9;
    char passwd[maxi + 1];
    while (true)
    {
        if (!get)
            m = getmessage();
        else
            get = false;
        if (m.x >= 312 && m.x <= 712 && m.y >= 350 && m.y <= 400)
        {
            setMouse(1);
            if (m.message == WM_LBUTTONDOWN)
            {
                setlinecolor(BLACK);
                line(322 + 25 * i, 360, 322 + 25 * i, 390);
                setlinecolor(WHITE);

                while (_kbhit())
                    _getch();

                while (true)
                {
                    if (peekmessage(&m, -1, false))
                    {
                        m = getmessage();
                        if (m.x < 312 || m.x > 712 || m.y < 350 || m.y > 400)
                        {
                            setMouse(0);
                            selectBox(452, 590, 572, 660, false);
                            selectBack(false);
                            if (m.x >= 462 && m.x <= 562 && m.y >= 600 && m.y <= 650)
                                selectBox(452, 590, 572, 660, true);
                            if (m.x >= 20 && m.x <= 120 && m.y >= 690 && m.y <= 735)
                                selectBack(true);
                            if (m.message == WM_LBUTTONDOWN)
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
                            fillrectangle(322 + 25 * i, 351, 322 + 25 * (i + 1), 399);
                            setlinecolor(BLACK);
                            line(322 + 25 * i, 360, 322 + 25 * i, 390);
                            setlinecolor(WHITE);
                            setfillcolor(LIGHTBLUE);
                            continue;
                        }
                        if (ch == 13)
                        {
                            get = true;
                            m.x = 462;
                            m.y = 600;
                            m.message = WM_LBUTTONDOWN;
                            break;
                        }
                        if (!isalnum(ch) || i == maxi)
                            continue;
                        settextstyle(50, 0, L"楷体");
                        outtextxy(322 + 25 * i, 350, '*');
                        passwd[i++] = ch;

                        setlinecolor(BLACK);
                        line(322 + 25 * i, 360, 322 + 25 * i, 390);
                        setlinecolor(WHITE);
                        line(322 + 25 * (i - 1), 360, 322 + 25 * (i - 1), 390);
                    }
                }
            }
        }
        else if (m.x >= 462 && m.x <= 562 && m.y >= 600 && m.y <= 650)
        {
            selectBox(452, 590, 572, 660, true);
            if (m.message == WM_LBUTTONDOWN)
            {
                setlinecolor(WHITE);
                line(322 + 25 * i, 360, 322 + 25 * i, 390);

                passwd[i] = '\0';

                if (!strlen(passwd))
                {
                    showMessage(L"请输入密码");
                    continue;
                }

                if (strcmp(passwd, ROOT_PASSWD) == 0)
                    return true;
                else
                    showMessage(L"密码错误");
            }
        }
        else if (m.x >= 20 && m.x <= 120 && m.y >= 690 && m.y <= 735)
        {
            selectBack(true);
            if (m.message == WM_LBUTTONDOWN)
                return false;
        }
        else
        {
            if (m.message == WM_LBUTTONDOWN)
            {
                setlinecolor(WHITE);
                line(322 + 25 * i, 360, 322 + 25 * i, 390);
            }
            setMouse(0);
            selectBox(452, 590, 572, 660, false);
            selectBack(false);
        }
    }
}

void setMouse(int mouse)
{
    HCURSOR hcur;
    switch (mouse)
    {
    case 0:
        hcur = LoadCursor(NULL, IDC_ARROW);
        break;
    case 1:
        hcur = LoadCursor(NULL, IDC_IBEAM);
        break;
    case 2:
        hcur = LoadCursor(NULL, IDC_HAND);
        break;
    default:
        hcur = LoadCursor(NULL, IDC_ARROW);
        break;
    }
    HWND hwnd = GetHWnd();
    SetClassLong(hwnd, GCL_HCURSOR, (long)hcur);
}

void selectBox(int left, int top, int right, int bottom, bool select)
{
    COLORREF temp = getlinecolor();
    if (select)
    {
        setlinecolor(LIGHTGREEN);
        setMouse(2);
    }
    else
    {
        setlinecolor(0xfbe6b3);
        setMouse(0);
    }

    setlinestyle(PS_SOLID, 10);
    rectangle(left, top, right, bottom);

    setlinestyle(PS_SOLID, 1);
    setlinecolor(temp);
}

void selectText(int left, int top, int right, int bottom, int color, LPCTSTR str)
{
    COLORREF temp1 = getfillcolor();
    COLORREF temp2 = getlinecolor();

    switch (color)
    {
    case 0:
        setMouse(0);
        setfillcolor(LIGHTGRAY);
        break;
    case 1:
        setMouse(2);
        setfillcolor(LIGHTBLUE);
        break;
    case 2:
        setMouse(0);
        setfillcolor(BLUE);
        break;
    case 3:
        setMouse(2);
        setfillcolor(LIGHTRED);
        break;
    case 4:
        setMouse(0);
        setfillcolor(RED);
        break;
    default:
        break;
    }

    setlinecolor(WHITE);
    fillrectangle(left, top, right, bottom);
    settextstyle(44, 0, L"楷体");
    settextcolor(WHITE);
    setbkmode(TRANSPARENT);
    outtextxy(left + 3, top + 3, str);

    settextcolor(BLACK);
    settextstyle(50, 0, L"楷体");
    setfillcolor(temp1);
    setlinecolor(temp2);
}

int selectForm(int left, int top, int right, LPCTSTR strs[], int layers, bool read)
{
    LPCTSTR* begin = strs;
    while (true)
    {
        selectBack(false);
        for (int j = 0; j < min(layers, 10); j++)
            selectText(left, top + 50 * j, right, top + 50 * (j + 1), 0, begin[j]);
        selectText(left - 50, top, left, top + 50, 0, L"👈");
        selectText(right, top, right + 50, top + 50, 0, L"👉");
        while (true)
        {
            ExMessage m = getmessage();
            for (int i = 0; i < min(layers, 10); i++)
            {
                if (m.x >= left && m.x <= right
                    && m.y >= top + 50 * i && m.y <= top + 50 * (i + 1))
                {
                    selectText(left - 50, top, left, top + 50, 0, L"👈");
                    selectText(right, top, right + 50, top + 50, 0, L"👉");
                    selectBack(false);
                    for (int j = 0; j < min(layers, 10); j++)
                        if (j != i)
                            selectText(left, top + 50 * j, right, top + 50 * (j + 1), 0, begin[j]);
                    selectText(left, top + 50 * i, right, top + 50 * (i + 1), read ? 0 : 1, begin[i]);
                    if (m.message == WM_LBUTTONDOWN)
                        return i + begin - strs;
                }
            }
            if (m.x < left || m.x > right || m.y < top || m.y > top + 50 * (min(layers, 10)))
                for (int j = 0; j < min(layers, 10); j++)
                    selectText(left, top + 50 * j, right, top + 50 * (j + 1), 0, begin[j]);
            if (m.x >= 20 && m.x <= 120 && m.y >= 690 && m.y <= 735)
            {
                selectBack(true);
                if (m.message == WM_LBUTTONDOWN)
                    return -1;
            }
            else if (m.x >= left - 50 && m.x <= left && m.y >= top && m.y <= top + 50)
            {
                selectText(left - 50, top, left, top + 50, 1, L"👈");
                if (m.message == WM_LBUTTONDOWN && begin > strs)
                {
                    begin = max(begin - 10, strs);
                    break;
                }
            }
            else if (m.x >= right && m.x <= right + 50 && m.y >= top && m.y <= top + 50)
            {
                selectText(right, top, right + 50, top + 50, 1, L"👉");
                if (m.message == WM_LBUTTONDOWN && begin + 10 < strs + layers)
                {
                    begin = min(begin + 10, strs + layers - 10);
                    break;
                }
            }
            else if (m.x < left || m.x > right || m.y < top || m.y > top + 50 * (min(layers, 10)))
            {
                selectText(left - 50, top, left, top + 50, 0, L"👈");
                selectText(right, top, right + 50, top + 50, 0, L"👉");
                selectBack(false);
            }
        }
    }
}

int select4Form(int left, int top, int right, LPCTSTR strs[], bool read)
{
    LPCTSTR* begin = strs;
    while (true)
    {
        selectBack(false);
        for (int j = 0; j < 4; j++)
            selectText(left, top + 50 * j, right, top + 50 * (j + 1), 0, begin[j]);
        while (true)
        {
            ExMessage m = getmessage();
            for (int i = 0; i < 4; i++)
            {
                if (m.x >= left && m.x <= right
                    && m.y >= top + 50 * i && m.y <= top + 50 * (i + 1))
                {
                    selectBack(false);
                    for (int j = 0; j < 4; j++)
                        if (j != i)
                            selectText(left, top + 50 * j, right, top + 50 * (j + 1), 0, begin[j]);
                    selectText(left, top + 50 * i, right, top + 50 * (i + 1), read ? 0 : 1, begin[i]);
                    if (m.message == WM_LBUTTONDOWN)
                        return i;
                }
            }
            if (m.x < left || m.x > right || m.y < top || m.y > top + 200)
                for (int j = 0; j < 4; j++)
                    selectText(left, top + 50 * j, right, top + 50 * (j + 1), 0, begin[j]);
            if (m.x >= 20 && m.x <= 120 && m.y >= 690 && m.y <= 735)
            {
                selectBack(true);
                if (m.message == WM_LBUTTONDOWN)
                    return -1;
            }
            else if (m.x < left || m.x > right || m.y < top || m.y > top + 200)
                selectBack(false);
        }
    }
}

void selectBack(bool select)
{
    COLORREF temp1 = getfillcolor();
    COLORREF temp2 = getlinecolor();

    if (select)
    {
        setfillcolor(LIGHTGREEN);
        setMouse(2);
    }
    else
    {
        setfillcolor(LIGHTGRAY);
        setMouse(0);
    }

    setlinecolor(WHITE);
    fillrectangle(20, 690, 120, 735);
    settextstyle(25, 0, L"楷体");
    settextcolor(BLACK);
    setbkmode(TRANSPARENT);
    outtextxy(37, 700, L"返 回");

    setfillcolor(temp1);
    setlinecolor(temp2);
}

void selectExit(bool select)
{
    COLORREF temp1 = getfillcolor();
    COLORREF temp2 = getlinecolor();

    if (select)
    {
        setfillcolor(LIGHTGREEN);
        setMouse(2);
    }
    else
    {
        setfillcolor(LIGHTGRAY);
        setMouse(0);
    }

    setlinecolor(WHITE);
    fillrectangle(20, 690, 120, 735);
    settextstyle(25, 0, L"楷体");
    settextcolor(BLACK);
    setbkmode(TRANSPARENT);
    outtextxy(37, 700, L"退 出");

    setfillcolor(temp1);
    setlinecolor(temp2);
}

void showMessage(LPCTSTR str)
{
    HWND hwnd = GetHWnd();
    MessageBox(hwnd, str, L"提示", MB_OK);
}

wchar_t* char2wchar(const char* cchar)
{
    wchar_t* m_wchar;
    int len = MultiByteToWideChar(CP_ACP, 0, cchar, strlen(cchar), NULL, 0);
    m_wchar = new wchar_t[len + 1];
    MultiByteToWideChar(CP_ACP, 0, cchar, strlen(cchar), m_wchar, len);
    m_wchar[len] = '\0';
    return m_wchar;
}

char* wchar2char(const wchar_t* wchar)
{
    char* m_char;
    int len = WideCharToMultiByte(CP_ACP, 0, wchar, wcslen(wchar), NULL, 0, NULL, NULL);
    m_char = new char[len + 1];
    WideCharToMultiByte(CP_ACP, 0, wchar, wcslen(wchar), m_char, len, NULL, NULL);
    m_char[len] = '\0';
    return m_char;
}
