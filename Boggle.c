#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include "dictionary.h"
#include "ui.h"
#include "boardUI.h"
extern char** dictionary;
extern int gamemode;
extern int boardSize;
extern char *d;
int main(){
  //int boardSize=0;
  dictionaryLoad();//Found in dictionary.c
  pickGameMode();//Found in ui.c Also will call pick_Size in ui.c.
if (gamemode==4){
  return 0;
}
int games=1;
while(games==1){
  games=draw();
}
  return 0;
}
