#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "Menu.h"
#include "Order.h"
#include "Admin.h"

void clearInputBuffer()
{
    int ch;
    while((ch = getchar())!= '\n' && ch !=EOF);
}
int main()
{
 int choice;


 while(1)
 {
    printf("\t\t\t\t////////////WELCOME TO TABLE-TRACK\\\\\\\\\\\\\\\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Exit\n");

    if(scanf("%d",&choice)!=1)
    {
        clearInputBuffer();
        continue;
    }

    clearInputBuffer();

    switch(choice)
    {
    case 1:
           registerUser();
           break;
    case 2:
           {
           char role[10];
           if(loginUser(role))
           {
               if(strcmp(role, "admin")==0)
               {
                   int subChoice;
                   while(1)
                   {
                       printf("\n========= Admin Menu ==========\n");
                       printf("1. Add Menu Item\n");
                       printf("2. View Menu Items\n");
                       printf("3. Update Menu Item\n");
                       printf("4. Delete Menu Item\n");
                       printf("5. Search Menu Item\n");
                       printf("6. Place Order\n");
                       printf("7. View Bill\n");
                       printf("8. Back\n");

                       if(scanf("%d",&subChoice)!=1)
                       {
                           clearInputBuffer();
                           continue;
                       }
                       clearInputBuffer();

                       if(subChoice == 8)
                           break;

                       switch(subChoice)
                       {
                       case 1: addMenuItem();
                              break;
                       case 2: viewMenuItems();
                              break;
                       case 3: updateMenuItem();
                              break;
                       case 4: deleteMenuItem();
                              break;
                       case 5: searchMenuItem();
                              break;
                       case 6: placeOrder();
                              break;
                       case 7: viewBill();
                              break;
                       default: printf("INVALID CHOICE\n");
                              break;
                       }
                   }
               }
               else
               {
                   int subChoice;
                   while(1)
                   {
                       printf("\n======== User Menu =========\n");
                       printf("1. View Menu Items\n");
                       printf("2. Search Menu Item\n");
                       printf("3. Place Order\n");
                       printf("4. View Bill\n");
                       printf("5. Back\n");

                       if(scanf("%d", &subChoice) != 1)
                       {
                           clearInputBuffer();
                           continue;
                       }
                       clearInputBuffer();

                       if(subChoice == 5)
                           break;

                       switch(subChoice)
                       {
                       case 1: viewMenuItems();
                              break;
                       case 2: searchMenuItem();
                              break;
                       case 3: placeOrder();
                              break;
                       case 4: viewBill();
                              break;
                       default: printf("INVALID CHOICE\n");
                              break;
                       }
                   }
               }
           }
           }
           break;
    case 3:
           printf("THANK YOU\n");
           return 0;
    default:
        printf("INVALID CHOICE\n");
        break;
    }

    }
    return 0;
}
