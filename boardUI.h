void draw();
void print_Board(WINDOW *board, int highlight, int y, int x,char d[20],int z);
void boardControls(WINDOW *board,char d[20]);
int checkValidOption(int highlight, int prevChoice, int allChoices[20],char *word,WINDOW *board);
void printLargeBoard(WINDOW *board, int highlight, int y, int x,char d[]);
