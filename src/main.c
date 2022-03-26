#include <main.h>
// gcc -I inc src/main.c -lcurses -o bin && ./bin out.txt
int main(int argc, char *argv[])
{
    //run ncurses setup
    setupCurses();
    //setup window with file name
    setupWindow(argv[1]);
    //open file and write to buffer
    openFile(argv[1]);
    //run text editor loop
    characterGet(argv[1]);
    //move to start (1,0)
    //y=1 because first row is title
    move(y, x);
}
void appendChar(char c)
{
    bufferPos += 1;
    //ste buffer position to current character from file
    buffer[bufferPos] = c;
    //increment bufferLength
    bufferLength += 1;
    //if character is newline, move to next line
    if (c == '\n')
    {
        y += 1;
        x = 0;
    }
    //otherwise move to next column
    else
    {
        x += 1;
    }
}
void characterEntered(int chNum)
{
    //only runs if character not newline
    //insert character into buffer
    insertChar(bufferPos, chNum);
    //increment values
    bufferLength += 1;
    bufferPos += 1;
    x += 1;
    //rewrite buffer to screen
    refreshBuffer();
    int currentbufferPos;
}
void enterEntered()
{
    //insert character
    insertChar(bufferPos, '\n');
    //gets size of array
    linesArraySize = getLinesSize();
    //clears + update lines array
    updateLines();
    //increment variables
    bufferLength += 1;
    bufferPos += 1;
    y += 1;
    x = 0;
    //refresh buffer to screen
    refreshBuffer();
    //move to start of new line
    move(y, 0);
    
}
void backspaceEntered()
{
    x -= 1;
    if (x <= -1)
    {
        x=0;
            int index = bufferPos - 1;
            int i;
            for (i = index; i < bufferLength - 1; i++)
            {
                buffer[i] = buffer[i + 1];
            }
            bufferPos += lines[y-1]-1;
            moveToLineAbove();
    }
    
    else
    {
        int index = bufferPos - 1;
        int i;
        for (i = index; i < bufferLength - 1; i++)
        {
            buffer[i] = buffer[i + 1];
        }
        lines[y-1] -= 1;
        bufferPos -= 1;
        move(y, x);
        bufferLength -=1;
    }
 

                debug();

    refreshBuffer();
}
void upArrowEntered()
{
    if (y != 1){
    refresh();
    moveToLineAbove();
    }
}
void downArrowEntered()
{
    if (lines[y] != 0){
    move(y + 1, 0);
    x = 0;
    y += 1;
    refresh();
    moveToLineBelow();
}
else{
    debugmsg("No");
}
}
void leftArrowEntered()
{
    if (x == 0)
    {
        refresh();
    }
    else
    {
        bufferPos -= 1;
        move(y, x - 1);
        x -= 1;
        // }
        refresh();
    }
}
void rightArrowEntered()
{
    if (buffer[bufferPos] == '\n')
    {
        if (lines[y] != 0){
        bufferPos += 1;
        move(y + 1, 0);
        x = 0;
        y += 1;
        refresh();
        }
    }
    else
    {
        bufferPos += 1;
        move(y, x + 1);
        x += 1;
        refresh();
    }
}
void debug()
{
    move(15, 0);
    if (buffer[bufferPos] == '\n')
    {
        printw("XY:%d%d", x, y);
        printw("P:%d:\\n", bufferPos);
        printw("L:%d",bufferLength);
        printw(" S:%d",linesArraySize);
                printw(" A:%d,%d,%d,%d,%d,%d",lines[0],lines[1],lines[2],lines[3],lines[4],lines[5],lines[6]);

    }
    else
    {
        printw("XY:%d%d", x, y);
        printw("P:%d:%c", bufferPos, buffer[bufferPos]);
        printw(" L:%d",bufferLength);
        printw(" S:%d",linesArraySize);
        printw(" A:%d,%d,%d,%d,%d,%d",lines[0],lines[1],lines[2],lines[3],lines[4],lines[5],lines[6]);
    }
    move(y, x);
}
void debugmsg(char *msg)
{
    //debug starts at 0,16
    //move to debug location
    move(debugY, debugX);
    //print message
    printw(msg);
    //increment debugX by length of message
    debugX += strlen(msg);
    move(y, x);
}
void refreshBuffer()
{

    move(1, 0);
    clrtobot();
    printw("%s", buffer);
    move(y, x);
    refresh();
}
void insertChar(int insertbufferPos, char character)
{
    int count;
    for (count = bufferLength - 1; count >= insertbufferPos - 1; count--)
    {
        buffer[count + 1] = buffer[count];
    }
    buffer[insertbufferPos] = character;
    lines[y - 1] += 1;
}
int moveToLineAbove()
{
    bool foundNewLineUp = false;
    bool normalChar = false;
    if (buffer[bufferPos] == '\n' && buffer[bufferPos - 1] == '\n')
    {
        bufferLength -=1;
        debug();
        bufferPos -= 2;
        int index = bufferPos + 1;
        int i;
        for (i = index; i < bufferLength - 1; i++)
        {
            buffer[i] = buffer[i + 1];
        }
        while (foundNewLineUp != true)
        {
            if (buffer[bufferPos] == '\n')
            {
                bufferPos += 1;
                foundNewLineUp = true;
            }
            else if (bufferPos == 0)
            {
                foundNewLineUp = true;
            }
            else
            {
                bufferPos -= 1;
            }
        }
    }
    if (buffer[bufferPos] == '\n' && x == 0)
    {
        bufferPos -= 1;
        while (foundNewLineUp != true)
        {
            if (buffer[bufferPos] == '\n')
            {
                // printw("%d",bufferPos);
                bufferPos += 1;
                foundNewLineUp = true;
                move(y - 1, 0);
                x = 0;
                y -= 1;
                refresh();
                return 0;
            }
            else if (bufferPos == 0)
            {
                move(y - 1, 0);
                x = 0;
                y -= 1;
                refresh();
                foundNewLineUp = true;
                return 0;
            }
            else
            {
                bufferPos -= 1;
            }
        }
    }
    else if (buffer[bufferPos] == '\n')
    {
        bufferPos -= 1;
        x -= 1;
    }

    while (foundNewLineUp != true)
    {

        if (buffer[bufferPos] == '\n')
        {
            bufferPos -= 1;
            foundNewLineUp = false;
            while (foundNewLineUp != true)
            {
                if (buffer[bufferPos] == '\n')
                {
                    bufferPos += 1;
                    foundNewLineUp = true;
                }
                else if (bufferPos == 0)
                {
                    foundNewLineUp = true;
                }
                else
                {
                    bufferPos -= 1;
                }
            }
        }
        else
        {
            bufferPos -= 1;
        }
    }
    move(y - 1, 0);
    x = 0;
    y -= 1;
    refresh();
    return 0;
}
void moveToLineBelow()
{
    bool foundNewLineDown = false;
    while (foundNewLineDown != true)
    {
        if (lines[y-1] == 0)
        {

        }
        else if (buffer[bufferPos] == '\n')
        {
            bufferPos += 1;
            foundNewLineDown = true;
        }
        else
        {
            bufferPos += 1;
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
void setupCurses(){
    setlocale(LC_ALL, "en_US.UTF-8");
    initscr();
    noecho();
}
void openFile(char *argv){
    int c;
    fp = fopen(argv, "r");
    while ((c = getc(fp)) != EOF)
    {
        appendChar(c);
    }
    updateLines();
    refreshBuffer();
}
void characterGet(char *argv){
while (true)
    {
        int chNum = getch();
        if (chNum == '\\')
        {
            int chNum = getch();
            if (chNum == 'd')
            {
                //printw("%d",sizeof(lines));
                debug();
            }
            if (chNum == 's')
            {
                
                debugmsg("Saving");
                FILE *file = fopen(argv, "w");
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
             //printw("%d",chNum);
            characterEntered(chNum);
        }
    // refresh to make sure everything is up to date
    refresh();
    }
}
void updateLines(){
    memset(lines, 0, sizeof(lines)); 
    debug();
    int tempLines = 0;
    int currentLine = 0;
    int charNum = 0;
    bool running = true;
    while (running == true){
        debugmsg("E");
        if (charNum == bufferLength){
            running = false;
        }
        if (buffer[charNum] == '\n'){
            tempLines += 1;
            lines[currentLine] = tempLines;
            currentLine += 1;
            tempLines = 0;
        }
        else{
            tempLines += 1;
        }
        charNum++;
    }
}
int getLinesSize(){
    //set up counter variables
    int currentLineCounter = 0;
    bool running = true;
    // calculate size of lines array
    // loops through lines until it finds empty line
    while (running == true){
        if (lines[currentLineCounter] == 0){
            debugmsg("Stop");
            running = false;
        }
        else {
            currentLineCounter++;
        }
    }
    return currentLineCounter;
}
void saveFile(char *argv);