#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
//defining the skape values
#define ENTER 13
#define TAB 9
#define BCKSPC 8


struct user
{
    char fullname[50];
    char email[50];
    char password[50];
    char username[50];
    char phone[50];
};

void takeinput(char ch[50]){
    fgets(ch, 50, stdin);
    ch[strlen(ch)-1] = 0;
}

void generateusername(char email[50], char username[50]){
    for(int i = 0; i<strlen(email); i++){
        if(email[i]= '@'){
            break;
        }
        else{
            username[i] = email[i];
        }
    }
}

// Function to display the   in the place of the password
void takepassword(char pwd[50]){
    int i;
    char ch;
    while(1){  // run while loop untill the user press the Enter button
        ch = getch();
        if(ch == ENTER || ch == TAB){
            printf("//3");
            pwd[i] = '\0';
            break;
        }else if(ch == BCKSPC){
            if(i>0){
                i--;
                printf("\b \b"); // If you press the backspace then the then cursor move one forward(abc|d) and then replace 'd' with space and last \b force cursor to move its original position
            }
        }
        else{
            pwd[i++] = ch;
            printf("* \b"); //line replace the character with *(astrick sign)
        }
    }
}


int main(){
    system("cls");
    system("color 0b");

    struct user user;
    int opt;

    printf("\n\t\t\t\t---------Welcome to authentication system---------");
    printf("\nPlease choose your operation");
    printf("\n1. Signup");
    printf("\n2. Login");   
    printf("\n3. Exit");

    printf("\n\nYour Choice:\t");
    scanf("%d", &opt); // It also generate the \n which went to fgets and it will stop working so need to consume the \n by fgetc(stdin)
    fgetc(stdin);

    switch (opt)
    {
    case 1:
        printf("\nEnter the full name:\t");
        takeinput(user.fullname); 
        printf("\nEnter your email:\t");
        takeinput(user.email);
        printf("\nEnter your contact number:\t");
        takeinput(user.phone);
        printf("\nEnter your Password:\t");
        // takeinput(user.password);
        takepassword(user.password);
        printf("\n%s", user.password);

        break;
    
    default:
        break;
    }

    return 0;
}
