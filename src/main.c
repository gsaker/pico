#include <main.h>
// gcc -I inc src/main.c -lcurses -o bin && ./bin out.txt
int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "en_US.UTF-8");
    initscr();
    noecho();
    setupWindow(argv[1]);
    fp = fopen(argv[1], "r");
    while ((c = getc(fp)) != EOF)
    {
        readChar(c);
    }
    move(y, x);
    while (true)
    {
        int chNum = getch();
        if (chNum == '\\')
        {
            int chNum = getch();
            if (chNum == 'd')
            {
                debug();
            }
            if (chNum == 's')
            {
                debugmsg("Saving");
                FILE *file = fopen(argv[1], "w");
                int results = fputs(buffer, file);
                if (results == EOF)
                {
                    printw("ERROR!");
                }
                fclose(file);
            }
        }
        else if (chNum == 10)
        {
            enterEntered();
        }
        else if (chNum == '\033')
        {
            getch();
            switch (getch())
            {
            case 'A':
                upArrowEntered();
                break;
            case 'B':
                downArrowEntered();
                break;
            case 'C':
                rightArrowEntered();
                break;
            case 'D':
                leftArrowEntered();
                break;
            }
        }
        else if (chNum == 127)
        {
            backspaceEntered();
        }
        else
        {
            // printw("%d",chNum);
            characterEntered(chNum);
        }
    }
}
void readChar(char c)
{
    pos += 1;
    buffer[pos] = c;
    printw("%c", c);
    
    bufferLength += 1;
    char ch = c;
    if (ch == '\n')
    {
        y += 1;
        x = 0;
        //printw(" XYPC:%d%d%d%c ",x,y,pos,buffer[pos]);
    }
    else
    {
        //printw(" XPC:%d%d%c ",x,pos,buffer[pos]);
        x += 1;
    }
}
void characterEntered(int chNum)
{
    insertChar(pos, chNum);
    bufferLength += 1;
    x += 1;
    pos += 1;
    refreshBuffer();
    int currentPos;
}
void enterEntered()
{
    printw("H");
    insertChar(pos, '\n');
    bufferLength += 1;
    pos += 1;
    y += 1;
    x = 0;
    refreshBuffer();
    move(y, 0);
    refresh();
}
void backspaceEntered()
{
    x -=1;
    if (x<=-1)
    {
        x = 0;
        refresh();

    }
    int index = pos-1;
    int i;
    for (i = index; i < bufferLength - 1; i++)
    {
        buffer[i] = buffer[i + 1];
    }
        pos -= 1;
    move(y, x);
    refreshBuffer();
    }
void upArrowEntered()
{
    move(y - 1, 0);
    x = 0;
    y -= 1;
    refresh();
    moveToLineAbove();
}
void downArrowEntered()
{
    move(y + 1, 0);
    x = 0;
    y += 1;
    refresh();
    moveToLineBelow();
}
void leftArrowEntered()
{
    if (x == 0)
    {
        refresh();
    }
    else
    {  
    pos -= 1;
    move(y, x - 1);
    x -= 1;
    // }
    refresh();
    }
}
void rightArrowEntered()
{
    if (buffer[pos] == '\n')
    {
        pos += 1;
        move(y+1,0);
        x=0;
        y+=1;
        refresh();
    }
    else{
    pos += 1;
    move(y, x + 1);
    x += 1;
    //}
    // refreshBuffer();
    refresh();
    }
}
void debug()
{
    move(15, 0);
    printw("XY:%d%d", x, y);
    printw("P:%d:%c", pos,buffer[pos]);
    move(y, x);
}
void debugmsg(char* msg){
    move(dy,dx);
    printw(msg);
    dx += strlen(msg);
    move(y,x);
}
void refreshBuffer()
{
    move(1, 0);
    clrtobot();
    printw("%s", buffer);
    move(y, x);
    refresh();
}
void insertChar(int insertPos, char character)
{
    int count;
    for (count = bufferLength - 1; count >= insertPos - 1; count--)
    {
        buffer[count + 1] = buffer[count];
    }
    buffer[insertPos] = character;
}
int moveToLineAbove()
{
    bool foundNewLineUp = false;
    bool normalChar = false;

    if (buffer[pos] == '\n')
    {
        pos -= 1;
        while (foundNewLineUp != true)
            {
                if (buffer[pos] == '\n')
                {
                    pos += 1;
                    foundNewLineUp = true;
                    return 0;
                }
                else if(pos == 0){
                    foundNewLineUp = true;
                    return 0;
                }
                else
                {
                    pos -= 1;
                }
            }
    
    }
    
    while (foundNewLineUp != true)
    {
        if (buffer[pos] == '\n')
        {
            pos -= 1;
            foundNewLineUp = false;
            while (foundNewLineUp != true)
            {
                if (buffer[pos] == '\n')
                {
                    pos += 1;
                    foundNewLineUp = true;
                }
                else if(pos == 0){
                    foundNewLineUp = true;
                }
                else
                {
                    pos -= 1;
                }
            }
        }
        else
        {
            pos -= 1;
        }
    }
    refresh();
}
void moveToLineBelow()
{
    bool foundNewLineDown = false;
    while (foundNewLineDown != true)
    {
        if (buffer[pos] == '\n')
        {
            pos += 1;
            foundNewLineDown = true;
        }
        else
        {
            pos += 1;
        }
    }
    refresh();
}

void setupWindow(char *argv)
{
    int row, col;
    getmaxyx(stdscr, row, col);
    int numToPrint = col - (strlen(argv) + 19);
    printw("-- ");
    printw("pico 0.1 -- ");
    printw("%s --", argv);
    mchar(numToPrint, "-");
}

char mchar(int number, char character[])
{
    int i;
    for (i = 0; i <= number; i++)
    {
        printw("%s", character);
    }
    return (0);
}