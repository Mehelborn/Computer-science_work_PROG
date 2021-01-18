#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <alloc.h>
#include <string.h>

const char FileName[] = "inf.dat"; // Имя файла

// Структура элемента двусвязного списка
struct Inf
{
   char title[30]; // Название книги
   char name[20]; // Фамилия автора
   int year; // Год издания
   Inf *prev; // Указатель на предыдущий элемент
   Inf *next; // Указатель на следующий элемент
};

Inf *head = NULL; // Указатель на первый элемент списка
Inf *tail = NULL; // Указатель на последний элемент списка

// Выводит меню на экран
void Menu()
{
  puts("1 - Создание списка");
  puts("2 - Просмотр списка");
  puts("3 - Добавление в список новой записи");
  puts("4 - Поиск и корректировка записи в списке");
  puts("5 - Удаление записи из списка");
  puts("6 - Сохранение списка в файле");
  puts("7 - Загрузка списка из файла");
  puts("8 - Выход\n");
}

// Очищает список
void Clear()
{
  Inf *p = head;
  while (p != NULL) {
    Inf *q = p;
    p = p->next;
    free(q); // Удаляем элемент списка из динамической памяти
  }
  head = NULL;
  tail = NULL;
}

// Выводит список на экран
void Print()
{
  Inf *p = head;
  while (p != NULL) { // Цикл по всем элементам списка
    printf("%30s ", p->title);
    printf("%20s ", p->name);
    printf("%10d\n", p->year);
    p = p->next;
  }
}

// Добавляет новую запись перед последней
void Add()
{
  Inf *p = (Inf *) malloc(sizeof(Inf)); // Выделяем динамическую память
  printf("Название книги: "); // Вводим все поля элемента списка
  scanf("%s", p->title);
  printf("Фамилия автора: ");
  scanf("%s", p->name);
  printf("Год издания: ");
  scanf("%d", &p->year);
  p->prev = NULL;
  p->next = NULL;
  if (head == NULL) // Если список пустой
    head = tail = p;
  else if (head->next == NULL) { // Если одна запись в списке
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

// Изменяет год издания по названию книги
void Change()
{
  char title[30];
  printf("Название: "); // Вводим название книги
  scanf("%s", title);
  Inf *p = head;
  int found = 0;
  while (p != NULL) { // Цикл по всем элементам списка
    if (!strcmp(p->title, title)) {
      printf("Год издания: ");
      scanf("%d", &p->year);
      found = 1;
      break;
    }
    p = p->next;
  }
  if (found == 0)
    puts("Книга не найдена");
  else
    puts("Год издания изменен");
}

// Удаляет из списка книги заданного автора
void Delete()
{
  char name[20];
  printf("Введите фамилию автора: ");
  scanf("%s", name);
  Inf *p = head;
  int found = 0;
  while (p != NULL) {
    if (!strcmp(p->name, name)) {
      // Если удаляемый элемент является одновременно первым и последним
      if (p->prev == NULL && p->next == NULL) {
        free(p); // Удаляем элемент списка из динамической памяти
        head = NULL;
        tail = NULL;
        break;
      }
      // Если удаляем первый элемент
      else if (p->prev == NULL) {
        Inf *q = p;
        p = p->next;
        free(q); // Удаляем элемент списка из динамической памяти
        p->prev = NULL;
        head = p;
      }
      // Если удаляем последний элемент
      else if (p->next == NULL) {
        Inf *q = p;
        p = p->prev;
        free(q); // Удаляем элемент списка из динамической памяти
        p->next = NULL;
	tail = p;
        break;
      }
      // Если удаляем элемент из середины списка
      else {
        p->prev->next = p->next;
        p->next->prev = p->prev;
        Inf *q = p;
        p = p->next;
        free(q); // Удаляем элемент списка из динамической памяти
      }
      found = 1;
    }
    else
      p = p->next;
  }
  if (found == 0)
    puts("Издания не найдены");
  else
    puts("Издания удалены");
}

// Сохраняет список в файле
void Save()
{
  FILE *f; // файл
  f = fopen(FileName, "w"); // открываем файл для записи
  Inf *p = head;
  while (p != NULL) { // Цикл по всем элементам списка
    fprintf(f, "%s %s %d\n", p->title, p->name, p->year);
    p = p->next;
  }
  fclose(f);
  printf("Список сохранен в файле %s\n", FileName);
}

// Загружает список из файла
void Load()
{
  Clear();
  FILE *f; // файл
  f = fopen(FileName, "r"); // открываем файл для чтения
  while (!feof(f)) {
    Inf *p = (Inf *) malloc(sizeof(Inf)); // Выделяем динамическую память
    fscanf(f, "%s", p->title); // Вводим все поля элемента списка
    if (feof(f))
      break;
    fscanf(f, "%s", p->name);
    fscanf(f, "%d", &p->year);
    p->prev = NULL;
    p->next = NULL;
    if (head == NULL) // Если список пустой
      head = tail = p;
    else {
      tail->next = p;
      p->prev = tail;
      tail = p;
    }
  }
  fclose(f);
  printf("Список загружен из файла %s\n", FileName);
}

void main()
{
  clrscr(); // Очищаем экран
  Menu();
  char c;
  while (1) {
    c = getch();
    switch(c) {
      case '1': // Создание списка
        Clear();
        puts("Список создан");
        break;
      case '2': // Просмотр списка
        puts("Список:");
        Print();
        break;
      case '3': // Добавление в список новой записи
        Add();
        break;
      case '4': // Поиск и корректировка записи в списке
        Change();
        break;
      case '5': // Удаление записи из списка
        Delete();
        break;
      case '6': // Сохранение списка в файле
        Save();
        break;
      case '7': // Загрузка списка из файла
        Load();
        break;
      case '8': // Выход
        return;
    }
  }
}
