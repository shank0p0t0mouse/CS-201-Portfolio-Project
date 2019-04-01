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
extern int gamemode;
int score[30]; //Keeps track of the score from current and previous games.
int num_Games=0; //Keeps track of the number of games that have been played.
int farUp; // For when the board size is bigger than 21. Keeps track of which rows and columns should be shown.
int farDown; //""
int farRight; //""
int farLeft; //""
int player_Num; //Keeps track of which player's turn it is for player vs. player.
char word[30]; //Stores the characters that the user inputs until they click space.
int player1_Score;
int player2_Score;


 int draw(){ //Function that does some of the work before the game begins.
  int size=boardSize*boardSize;
  char *d; //Holds all characters of the board.
  d=(char*)malloc(size);
  printf("%s",d);
  const char *dice[25]={ //Represent 25 valid boggle dice.
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
  for (int i=0; i<boardSize*boardSize; i++){ //Randomly selects letters from dice depending on the time.
    n=rand()%6;
    interval=i%(25);
    d[i]= dice[interval][n]; //d holds all the characters for the board. They are placed in the array here.
  }
  WINDOW *board;
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
  board = newwin(y, x, 0, 0);
  resize_Board(board, y ,x);
  wrefresh(board);
  farLeft=1;
  farRight=20;
  farUp=1;
  farDown=20;
  int game;
  wrefresh(board);
  if (gamemode==1){
    game = boardControls(board,d);
}
if (gamemode==2){
  game = boardControls(board,d);
  ++player_Num;
}
num_Games++;
return game;
}

int boardControls(WINDOW *board, char d[]){
  int y,x;
  int c=0;//Keeps track of what the user inputs from the keyboard.
  getmaxyx(stdscr, y, x);
  start_color();
  init_pair(4,COLOR_CYAN,COLOR_BLACK);
  init_pair(3,COLOR_RED,COLOR_BLACK);
  int movement=boardSize; //Used for up and down movements across the board.
  int allChoices[100]; //Keeps track of the number of the choice in the board. For example if the upper left character is selected, allChoices stores 1.
  char wordList[500][200]; //Stores all words inputted by the user.
  int highlight=1; //Used by the program to know which character to highlight and when a character is selected, its location on the board.
  int check=0; //Used to check if a selection in the board is a valid boggle movement. 1 represents false and 0 represents valid.
  int drawx=(x)-(20*4); //Mainly used to know where to move the cursor to when before a wclrtobot is called.
  int drawy=y-(20*2); //Same as drawy.
  int word_Num=0; //Keeps track of how many words have been selected by the user.
  int choice=0; //Choice is equal to highlight and is used to know what character is selected in the board.
  int k; //Keeps track of the string length of the word as the user adds characters to it.
  int wordScore[100]; //Keeps track of the score for each word inputted by the user.

  keypad(board,TRUE);
  wattron(board,COLOR_PAIR(3));
  if (gamemode==2){
    mvwprintw(board,(y/2)-2,(x/2)-8,"Player %d's Turn",player_Num+1);
  }
  do {
    mvwprintw(board,y/2,(x/2)-19,"Press The Space Bar to Start the Game."); //Part where the player must click space to start the game.
    wrefresh(board);
  }while((c=wgetch(board)!=32));

  wattroff(board,COLOR_PAIR(3));
  wclear(board);
  resize_Board(board,y,x);
  wattron(board,COLOR_PAIR(3));
  mvwprintw(board,2,4,"WORDS:");
  wattroff(board,COLOR_PAIR(3));
  int charIndex=0; //Used for when the board is bigger than 20. Keeps track of the character in d that the board should draw from.
  if(boardSize<21)
    print_Board(board,highlight, y,x,d);
      else
        printLargeBoard(board,highlight, y, x,d,charIndex);
  time_t start,end; //Variables used for timer.
  int elapsed; //The difference between start and end.
  time(&start); //Gets the start value of when the game starts.
  do{ //Beginning of while loop that starts the game. Condition at the bottom is elapsed<180.
    wattron(board,COLOR_PAIR(3));
    time(&end);
    elapsed = difftime(end,start);
    mvwprintw(board,4,x-20,"Time elapsed: %d",elapsed); //Refreshs the timer.
    wattroff(board, COLOR_PAIR(3));
    wrefresh(board);
    c = wgetch(board); //Gets user input from keyboard.
    switch(c)
    {	case KEY_UP:
      wrefresh(board);
      if((highlight-movement)>0){
          highlight = (highlight - movement);
          if(highlight<=(boardSize*(farUp-1))){ //If loop for when the board size is greater than 20. Checks to see if the board should be shifted.
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
      if ((highlight+movement)<=(boardSize*boardSize)){
        highlight=highlight+(movement);
        if (highlight>(boardSize*farDown)){ //If loop for when the board size is greater than 20. Checks to see if the board should be shifted.

          farDown++;
          farUp++;
          charIndex=((farUp-1)*(boardSize))+farLeft-1;

          wmove(board,drawy,drawx);
          wclrtobot(board);
          resize_Board(board,y,x);

        }

}

        break;
      case KEY_RIGHT:
      wrefresh(board);
      if(boardSize>20){
        if ((highlight%boardSize)!=0){
          if (((highlight-farRight)%boardSize)==0){ //If loop for when the board size is greater than 20. Checks to see if the board should be shifted.
            farRight++;
            farLeft++;
            charIndex=((farUp-1)*(boardSize))+farLeft-1;
            wmove(board,drawy,drawx);
            wclrtobot(board);
            resize_Board(board,y,x);
        }
            highlight++;
      }
    }
      else{
        if ((highlight%boardSize)!=0){
          highlight++;
      }
    }
        break;

        case KEY_LEFT:
        wrefresh(board);
        if (boardSize>20){
          if ((highlight%boardSize)!=1){
            if (((highlight-farLeft)%boardSize)==0){ //If loop for when the board size is greater than 20. Checks to see if the board should be shifted.
              farLeft--;
              farRight--;
              charIndex=((farUp-1)*(boardSize))+farLeft-1;
              wmove(board,drawy,drawx);
              wclrtobot(board);
              resize_Board(board,y,x);
          }
          --highlight;
        }
      }
        else {
          if ((highlight%boardSize)!=1){
            --highlight;
        }
      }

        break;
      case 10: //When enter is selected to insert a character.
      check=checkValidOption(highlight, choice,allChoices,word,board,y,x); //Choice is used in the function because it is equal to the previous selected character.
        if (check==1){                                                      // Highlight is used as the recently chosen character and is compared to the position of choice in the function.
          check=0;
          break;
        }
        else{
        choice = highlight;
        allChoices[strlen(word)]=choice;
        wattron(board,COLOR_PAIR(3));
        mvwprintw(board,2,4,"WORDS:");
        wattroff(board,COLOR_PAIR(3));
        k=strlen(word);
        wattron(board,COLOR_PAIR(4));
        if ((d[choice-1]=='u')||(d[choice-1]=='Q')){
          word[k]='Q';
          word[k+1]='U';
          mvwprintw(board, 3+word_Num,4,"%s", word);
        }
        else{
        word[k]=d[choice-1];
        mvwprintw(board, 3+word_Num,4,"%s", word);
      }
      wattroff(board,COLOR_PAIR(4));
    }
        break;

        case 32: //When space is selected to insert a word for scoring.
          wordScore[word_Num]=word_Check(word,word_Num);
          if(wordScore!=0)
          strcpy(wordList[word_Num],word);
          wattron(board,COLOR_PAIR(4));
          for (int i=0; i<strlen(word); i++){
            allChoices[i]=0;
          }
          score[num_Games]=score[num_Games]+wordScore[word_Num];

          mvwprintw(board, 4,(x/2)-8,"TOTAL SCORE: %d",score[num_Games]);
          for(int i=0; i<=word_Num;i++){
          mvwprintw(board, 3+i,4,"%s = %d", wordList[i], wordScore[i]);
        }
          memset(word, '\0', strlen(word));
          wattroff(board,COLOR_PAIR(4));
        word_Num++;
          choice=0;
        break;
    }
    wattron(board,COLOR_PAIR(3));
    mvwprintw(board,2,4,"WORDS:");
    wattroff(board,COLOR_PAIR(3));
    if(word_Num!=0){
      wattron(board,COLOR_PAIR(4));
      mvwprintw(board, 4,(x/2)-8,"TOTAL SCORE: %d",score[num_Games]);
      for(int i=0; i<word_Num;i++){
        mvwprintw(board, 3+i,4,"%s = %d", wordList[i], wordScore[i]);
  }
    wattroff(board,COLOR_PAIR(4));
}
  wattron(board,COLOR_PAIR(3));
  time(&end);
  elapsed = difftime(end,start);
  mvwprintw(board,4,x-20,"Time elapsed: %d",elapsed);
  wattroff(board, COLOR_PAIR(3));
  wrefresh(board);
    if(boardSize<21)
      print_Board(board,highlight, y,x,d);
        else
          printLargeBoard(board,highlight, y, x,d,charIndex);
  }while (elapsed <15); //Adjust this value if you want the game time to be shorter. Default is 180.

  memset(word, '\0', strlen(word));//Used to clear word so that the next game or player doesn't carry over characters already inputted.
  int game=1;
  if (gamemode==1){
    game=endgame(board,num_Games,y,x);
    if (game!=1){
      endwin();
    }
}
  if(player_Num==1){
      game=endgame(board,num_Games,y,x);
      if (game!=1){
        endwin();
      }
    }
  return game;
}
void print_Board(WINDOW *board, int highlightx, int y, int x,char d[]){ //Function that prints the window for when the board size is less than 21.
  int drawx=(x)-(boardSize*4);
  int drawy=y-(boardSize*2);
int charIndex=0; //This local variable of charIndex is used to go through each possible number for the board.
int xx=0; //Keeps up with where each character should be printed on the x axis.
int yy=0; //Keeps up with where each character should be printed on the y axis.
start_color();
init_pair(1, COLOR_GREEN,COLOR_BLACK);
init_pair(5,COLOR_YELLOW,COLOR_BLACK);
wattron(board,COLOR_PAIR(5));
for (int i=1; i<=boardSize;i++){
mvwprintw(board,drawy/2,(drawx/2)+2+xx,"%d",i); //Prints the column numbers.
xx=xx+4;
}
for (int i=1;i<=boardSize;i++){
mvwprintw(board,(drawy/2)+1+yy,(drawx/2)-2,"%d",i); //Prints the row numbers.
yy=yy+2;
}
wattroff(board,COLOR_PAIR(5));
xx=0;
yy=0;
for(int i =0; i<boardSize; i++){
for(int b=0; b<=boardSize; b++){
  mvwprintw(board,(drawy/2)+yy+1, (drawx/2)+xx, "|");
  xx=xx+4;

}
yy=yy+2;
xx=0;
}

xx=2;
yy=1;
  wattron(board,COLOR_PAIR(1));
if (num_Games>0){ //Prints the previous scores for either games for single player or player scores for player vs. player.
  if (gamemode==1){
for (int i=0; i<num_Games;i++){
    mvwprintw(board,y/3,(x-20),"Previous Scores:");
    mvwprintw(board,(y/3)+i+1,(x-20),"Game %d: %d",i+1,score[i]);
}
}
  else if (gamemode==2){
    for (int i=0; i<num_Games;i++){
        mvwprintw(board,y/3,(x-20),"Previous Scores:");
        mvwprintw(board,(y/3)+i+1,(x-20),"Player %d: %d",(i%2)+1,score[i]);
    }
  }
}
  wattroff(board,COLOR_PAIR(1));
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
void printLargeBoard(WINDOW *board, int highlightx, int y, int x,char d[],int charIndex){ //Function to print the menu when the board size is greater than 20.
  int drawx=x-(20*4);
  int drawy=y-(20*2);
  start_color();
  init_pair(5,COLOR_YELLOW,COLOR_BLACK);
  int xx=0; //Keeps up with where each character should be printed on the x axis.
  int yy=0; //Keeps up with where each character should be printed on the y axis.
  wattron(board,COLOR_PAIR(5));
  for (int i=farLeft; i<=farRight;i++){
    mvwprintw(board,drawy/2,(drawx/2)+2+xx,"%d",i); //Prints the number of the columns for the board.
    xx=xx+4;
  }
  for (int i=farUp;i<=farDown;i++){
    mvwprintw(board,(drawy/2)+1+yy,(drawx/2)-2,"%d",i); //Prints the number of the columns for the board.
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
    wattron(board,COLOR_PAIR(1));
    if (num_Games>0){
      if (gamemode==1){
        for (int i=0; i<num_Games;i++){
          mvwprintw(board,y/3,(x-20),"Previous Scores:");
          mvwprintw(board,(y/3)+i+1,(x-20),"Game %d: %d",i+1,score[i]);
        }
      }
      else if (gamemode==2){
        for (int i=0; i<num_Games;i++){
          mvwprintw(board,y/3,(x-20),"Previous Scores:");
          mvwprintw(board,(y/3)+i+1,(x-20),"Player %d: %d",(i%2)+1,score[i]);
    }
  }
}
  wattroff(board,COLOR_PAIR(1));
  yy=yy+2;
  xx=0;
}
  wrefresh(board);
  init_pair(1, COLOR_GREEN,COLOR_BLACK);
  xx=2;
  yy=1;
for (int f=0; f<20; f++){ //Prints all of the characters for the board.
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
int checkValidOption(int highlight, int choice, int allChoices[20], char *word,WINDOW *board,int y,int x){
  start_color();
  init_pair(1,COLOR_RED,COLOR_BLACK);
  if (choice==0){
    return 0;
  }
  wattron(board,COLOR_PAIR(1));
  for(int i=0; i<=strlen(word);i++){ //Checks through previous choices so letters are not reusable.
    if (highlight==allChoices[i]){
      mvwprintw(board, y-3, (x/2)-28, "You can't choose that character! It's already in the word.");
      return 1;
    }
  }
  wattroff(board,COLOR_PAIR(1));
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
int endgame(WINDOW *board,int num_Games,int y,int x){ //Prints the end game menu and shows the result from the game. Prompts the user to either play another game or exit boggle.
  wclear(board);
  wattron(board,COLOR_PAIR(2));
	for (int i =5;i<(x-6);){ //You will notice this for loop and the one below this throughout the code, but it easily maintains the border around the window.
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
  wattron(board,COLOR_PAIR(1));
  if(gamemode==1){
    int highscore=score[num_Games];
  mvwprintw(board,1,(x/2)-4,"GAME OVER");
  mvwprintw(board,2,(x/2)-15,"You Finished With a Score of %d",score[num_Games]);
  for (int i=1; i<=num_Games; i++){
    if (highscore<score[i]){
      highscore=score[i];
    }
  }
  mvwprintw(board,5,(x/2)-15,"Your Highscore is currently: %d",highscore);
}
  else if (gamemode==2){ //Handles scoring for player vs. player and shows who is winning.
    mvwprintw(board,1,(x/2)-4,"GAME OVER");
    mvwprintw(board,2+player_Num-1,(x/2)-17,"Player 1 finished With a Score of %d",score[num_Games-1]);
    mvwprintw(board,2+player_Num,(x/2)-17,"Player 2 finished With a Score of %d",score[num_Games]);
    if(score[num_Games]>score[num_Games-1]){
      mvwprintw(board,6,(x/2)-10, "Player 2 is the winner!");
      player2_Score++;
    }
    else if(score[num_Games]<score[num_Games-1]){
      mvwprintw(board,6,(x/2)-10, "Player 1 is the winner!");
      player1_Score++;
    }
    else if(score[num_Games]==score[num_Games-1]){
      mvwprintw(board,6,(x/2)-7,"There is a Tie!");
    }
    if (player2_Score>player1_Score){
      mvwprintw(board,8,(x/2)-13,"Player 2 is leading %d to %d.",player2_Score, player1_Score);
    }
    else if(player2_Score<player1_Score){
      mvwprintw(board,8,(x/2)-13,"Player 1 is leading %d to %d.",player1_Score, player2_Score);
    }
    else if(player2_Score==player1_Score){
      mvwprintw(board,8,(x/2)-16,"There is currently a tie at %d to %d.",player1_Score, player2_Score);
    }
  }
  wattroff(board,COLOR_PAIR(1));
  wattron(board,COLOR_PAIR(3));
  mvwprintw(board,y/2,(x/2)-40,"Enter 1 Then Enter to Play Another Game or Any Other Number Then Enter to Exit Boggle.");
  wattroff(board,COLOR_PAIR(3));
  wrefresh(board);
  int game;
  scanf("%d",&game);

  return game;
}
