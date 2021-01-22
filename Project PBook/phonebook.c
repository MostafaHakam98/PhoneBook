#include "phonebook.h"
int substring(char s1[], char s2[])
{
  int x=strlen(s1),y=strlen(s2),i=0,j=0;
  for(i=0;i<x;i++)
  {
      if(s1[i]==s2[0])
      {
          for(j=0;j<y;j++)
          {
              if(s1[(i+j)]!=s2[j])
              {
                  break;
              }


          }
            if(j==y)
            {
                return 1;
            }
      }

  }
  return 0;
}
int validate_string(char *s)
{
    int i;
    for(i=0;i<strlen(s);i++)
    {
        if(!( (*(s+i)>47 && *(s+i)<58) || (*(s+i)>64 && *(s+i)<91) || (*(s+i)>96 && *(s+i)<123) || (*(s+i)==32) )) //Anything besides the letters, numbers and spaces will return 0, numbers are from the ascii table
            return 0;
    }
    return 1;
}
int validate_email(char* s)
{
    int count1=0,count2=0,flag1=1;
    char *p=s;
    char tok[20];
    int i=0;
    int y=strlen(s);
    char delim[2]=" ";
    if(flag1)
    {
        while(y--)
        {
            if(*p=='@')
            {
                count1++;
            }
            p++;
        }
        if(count1!=1)
        {
            return 0;
        }
        /*y=strlen(s);
        i=0;
        for(i=0;i<y;i++)
        {
            tok[i]=*s;
            s++;
            if(*s=='@')
            {
                break;
            }
        }
        y=strlen(s);
        int x=strlen(tok);
        i=0;*/
        y=strlen(s);
        if(substring(s,".com\0")||substring(s,".net\0")||substring(s,".org\0")||substring(s,".edu\0")||substring(s,".gov\0"))
        {
                while(y--)
                {
                    if(*s=='.'&&*(s+1)=='.'|| *s=='.'&&*(s+1)=='@' || *s=='.' && *(s-1)=='@')
                    {
                        return 0;
                    }
                    s++;
                }
                return 1;
        }
        else
            return 0;

        /*while(x--)
        {
            if(tok[i]=='.' && tok[i+1]=='.')
            {
                return 0;
            }
            i++;
        }*/
    }
}
int validate_number(char* n)
{
    int flag=1,count=0,j=sizeOfArray;
    while(j--)
    {
        if((strcasecmp(contacts[j].number,n))==0)
        {
            printf("ERROR: Number already exists!\n");
            return 0;
        }
    }
    while(flag)
    {
        if(*n>60)
        {
            flag=0;
            return flag;
        }
        if(*n=='\0')
        {
            return flag;
        }
        n++;
    }
}
int validate_birthday(date bday)
{
    if (bday.year<1800||bday.month>12||bday.month<1||bday.day>31||bday.year>2018)
    {
        return 0;
    }
    if(bday.year%4==0&&bday.year%100!=0 || bday.year%400==0&&bday.year%100==0)
    {
        if(bday.month==2&&bday.day>29)
        {
            return 0;
        }
    }
    else
        if(bday.day>28&&bday.month==2)
        {
            return 0;
        }
    if(bday.month<=7&&bday.month%2==0&&bday.day>30)
        return 0;
    else if(bday.month>7&&bday.month%2&&bday.day>30)
        return 0;
    return 1;

}
void mainmenu() //Main function
{
    system("cls"); //Clears screen
    printf("(1) Load\n(2) Query\n(3) Add\n(4) Delete\n(5) Modify\n(6) Print\n(7) Save\n(8) Quit\n\n\nChoose a number and press ENTER: ");
    char x;
    int i; scanf("%d",&i); //User's option number
    switch(i)
    {
        case(1):check(i);free(contacts);load();secDelay(1);mainmenu();break;
        case(2):check(i);warning();query();printf("PRESS ANY KEY TO PROCEED...");getch();mainmenu();break;
        case(3):check(i);warning();add();secDelay(1);mainmenu();break;
        case(4):check(i);warning();del();secDelay(1);mainmenu();break;
        case(5):check(i);warning();modify();secDelay(1);mainmenu();break;
        case(6):warning();print();secDelay(1);mainmenu();break;
        case(7):check(i);warning();save();secDelay(1);mainmenu();break;
        case(8):quit();break;
        default: //Wrong entry
            while (1)
        {
            system("cls");
            printf("Invalid option.\n");
            printf("Return to Main Menu: <y/n>\n");
            scanf(" %c",&x);
            if (x=='y' || x=='Y') //Back to Main Menu
            {
                mainmenu();
                break;
            }
            else if (x=='n' || x=='N') //Exit Program
                break;
        }
    }
}

void load() //Reads in a file name and loads the phone directory from this file.
{
    sizeOfArray=0; //To avoid duplication after multiple loads
    char name[20]; //file name
    int i=0;
    system("CLS");
    printf("Please enter a file name:\n\nContacts filename: ");
    scanf(" %s",name);
    strcat(name,".txt");
    fptr=fopen(name,"r");
    if (fptr==NULL) //No such file with this name
    {
        system("CLS");
        printf("FILE NOT FOUND!\n");
        secDelay(1);
        load();
        return;
    }
    contacts=(entry *)malloc(1000*sizeof(entry)); //Allocating array of structures containing contacts
    while(!feof(fptr)) //Allocating each contact in a structure
    {
        fscanf(fptr," %[^,],%[^,],%d-%d-%d,%[^,],%[^,],%[^\n]",(contacts[i].first_name),(contacts[i].last_name),&contacts[i].birthdate.day,&contacts[i].birthdate.month,&contacts[i].birthdate.year,contacts[i].address,&contacts[i].email,contacts[i].number);
        sizeOfArray++;
        i++;
    }
    fclose(fptr);
    printf("Loaded Successfully\n");
}

void query() //Multi search function using many fields to search for a contact.
{
    system("cls");
    printf("(1) First Name\n(2) Last Name\n(3) Birthday\n(4) Address\n(5) E-Mail\n(6) Phone Number\n\nChoose the number of the field you want to search with and press ENTER: \n");
    int f=0,l=0,b=0,a=0,m=0,n=0; //One variable for each field
    char x[10]; //To choose a field
    while(1)
    {
        scanf("%s",x);
        if (!strcasecmp(x,"PASS")) //Proceed to search
            break;
        else if(x[0]=='1' || x[0]=='2' || x[0]=='3' || x[0]=='4' || x[0]=='5' || x[0]=='6')
        {
            switch(x[0])
            {
                case('1'):f=1;printf("\nPress 'PASS' to process OR choose another number and press ENTER: \n");break;
                case('2'):l=1;printf("\nPress 'PASS' to process OR choose another number and press ENTER: \n");break;
                case('3'):b=1;printf("\nPress 'PASS' to process OR choose another number and press ENTER: \n");break;
                case('4'):a=1;printf("\nPress 'PASS' to process OR choose another number and press ENTER: \n");break;
                case('5'):m=1;printf("\nPress 'PASS' to process OR choose another number and press ENTER: \n");break;
                case('6'):n=1;printf("\nPress 'PASS' to process OR choose another number and press ENTER: \n");break;
            }
        }
        else
        {
            printf("INVALID OPTION\n"); //Invalid Option
        }
    }

    char first_name[15];
    char last_name[15];
    date birthdate;
    char address[40];
    char email[50];
    char number[20];

    system("cls");
    int id[sizeof(sizeOfArray)/sizeof(int)]; //Create temporary array to copy searched contacts IDs
    memset(id,1,sizeof(id));
    int i;
    if(f) //First name condition
    {
        printf("Please enter first name: ");
        scanf("\n%[^\n]s",&first_name);
        for(i=0;i<sizeOfArray;i++)
        {
            if(strcasecmp(first_name,contacts[i].first_name)) //If the scanned first name doesn't match contact[i]'s first name (Applies for all rest functions)
            {
                id[i]=0; //Elements with i=0 won't be selected
            }
        }
    }
    if(l) //Last name condition
    {
        printf("Please enter last name: ");
        scanf("\n%[^\n]s",&last_name);
        for(i=0;i<sizeOfArray;i++)
        {
            if(strcasecmp(last_name,contacts[i].last_name))
            {
                id[i]=0;
            }
        }
    }
    if(b) //Birthday condition
    {
        printf("Please enter birthday (d m yyyy): ");
        scanf("%d %d %d",&birthdate.day,&birthdate.month,&birthdate.year);
        for(i=0;i<=sizeOfArray;i++)
        {
            if(birthdate.day!=contacts[i].birthdate.day || birthdate.month!=contacts[i].birthdate.month || birthdate.year!=contacts[i].birthdate.year)
            {
                id[i]=0;
            }
        }
    }
    if(a) //Address condition
    {
        printf("Please enter the address: ");
        scanf("\n%[^\n]s",address);
        for(i=0;i<=sizeOfArray;i++)
        {
            if(strcasecmp(address,contacts[i].address))
            {
                id[i]=0;
            }
        }
    }
    if(m) //E-mail condition
    {
        printf("Please enter the E-Mail: ");
        scanf("\n%[^\n]s",email);
        for(i=0;i<=sizeOfArray;i++)
        {
            if(strcasecmp(email,contacts[i].email))
            {
                id[i]=0;
            }
        }
    }
    if(n) //Phone number condition
    {
        printf("Please enter number: ");
        scanf("\n%[^\n]s",number);
        for(i=0;i<=sizeOfArray;i++)
        {
            if(strcasecmp(number,contacts[i].number))
            {
                id[i]=0;
            }
        }
    }

    system("cls");
    printf("Search results: \n\n");
    for(i=0;i<sizeOfArray;i++) //Print contacts with IDs marked with 1 ONLY
    {
        if(id[i])
            printf("ID: (%d)\n%s %s\nPhone Number: %s\nE-mail Address: %s\nAddress: %s\nBirthday: %d-%d-%d\n\n",i+1,contacts[i].first_name,contacts[i].last_name,contacts[i].number,contacts[i].email,contacts[i].address,contacts[i].birthdate.day,contacts[i].birthdate.month,contacts[i].birthdate.year);
    }
}

void add() //Prompts the user field by field for the data of a single contact and adds it to the directory.
{
    system("cls");
    printf("Please enter a new contact first name: ");
    scanf(" %[^\n]s",contacts[sizeOfArray].first_name); //New first name delimited by a new line character (to include spaces)
    int flagFirst=validate_string(contacts[sizeOfArray].first_name);
    while(!flagFirst)
    {
        printf("Invalid character in name!\nPlease enter a proper name(characters beside spaces, letters and numbers are not allowed!): ");
        scanf(" %[^\n]s",contacts[sizeOfArray].first_name);
        flagFirst=validate_string(contacts[sizeOfArray].first_name);
    }
    printf("Please enter a new contact last name: ");
    scanf(" %[^\n]s",contacts[sizeOfArray].last_name); //Last first name delimited by a new line character (to include spaces)
    int flagLast=validate_string(contacts[sizeOfArray].last_name);
    while(!flagLast)
    {
        printf("Invalid character in name!\nPlease enter a proper name(characters beside spaces, letters and numbers are not allowed!): ");
        scanf(" %[^\n]s",contacts[sizeOfArray].last_name);
        flagLast=validate_string(contacts[sizeOfArray].last_name);
    }
    printf("Please enter the new contact's birthday (dd mm yyyy): ");
    scanf("%d %d %d",&contacts[sizeOfArray].birthdate.day,&contacts[sizeOfArray].birthdate.month,&contacts[sizeOfArray].birthdate.year); //Day, month and year are delimited by spaces
    int flagDate=validate_birthday(contacts[sizeOfArray].birthdate); //Validation of birthday (including months limits and leap years)
    while(!flagDate) //flagDate is 0 for invalid dates and 1 for valid dates
    {
        printf("Invalid date\nPlease enter a valid birthday (dd mm yyyy): ");
        scanf(" %d %d %d",&contacts[sizeOfArray].birthdate.day,&contacts[sizeOfArray].birthdate.month,&contacts[sizeOfArray].birthdate.year);
        flagDate=validate_birthday(contacts[sizeOfArray].birthdate);
    }
    printf("Please enter the new contact's address: "); //New Address delimited by a new line character (to include spaces)
    scanf(" %[^\n]s",contacts[sizeOfArray].address);
    printf("Please enter the new contact's E-mail: "); //New E-Mail delimited by a new line character
    scanf(" %s",contacts[sizeOfArray].email);
    int flagEmail=validate_email(contacts[sizeOfArray].email); //Validation of E-mail
    while(!flagEmail) // flagEmail is 0 for invalid E-Mails and 1 for valid E-Mails
    {
        printf("Invalid E-Mail\nPlease enter a valid E-Mail: ");
        scanf(" %s",contacts[sizeOfArray].email);
        flagEmail=validate_email(contacts[sizeOfArray].email);
    }
    printf("Please enter the new contact's number: "); //New phone number
    scanf(" %s",contacts[sizeOfArray].number);
    int flagNumber=validate_number(contacts[sizeOfArray].number);
    while(!flagNumber) //Validation of the Phone number
    {
        printf("Invalid number\nPlease Enter a valid number: ");
        scanf(" %s",contacts[sizeOfArray].number);
        flagNumber=validate_number(contacts[sizeOfArray].number);
    }
    printf("Successfully added!\n");
    sizeOfArray++;
    char choice[5];
    while(1) //Option to add another phone number
    {
        printf("Would you like to add another contact? (y/n) ");
        scanf("%s",choice);
        if(strcasecmp(choice,"y")==0)
        {
            add();
            return;
        }
        else if(strcasecmp(choice,"n")==0)
        {
            printf("Returning to Main Menu...");
            secDelay(1);
            return;
        }
        else
        {
            printf("Invalid option"); //Wrong character entered
        }
    }
}

void del() //Function to search for and delete contacts
{
    system("cls");
    int i,j;
    char x;
    query(); //Search for contact
    printf("Please enter the ID of the contact you want to delete: ");
    scanf("%d",&i);
    i=i-1;

            invalid1: printf("Delete %s %s? (y/n)",contacts[i].first_name,contacts[i].last_name);
            scanf("\n%c",&x);
            if (x=='y' || x=='Y')
            {
                j=i;
                while(j<sizeOfArray)
                {
                    contacts[j]=contacts[j+1];
                    j++;
                }
                sizeOfArray--;
                system("cls");
                printf("Contact deleted successfully...");
                return;
            }
            else if (x=='n' || x=='N')
            {
                del();
                return;
            }
            else
            {
                system("cls");
                printf("INVALID OPTION\n");
                goto invalid1;
            }
}


void modify() //Function to modify contacts in array of structures
{
    int count=0,i,flag=0,choice;
    char sChoice[5];
        query();
        printf("\n\nPlease enter the ID of the contact you want to modify (Enter 0 if you don't want to modify anymore): ");
        scanf("%d",&i);
        system("cls");
        if(!i)
        {
            while(1)
            {

                printf("Do you want to Re-Search?(Yes/No): ");
                scanf(" %s",sChoice);
                if(strcasecmp(sChoice,"yes")==0)
                {
                    modify();
                    return;
                }
                else if(strcasecmp(sChoice,"no")==0)
                    {
                        printf("Returning to Main Menu..");
                        secDelay(1);
                        return;
                    }
                else
                {
                    printf("Invalid option");
                }
            }
        }
        i=i-1;

    while(flag==0)
    {
        printf("Please choose the field you want to modify:\n(1) Name\n(2) Lastname\n(3) Birthday\n(4) Address\n(5) E-mail\n(6) Number\n");
        scanf("%d",&choice);
        switch(choice)
            {
                case (1):
                    {
                        count=0;
                        do
                        {
                            if(count>0)
                            {
                                printf("Invalid option\n");
                            }
                            printf("Current name is %s would you still want to change it?v(y/n)\n ",contacts[i].first_name);
                            scanf(" %s",sChoice);
                            count++;
                        }while(strcasecmp(sChoice,"y")&&strcasecmp(sChoice,"n"));
                        if(strcasecmp(sChoice,"n")==0)
                        {
                            printf("Would you still like to modify any other contact? (y/n)\nYour choice: ");
                            scanf(" %s",sChoice);
                            if(strcasecmp(sChoice,"y")==0)
                            {
                                modify();
                                return;
                            }
                        }
                        else
                        {
                            printf("Please enter the new name: ");
                            scanf(" %[^\n]s",contacts[i].first_name);
                            int flagFirst=validate_string(contacts[i].first_name);
                            while(!flagFirst)
                            {
                                printf("Invalid character in name!\nPlease enter a proper name (characters beside letters, numbers and spaces are not allowed!): ");
                                scanf(" %[^\n]s",contacts[i].first_name);
                                flagFirst=validate_string(contacts[i].first_name);
                            }
                            printf("Successfully updated\n");
                        }
                        flag=1;
                        }break;

                case (2):
                    {
                         count=0;
                        do
                        {
                            if(count>0)
                            {
                                printf("Invalid option\n");
                            }
                            printf("Current lastname is %s would you still want to change it? (y/n)\n ",contacts[i].last_name);
                            scanf(" %s",sChoice);
                            count++;
                        }while(strcasecmp(sChoice,"y")&&strcasecmp(sChoice,"n"));
                        if(strcasecmp(sChoice,"n")==0)
                        {
                            printf("Would you still like to modify any other contact? (y/n)\n");
                            scanf(" %s",sChoice);
                            if(strcasecmp(sChoice,"y")==0)
                            {
                                modify();
                                return;
                            }
                        }
                        else
                        {
                            printf("Please enter the new lastname: ");
                            scanf(" %[^\n]s",contacts[i].last_name);
                            int flagLast=validate_string(contacts[i].last_name);
                            while(!flagLast)
                            {
                                printf("Invalid character in name!\nPlease enter a proper name (characters beside letters, numbers and spaces are not allowed!): ");
                                scanf(" %[^\n]s",contacts[i].last_name);
                                flagLast=validate_string(contacts[i].last_name);
                            }
                            printf("Successfully updated\n");
                        }
                        flag=1;
                    }break;
                case (3):
                    {
                         count=0;
                        do
                        {
                            if(count>0)
                            {
                                printf("Invalid option\n");
                            }
                            printf("Current birthdate is %0d/%0d/%0d would you still want to change it? (y/n)\n",contacts[i].birthdate.day,contacts[i].birthdate.month,contacts[i].birthdate.year);
                            scanf(" %s",sChoice);
                            count++;
                        }while(strcasecmp(sChoice,"y")&&strcasecmp(sChoice,"n"));
                        if(strcasecmp(sChoice,"n")==0)
                        {
                            printf("Would you still like to modify any other contact? (y/n)\n");
                            scanf(" %s",sChoice);
                            if(strcasecmp(sChoice,"y")==0)
                            {
                                modify();
                                return;
                            }
                        }
                        else
                        {
                            printf("Please enter the new birthdate\nDay: ");
                            scanf(" %d",&contacts[i].birthdate.day);
                            printf("Month: ");
                            scanf(" %d",&contacts[i].birthdate.month);
                            printf("Year: ");
                            scanf(" %d",&contacts[i].birthdate.year);
                            int flagDate=validate_birthday(contacts[i].birthdate);
                            while(!flagDate)
                            {
                                printf("Invalid date\n");
                                printf("Please enter a valid birthday\n");
                                printf("Please enter the new birthdate\nDay: ");
                                scanf(" %d",&contacts[i].birthdate.day);
                                printf("Month: ");
                                scanf(" %d",&contacts[i].birthdate.month);
                                printf("Year: ");
                                scanf(" %d",&contacts[i].birthdate.year);
                                flagDate=validate_birthday(contacts[i].birthdate);
                            }
                            printf("Successfully updated\n");
                        }
                     flag=1;
                    }break;
                case (4):
                    {
                         count=0;
                        do
                        {
                            if(count>0)
                            {
                                printf("Invalid option\n");
                            }
                            printf("Current address is %s would you still want to change it? (y/n)\n",contacts[i].address);
                            scanf(" %s",sChoice);
                            count++;
                        }while(strcasecmp(sChoice,"y")&&strcasecmp(sChoice,"n"));
                        if(strcasecmp(sChoice,"n")==0)
                        {
                            printf("Would you still like to modify any other contact? (y/n)\n");
                            scanf(" %s",sChoice);
                            if(strcasecmp(sChoice,"y")==0)
                            {
                                modify();
                                return;
                            }
                        }
                        else
                        {
                            printf("Please enter the new address: ");
                            scanf(" %[^\n]s",contacts[i].address);
                            printf("Successfully updated\n");
                        }
                    flag=1;
                    }break;
                case (5):
                    {
                         count=0;
                        do
                        {
                            if(count>0)
                            {
                                printf("Invalid option\n");
                            }
                            printf("Current E-mail is %s would you still want to change it? (y/n)\n",contacts[i].email);
                            scanf(" %s",sChoice);
                            count++;
                        }while(strcasecmp(sChoice,"y")&&strcasecmp(sChoice,"n"));
                        if(strcasecmp(sChoice,"n")==0)
                        {
                            printf("Would you still like to modify any other contact? (y/n)\n");
                            scanf(" %s",sChoice);
                            if(strcasecmp(sChoice,"y")==0)
                            {
                                modify();
                                return;
                            }
                        }
                        else
                        {
                            printf("Please enter the new name of the E-mail: ");
                            scanf(" %s",contacts[i].email);
                            int flagEmail=validate_email(contacts[i].email);
                            while(!flagEmail)
                            {
                                printf("Invalid email\n");
                                printf("Please enter a valid E-mail address\n");
                                scanf(" %s",contacts[i].email);
                                flagEmail=validate_email(contacts[i].email);
                            }
                            printf("Successfully updated\n");
                        }
                    flag=1;
                    }break;
                case (6):
                    {
                         count=0;
                        do
                        {
                            if(count>0)
                            {
                                printf("Invalid option\n");
                            }
                            printf("Current number is %s would you still want to change it? (y/n)\n",contacts[i].number);
                            scanf("%s",sChoice);
                            count++;
                        }while(strcasecmp(sChoice,"y")&&strcasecmp(sChoice,"n"));
                        if(strcasecmp(sChoice,"n")==0)
                        {
                            printf("Would you still like to modify any other contact? (y/n)\n");
                            scanf("%s",sChoice);
                            if(strcasecmp(sChoice,"y")==0)
                            {
                                modify();
                                return;
                            }
                        }
                        else
                        {
                            printf("Please enter the new number: ");
                            scanf("%s",contacts[i].number);
                            int flagNumber=validate_number(contacts[i].number);
                            while(!flagNumber)
                            {
                                printf("Invalid number");
                                printf("Please enter a valid number");
                                flagNumber=validate_number(contacts[i].number);
                            }
                            printf("Successfully updated\n");
                        }
                    flag=1;
                    }break;
                default:printf("Invalid option\n");
            }
    }
}

void print() //Function to print sorted contacts
{
    entry* contactsTemp = getSorted();
    int n;
    system("cls");

    for (n=1;n<sizeOfArray+1;n++) //Prints ID, contact name, phone number, E-Mail, address and birthday
    {
        printf("(%d) %s %s\nPhone Number: %s\nE-mail Address: %s\nAddress: %s\nBirthday: %d-%d-%d\n\n",n,contactsTemp[n].first_name,contactsTemp[n].last_name,contactsTemp[n].number,contactsTemp[n].email,contactsTemp[n].address,contactsTemp[n].birthdate.day,contactsTemp[n].birthdate.month,contactsTemp[n].birthdate.year);
    }
    printf("PRESS ANY KEY TO PROCEED...");
    free(contactsTemp); //To avoid duplication of array after multiple usage of the sort function
    getch();
}

entry* getSorted() //Function to sort contacts
{
    entry* contactsTemp=(entry *)malloc(sizeof(entry)*(sizeOfArray+1)); //Create temporary array to avoid changes in main array
    int sizeTemp=sizeOfArray;
    for(sizeTemp=0; sizeTemp<=sizeOfArray; sizeTemp++)
    {
        contactsTemp[sizeTemp]=contacts[sizeTemp]; //Copying main array to temporary array
    }
    int i,j;
    entry temp; //Struct to swap two contacts
    for(i=0;i<=sizeOfArray;i++) //Main loop
    {
        for(j=i+1;j<=sizeOfArray;j++) //Main loop
            {
                if (strcasecmp(contactsTemp[i].first_name,contactsTemp[j].first_name)==0) //if first name duplicated
                {
                        if (strcasecmp(contactsTemp[i].last_name,contactsTemp[j].last_name)==0) //if second name duplicated
                        {
                                if(strcasecmp(contactsTemp[i].number,contactsTemp[j].number)>0)
                                {
                                    temp=contactsTemp[i];
                                    contactsTemp[i]=contactsTemp[j];
                                    contactsTemp[j]=temp;
                                }
                        }
                        else if(strcasecmp(contactsTemp[i].last_name,contactsTemp[j].last_name)>0)
                        {
                            temp=contactsTemp[i];
                            contactsTemp[i]=contactsTemp[j];
                            contactsTemp[j]=temp;
                        }
                }
                else if(strcasecmp(contactsTemp[i].first_name,contactsTemp[j].first_name)>0)
                {
                    temp=contactsTemp[i];
                    contactsTemp[i]=contactsTemp[j];
                    contactsTemp[j]=temp;
                }
            }
    }
    return contactsTemp;
}

void save() //function to save program
{
    int count=0,i=0,j=sizeOfArray;
    FILE *fptr1; //Pointer to file
    char nameOfFile[20];
    char choice[5]="no";
    while(!strcmp(choice,"no"))
    {
        printf("Please enter the name of the new file: \n ");
        scanf("%s",&nameOfFile); //Reads name of new file
        strcat(nameOfFile,".txt");
        if(fopen(nameOfFile,"r")!=NULL) //File already exists
        {
            printf("A file with that name exists would you like to overwrite data? (y/n) \n");
            count=0;
            do
            {
                if(count) //If user enters an invalid option
                    printf("Invalid option");
                scanf("%s",choice);
                count++;
            }while(strcmp(choice,"y")&&strcmp(choice,"n"));
            if(!strcmp(choice,"y"))
            {
              fptr1=fopen(nameOfFile,"w");
              fprintf(fptr1,"%s,%s,%d-%d-%d,%s,%s,%s",contacts[i].first_name,contacts[i].last_name,contacts[i].birthdate.day,contacts[i].birthdate.month,contacts[i].birthdate.year,contacts[i].address,&contacts[i].email,contacts[i].number);
              j=j-1;
              i=1;
              while(j--)
                {
                    fprintf(fptr1,"\n%s,%s,%d-%d-%d,%s,%s,%s",contacts[i].first_name,contacts[i].last_name,contacts[i].birthdate.day,contacts[i].birthdate.month,contacts[i].birthdate.year,contacts[i].address,&contacts[i].email,contacts[i].number);
                    i++;
                }
                printf("Saved");
                fclose(fptr1);
                break;
            }
        }
        else
        {
            fptr1=fopen(nameOfFile,"w");
            fprintf(fptr1,"%s,%s,%d-%d-%d,%s,%s,%s\n",contacts[i].first_name,contacts[i].last_name,contacts[i].birthdate.day,contacts[i].birthdate.month,contacts[i].birthdate.year,contacts[i].address,&contacts[i].email,contacts[i].number);
              sizeOfArray++;
              j=j-1;
              i=1;
              while(j--)
                {
                    fprintf(fptr1,"\n%s,%s,%d-%d-%d,%s,%s,%s",contacts[i].first_name,contacts[i].last_name,contacts[i].birthdate.day,contacts[i].birthdate.month,contacts[i].birthdate.year,contacts[i].address,&contacts[i].email,contacts[i].number);
                    i++;
                }
                printf("Saved");
                fclose(fptr1);
                break;
        }
        break;
    }
}

void quit() //Function to exit program
{
    char c;
    system("cls");
    printf("WARNING: Any unsaved data will be lost.\nProceed to EXIT? (y/n)\n");
    scanf(" %c",&c);
    system("cls");
    if (c=='n' || c=='N')
        mainmenu(); //User doesn't proceed to exit
    else if (c=='y' || c=='Y')
        exit(0); //User proceeds to exit
    else //Wrong character entered
    {
        printf("Invalid option.\n");
        quit();
    }
}

void secDelay(int t) //Delays a period of time in seconds
{
    t*=1000;
    clock_t start=clock();
    while(clock()<start+t);
}

void MilliSecDelay(int t) //Delays a period of time in milliseconds
{
    clock_t start=clock();
    while(clock()<start+t);
}

void check(int x) //Function to check if the user wants to proceed or get back to main menu
{
    char bar[10];
    switch(x)
    {
        case(1): strcpy(bar,"Load");break;
        case(2): strcpy(bar,"Query");break;
        case(3): strcpy(bar,"Add");break;
        case(4): strcpy(bar,"Delete");break;
        case(5): strcpy(bar,"Modify");break;
        case(7): strcpy(bar,"Save");break;
    }
        system("cls");
        printf("Proceed to %s? (y/n)\n",bar); //Check to proceed
        char c; scanf(" %c",&c);
        switch(c)
        {
            case('y'): //Proceed to Load
            case('Y'):break;
            case('n'): //Return to main menu
            case('N'):mainmenu();break;
            default:
                while (1)
                {
                    system("cls");
                    printf("Invalid option.\n");
                    printf("Proceed to %s? (y/n)\n",bar);
                    scanf(" %c",&c);
                    if (c=='y' || c=='Y') //Proceed to Load
                    {
                        break;
                    }
                    else if (c=='n' || c=='N') //Return to main menu
                        mainmenu();
                }
        } //Successfully checked
}

void intro() //First function presented
{
    printf("PPPPPPPPPPPPPPPPP  BBBBBBBBBBBBBBBBB       OOOOOOOOO         OOOOOOOOO    KKKKKKKKK    KKKKKKK\n");
    MilliSecDelay(50);
    printf("P::::::::::::::::P B::::::::::::::::B    OO:::::::::OO     OO:::::::::OO  K:::::::K    K:::::K\n");
    MilliSecDelay(50);
    printf("P::::::PPPPPP:::::PB::::::BBBBBB:::::B OO:::::::::::::OO OO:::::::::::::OOK:::::::K    K:::::K\n");
    MilliSecDelay(50);
    printf("PP:::::P     P:::::BB:::::B     B:::::O:::::::OOO:::::::O:::::::OOO:::::::K:::::::K   K::::::K\n");
    MilliSecDelay(50);
    printf("  P::::P     P:::::P B::::B     B:::::O::::::O   O::::::O::::::O   O::::::KK::::::K  K:::::KKK\n");
    MilliSecDelay(50);
    printf("  P::::P     P:::::P B::::B     B:::::O:::::O     O:::::O:::::O     O:::::O K:::::K K:::::K   \n");
    MilliSecDelay(50);
    printf("  P::::PPPPPP:::::P  B::::BBBBBB:::::BO:::::O     O:::::O:::::O     O:::::O K::::::K:::::K    \n");
    MilliSecDelay(50);
    printf("  P:::::::::::::PP   B:::::::::::::BB O:::::O     O:::::O:::::O     O:::::O K:::::::::::K     \n");
    MilliSecDelay(50);
    printf("  P::::PPPPPPPPP     B::::BBBBBB:::::BO:::::O     O:::::O:::::O     O:::::O K:::::::::::K     \n");
    MilliSecDelay(50);
    printf("  P::::P             B::::B     B:::::O:::::O     O:::::O:::::O     O:::::O K::::::K:::::K    \n");
    MilliSecDelay(50);
    printf("  P::::P             B::::B     B:::::O:::::O     O:::::O:::::O     O:::::O K:::::K K:::::K   \n");
    MilliSecDelay(50);
    printf("  P::::P             B::::B     B:::::O::::::O   O::::::O::::::O   O::::::KK::::::K  K:::::KKK\n");
    MilliSecDelay(50);
    printf("PP::::::PP         BB:::::BBBBBB::::::O:::::::OOO:::::::O:::::::OOO:::::::K:::::::K   K::::::K\n");
    MilliSecDelay(50);
    printf("P::::::::P         B:::::::::::::::::B OO:::::::::::::OO OO:::::::::::::OOK:::::::K    K:::::K\n");
    MilliSecDelay(50);
    printf("P::::::::P         B::::::::::::::::B    OO:::::::::OO     OO:::::::::OO  K:::::::K    K:::::K\n");
    MilliSecDelay(50);
    printf("PPPPPPPPPP         BBBBBBBBBBBBBBBBB       OOOOOOOOO         OOOOOOOOO    KKKKKKKKK    KKKKKKK\n");
    MilliSecDelay(50);

}
void warning() //to avoid frequent errors caused by the NULL value in the fptr
{
    if(fptr==NULL)
    {
        system("cls");
        printf("WARNING: you haven't loaded a file yet!\nProceed to load?(y/n): ");
        char choice;
        scanf(" %c",&choice);
        if(choice=='y'||choice=='Y')
        {
            load();
            secDelay(1);
        }
        else if(choice=='n'||choice=='N')
        {
            mainmenu();
        }
        else
        {
            printf("Invalid option");
            secDelay(1);
            warning();
            return;
        }

    }
}
