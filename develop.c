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

char* createPassword(char array[MAX_PASSWORD + 1])
{
    //initialize variables
    int i;
    char ch;

    printf("Enter password: ");    //prompt user to enter password

    /* each iteration of this loop will get a character
    from user input, and hide each character for privacy, until a valid password is confirmed */
    for(i = 0; i <= MAX_PASSWORD; i++)
    {
        ch = getch(); //get character input from user
        
        if(i < 4 && ch == 10)   //prevent user from confirming password less than 4 characters
        {
            i--;
            continue;
        }
        else if(i == MAX_PASSWORD && ch != 10)  //prevent user from entering more than 24 characters
        {
            i--;
            continue;
        }
        else if(ch == 10)    //confirm password if user presses 'Enter' while password is valid
        {
            break;
        }
        else if (ch == 32 || ch == 9)   //ignore input if user presses 'space' or 'tab'
        {
            i--;
            continue;
        }
        else if (ch == 127)   //remove character if user presses 'backspace', unless there are no characters to delete
        {

            if(i == 0)
            {
                i--;
                continue;
            }
            else if(i > 0)
            {
                i--;
                array[i] = '\0';
                printf("\b");
                i--;
            }
        }
        else    //add character to password array if input is valid and display blank space
        {
            array[i] = ch;
            printf(" ");
        }
    }

    return array;
}

int main()
{
    char password[MAX_PASSWORD + 1];
    createPassword(password);

    printf("\nPassword: %s\n", password);
}
