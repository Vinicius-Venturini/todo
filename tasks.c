#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "tasks.h"
#include "lista.h"

void addTask(char *task, lista *l){
  tarefa *new = (tarefa*)malloc(sizeof(tarefa));
  new->myTask = task;
  new->done = 0;
  insere(l, new);
}

void taskDone(int index, lista *l){
  index -= 1;
  iterador i;
  if(getPos(l, &i, index))
    i.posicao->data->done = 1;
}

void showTasks(lista *l){
  iterador i = primeiro(l);
  int index = 1;
  while(!acabou(&i)){
    if(i.posicao->data->done)
      printf("%s%d.%s%s%s%s\n", BOLD, index, NONE, STRIKE, i.posicao->data->myTask, NONE);
    else
      printf("%s%d.%s%s\n", BOLD, index, NONE, i.posicao->data->myTask);
    index++;
    proximo(&i);
  }
}

void removeTask(int index, lista *l){
  index -= 1;
  iterador i;
  if(getPos(l, &i, index))
    retira(l, i);
}

void sortTasks(lista *l){
  iterador i = primeiro(l);
  int index = 0, times = l->qtd;
  while(!acabou(&i) && index < times){
    if(i.posicao->data->done){
      tarefa *new = (tarefa*)malloc(sizeof(tarefa));
      new->myTask = i.posicao->data->myTask;
      new->done = i.posicao->data->done;
      retira(l, i);
      insere(l, new);
      i = primeiro(l);
      times--;
      index = 0;
    }else{
      proximo(&i);
      index++;
    }
  }
}

void showHelp(){
  char todo[] = "Todo - Para te ajudar a se organizar";
  printf("%*s%s\n\n", (int)(50-strlen(todo)/2), "", todo);
  printf("%sSINTAXE%s\n", BOLD, NONE);
  printf("\t%stodo%s [ARGUMENTO]... [TAREFA]...\n\n", BOLD, NONE);
  printf("%sARGUMENTOS%s\n", BOLD, NONE);
  printf("\t%s-a, --add%s\n", BOLD, NONE);
  printf("\t\tadiciona uma nova tarefa à lista de tarefas (ex: todo --add \"Lavar as louças\")\n\n");
  printf("\t%s-c, --clear%s\n", BOLD, NONE);
  printf("\t\tlimpa a lista de tarefas\n\n");
  printf("\t%s-d, --done%s\n", BOLD, NONE);
  printf("\t\tmarca a tarefa passada pelo índice como concluída (ex: todo --done 2)\n\n");
  printf("\t%s-e, --edit%s\n", BOLD, NONE);
  printf("\t\tedita o texto de uma tarefa passada pelo índice (ex: todo --edit 2 \"Ir para a academia\")\n\n");
  printf("\t%s-h, --help%s\n", BOLD, NONE);
  printf("\t\tmostra uma ajuda de como utilizar o programa\n\n");
  printf("\t%s-r, --remove%s\n", BOLD, NONE);
  printf("\t\tremove a tarefa passada pelo índice da lista (ex: todo --remove 2)\n\n");
  printf("\t%s-s, --sort%s\n", BOLD, NONE);
  printf("\t\torganiza a lista, colocando as tarefas já concluídas no final da lista\n\n");
  printf("%sAUTOR%s\n", BOLD, NONE);
  printf("\tEscrito por Vinícius Carvalho Venturini\n\n");
}

void clearList(lista *l){
  destroy(l);
  initialize(l);
}

void editTask(int index, char *task, lista *l){
  index -= 1;
  iterador i;
  if(getPos(l, &i, index)){
      free(i.posicao->data->myTask);
      i.posicao->data->myTask = task;
  }
}

void addByFile(lista *l){

  char *name, arquivo[500] = "/home/", final[] = "/.todo/list.td";
  name = getlogin();
  strcat(arquivo, name);
  strcat(arquivo, final);

  char c, task[500], t = 't', *newTask;
  int count = 0;
  FILE *fr;
  fr = fopen(arquivo, "r");
  while(fscanf(fr, "%c", &c) != EOF){
    if(c == '\n' && t == 't'){
      newTask = (char*)malloc(sizeof(char)*count);
      for(int i = 0; i < count; i++)
        newTask[i] = task[i];
      addTask(newTask, l);
      count = 0;
      t = 'd';
    }else if(c == '\n' && t == 'd'){
      if(task[0] != '0')
        taskDone(l->qtd, l);
      count = 0;
      t = 't';
    }else if(c != '\n'){
      task[count] = c;
      count++;
    }
  }
}

void attFile(lista *l){

  char *name, arquivo[500] = "/home/", final[] = "/.todo/list.td";
  name = getlogin();
  strcat(arquivo, name);
  strcat(arquivo, final);

  char text[100000];
  int iText = 0, k = 0;
  iterador i = primeiro(l);
  FILE *fw;
  fw = fopen(arquivo, "w");
  while(!acabou(&i)){
    k = 0;
    while(1){
      if(i.posicao->data->myTask[k] == '\0')
				break;
			text[iText] = i.posicao->data->myTask[k];
			k++;
      iText++;
    }
    if(k){
      text[iText] = '\n';
      iText++;
      (i.posicao->data->done) ? (text[iText] = '1') : (text[iText] = '0');
      iText++;
      text[iText] = '\n';
      iText++;
    }
    proximo(&i);
  }

  char newText[iText];
  strcpy(newText, text);

  fprintf(fw, "%s", newText);
}
