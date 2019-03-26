void draw();
void print_Board(WINDOW *board, int highlight, int y, int x,char d[]);
void boardControls(WINDOW *board,char d[]);
int checkValidOption(int highlight, int prevChoice, int allChoices[],char *word,WINDOW *board);
void printLargeBoard(WINDOW *board, int highlight, int y, int x,char d[], int charIndex);
