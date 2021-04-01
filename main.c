#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#define TOTAL_HOURS 124
#define MAX_PASSWORD 24

//function prototypes
void printMainMenuHeading();
int getSelection();
int createNewStudent();
void printNewStudentHeading();
int getch(void);
char* createPassword(char array[MAX_PASSWORD + 1]);
void emptyPassword();

//course structure
typedef struct
{
    char prefix[10];
    int num;
    float hours;
    int grade;

} course;

//transcript structure
typedef struct
{
    course arr_course[100];
    float hours_earned;
    float quality_points_earned;
    float gpa;
    float percentage_complete;

} transcript;

//student structure
typedef struct
{
    char first_name[20];
    char last_name[20];
    char wNum[8];
    char password[25];
    char classification[10];
    char concentration[20];
    transcript t1;

} student;

//main function
int main()
{
    int selection;
    int quit_check;

    //run main menu on infinite loop until user selects quit
    while(1)
    {
        system("clear");
        printMainMenuHeading();

        printf("1) New Student\n");
        printf("2) View my Records\n");
        printf("3) Quit\n");

        selection = getSelection();

        switch(selection)
        {
        //option 1 lunches new stuent registration
        case 1:
            system("clear");
            
            quit_check = createNewStudent();
            
            switch(quit_check)
            {
            //return to main menu
            case 1:
                break;

            //terminate program
            case 0:
                system("clear");
                printf("Goodbye!\n");
                sleep(3);
                system("clear");
                return 0;
            }
            break;
            
        //option 2 launches student login
        case 2:
            system("clear");
            printMainMenuHeading();
            printf("You chose option 2!\n");
            sleep(3);
            break;

        //option 3 terminates program
        case 3:
            system("clear");
            printf("Goodbye!\n");
            sleep(3);
            system("clear");
            return 0;
        
        //invaild inputs relaunches main menu
        default:
            system("clear");
            printMainMenuHeading();
            printf("Invalid input!\n");
            sleep(3);
            break;
        }
    }
}

//function to display main menu heading
void printMainMenuHeading()
{
    printf("_______________________________________________\n\n");
    printf("               STUDENT RECORDS                 \n");
    printf("_______________________________________________\n\n");
}

//function that returns user selection as integer for menu system
int getSelection()
{
    int i;

    printf("\nMake a selection: ");
    scanf("%d", &i);

    return i;
}

//function to get data from new student
int createNewStudent()
{
    student student1;
    int pass_comp, selection, i;
    char password_model[MAX_PASSWORD + 1];
    char confirm_pass_model[MAX_PASSWORD + 1];

    printNewStudentHeading();

    //get full name
    printf("Welcome New Student! Please enter your first\n");
    printf("and last name.\n\n");
    printf("First name: ");
    scanf("%s", student1.first_name);
    printf("Last name: ");
    scanf("%s", student1.last_name);

    system("clear");
    printNewStudentHeading();

    //get w-number
    printf("Hello %s, what is your W-number?\n\n", student1.first_name);
    printf("W-Number: W");
    scanf("%s", student1.wNum);
    
    //create password model
    system("clear");
    printNewStudentHeading();
    printf("Please create a password (4 - 24 characters)\n");
    printf("Note - passwords are case sensitive\n\n");
    printf("Password: ");
    createPassword(password_model);

    //confirm password model
    system("clear");
    printNewStudentHeading();
    printf("Please create a password (4 - 24 characters)\n");
    printf("Note - passwords are case sensitive\n\n");
    printf("Confirm Password: ");
    createPassword(confirm_pass_model);

    //check if password models match
    pass_comp = strcmp(confirm_pass_model, password_model);

    while(pass_comp != 0)
    {
        //print error message
        system("clear");
        printNewStudentHeading();
        printf("Those passwords didn't match.. Please try again");
        sleep(2);

        //empty password arrays if they do not match
        emptyPassword(password_model);
        emptyPassword(confirm_pass_model);

        //re-create and verify password
        system("clear");
        printNewStudentHeading();
        printf("Please create a password (4 - 24 characters)\n");
        printf("Note - passwords are case sensitive\n\n");
        printf("Password: ");
        createPassword(password_model);

        //confirm password model
        system("clear");
        printNewStudentHeading();
        printf("Please create a password (4 - 24 characters)\n");
        printf("Note - passwords are case sensitive\n\n");
        printf("Confirm Password: ");
        createPassword(confirm_pass_model);

        pass_comp = strcmp(confirm_pass_model, password_model);
    }

    //copy confirmed password model to student password
    strcpy(student1.password, confirm_pass_model);

    //display all data that has been confirmed
    printf("\n%s\n%s\nW%s\n%s\n", student1.first_name, student1.last_name, student1.wNum, student1.password);
    sleep(3);

    return 1;
}

//function to display new student heading
void printNewStudentHeading()
{
    printf("_______________________________________________\n\n");
    printf("                  NEW STUDENT                  \n");
    printf("_______________________________________________\n\n");
}

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

// this function populates an array to create a password
char* createPassword(char array[MAX_PASSWORD + 1])
{
    //initialize variables
    int i;
    char ch;

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

//deletes all elements of password array
void emptyPassword(char array[MAX_PASSWORD + 1])
{
    int i;
    for(i = 0; i <= MAX_PASSWORD; i++)
    {
        array[i] = '\0';
    }
}