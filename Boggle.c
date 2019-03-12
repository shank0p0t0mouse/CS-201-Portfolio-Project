#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include "dictionary.h"
#include "ui.h"
#include "boardUI.h"
extern char** dictionary;
extern int gamemode;
extern int boardSize;
int main(){
  int boardSize;
  dictionaryLoad();//Found in dictionary.c
  boardSize=pickGameMode();//Found in ui.c Also will call pick_Size in ui.c.
if (gamemode==4){
  return 0;
}
  draw();
  printf("%d, %d", boardSize, gamemode);
  return 0;
}
