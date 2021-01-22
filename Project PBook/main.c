#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "phonebook.h"


void main()
{
    int intro1=3;
    while(intro1--)
    {   system("cls");
        intro();
    }
    printf("\n\n\n\t\t\t\t\tPress any KEY to proceed ...");
    getch(); //user enters any character to proceed to main menu
    mainmenu();
}
