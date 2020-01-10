#include <ncurses.h>
#include <string>
#include <time.h>
using namespace std;

//some global variable storage


int height=20;
int width=20;
int playerX=0;
int playerY=0;
int userInput;
string GAME_STATUS="LOBBY";
char BOX_BLOCK='#';
float GAME_TIME =0.001;
float gameTime=0;
//end of gvs
void prepare();
void drawGameBoard();
void keyboardHandler();
void gameTick();
//main function
int main() {
    prepare();
    while(true) {
        drawGameBoard();
        keyboardHandler();
	if(gameTime>500)
        gameTick();
	if(userInput==-1)gameTime++;
        refresh();
    };
    endwin();
    return 1;
};

//some prepration for ncurses
void prepare() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);
    timeout(1);//wait for user input, else go into next function
};


//just drowing game board
void drawGameBoard() {
    erase();
    for(int i=0; i<height; i++) {
        move(i,0);
        addch(BOX_BLOCK);
        move(i,width+1);
        addch(BOX_BLOCK);
    }
    for(int i=0; i<width+2; i++) {
        move(height,i);
        addch(BOX_BLOCK);

    }
    move(25,25);
    printw("gameTime %i time %f",(char)userInput,gameTime);
    move(playerY,playerX+1);
    addch('A');

}
void keyboardHandler() {
    userInput=getch();
    if(userInput==KEY_RIGHT) {
        if(playerX+1<width)playerX++;
    }
    else if(userInput==KEY_LEFT) {
        if(playerX>0)playerX--;
    }

}
void gameTick() {
    gameTime=0;
   if(playerY+1<height)playerY++;
};
