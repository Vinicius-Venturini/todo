#include <stdlib.h>
#include "lista.h"

void initialize(lista *l){
  qnode *n = (qnode*)malloc(sizeof(qnode));
  n->next = n->prev = l->sentinela = n;
  l->qtd = 0;
}

int empty(lista *l){
  return l->sentinela->next == l->sentinela;
}

void retira(lista *l, iterador i){
  qnode *n = i.posicao;
  if(n != l->sentinela){
    n->next->prev = n->prev;
    n->prev->next = n->next;
    free(n);
    l->qtd--;
  }
}

iterador primeiro(lista *l){
  iterador i;
  i.posicao = l->sentinela->next;
  i.estrutura = l;
  return i;
}

iterador ultimo(lista *l){
  iterador i;
  i.posicao = l->sentinela->prev;
  i.estrutura = l;
  return i;
}

void destroy(lista *l){
  iterador i;
  while(!empty(l)){
    i = primeiro(l);
    retira(l, i);
  }
  free(l->sentinela);
}

void insere(lista *l, tarefa* data){
  iterador i = ultimo(l);
  qnode *n = (qnode*)malloc(sizeof(qnode));
  n->data = data;
  n->next = i.posicao->next;
  n->prev = i.posicao;
  i.posicao->next = n;
  n->next->prev = n;
  l->qtd++;
}

int acabou(iterador *i){
  return i->posicao == i->estrutura->sentinela;
}

int proximo(iterador *i){
  if(!acabou(i)){
    i->posicao = i->posicao->next;
    return 1;
  }
  return 0;
}

int anterior(iterador *i){
  if(!acabou(i)){
    i->posicao = i->posicao->prev;
    return 1;
  }
  return 0;
}

int getPos(lista *l, iterador *i, int index){
  if(index < 0) return 0;
  if(index > l->qtd - 1) return 0;
  iterador first = primeiro(l);
  *i = first;
  for(int j = 0; j < index; j++, proximo(i))
    if(acabou(i)) return 0;
  return 1;
}

void* elemento(iterador i){
  return i.posicao->data;
}
