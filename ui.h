#include <ncurses.h>
int pick_Size(WINDOW *menu_win,int y, int x, int gamemodeNum, const char *gameMode);
void print_menu2(WINDOW *menu_win,int y, int x, int highlight);
void print_menu1(WINDOW *menu_win, int highlight, int y, int x);
int pickGameMode();
void resize_Window(WINDOW *menu_win, int y, int x);
void resize_Board(WINDOW *board, int y, int x);
