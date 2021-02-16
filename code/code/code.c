#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <alloc.h>
#include <string.h>

const char FileName[] = "inf.dat"; // ��� �����

// ��������� �������� ����������� ������
struct Inf
{
    char title[30]; // �������� �����
    char name[20]; // ������� ������
    int year; // ��� �������
    Inf* prev; // ��������� �� ���������� �������
    Inf* next; // ��������� �� ��������� �������
};

Inf* head = NULL; // ��������� �� ������ ������� ������
Inf* tail = NULL; // ��������� �� ��������� ������� ������

// ������� ���� �� �����
void Menu()
{
    puts("1 - �������� ������");
    puts("2 - �������� ������");
    puts("3 - ���������� � ������ ����� ������");
    puts("4 - ����� � ������������� ������ � ������");
    puts("5 - �������� ������ �� ������");
    puts("6 - ���������� ������ � �����");
    puts("7 - �������� ������ �� �����");
    puts("8 - �����\n");
}

// ������� ������
void Clear()
{
    Inf* p = head;
    while (p != NULL) {
        Inf* q = p;
        p = p->next;
        free(q); // ������� ������� ������ �� ������������ ������
    }
    head = NULL;
    tail = NULL;
}

// ������� ������ �� �����
void Print()
{
    Inf* p = head;
    while (p != NULL) { // ���� �� ���� ��������� ������
        printf("%30s ", p->title);
        printf("%20s ", p->name);
        printf("%10d\n", p->year);
        p = p->next;
    }
}

// ��������� ����� ������ ����� ���������
void Add()
{
    Inf* p = (Inf*)malloc(sizeof(Inf)); // �������� ������������ ������
    printf("�������� �����: "); // ������ ��� ���� �������� ������
    scanf("%s", p->title);
    printf("������� ������: ");
    scanf("%s", p->name);
    printf("��� �������: ");
    scanf("%d", &p->year);
    p->prev = NULL;
    p->next = NULL;
    if (head == NULL) // ���� ������ ������
        head = tail = p;
    else if (head->next == NULL) { // ���� ���� ������ � ������
        p->next = head;
        head->prev = p;
        head = p;
    }
    else {
        p->prev = tail->prev;
        p->next = tail;
        p->prev->next = p;
        tail->prev = p;
    }
}

// �������� ��� ������� �� �������� �����
void Change()
{
    char title[30];
    printf("��������: "); // ������ �������� �����
    scanf("%s", title);
    Inf* p = head;
    int found = 0;
    while (p != NULL) { // ���� �� ���� ��������� ������
        if (!strcmp(p->title, title)) {
            printf("��� �������: ");
            scanf("%d", &p->year);
            found = 1;
            break;
        }
        p = p->next;
    }
    if (found == 0)
        puts("����� �� �������");
    else
        puts("��� ������� �������");
}

// ������� �� ������ ����� ��������� ������
void Delete()
{
    char name[20];
    printf("������� ������� ������: ");
    scanf("%s", name);
    Inf* p = head;
    int found = 0;
    while (p != NULL) {
        if (!strcmp(p->name, name)) {
            // ���� ��������� ������� �������� ������������ ������ � ���������
            if (p->prev == NULL && p->next == NULL) {
                free(p); // ������� ������� ������ �� ������������ ������
                head = NULL;
                tail = NULL;
                break;
            }
            // ���� ������� ������ �������
            else if (p->prev == NULL) {
                Inf* q = p;
                p = p->next;
                free(q); // ������� ������� ������ �� ������������ ������
                p->prev = NULL;
                head = p;
            }
            // ���� ������� ��������� �������
            else if (p->next == NULL) {
                Inf* q = p;
                p = p->prev;
                free(q); // ������� ������� ������ �� ������������ ������
                p->next = NULL;
                tail = p;
                break;
            }
            // ���� ������� ������� �� �������� ������
            else {
                p->prev->next = p->next;
                p->next->prev = p->prev;
                Inf* q = p;
                p = p->next;
                free(q); // ������� ������� ������ �� ������������ ������
            }
            found = 1;
        }
        else
            p = p->next;
    }
    if (found == 0)
        puts("������� �� �������");
    else
        puts("������� �������");
}

// ��������� ������ � �����
void Save()
{
    FILE* f; // ����
    f = fopen(FileName, "w"); // ��������� ���� ��� ������
    Inf* p = head;
    while (p != NULL) { // ���� �� ���� ��������� ������
        fprintf(f, "%s %s %d\n", p->title, p->name, p->year);
        p = p->next;
    }
    fclose(f);
    printf("������ �������� � ����� %s\n", FileName);
}

// ��������� ������ �� �����
void Load()
{
    Clear();
    FILE* f; // ����
    f = fopen(FileName, "r"); // ��������� ���� ��� ������
    while (!feof(f)) {
        Inf* p = (Inf*)malloc(sizeof(Inf)); // �������� ������������ ������
        fscanf(f, "%s", p->title); // ������ ��� ���� �������� ������
        if (feof(f))
            break;
        fscanf(f, "%s", p->name);
        fscanf(f, "%d", &p->year);
        p->prev = NULL;
        p->next = NULL;
        if (head == NULL) // ���� ������ ������
            head = tail = p;
        else {
            tail->next = p;
            p->prev = tail;
            tail = p;
        }
    }
    fclose(f);
    printf("������ �������� �� ����� %s\n", FileName);
}

void main()
{
    clrscr(); // ������� �����
    Menu();
    char c;
    while (1) {
        c = getch();
        switch (c) {
        case '1': // �������� ������
            Clear();
            puts("������ ������");
            break;
        case '2': // �������� ������
            puts("������:");
            Print();
            break;
        case '3': // ���������� � ������ ����� ������
            Add();
            break;
        case '4': // ����� � ������������� ������ � ������
            Change();
            break;
        case '5': // �������� ������ �� ������
            Delete();
            break;
        case '6': // ���������� ������ � �����
            Save();
            break;
        case '7': // �������� ������ �� �����
            Load();
            break;
        case '8': // �����
            return;
        }
    }
}
