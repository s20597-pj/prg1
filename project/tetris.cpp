#include <ncurses.h>
#include <string>
using namespace std;
const char gameBlock='#';
int gameTime=0;
int userInput=0;
unsigned int width=10;
unsigned int height=20;
int playerX=0;
int playerY=0;
int currentRotation=1;
int currentTetromino=0;
char tetrominoChars[7] = {'I','J','L','O','S','T','Z'};
string tetromino_I[4]= {"10111213","02122232","10111213","02122232"};
string tetromino_J[4]= {"10111222","01112120","00101112","21110102"};
string tetromino_L[4]= {"20101112","00011121","10111202","01112122"};
string tetromino_O[4]= {"11122122","11122122","11122122","11122122"};
string tetromino_S[4]= {"20211112","01111222","20211112","01111222"};
string tetromino_T[4]= {"21101112","10011121","01101112","01111221"};
string tetromino_Z[4]= {"10112122","02111221","10112122","02111221"};
int normalizedX[4];
int normalizedY[4];
string allTetrominos[7][4] = {tetromino_I,tetromino_J,tetromino_L,tetromino_O,tetromino_S,tetromino_T,tetromino_Z};
int gameMap[28][18]= {-1};
bool gameOver=false;


void prepare();
void draw();
void keyboardHandler();
void gameTick();
void drawBoard();
void drawCurrentTetromino();
void drawBlocksInsideBoard();
void setNormalizedValues();
void fillMap();
void drawGameMap();
bool playerCanMoveRight();
bool playerCanMoveLeft();
bool playerCanMoveDown();
bool playerCanRotate();
bool playerHaveFreeSpaceOnRight(int passNormalizedY[], int passNormalizedX[]);
bool playerHaveFreeSpaceOnLeft(int passNormalizedY[], int passNormalizedX[]);
bool playerHaveFreeSpaceOnBottom(int passNormalizedY[], int passNormalizedX[]);
bool playerHaveFreeSpaceOnTop(int passNormalizedY[], int passNormalizedX[]);
void tetrominoTouchFloor();
void resetPlayer();
int main() {
    prepare();
    while(!gameOver) {
        setNormalizedValues();
        draw();
        keyboardHandler();
        if(gameTime>500)
            gameTick();
        if(userInput==-1)gameTime++;
        refresh();
    };
    endwin();
    return 1;
};

void prepare() {
    fillMap();
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);
    timeout(1);//wait for user input, else go into next function
};
void fillMap() {
    for(int i=0; i<28; i++) {
        for(int j=0; j<18; j++) {
            gameMap[i][j]=-1;
        }
    }
}
void setNormalizedValues() {
    string currentTetrominoTMP = allTetrominos[currentTetromino][currentRotation];
    for(int i=0; i<currentTetrominoTMP.length()/2; i++) {
        int pos = i*2;
        string y=currentTetrominoTMP.substr(pos,1);
        string x=currentTetrominoTMP.substr(pos+1,1);
        normalizedX[i] = stoi(x);
        normalizedY[i]  = stoi(y);
    }
}
void draw() {
    erase();
    drawBoard();
    drawGameMap();
    drawCurrentTetromino();
    refresh();
}
void drawBoard() {
    for(int i =0; i<20; i++) {
        move(i,10);
        addch(gameBlock);
    }
};
void drawGameMap() {
    for(int i=3; i<24; i++) {
        for(int j=3; j<14; j++) {
            move(i-3,j-3);
            if(gameMap[i][j]!=-1) {
                addch(gameMap[i][j]);
            }
        }
    }

    for(int i=0; i<28; i++) {
        for(int j=3; j<18; j++) {
            move(i,j+50);
            printw("%i",gameMap[i][j]+45);
        }
    }
}
void drawCurrentTetromino() {
    for(int i=0; i<4; i++) {
        move(playerY+normalizedY[i],playerX+normalizedX[i]);
        addch(tetrominoChars[currentTetromino]);
        move(5,25);
        printw("x %i y %i",playerX,playerY);
        move(6,25);
        printw("normalizedY 1 %i 2 %i 3 %i 4 %i",normalizedY[0],normalizedY[1],normalizedY[2],normalizedY[3]);
        move(7,25);
        printw("normalizedX 1 %i 2 %i 3 %i 4 %i",normalizedX[0],normalizedX[1],normalizedX[2],normalizedX[3]);
    }
}
void gameTick() {
    clear();
    gameTime=0;
    if(playerCanMoveDown()&&!playerHaveFreeSpaceOnBottom(normalizedY,normalizedX)) {
        playerY++;
    }
    else {
        tetrominoTouchFloor();
        resetPlayer();
    }

};
void resetPlayer() {
    playerX=0;
    playerY=0;
}
void tetrominoTouchFloor() {
    for(int i=0; i<4; i++) {
        gameMap[normalizedY[i]+playerY+3][normalizedX[i]+playerX+3]=tetrominoChars[currentTetromino];
    }
}
bool playerCanMoveRight() {
    for(int i=0; i<4; i++) {
        if(normalizedX[i]+playerX+1>=width) {
            return false;
        };
    }
    return true;
};
bool playerCanMoveLeft() {
    for(int i=0; i<4; i++) {
        if(normalizedX[i]+playerX-1<0) {
            return false;
        };
    }
    return true;
};
bool playerCanMoveDown() {
    for(int i=0; i<4; i++) {
        if(normalizedY[i]+playerY+1>=height) {
            return false;
        };
    }
    return true;
};
bool playerHaveFreeSpaceOnRight(int passNormalizedY[], int passNormalizedX[]) {
    for(int i=0; i<4; i++) {
        if(gameMap[passNormalizedY[i]+playerY+3][passNormalizedX[i]+playerX+1+3]!=-1) {
            return true;
        }
    }
    return false;
}
bool playerHaveFreeSpaceOnLeft(int passNormalizedY[], int passNormalizedX[]) {
    for(int i=0; i<4; i++) {
        if(gameMap[passNormalizedY[i]+playerY+3][passNormalizedX[i]+playerX-1+3]!=-1) {
            return true;
        }
    }
    return false;
}
bool playerHaveFreeSpaceOnBottom(int passNormalizedY[], int passNormalizedX[]) {
    for(int i=0; i<4; i++) {
        if(gameMap[passNormalizedY[i]+playerY+1+3][passNormalizedX[i]+playerX+3]!=-1) {
            return true;
        }
    }
    return false;
}
bool playerHaveFreeSpaceOnTop(int passNormalizedY[], int passNormalizedX[]) {
    for(int i=0; i<4; i++) {
        if(gameMap[passNormalizedY[i]+playerY-1+3][passNormalizedX[i]+playerX+3]!=-1) {
            return true;
        }
    }
    return false;
}
bool playerCanRotate() {
    string currentTetrominoTMP = allTetrominos[currentTetromino][(currentRotation+1)%4];
    int tmpNormalizedArrX[4]= {};
    int tmpNormalizedArrY[4]= {};
    for(int i=0; i<currentTetrominoTMP.length()/2; i++) {
        int pos = i*2;
        string y=currentTetrominoTMP.substr(pos,1);
        string x=currentTetrominoTMP.substr(pos+1,1);
        tmpNormalizedArrX[i] = stoi(x);
        tmpNormalizedArrY[i]  = stoi(y);
    }
    if(!playerHaveFreeSpaceOnBottom(tmpNormalizedArrY,tmpNormalizedArrX)&&!playerHaveFreeSpaceOnLeft(tmpNormalizedArrY,tmpNormalizedArrX)&&!playerHaveFreeSpaceOnRight(tmpNormalizedArrY,tmpNormalizedArrX)&&!playerHaveFreeSpaceOnTop(tmpNormalizedArrY,tmpNormalizedArrX)) {
        for(int i=0; i<4; i++) {
            if(tmpNormalizedArrY[i]+playerY>=height || tmpNormalizedArrX[i]+playerX<0 || tmpNormalizedArrX[i]+playerX>width-1) {
                return false;
            }
        }
    }

    return true;
};
void keyboardHandler() {
    userInput=getch();
    if(userInput==KEY_RIGHT) {
        if(playerCanMoveRight()&&!playerHaveFreeSpaceOnRight(normalizedY,normalizedX)) {
            playerX++;
        };
    }
    else if(userInput==KEY_LEFT) {
        if(playerCanMoveLeft()&&!playerHaveFreeSpaceOnLeft(normalizedY,normalizedX)) {
            playerX--;
        };
    }
    else if(userInput==KEY_DOWN) {
        if(playerCanMoveDown()&&!playerHaveFreeSpaceOnBottom(normalizedY,normalizedX)) {
            playerY++;
        };
    }
    else if(userInput==KEY_UP) {
        if(playerCanRotate()) {
            currentRotation=(currentRotation+1)%4;
        };
    }
    else if(userInput==102) {
        currentTetromino=(currentTetromino+1)%7;
    }

}
