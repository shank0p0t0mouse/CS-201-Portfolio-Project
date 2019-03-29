#include <curses.h>
#include <string.h>
#include <strings.h>
#include "ui.h"
int startx = 0;
int starty = 0;

const char *choices[] = {
			"Single Player",
			"Player vs. Player",
			"Player vs. CPU",
			"Exit Boggle",
		  };
const char *board_Choice[] = {
			"0",
			"1",
			"2",
			"3",
			"4",
			"5",
			"6",
			"7",
			"8",
			"9",
			"Back to GameMode Selection"
};
int gamemode=0;
int boardSize;
int n_choices = sizeof(choices) / sizeof(char *);
int board_Size = sizeof(board_Choice)/sizeof(char *);
void pickGameMode()
{	WINDOW *menu_win;
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
	startx=x;
	starty=y;
	menu_win = newwin(y, x, 0, 0);

	keypad(menu_win, TRUE);
  const char sentence[]="Use arrow keys to go up and down, Press enter to select a choice";
	const char sentence2[]="Make Your Game Take up the Full Screen for the Best Boggle Experience.";
    wattron(menu_win, COLOR_PAIR(1));
	mvwprintw(menu_win,1,(x/2)-(strlen(sentence))/2, "%s",sentence);
	mvwprintw(menu_win,(y/2)-8,(x/2)-(strlen(sentence2))/2,"%s",sentence2);
  wattroff(menu_win, COLOR_PAIR(1));
  wattron(menu_win,COLOR_PAIR(2));
  for (int i =5;i<(x-6);){
    mvwprintw(menu_win, 0, i,"BOGGLE ");
    mvwprintw(menu_win, y-1, i,"BOGGLE ");
    i=i+7;
  }
	for (int i=0; i<y; i++){
		mvwprintw(menu_win,i,0,"|");
		mvwprintw(menu_win,i,x-1,"|");
	}
	wrefresh(menu_win);
	wattroff(menu_win, COLOR_PAIR(2));
	wattron(menu_win,COLOR_PAIR(1));
		 print_menu1(menu_win, highlight,y,x);

	while(1)
	{	c = wgetch(menu_win);
		getmaxyx(stdscr, starty,startx);
		if ((x!=startx)||y!=starty){
			x=startx;
			y=starty;
		resize_Window(menu_win, y,x);
		}
		switch(c)
		{	case KEY_UP:
				if(highlight == 1)
					highlight = n_choices;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices)
					highlight = 1;
				else
					++highlight;
				break;
			case 10:
				choice = highlight;
				break;
			default:
				break;
		}
		print_menu1(menu_win, highlight, y,x);
		if(choice != 0)
      break;
	}

	getmaxyx(stdscr,y,x);
	gamemode=choice;
if (choice==4){
endwin();
return;
}
pick_Size(menu_win,y,x,choice,choices[choice-1]);
		wrefresh(menu_win);
		return;
}

void print_menu1(WINDOW *menu_win, int highlight, int y, int x)
{
int i;
y=y/2;
x=x/2;
	for(i = 0; i < n_choices; ++i)
	{	if(highlight == i + 1)
		{	wattron(menu_win, A_REVERSE);
      wattron(menu_win, COLOR_PAIR(1));
			mvwprintw(menu_win, y-4, x-4, "%s", choices[i]);
			wattroff(menu_win, A_REVERSE);
      wattroff(menu_win, COLOR_PAIR(1));
		}
		else
			mvwprintw(menu_win, y-4, x-4, "%s", choices[i]);
		++y;
	}
	wrefresh(menu_win);
}
void resize_Window(WINDOW *menu_win, int y, int x){
	wclear(menu_win);
	wresize(menu_win,y,x);
	wattron(menu_win, COLOR_PAIR(1));
	if (gamemode==0){
	const char sentence[]="Use arrow keys to go up and down, Press enter to select a choice";
	const char sentence2[]="Make Your Game Take up the Full Screen for the Best Boggle Experience.";

	mvwprintw(menu_win,1,(x/2)-(strlen(sentence))/2, "%s",sentence);
	mvwprintw(menu_win,(y/2)-8,(x/2)-(strlen(sentence2))/2,"%s",sentence2);
	wrefresh(menu_win);
}
else {
	const char *message="Enter in the Boardsize for a NxN Boggle Board and Click Enter!";
	const char *message2 ="(WARNING: If the Boardsize is greater than 20, Only 20x20 of the Board will be shown at a time.)";
	mvwprintw(menu_win,y/5,(x/2)-(strlen(message))/2,"%s",message);
	mvwprintw(menu_win,(y/5)+1,(x/2)-(strlen(message2))/2,"%s",message2);
	wrefresh(menu_win);
}
wattroff(menu_win, COLOR_PAIR(1));
	wattron(menu_win,COLOR_PAIR(2));
	for (int i =5;i<(x-6);){
		mvwprintw(menu_win, 0, i,"BOGGLE ");
		mvwprintw(menu_win, y-1, i,"BOGGLE ");
		i=i+7;
	}
	for (int i=0; i<y; i++){
		mvwprintw(menu_win,i,0,"|");
		mvwprintw(menu_win,i,x-1,"|");
	}
	wattroff(menu_win, COLOR_PAIR(2));
	wrefresh(menu_win);
}
void pick_Size(WINDOW * menu_win,int y, int x,int gamemodeNum, const char *gameMode){
	resize_Window(menu_win,y,x);
	start_color();
	wattron(menu_win,COLOR_PAIR(1));
	const char *message="Enter in the Boardsize for a NxN Boggle Board and Click Enter!";
	const char *message2 ="(WARNING: If the Boardsize is greater than 20, Only 20x20 of the Board will be shown at a time.)";
	mvwprintw(menu_win,y/5,(x/2)-(strlen(message))/2,"%s",message);
	mvwprintw(menu_win,(y/5)+1,(x/2)-(strlen(message2))/2,"%s",message2);
	wrefresh(menu_win);
	wattroff(menu_win, COLOR_PAIR(1));
	wrefresh(menu_win);
	wattron(menu_win,COLOR_PAIR(1));
//int k;
	//while(1){
	scanf("%d",&boardSize);
	// if (k==0){
	//			mvwprintw(menu_win,y/2,(x/2)-15,"Incorrect Input. Type in an Integer for N!");
		//		wrefresh(menu_win);
			//}
		//	else {
			//	return;
			//}
	//}

return;


}
void print_menu2(WINDOW *menu_win,int y, int x, int highlight){
	int i;
	y=y/2;
	x=x/2;
	mvwprintw(menu_win, y-10,x-30,"%d",highlight);
		for(i = 0; i < board_Size; ++i)
		{	if(highlight == i + 1)
			{	wattron(menu_win,A_REVERSE);
	      wattron(menu_win,COLOR_PAIR(1));
				mvwprintw(menu_win,y-3, x-3, "%s", board_Choice[i]);
				wattroff(menu_win,A_REVERSE);
	      wattroff(menu_win,COLOR_PAIR(1));
			}
			else
				mvwprintw(menu_win,y-3, x-3, "%s", board_Choice[i]);
			++y;
		}
		wrefresh(menu_win);
	}
void resize_Board(WINDOW *board,int y,int x){
	wclear(board);
	wresize(board,y,x);
	init_pair(3,COLOR_RED, COLOR_BLACK);
	const char sentence[]="Use arrow keys to navigate, Press enter to select a character to create a word.";
	const char sentence2[]="Once you have found a word, Press space to score it.";
	const char sentence3[]="You have 180 Seconds!";
	wattron(board, COLOR_PAIR(3));
	mvwprintw(board,1,(x/2)-(strlen(sentence))/2, "%s", sentence);
		mvwprintw(board,2,(x/2)-(strlen(sentence2))/2, "%s",sentence2);
		mvwprintw(board,3,(x/2)-(strlen(sentence3)/2),"%s",sentence3);
	wattroff(board, COLOR_PAIR(3));
	wrefresh(board);
	wattron(board,COLOR_PAIR(2));
	for (int i =5;i<(x-6);){
		mvwprintw(board, 0, i,"BOGGLE ");
		mvwprintw(board, y-1, i,"BOGGLE ");
		i=i+7;
	}
	for (int i=0; i<y; i++){
		mvwprintw(board,i,0,"|");
		mvwprintw(board,i,x-1,"|");
	}
	wattroff(board, COLOR_PAIR(2));
	wrefresh(board);
}
