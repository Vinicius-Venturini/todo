#ifndef TASKS_H
#define TASKS_H
#define BOLD "\033[1m"
#define STRIKE "\033[9m"
#define NONE "\033[0m"

#include "lista.h"

void addTask(char *task, lista *l);
void taskDone(int index, lista *l);
void showTasks(lista *l);
void removeTask(int index, lista *l);
void sortTasks(lista *l);
void showHelp();
void clearList(lista *l);
void editTask(int index, char *task, lista *l);
void addByFile(lista *l);
void attFile(lista *l);

#endif
