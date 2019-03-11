#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "dictionary.h"

char **dictionary; //Global Variable holding the dictionary.
void dictionaryLoad(){
  ////////////////////////////////////////////////////
  //Loads in dictionary from dictionary.txt.
  dictionary=(char**)malloc(sizeof(char *)*(370200));
  for(int x =0; x<370100; x++){
    dictionary[x]=(char *)malloc(30);
  }
  FILE *d = fopen("dictionary.txt", "r");
  if (d ==NULL){
   printf("Error Opening File.\n");
   return;
  }

  int i=0;
  while(!feof(d)){
  fscanf(d, "%s", dictionary[i]);
  if (strlen(dictionary[i])<3){
  }
  else{
   i++;
  }
}
  srand(time(NULL));
  printf("%d",i);
  fclose(d);




  return;
}
