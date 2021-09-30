#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tasks.h"
#include "lista.h"

int main(int argc, char *argv[]){

  int index = 0;
  char f = '\0';
  lista l;
  initialize(&l);
  addByFile(&l);

	for(int i = 1; i < argc; i++){
    if(strcmp(argv[i], "--add") == 0 || strcmp(argv[i], "-a") == 0){
      f = 'a';
    }else if(strcmp(argv[i], "--clear") == 0 || strcmp(argv[i], "-c") == 0){
      clearList(&l);
    }else if(strcmp(argv[i], "--done") == 0 || strcmp(argv[i], "-d") == 0){
      f = 'd';
    }else if(strcmp(argv[i], "--edit") == 0 || strcmp(argv[i], "-e") == 0){
      f = 'e';
    }else if(strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0){
      showHelp();
      attFile(&l);
      return 0;
    }else if(strcmp(argv[i], "--sort") == 0 || strcmp(argv[i], "-s") == 0){
      sortTasks(&l);
    }else if(strcmp(argv[i], "--remove") == 0 || strcmp(argv[i], "-r") == 0){
      f = 'r';
    }else if(f == 'a'){
      addTask(argv[i], &l);
    }else if(f == 'd'){
      index = atoi(argv[i]);
      taskDone(index, &l);
    }else if(f == 'e'){
      index = atoi(argv[i]);
      f = 'x';
    }else if(f == 'r'){
      index = atoi(argv[i]);
      removeTask(index, &l);
    }else if(f == 'x'){
      editTask(index, argv[i], &l);
      f = '\0';
    }
  }

  showTasks(&l);
  attFile(&l);

	return 0;
}
