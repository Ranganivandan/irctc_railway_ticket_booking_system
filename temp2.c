// STUDENT RECORD MANAGEMENT SYSTEM
// LIBRARY
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
// FUNCTION
void gotoxy(int, int);
void menu();
void add();
void view();
void search();
void modify();
void deleterec();
// MAKE STUDENT STRUCT
struct student
{
    char Idno[10];
    char name[15];
    char mobile[12];
    char Email[23];
    char Divclass[5];
    char quota[6];
};
// MAIN
int main()
{
    system("cls");
    gotoxy(15, 8);
    printf("::::Student Record Management System::::");
    gotoxy(19, 15);
    printf("Press any key to continue.");
    getch();
    menu();
    return 0;
}
// MENU BAR
void menu()
{
    int choice;
    system("cls");
    gotoxy(10, 3);
    printf("::::MENU::::");
    gotoxy(10, 5);
    printf("Enter appropriate number to perform following task.");
    gotoxy(10, 7);
    printf("1 : Add Record.");
    gotoxy(10, 8);
    printf("2 : View Record.");
    gotoxy(10, 9);
    printf("3 : Search Record.");
    gotoxy(10, 10);
    printf("4 : Modify Record.");
    gotoxy(10, 11);
    printf("5 : Delete.");
    gotoxy(10, 12);
    printf("6 : Exit.");
    gotoxy(10, 15);
    printf("Enter your choice.");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        add();
        break;

    case 2:
        view();
        break;
    case 3:
        search();
        break;
    case 4:
        modify();
        break;
    case 5:
        deleterec();
        break;
    default:
        gotoxy(10, 17);
        printf("Invalid Choice.");
    }
}
// ADD DATA
void add()
{
    FILE *fp;
    struct student std;
    char another = 'y';
    system("cls");

    fp = fopen("record.txt", "ab+");
    if (fp == NULL)
    {
        gotoxy(10, 5);
        printf("Not data available-Error opening file");
        exit(1);
    }
    fflush(stdin);
    while (another == 'y')
    {
        gotoxy(10, 3);
        printf("::::ADD RECORD::::");
        gotoxy(10, 5);
        printf("Enter details of student.");
        gotoxy(10, 7);
        printf("Enter ID No : ");
        fflush(stdin);
        gets(std.Idno);
        gotoxy(10, 8);
        printf("Enter Name : ");
        fflush(stdin);
        gets(std.name);
        gotoxy(10, 9);
        printf("Enter Mobile no : ");
        fflush(stdin);
        gets(std.mobile);
        gotoxy(10, 10);
        printf("Enter Email ID : ");
        fflush(stdin);
        gets(std.Email);
        gotoxy(10, 11);
        printf("Enter Div&class : ");
        fflush(stdin);
        gets(std.Divclass);
        gotoxy(10, 12);
        printf("Enter Your Quota :");
        fflush(stdin);
        gets(std.quota);
        fwrite(&std, sizeof(std), 1, fp);
        gotoxy(10, 15);
        printf("Want to add of another record? Then press 'y' else 'n'.");
        fflush(stdin);
        another = getch();
        system("cls");
        fflush(stdin);
    }
    fclose(fp);
    gotoxy(10, 18);
    printf("Press any key to continue.");
    getch();
    menu();
}
// VIEW DATA
void view()
{
    FILE *fp;
    int j;
    struct student std;
    system("cls");
    gotoxy(10, 3);
    printf("::::VIEW RECORD::::");
    gotoxy(10, 5);
    printf("ID.No    Name                Mobile No         Email ID                 Div&Class   Quota");
    gotoxy(10, 6);
    printf("------------------------------------------------------------------------------------------");
    fp = fopen("record.txt", "rb+");
    if (fp == NULL)
    {
        gotoxy(10, 8);
        printf("Error opening file.");
        exit(1);
    }
    j = 8;
    while (fread(&std, sizeof(std), 1, fp) == 1)
    {
        gotoxy(10, j);
        printf("%-9s%-20s%-18s%-25s%-12s%-5s", std.Idno, std.name, std.mobile, std.Email, std.Divclass, std.quota);
        j++;
    }
    fclose(fp);
    gotoxy(10, j + 3);
    printf("Press any key to continue.");
    getch();
    menu();
}
// SEARCH DATA
void search()
{
    FILE *fp;
    struct student std;
    char stname[20];
    char stidno[7];
    int serchchoice = 1;
    system("cls");
    gotoxy(10, 3);
    printf("::::SEARCH RECORD::::");
    gotoxy(10, 5);
    printf("Enter name of student or Id no(Name : 0 and Id no :1 ) : ");
    fflush(stdin);
    scanf("%d", &serchchoice);
    fp = fopen("record.txt", "rb+");
    if (fp == NULL)
    {
        gotoxy(10, 6);
        printf("Error opening file");
        exit(1);
    }
    if (serchchoice == 0)
    {
        gotoxy(10, 6);
        printf("Enter name of student : ");
        fflush(stdin);
        gets(stname);
        while (fread(&std, sizeof(std), 1, fp) == 1)
        {
            if (strcmp(stname, std.name) == 0)
            {
                gotoxy(10, 8);
                printf("ID No : %s", std.Idno);
                gotoxy(10, 9);
                printf("Name : %s", std.name);
                gotoxy(10, 10);
                printf("Mobile No: %s", std.mobile);
                gotoxy(10, 11);
                printf("Email Id : %s", std.Email);
                gotoxy(10, 12);
                printf("Div&Class : %s", std.Divclass);
                gotoxy(10, 13);
                printf("Quota : %s", std.quota);
            }
        }
    }
    else
    {
        gotoxy(10, 6);
        printf("Enter Id No : ");
        fflush(stdin);
        gets(stidno);
        while (fread(&std, sizeof(std), 1, fp) == 1)
        {
            if (strcmp(stidno, std.Idno) == 0)
            {
                gotoxy(10, 8);
                printf("ID No : %s", std.Idno);
                gotoxy(10, 9);
                printf("Name : %s", std.name);
                gotoxy(10, 10);
                printf("Mobile No: %s", std.mobile);
                gotoxy(10, 11);
                printf("Email Id : %s", std.Email);
                gotoxy(10, 12);
                printf("Div&Class : %s", std.Divclass);
                gotoxy(10, 13);
                printf("Quota : %s", std.quota);
            }
        }
    }
    fclose(fp);
    gotoxy(10, 16);
    printf("Press any key to continue.");
    getch();
    menu();
}
// MODIFY DATA
void modify()
{
    char stname[20];
    char stidno[7];
    int modifychoice = 1;
    FILE *fp;
    struct student std;
    system("cls");
    gotoxy(10, 3);
    printf("::::MODIFY RECORD::::");
    gotoxy(10, 5);
    printf("Enter name of student or Id No to modify(Name=0  or  Id no=1): ");
    fflush(stdin);
    scanf("%d", &modifychoice);
    fp = fopen("record.txt", "rb+");
    if (fp == NULL)
    {
        gotoxy(10, 6);
        printf("Error opening file");
        exit(1);
    }
    rewind(fp);
    fflush(stdin);
    if (modifychoice == 0)
    {
        gotoxy(10, 7);
        printf("Enter name of student : ");
        fflush(stdin);
        gets(stname);
        while (fread(&std, sizeof(std), 1, fp) == 1)
        {
            if (strcmp(stname, std.name) == 0)
            {
                fflush(stdin);
                gotoxy(10, 8);
                printf("Enter ID no: ");
                gets(std.Idno);
                fflush(stdin);
                gotoxy(10, 9);
                printf("Enter Name : ");
                gets(std.name);
                fflush(stdin);
                gotoxy(10, 10);
                printf("Enter Mobile No : ");
                gets(std.mobile);
                fflush(stdin);
                gotoxy(10, 11);
                printf("Enter Email Id : ");
                fflush(stdin);
                gets(std.Email);
                gotoxy(10, 12);
                fflush(stdin);
                printf("Enter Divandclass(ex:A03->A=div,03=class) : ");
                gets(std.Divclass);
                gotoxy(10, 13);
                fflush(stdin);
                printf("Enter your Quota(government::GIA,selfinance::SELF) : ");
                gets(std.quota);
                fflush(stdin);
                fseek(fp, -sizeof(std), SEEK_CUR);
                fwrite(&std, sizeof(std), 1, fp);
                break;
            }
        }
    }
    else
    {
        gotoxy(10, 7);
        printf("Enter ID No : ");
        fflush(stdin);
        gets(stidno);
        while (fread(&std, sizeof(std), 1, fp) == 1)
        {
            if (strcmp(stidno, std.Idno) == 0)
            {
                fflush(stdin);
                gotoxy(10, 8);
                printf("Enter ID no: ");
                gets(std.Idno);
                gotoxy(10, 9);
                printf("Enter Name : ");
                gets(std.name);
                gotoxy(10, 10);
                printf("Enter Mobile No : ");
                gets(std.mobile);
                gotoxy(10, 11);
                printf("Enter Email Id : ");
                fflush(stdin);
                gets(std.Email);
                gotoxy(10, 12);
                printf("Enter Divandclass(ex:A03->A=div,03=class) : ");
                fflush(stdin);
                gets(std.Divclass);
                gotoxy(10, 13);
                printf("Enter your Quota(government::GIA,selfinance::SELF) : ");
                gets(std.quota);
                fseek(fp, -sizeof(std), SEEK_CUR);
                fwrite(&std, sizeof(std), 1, fp);
                break;
            }
        }
    }

    fclose(fp);
    gotoxy(10, 16);
    printf("Press any key to continue.");
    getch();
    menu();
}
// DELETE RECORD
void deleterec()
{
    char stname[20];
    FILE *fp, *ft;
    struct student std;
    system("cls");
    gotoxy(10, 3);
    printf("::::DELETE RECORD::::");
    gotoxy(10, 5);
    printf("Enter name of student to delete record : ");
    fflush(stdin);
    gets(stname);
    fp = fopen("record.txt", "rb+");
    if (fp == NULL)
    {
        gotoxy(10, 6);
        printf("Error opening file");
        exit(1);
    }
    ft = fopen("temp.txt", "wb+");
    if (ft == NULL)
    {
        gotoxy(10, 6);
        printf("Error opening file");
        exit(1);
    }
    while (fread(&std, sizeof(std), 1, fp) == 1)
    {
        if (strcmp(stname, std.name) != 0)
            fwrite(&std, sizeof(std), 1, ft);
    }
    fclose(fp);
    fclose(ft);
    remove("record.txt");
    rename("temp.txt", "record.txt");
    gotoxy(10, 10);
    printf("Press any key to continue.");
    getch();
    menu();
}
// GOTOXY
void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
// THANKS//