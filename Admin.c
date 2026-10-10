#include <stdio.h>
#include <string.h>
#include "Admin.h"
#define USERS_FILES "users.txt"

void registerUser()
{
    char username[30];
    char password[30];
    char checkUser[30];
    char checkPass[30];
    char checkRole[10];
    char role[10];

    int roleChoice;

    FILE *fp;

    printf("Choose a Username:");
    scanf("%s", username);

     printf("Choose a Password:");
    scanf("%s", password);

    printf("Register as:\n  1. Admin\n\t 2. User\n");
    printf("Enter choice: ");
    scanf("%d", &roleChoice);

    if(roleChoice == 1)
        strcpy(role, "admin");
    else
        strcpy(role, "user");

    fp = fopen(USERS_FILES, "r");

    if(fp != NULL)
    {
        while (fscanf (fp,"%s %s %s", checkUser,checkPass,checkRole )== 3)
        {
            if(strcmp(checkUser, username) == 0)
            {
                printf("Username already exists....\n");
                fclose(fp);
                return;
            }
        }

    fclose(fp);
    }

fp = fopen(USERS_FILES, "a");

if(fp == NULL)
{
    printf("Could not open users file.\n");
    return;
}


fprintf(fp, "%s %s %s\n",username, password, role);
fclose(fp);

printf("Registered successfully as %s.\n", role);
}

int loginUser(char  *role)
{
    char username[30];
    char password[30];
    char checkUser[30];
    char checkPass[30];
    char checkRole[10];

    FILE *fp;
    int found =0;

    printf("Choose a Username");  printf("(don't use any space on it.):");
    scanf("%s", username);

     printf("Choose a Password:");  printf("(don't use any space on it.):");
    scanf("%s", password);

    fp=fopen(USERS_FILES, "r");

    if(fp == NULL)
    {
        printf("No registered users found.Please register first for services.\n");
        return 0;
    }

while (fscanf(fp, "%s %s %s", checkUser, checkPass, checkRole) == 3)
{
    if (strcmp(checkUser, username) == 0 && strcmp(checkPass, password) == 0)
    {
        found = 1;
        strcpy(role, checkRole);
        break;
    }
}
 fclose(fp);
    if(found)
       {

          return 1;
       }
    else
       {

         return 0;
       }

}
