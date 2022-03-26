#include <stdio.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <ncurses.h>
#include <locale.h>
#include <string.h>
#define MAXCHAR 100

int moveToLineAbove();
void moveToLineBelow();
int main(int argc, char *argv[] );
void setupWindow();
char mchar(int number,char character[]);
void moveCursor(int x,int y);
void insertChar(int insertPos,char character);
void refreshBuffer();
void enterEntered();
void characterEntered(int chNum);
void backspaceEntered();
void upArrowEntered();
void downArrowEntered();
void leftArrowEntered();
void rightArrowEntered();
void appendChar(char c);
void debug();
void debugmsg(char* msg);
void setupCurses();
void openFile(char *argv);
void characterGet(char *argv);
void saveFile(char *argv);
void updateLines();
int getLinesSize();

int x = 0;
int charLineCount = 0;
int y = 1;
int debugX = 0;
int debugY = 16;

int linesArraySize;
int bufferPos = -1;
int bufferLength = 0;
char buffer[10000];
int lines[1000];
FILE *fp;