#include <curses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "dictionary.h"
//char *d;
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
int word_Check(char *word){
    char *lowerWord=word;
    for (int i=0; i<strlen(lowerWord); i++){
      lowerWord[i]=tolower(lowerWord[i]);
    }
  for (int i=0; i<370000; i++){
    if (strcmp(lowerWord,dictionary[i])==0){
      int k=strlen(word);
      return k;
    }
  //  else if (strcmp(lowerWord,dictionary[i])==1){
    //  mvwprintw(board, 25,5,"%s                 %s",lowerWord,dictionary[i]);
      //mvwprintw(board,21,5,"boyyyy");
      //int k=8;
      //return k;
    //}
    else{

    }
  }
  return 0;
}
