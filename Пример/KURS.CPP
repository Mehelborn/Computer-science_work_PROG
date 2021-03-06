#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <alloc.h>
#include <string.h>

const char FileName[] = "inf.dat"; // ��� 䠩��

// ������� ������� ����吝��� ᯨ᪠
struct Inf
{
   char title[30]; // �������� �����
   char name[20]; // ������� ����
   int year; // ��� �������
   Inf *prev; // �����⥫� �� �।��騩 �������
   Inf *next; // �����⥫� �� ᫥���騩 �������
};

Inf *head = NULL; // �����⥫� �� ���� ������� ᯨ᪠
Inf *tail = NULL; // �����⥫� �� ��᫥���� ������� ᯨ᪠

// �뢮��� ���� �� ��࠭
void Menu()
{
  puts("1 - �������� ᯨ᪠");
  puts("2 - ��ᬮ�� ᯨ᪠");
  puts("3 - ���������� � ᯨ᮪ ����� �����");
  puts("4 - ���� � ���४�஢�� ����� � ᯨ᪥");
  puts("5 - �������� ����� �� ᯨ᪠");
  puts("6 - ���࠭���� ᯨ᪠ � 䠩��");
  puts("7 - ����㧪� ᯨ᪠ �� 䠩��");
  puts("8 - ��室\n");
}

// ��頥� ᯨ᮪
void Clear()
{
  Inf *p = head;
  while (p != NULL) {
    Inf *q = p;
    p = p->next;
    free(q); // ����塞 ������� ᯨ᪠ �� �������᪮� �����
  }
  head = NULL;
  tail = NULL;
}

// �뢮��� ᯨ᮪ �� ��࠭
void Print()
{
  Inf *p = head;
  while (p != NULL) { // ���� �� �ᥬ ������⠬ ᯨ᪠
    printf("%30s ", p->title);
    printf("%20s ", p->name);
    printf("%10d\n", p->year);
    p = p->next;
  }
}

// �������� ����� ������ ��। ��᫥����
void Add()
{
  Inf *p = (Inf *) malloc(sizeof(Inf)); // �뤥�塞 ���������� ������
  printf("�������� �����: "); // ������ �� ���� ������� ᯨ᪠
  scanf("%s", p->title);
  printf("������� ����: ");
  scanf("%s", p->name);
  printf("��� �������: ");
  scanf("%d", &p->year);
  p->prev = NULL;
  p->next = NULL;
  if (head == NULL) // �᫨ ᯨ᮪ ���⮩
    head = tail = p;
  else if (head->next == NULL) { // �᫨ ���� ������ � ᯨ᪥
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

// ������� ��� ������� �� �������� �����
void Change()
{
  char title[30];
  printf("��������: "); // ������ �������� �����
  scanf("%s", title);
  Inf *p = head;
  int found = 0;
  while (p != NULL) { // ���� �� �ᥬ ������⠬ ᯨ᪠
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

// ������ �� ᯨ᪠ ����� ��������� ����
void Delete()
{
  char name[20];
  printf("������ 䠬���� ����: ");
  scanf("%s", name);
  Inf *p = head;
  int found = 0;
  while (p != NULL) {
    if (!strcmp(p->name, name)) {
      // �᫨ 㤠�塞� ������� ���� �����६���� ���� � ��᫥����
      if (p->prev == NULL && p->next == NULL) {
        free(p); // ����塞 ������� ᯨ᪠ �� �������᪮� �����
        head = NULL;
        tail = NULL;
        break;
      }
      // �᫨ 㤠�塞 ���� �������
      else if (p->prev == NULL) {
        Inf *q = p;
        p = p->next;
        free(q); // ����塞 ������� ᯨ᪠ �� �������᪮� �����
        p->prev = NULL;
        head = p;
      }
      // �᫨ 㤠�塞 ��᫥���� �������
      else if (p->next == NULL) {
        Inf *q = p;
        p = p->prev;
        free(q); // ����塞 ������� ᯨ᪠ �� �������᪮� �����
        p->next = NULL;
	tail = p;
        break;
      }
      // �᫨ 㤠�塞 ������� �� �।��� ᯨ᪠
      else {
        p->prev->next = p->next;
        p->next->prev = p->prev;
        Inf *q = p;
        p = p->next;
        free(q); // ����塞 ������� ᯨ᪠ �� �������᪮� �����
      }
      found = 1;
    }
    else
      p = p->next;
  }
  if (found == 0)
    puts("������� �� �������");
  else
    puts("������� 㤠����");
}

// ���࠭�� ᯨ᮪ � 䠩��
void Save()
{
  FILE *f; // 䠩�
  f = fopen(FileName, "w"); // ���뢠�� 䠩� ��� �����
  Inf *p = head;
  while (p != NULL) { // ���� �� �ᥬ ������⠬ ᯨ᪠
    fprintf(f, "%s %s %d\n", p->title, p->name, p->year);
    p = p->next;
  }
  fclose(f);
  printf("���᮪ ��࠭�� � 䠩�� %s\n", FileName);
}

// ����㦠�� ᯨ᮪ �� 䠩��
void Load()
{
  Clear();
  FILE *f; // 䠩�
  f = fopen(FileName, "r"); // ���뢠�� 䠩� ��� �⥭��
  while (!feof(f)) {
    Inf *p = (Inf *) malloc(sizeof(Inf)); // �뤥�塞 ���������� ������
    fscanf(f, "%s", p->title); // ������ �� ���� ������� ᯨ᪠
    if (feof(f))
      break;
    fscanf(f, "%s", p->name);
    fscanf(f, "%d", &p->year);
    p->prev = NULL;
    p->next = NULL;
    if (head == NULL) // �᫨ ᯨ᮪ ���⮩
      head = tail = p;
    else {
      tail->next = p;
      p->prev = tail;
      tail = p;
    }
  }
  fclose(f);
  printf("���᮪ ����㦥� �� 䠩�� %s\n", FileName);
}

void main()
{
  clrscr(); // ��頥� ��࠭
  Menu();
  char c;
  while (1) {
    c = getch();
    switch(c) {
      case '1': // �������� ᯨ᪠
        Clear();
        puts("���᮪ ᮧ���");
        break;
      case '2': // ��ᬮ�� ᯨ᪠
        puts("���᮪:");
        Print();
        break;
      case '3': // ���������� � ᯨ᮪ ����� �����
        Add();
        break;
      case '4': // ���� � ���४�஢�� ����� � ᯨ᪥
        Change();
        break;
      case '5': // �������� ����� �� ᯨ᪠
        Delete();
        break;
      case '6': // ���࠭���� ᯨ᪠ � 䠩��
        Save();
        break;
      case '7': // ����㧪� ᯨ᪠ �� 䠩��
        Load();
        break;
      case '8': // ��室
        return;
    }
  }
}
