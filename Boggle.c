#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include "dictionary.h"
#include "ui.h"
extern char** dictionary;
int main(){
  dictionaryLoad();//Found in dictionary.c
  pickGameMode();//Found in ui.c Also will call pick_Size in ui.c.
  return 0;
}
