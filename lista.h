#ifndef LISTA_H
#define LISTA_H

typedef struct{
  char *myTask;
  int done;
} tarefa;

typedef struct qnode{
  tarefa* data;
  struct qnode *next, *prev;
} qnode;

typedef struct{
  qnode *sentinela;
  unsigned qtd;
} lista;

typedef struct {
  qnode *posicao;
  lista *estrutura;
} iterador;

void initialize(lista *l);
int empty(lista *l);
void retira(lista *l, iterador i);
iterador primeiro(lista *l);
iterador ultimo(lista *l);
void destroy(lista *l);
void insere(lista *l, tarefa* data);
int acabou(iterador *i);
int proximo(iterador *i);
int anterior(iterador *i);
int getPos(lista *l, iterador *i, int index);
void* elemento(iterador i);

#endif
