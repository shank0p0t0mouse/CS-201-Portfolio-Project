#include <curses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "dictionary.h"
char **dictionary; //Global Variable holding the dictionary.
char word_List[500][100];
int dictionaryLoad(){
  ////////////////////////////////////////////////////
  //Loads in dictionary from dictionary.txt.
  dictionary=(char**)malloc(sizeof(char *)*(370100));
  for(int x =0; x<370100; x++){
    dictionary[x]=(char *)malloc(30);
  }
  FILE *d = fopen("dictionary.txt", "r");
  if (d ==NULL){
   printf("Error Opening File.\n");
   return 2;
  }

  int i=0;
  while(!feof(d)){
    fscanf(d, "%s", dictionary[i]);
    if (strlen(dictionary[i])<3){ //Skips over words with a length of less than 3.
  }
    else{
      i++;
  }
}
  srand(time(NULL));
  printf("%d",i);
  fclose(d);
  return 1;
}
int word_Check(char *word,int word_Num){ //Function to check that a word is valid in the dictionary and that it has never been inputted in the game yet.
    char lowerWord[100];
    strcpy(lowerWord,word);
    for (int i=0; i<strlen(lowerWord); i++){
      lowerWord[i]=tolower(lowerWord[i]); //Word is put to lower because all of the words in dictionary.txt are lowercase.
    }
  for (int i=0; i<370100; i++){
    if (strcmp(lowerWord,dictionary[i])==0){

      for(int b=0; b<word_Num; b++){
        if (strcmp(word,word_List[b])==0){
          return 0;
        }
      }
      strcpy(word_List[word_Num],word);
      if(strlen(word)==3) //The if statements are for scoring purposes Depending on the word length the function returns a score.
        return 1;
      if(strlen(word)==4)
        return 2;
      if(strlen(word)==5)
        return 3;
      if(strlen(word)==6)
        return 4;
      if(strlen(word)==7)
        return 5;
      if(strlen(word)>=8)
        return 6;
    }
  }
  return 0;
}
