#include <ncurses.h>
#include <string>
#include <ctime>
using namespace std;
const char gameBlock='#';
const int pointsForLine=10;
int gameTime=0;
int userInput=0;
int points=0;
unsigned int width=10;
unsigned int height=20;
int playerX=0;
int nextTetromino=0;
int playerY=-1;
int currentRotation=0;
int currentTetromino=0;
int comboMultiplayer=1;
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
int gameMap[26][16]= {-1};
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
void checkForGameOver();
void checkForLine();
void moveMapOneDown(int startPoint);
bool playerCanMoveRight();
bool playerCanMoveLeft();
bool playerCanMoveDown();
bool playerCanRotate();
void checkForLines();
void addPoints();
void drawNextTetromino();
void randomizeNextTetromino();
bool checkLine(int i);
void destroyLine(int i);
bool playerHaveFreeSpaceOnRight(int passNormalizedY[], int passNormalizedX[]);
bool playerHaveFreeSpaceOnLeft(int passNormalizedY[], int passNormalizedX[]);
bool playerHaveFreeSpaceOnBottom(int passNormalizedY[], int passNormalizedX[]);
bool playerHaveFreeSpaceOnTop(int passNormalizedY[], int passNormalizedX[]);
void tetrominoTouchFloor();
void resetPlayer();
int main() {
	    prepare();
	        while(true) {
				 setNormalizedValues();
				         if(!gameOver)draw();
					         keyboardHandler();
						         if(gameTime>100)
								             gameTick();
							         if(userInput==-1)gameTime++;
								 		move(0,2);
												if(gameOver)printw("GAMEOVER");
												        refresh();
														};
		    return 1;
};

void prepare() {
	srand(time(NULL));
	    fillMap();
	    	currentTetromino=(rand() % 7);
			randomizeNextTetromino();
			    initscr();
			        noecho();
				    cbreak();
				        keypad(stdscr, TRUE);
					    curs_set(0);
					        timeout(5);//wait for user input, else go into next function
};
void fillMap() {
	    for(int i=0; i<26; i++) {
		            for(int j=0; j<16; j++) {
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
			drawNextTetromino();
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
	    	move(8,30);
			printw("Score: %i",points);
}
void drawNextTetromino(){
		string nextTetrominoTMP = allTetrominos[nextTetromino][0];
			move(3,30);
				  for(int i=0; i<4; i++) {
					  	          int pos = i*2;
							  		string y=nextTetrominoTMP.substr(pos,1);
									        string x=nextTetrominoTMP.substr(pos+1,1);
										        move(3+stoi(y),30+stoi(x));
											        addch(tetrominoChars[nextTetromino]);
												    }
}
void drawCurrentTetromino() {

	    for(int i=0; i<4; i++) {
		            move(playerY+normalizedY[i],playerX+normalizedX[i]);
			            addch(tetrominoChars[currentTetromino]);
				        }
}
void randomizeNextTetromino(){
		nextTetromino=(rand() % 7);
}
void gameTick() {
	    clear();
	        gameTime=0;
		    if(playerCanMoveDown()&&!playerHaveFreeSpaceOnBottom(normalizedY,normalizedX)) {
			            playerY++;
				        }
		        else {
				        tetrominoTouchFloor();
							checkForLines();
									checkForGameOver();
									        resetPlayer();
										    }

};
void checkForLines(){
		for(int i=0;i<24;i++){
					if(checkLine(i)){
									destroyLine(i);
												comboMultiplayer=(comboMultiplayer+1)*2;
															moveMapOneDown(i);
																		addPoints();
																				}
						}
			comboMultiplayer=0;
}
bool checkLine(int i){
		for(int j=3;j<13;j++){
					if(gameMap[i][j]==-1){return false;}
						}
			return true;
}
void checkForGameOver(){
		for(int i=3;i<24;i++){
					if(gameMap[2][i]!=-1){
								gameOver=true;
										}
						}
}
void destroyLine(int i){
		for(int j=3;j<14;j++){
					gameMap[i][j]=-1;
						}
			}
void resetPlayer() {
	    playerX=0;
	        playerY=-1;
			currentRotation=0;
				currentTetromino=nextTetromino;
					randomizeNextTetromino();
}
void addPoints(){
		points=(pointsForLine*comboMultiplayer)+points;
}
void tetrominoTouchFloor() {
	    for(int i=0; i<4; i++) {
		            gameMap[normalizedY[i]+playerY+3][normalizedX[i]+playerX+3]=tetrominoChars[currentTetromino];
			        }
}
void moveMapOneDown(int startPoint){
		 for(int i=startPoint; i<3; i=i-1) {
			         for(int j=3; j<14; j++) {
					 			gameMap[i][j]=gameMap[i+1][j];
										}}
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
