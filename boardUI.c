#include <curses.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "ui.h"
#include "boardUI.h"
#include "ui.h"
#include "dictionary.h"
extern int boardSize;
int farUp;
int farDown;
int farRight;
int farLeft;
char word[30];
void draw(){
  int size=boardSize*boardSize;
  char *d;
  d=(char*)malloc(size);
  printf("%s",d);
  const char *dice[25]={
  "AAAFRS",
  "AAEEGMU",
  "CEIILT",
  "DHLNOR",
  "FIPRSY",
  "AAEEEE",
  "AEGMNN",
  "CEILPT",
  "BJKQXZ",
  "DDLNOR",
  "GORRVW",
  "AAFIRS",
  "AFIRSY",
  "CEIPST",
  "EIIITT",
  "HIPRRY",
  "ADENNN",
  "DHHNOT",
  "EMOTTT",
  "NOOTUW",
  "AEEEEM",
  "CCNSTW",
  "DHHLOR",
  "ENSSSU",
  "OOOTTU"};
srand(time(0));
int n=0;
int interval=0;
for (int i=0; i<boardSize*boardSize; i++){
  n=rand()%6;
  interval=i%(25);
d[i]= dice[interval][n];
}
  WINDOW *board;
  	unsigned int highlightx = 1;
  	int choice = 0;
  	int c;
  	int x, y;
  	initscr();
  	clear();
  	noecho();
  	cbreak();
  	start_color();
    char *ptr;
  	init_pair(1,COLOR_RED,COLOR_BLACK);
    init_pair(2, COLOR_CYAN,COLOR_BLACK);
    getmaxyx(stdscr, y,x);
  	board = newwin(y, x, 0, 0);
    resize_Board(board, y ,x);
    wrefresh(board);
farLeft=1;
farRight=20;
farUp=1;
farDown=20;

  wrefresh(board);

boardControls(board,d);

return;
}

void boardControls(WINDOW *board, char d[]){
  int num_Choices=boardSize*boardSize;
  int movement;
  if(boardSize>=21){
    movement=boardSize;
  }
  else
    movement=boardSize;
  int allChoices[30];
  char wordList[500][200];
  int highlightx=1;
  int check=0;
  int y,x,c;
  int score=0;
  getmaxyx(stdscr, y, x);
  int starty=y;
  int startx=x;
  int drawx=(x)-(20*4);
  int drawy=y-(20*2);
  int word_Num=0;
  int choice=0;
  int v=0;
  int wordScore;
  start_color();
  init_pair(4,COLOR_CYAN,COLOR_BLACK);
  init_pair(3,COLOR_RED,COLOR_BLACK);
//  wclear(board);
  //resize_Board(board,y,x);
  keypad(board,TRUE);
  wattron(board,COLOR_PAIR(3));
  do {
    mvwprintw(board,y/2,(x/2)-18,"Press The Space Bar to Start the Game.");
    wrefresh(board);
  }while((c=wgetch(board)!=32));
  wattroff(board,COLOR_PAIR(3));
  wclear(board);
  resize_Board(board,y,x);
  int charIndex=0;
  if(boardSize<21)
    print_Board(board,highlightx, y,x,d);
      else
        printLargeBoard(board,highlightx, y, x,d,charIndex);
  while(1)
  {	c = wgetch(board);


    switch(c)
    {	case KEY_UP:
      wrefresh(board);
      if((highlightx-movement)>0){
          highlightx = (highlightx - movement);
          if(highlightx<=(boardSize*(farUp-1))){
            farDown--;
            farUp--;
            charIndex=((farUp-1)*(boardSize))+farLeft-1;
            wmove(board,drawy,drawx);
            wclrtobot(board);
            resize_Board(board,y,x);
          }
        }

        break;
      case KEY_DOWN:
      wrefresh(board);
      if ((highlightx+movement)<=(boardSize*boardSize)){
        highlightx=highlightx+(movement);
        if (highlightx>(boardSize*farDown)){
          mvwprintw(board,y-40,x-30,"%d",farDown);
          farDown++;
          farUp++;
          charIndex=((farUp-1)*(boardSize))+farLeft-1;
          mvwprintw(board,y-5,x-20,"%d",charIndex);
          wmove(board,drawy,drawx);
          wclrtobot(board);
          resize_Board(board,y,x);

        }

}

        break;
      case KEY_RIGHT:
      wrefresh(board);
      if ((highlightx%boardSize)!=0){
        if(highlightx<=boardSize){
          if(highlightx==farRight){
            farRight++;
            farLeft++;
            charIndex=((farUp-1)*(boardSize))+farLeft-1;
            wmove(board,drawy,drawx);
            wclrtobot(board);
            resize_Board(board,y,x);
          }
        }
        else if (((highlightx-farRight)%boardSize)==0){
          farRight++;
          farLeft++;
          charIndex=((farUp-1)*(boardSize))+farLeft-1;
          wmove(board,drawy,drawx);
          wclrtobot(board);
          resize_Board(board,y,x);
        }

        highlightx++;
      }
        break;

        case KEY_LEFT:
        wrefresh(board);
        if ((highlightx%boardSize)!=1){
          if(highlightx<=boardSize){
            if (highlightx==farLeft){
              farLeft--;
              farRight--;
              charIndex=((farUp-1)*(boardSize))+farLeft-1;
              wmove(board,drawy,drawx);
              wclrtobot(board);
              resize_Board(board,y,x);

            }
          }
          else if (((highlightx-farLeft)%boardSize)==0){
            farLeft--;
            farRight--;
            charIndex=((farUp-1)*(boardSize))+farLeft-1;
            wmove(board,drawy,drawx);
            wclrtobot(board);
            resize_Board(board,y,x);
          }
          --highlightx;
        }

        break;
      case 10:
      check=checkValidOption(highlightx, choice,allChoices,word,board);
        if (check==1){
          check=0;
          break;
        }
        else{
        choice = highlightx;
        mvwprintw(board,y-10,x-50,"%d",choice);
        allChoices[strlen(word)]=choice;
        wattron(board,COLOR_PAIR(3));
        mvwprintw(board,2,4,"WORDS:");
        wattroff(board,COLOR_PAIR(3));
        int k=strlen(word);
        wattron(board,COLOR_PAIR(4));
        if ((d[choice-1]=='u')||(d[choice-1]=='Q')){
          word[k]='Q';
          word[k+1]='U';
          mvwprintw(board, 3+v,4,"%s", word);
        }
        else{
        word[k]=d[choice-1];
        mvwprintw(board, 3+v,4,"%s", word);
      }
      wattroff(board,COLOR_PAIR(4));
    }
        break;

        case 32:
          wordScore=word_Check(word,word_Num);
          if(wordScore!=0)
            strcpy(wordList[word_Num],word);
          wattron(board,COLOR_PAIR(4));
          for (int i=0; i<strlen(word); i++){
            allChoices[i]=0;
          }
          score=score+wordScore;

          mvwprintw(board, 3,(x/2)-8,"TOTAL SCORE: %d",score);
          mvwprintw(board, 3+v,4,"%s = %d", word, wordScore);
          memset(word, '\0', strlen(word));
          wattroff(board,COLOR_PAIR(4));
          word_Num++;
          v++;
          choice=0;
        break;
    }

    if(boardSize<21)
      print_Board(board,highlightx, y,x,d);
        else
          printLargeBoard(board,highlightx, y, x,d,charIndex);
  }
  return;
}
void print_Board(WINDOW *board, int highlightx, int y, int x,char d[]){
  int drawx=(x)-(boardSize*4);
  int drawy=y-(boardSize*2);
int charIndex=0;
int num_Choices=boardSize*boardSize;
int xx=0;
int yy=0;
start_color();
init_pair(1, COLOR_GREEN,COLOR_BLACK);
xx=2;
yy=1;
for (int f=0; f<boardSize; f++){
  for (int j=0; j<(boardSize); j++){
    if ((highlightx==(charIndex+1) )){
      wattron(board, A_REVERSE);
      wattron(board,COLOR_PAIR(1));
      if ((d[charIndex]=='u')||(d[charIndex]=='Q')){
          mvwprintw(board, (drawy/2)+yy,(drawx/2)+xx,"QU");
      }
        else{
          mvwprintw(board, (drawy/2)+yy,(drawx/2)+xx,"%c",d[charIndex]);
        }
      wattroff(board,COLOR_PAIR(1));
      wattroff(board, A_REVERSE);
}
  else{
    if ((d[charIndex]=='u')||(d[charIndex]=='Q')){
   mvwprintw(board, (drawy/2)+yy,(drawx/2)+xx,"Qu");
    }
    else{
    mvwprintw(board, (drawy/2)+yy,(drawx/2)+xx,"%c",d[charIndex]);
  }
}
xx=xx+4;
charIndex++;
}

xx=2;
yy=yy+2;
}
wrefresh(board);
wmove(board,y,x);

return;

}
void printLargeBoard(WINDOW *board, int highlightx, int y, int x,char d[],int charIndex){
  int drawx=x-(20*4);
  int drawy=y-(20*2);
  start_color();
  init_pair(5,COLOR_YELLOW,COLOR_BLACK);
int xx=0;
int yy=0;
wattron(board,COLOR_PAIR(5));
for (int i=farLeft; i<=farRight;i++){
  mvwprintw(board,drawy/2,(drawx/2)+2+xx,"%d",i);
  xx=xx+4;
}
for (int i=farUp;i<=farDown;i++){
  mvwprintw(board,(drawy/2)+1+yy,(drawx/2)-2,"%d",i);
  yy=yy+2;
}
wattroff(board,COLOR_PAIR(5));
yy=0;
xx=0;
for(int i =0; i<20; i++){
for(int b=0; b<=20; b++){
  mvwprintw(board,(drawy/2)+yy+1, (drawx/2)+xx, "|");
  xx=xx+4;

}
yy=yy+2;
xx=0;
}
wrefresh(board);
init_pair(1, COLOR_GREEN,COLOR_BLACK);
xx=2;
yy=1;
mvwprintw(board,y-30,x-30,"%d     %d",highlightx,charIndex);
for (int f=0; f<20; f++){
  for (int j=0; j<(20); j++){

    if ((highlightx==(charIndex+1) )){
      wattron(board, A_REVERSE);
      wattron(board,COLOR_PAIR(1));

      if ((d[charIndex]=='u')||(d[charIndex]=='Q')){
          mvwprintw(board, (drawy/2)+yy,(drawx/2)+xx,"QU");
      }
        else{
          mvwprintw(board, (drawy/2)+yy,(drawx/2)+xx,"%c",d[charIndex]);
        }
      wattroff(board,COLOR_PAIR(1));
      wattroff(board, A_REVERSE);
}
  else{

    if ((d[charIndex]=='u')||(d[charIndex]=='Q')){
   mvwprintw(board, (drawy/2)+yy,(drawx/2)+xx,"Qu");
    }
    else{
    mvwprintw(board, (drawy/2)+yy,(drawx/2)+xx,"%c",d[charIndex]);
  }
}
xx=xx+4;
charIndex++;
}
charIndex=charIndex+boardSize-20;
xx=2;
yy=yy+2;
}
wrefresh(board);
wmove(board,y,x);
  return;
}
int checkValidOption(int highlight, int choice, int allChoices[20], char *word,WINDOW *board){
  if (choice==0){
    return 0;
  }
  for(int i=0; i<=strlen(word);i++){ //Checks through previous choices so letters are not reusable.
    if (highlight==allChoices[i]){
      mvwprintw(board, 40, 150, "You can't choose that character! It's already in the word.");
      return 1;
    }
  }
  if(choice==(boardSize*boardSize)){ //Checks all valid inputs after bottom right corner letter is chosen.
    if (highlight==(choice-boardSize))
      return 0;
    if (highlight==(choice-1))
      return 0;
    if (highlight==(choice-boardSize-1))
      return 0;
    return 1;
  }
  if(choice==((boardSize*boardSize)-boardSize+1)){ //Checks all valid inputs after bottom left corner letter is chosen.
    if (highlight==(choice+1))
      return 0;
    if (highlight==(choice-boardSize))
      return 0;
    if (highlight==(choice-boardSize+1))
      return 0;
    return 1;
  }
  if (choice==boardSize){ //Checks all valid inputs after upper right corner letter is chosen.
    if (highlight==(choice-1))
      return 0;
    if (highlight==(choice+boardSize-1))
      return 0;
    if (highlight==(choice+boardSize))
      return 0;
    return 1;
  }
  if(choice==1){ //Checks all valid inputs after upper left corner letter is chosen.
    if (highlight==(choice+1))
      return 0;
    if (highlight==(choice+boardSize))
      return 0;
    if (highlight==(choice+boardSize+1))
      return 0;
    return 1;
  }
  if ((choice%boardSize)==0){ //Checks all valid inputs after a rightmost letter is chosen.
    if (highlight==(choice-1))
      return 0;
    if (highlight==(choice-boardSize))
      return 0;
    if (highlight==(choice+boardSize))
      return 0;
    if (highlight==(choice+boardSize-1))
      return 0;
    if (highlight==(choice-boardSize-1))
      return 0;
    return 1;
  }
  if((choice%boardSize)==1){ //Checks all valid inputs after a leftmost letter is chosen.
    if (highlight==(choice+1))
      return 0;
    if (highlight==(choice+boardSize))
      return 0;
    if (highlight==(choice+boardSize+1))
      return 0;
    if (highlight==(choice-boardSize))
      return 0;
    if (highlight==(choice-boardSize+1))
      return 0;
    return 1;
  }
  if (highlight==(choice+1)) //All of these if statements check for input from all other inputs.
    return 0;
  if (highlight==(choice-1))
    return 0;
  if (highlight==(choice+boardSize+1))
    return 0;
  if (highlight==(choice-boardSize-1))
    return 0;
  if (highlight==(choice+boardSize))
    return 0;
  if (highlight==(choice-boardSize))
    return 0;
  if (highlight==(choice+boardSize-1))
    return 0;
  if (highlight==(choice-boardSize+1))
    return 0;

    return 1;

}
