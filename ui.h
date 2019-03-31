#include <ncurses.h>
void pick_Size(WINDOW *menu_win,int y, int x, int gamemodeNum, const char *gameMode);
void print_Size_Menu(WINDOW *menu_win,int y, int x, int highlight);
void print_Game_Menu(WINDOW *menu_win, int highlight, int y, int x);
void pickGameMode();
void resize_Window(WINDOW *menu_win, int y, int x);
void resize_Board(WINDOW *board, int y, int x);
