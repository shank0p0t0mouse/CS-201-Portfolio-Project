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
  const char *dice[20]={
  "AOBBOJ",
  "WHGEEN",
  "NRNZHL",
  "NAEAGE",
  "DIYSTT",
  "IESTSO",
  "AOTTWO",
  "HQuUMNI",
  "RYTLTE",
  "POHCSA",
  "LREVYD",
  "EXLDIR",
  "IENSUE",
  "SFFKAP",
  "IOTMUC",
  "EHWVTR"};
srand(time(0));
int n=0;
int interval=0;
for (int i=0; i<boardSize*boardSize; i++){
  n=rand()%6;
  interval=i%(15);
d[i]= dice[interval][n];
}
//  int numWindow=boardSize/20;
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
  /*  if(boardSize<=20){
      int drawx=(x)-(boardSize*4);
      int drawy=y-(boardSize*2);
      int xx=0;
      int yy=0;
      srand(time(0));

/*  for (int b=0; b<=(boardSize); b++){
  for(int i=0; i<=boardSize*4; i++){
  wmove(board,(drawy/2)+yy,(drawx/2)+i);
whline(board,ACS_HLINE,1);
	wrefresh(board);
}
yy=yy+2;
}*/
/*xx=0;
yy=0;
for(int i =0; i<boardSize; i++){
  for(int b=0; b<=boardSize; b++){
    mvwprintw(board,(drawy/2)+yy+1, (drawx/2)+xx, "|");
    xx=xx+4;

  }
  yy=yy+2;
  xx=0;
}
wrefresh(board);
int z =0;
xx=2;
yy=1;
for (int j=0; j<boardSize; j++){
  for (int f=0; f<boardSize; f++){
   mvwprintw(board, (drawy/2)+yy,(drawx/2)+xx,"%c",d[z]);
   z++;
   xx=xx+4;
  }
  xx=2;
  yy=yy+2;
}
}
else{
  int drawx=(x)-(20*4);
  int drawy=y-(20*2);
  int xx=0;
  int yy=0;
  srand(time(0));
/*for (int b=0; b<=20; b++){
for(int i=0; i<=20*4; i++){
wmove(board,(drawy/2)+yy,(drawx/2)+i);
whline(board,ACS_HLINE,1);
wrefresh(board);
}
yy=yy+2;
}*/
/*xx=0;
yy=0;
// if(boardSize>21){
for(int i =0; i<20; i++){
for(int b=0; b<=20; b++){
  mvwprintw(board,(drawy/2)+yy+1, (drawx/2)+xx, "|");
  xx=xx+4;

}
yy=yy+2;
xx=0;
}
wrefresh(board);
int a =0;

xx=2;
yy=1;
for (int j=0; j<20; j++){
for (int f=0; f<20; f++){
 mvwprintw(board, (drawy/2)+yy,(drawx/2)+xx,"%c",d[a]);
 a++;
 xx=xx+4;
}
xx=2;
yy=yy+2;
}
}
*/
farLeft=1;
farRight=20;
farUp=1;
farDown=20;
  wrefresh(board);

  int f=0;

  for (int b=0; b<boardSize; b++){
  for(int i=0; i<boardSize; i++){
    mvwprintw(board,b+2,i+2,"%c",d[f]);
    f++;
  }

}
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
  int allChoices[20];
  char word_List[100][30];
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
  int v=0;
  int choice=0;;
  //print_Board(board,1,y,x,d);
  int wordScore;
  int charIndex=0;
  mvwprintw(board,y-10,x-30,"yoooo");
  while(1)
  {	c = wgetch(board);
  keypad(board,TRUE);
    switch(c)
    {	case KEY_UP:
      if((highlightx-movement)>0){
          highlightx = (highlightx - movement);
          if(highlightx<=(boardSize*(farUp-1))){
            farDown--;
            farUp--;
            charIndex=((farUp-1)*20)+farLeft-1;
            wmove(board,drawy,drawx);
            wclrtobot(board);
            resize_Board(board,y,x);
          }
        }

        break;
      case KEY_DOWN:
      if ((highlightx+movement)<(boardSize*boardSize)){
        highlightx=highlightx+(movement);
        if (highlightx>=(boardSize*farDown)){
          mvwprintw(board,y-10,x-30,"yoooo");
          farDown++;
          farUp++;
          charIndex=((farUp-1)*20)+farLeft;
          mvwprintw(board,y-5,x-20,"%d",charIndex);
          wmove(board,drawy,drawx);
          wclrtobot(board);
          resize_Board(board,y,x);

        }

}

        break;
      case KEY_RIGHT:
              ++highlightx;
        break;

        case KEY_LEFT:
            --highlightx;
        break;
      case 10:
      check=checkValidOption(highlightx, choice,allChoices,word,board);
      mvwprintw(board,30,50,"%d",check);
        if (check==1){
          check=0;
          break;
        }
        else{
        choice = highlightx;
        mvwprintw(board,y-10,x-50,"%d",choice);
        allChoices[strlen(word)]=choice;


        int k=strlen(word);
        if ((d[choice-1]=='u')||(d[choice-1]=='Q')){
          word[k]='Q';
          word[k+1]='U';
          mvwprintw(board, 6+v,7,"%s", word);
        }
        else{
        word[k]=d[choice-1];
        mvwprintw(board, 6+v,7,"%s", word);
      }
    }
        break;

        case 32:
          strcpy(word_List[word_Num],word);
          wordScore=word_Check(word);
          score=score+wordScore;
          mvwprintw(board, 10,97,"TOTAL SCORE: %d",score);
          mvwprintw(board, 6+v,7,"%s = %d", word_List[word_Num], wordScore);
          memset(word, '\0', strlen(word));
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
/*  if (boardSize>=21){
  if ((highlightx>(farRight*farDown))&&(highlightx<=(boardSize*(boardSize-1)))){
    mvwprintw(board,y-10,x-30,"yoooo");
    farDown++;
    farUp++;
    charIndex=((farUp-1)*boardSize)+farLeft-1;
    wmove(board,drawy,drawx);
    wclrtobot(board);
    resize_Board(board,y,x);
  }
  else
    charIndex=((farUp)*boardSize)+farLeft-1;
  printLargeBoard(board,highlightx, y, x,d);
  return;
}
  else{*/
    mvwprintw(board,y-11,x-30,"y12312oooo");
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
  int f=0;

  for (int b=0; b<boardSize; b++){
  for(int i=0; i<boardSize; i++){
    mvwprintw(board,b+2,i+2,"%c",d[f]);
    f++;
  }

}
mvwprintw(board,y-30,x-50,"9814327649823");
int xx=0;
int yy=0;

for(int i =0; i<20; i++){
for(int b=0; b<=20; b++){
  mvwprintw(board,(drawy/2)+yy+1, (drawx/2)+xx, "|");
  xx=xx+4;

}
yy=yy+2;
xx=0;
}
wrefresh(board);
start_color();
init_pair(1, COLOR_GREEN,COLOR_BLACK);
xx=2;
yy=1;
mvwprintw(board, y-20,x-20,"%d    %d",highlightx,charIndex);
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
charIndex=charIndex+boardSize-20+farLeft-1;
xx=2;
yy=yy+2;
}
/*for (int i=0;i<=80;i++){
wmove(board,(drawy/2)+40,(drawx/2)+i);
whline(board,ACS_HLINE,1);
wrefresh(board);
}*/
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
