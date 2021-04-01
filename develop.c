#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#define MAX_PASSWORD 24

/* reads from keypress, doesn't echo
this snippet imulates getch() from conio.h
(not available for gcc compiler) */
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

int main(void)
{
    int i;
    num_options = 4;
    for(i = 0; i < num_options + 1; i++)
    {
        switch(i)
        {
            case 0:
                printf("\tOption1\n");
                getch();
                
            case 1:
                
               
                
