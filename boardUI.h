int draw();
void print_Board(WINDOW *board, int highlight, int y, int x,char d[]);
int boardControls(WINDOW *board,char d[]);
int checkValidOption(int highlight, int prevChoice, int allChoices[],char *word,WINDOW *board,int y,int x);
void printLargeBoard(WINDOW *board, int highlight, int y, int x,char d[], int charIndex);
int endgame(WINDOW *board,int num_Games,int y,int x);
