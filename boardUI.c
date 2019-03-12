#include <ncurses.h>
#include <string.h>
#include "ui.h"
#include "boardUI.h"
extern int boardSize;
void draw(){
  WINDOW *board;
  	int highlight = 1;
  	int choice = 0;
  	int c;
  	int x, y;
  	initscr();
  	clear();
  	noecho();
  	cbreak();
  	start_color();
  	init_pair(1,COLOR_RED,COLOR_BLACK);
    init_pair(2, COLOR_CYAN,COLOR_BLACK);
    getmaxyx(stdscr, y,x);
  //	startx=x;
  	//starty=y;
  	board = newwin(y, x, 0, 0);
    resize_Board(board, y ,x);
  //for (int i =0; i<boardSize;i++){
    //mvwprintw(board,(y/3)+i,(x/3),"|");
    //mvwprintw(board,(y/3)+i,(x/2),"|");
  //  for (int b=(x/3)+1; b<(x/2)+boardSize;b++){
    //mvwprintw(board, (y/3)+i, b, "-");
  //}
  //}
//  mvwprintw(board, y/2,x/2,"|");
  //mvwprintw(board, y/2, (x/2)+1, "|");
  //mvwprintw(board, y/2, (x/2), "_");
//  mvwprintw(board, (y/2)-1, (x/2), "_");
//int i,h;
//for(i=4;i<=10;i++) {
		//mvwprintw(board,i, 0,"|");
		//mvwprintw(board,i, 4, "|");
		//mvwprintw(board,i, 8, "|");
		//mvwprintw(board,i, 4, "|");
		//mvwprintw(board,i, 8, "|");
		//mvwprintw(board,i, 12,"|");

	//	if(i%2 == 0){
		//	for(h=4;h<=16;h++) {
			//	mvwprintw(board,i, h, "-");
		//	}
		//}
	//	move(1,2);
	//}
  int drawx=x-boardSize*4;
  int drawy=y-boardSize*2;
  for (int b=0; b<(boardSize*2)+2; b=b+2){
  for(int i=0; i<=boardSize*4; i++){
  wmove(board,(drawy/2)+b,(drawx/2)+i);
whline(board,ACS_HLINE,1);
	wrefresh(board);
}
}
for(int i =0; i<=boardSize*4; i=i+4){
  for(int b=0; b<boardSize*2; b=b+2){
    mvwprintw(board,(drawy/2)+b+1, (drawx/2)+i, "|");
  }
}



  wrefresh(board);
/*  for (int i =5; i<20; i++){
    for (int b=5; b<50; b++){
      mvwprintw(board, (y/3)+i,b,"-");
    }
  }
wrefresh(board);
keypad(stdscr, TRUE);*/
while(1){

}
return;
}
