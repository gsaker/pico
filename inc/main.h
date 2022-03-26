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
void readChar(char c);
void debug();
void debugmsg(char* msg);
void setupCurses();
void openFile(char *argv);
void characterGet(char *argv);
void saveFile(char *argv);

int x = 0;
int charCount = 0;
int y = 1;
int dx = 0;
int dy = 16;
int c;
int size;
int pos = -1;
int bufferLength = 0;
char buffer[10000];
int lines[1000];
FILE *fp;