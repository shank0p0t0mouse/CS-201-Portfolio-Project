#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include "dictionary.h"
#include "ui.h"
#include "boardUI.h"
extern int player_Num;
extern char** dictionary;
extern int gamemode;
extern int boardSize;
extern char *d;
int main(){ //Main function that runs the program.

  int fileOpen=dictionaryLoad();//Found in dictionary.c
  if (fileOpen==2){ //Checks if the dictionary was opened correctly.
    return 0;
  }
  pickGameMode();//Found in ui.c Also will call pick_Size in ui.c.
  if (gamemode==3){
    return 0;
  }
  int games=1;
  if (gamemode==2) { // For when the user selects Player vs. Player.
    while (games==1){// If the user selects any key other than 1, the while loop terminates.
      games=draw(); // Draw is called twice for the 1st and 2nd player.
      games=draw();
      player_Num=0;
    }
}
  if (gamemode==1){ //For when the user selects Single Player.
    while(games==1){
      games=draw();
    }
}
  return 0;
}
