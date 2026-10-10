#include<stdio.h>
#include "Order.h"
#include "Menu.h"
#define ORDERS_FILES "orders.txt"

void placeOrder()
{
    int id,quantity;
    MenuItem item;
    FILE *fp;
    float bill;

    printf("Enter your id:\n");
    scanf("%d",&id);

    if(!loadMenuItemById(id, &item))
    {
        printf("Item is not found.\n");
        return;
    }
    printf("Enter your quantity:\n");
    scanf("%d",&quantity);

    if(quantity<=0)
    {
        printf("Invalid quantity.\n");
        return;
    }

    if(quantity > item.stock)
    {
        printf("Not enough stock.\n");
        return;
    }

    bill = item.price * quantity;

    printf("Item : %s\n",item.name);
    printf("Quantity : %d\n",quantity);
    printf("Unit Price : %0.2f\n",item.price);
    printf("Total : %0.2f Taka\n",bill);

    fp = fopen(ORDERS_FILES, "a");
    if(fp == NULL)
    {
        printf("Could not open orders file.\n");
        return;
    }

    fprintf(fp,"ItemId : %d Name : %s  Quantity : %d Total : %0.2f\n", id, item.name, quantity, bill);
    fclose(fp);

    updateStock(id, item.stock - quantity);
}

void viewBill()
{
    char line[150];
    FILE *fp = fopen(ORDERS_FILES, "r");

    printf("\n======Order / Bill History ======\n");

    if(fp == NULL)
    {
        printf("No orders found yet.\n");
        return;
    }

    while(fgets(line, sizeof(line), fp) != NULL)
    {
        printf("%s", line);
    }

    fclose(fp);
}
