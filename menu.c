#include <stdio.h>
#include <string.h>
#include "Menu.h"
#define MENU_FILE "menu.txt"
#define TEMP_FILE "menu_temp.txt"

static void clearInputBuffer()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

}


static int readRecord(FILE *fp, MenuItem *item)
{
    return fscanf(fp, "%d|%49[^|]|%29[^|]|%f|%d\n",&item->id, item->name, item->category, &item->price, &item->stock) == 5;
}

static void writeRecord(FILE *fp, MenuItem *item)
{
    fprintf(fp, "%d|%s|%s|%.2f|%d\n",item->id, item->name, item->category, item->price, item->stock);
}


static int getNextId()
{
    FILE *fp = fopen(MENU_FILE, "r");
    MenuItem item;
    int maxId = 0;

    if (fp == NULL)
        return 1;

    while (readRecord(fp, &item))
    {
        if (item.id > maxId)
            maxId = item.id;
    }
    fclose(fp);
    return maxId + 1;
}

void addMenuItem()
{
    MenuItem item;
    FILE *fp;

    item.id = getNextId();

    printf("\n======= Add Menu Item =========\n");
    printf("Item name: ");
    scanf(" %49[^\n]", item.name);
    printf("Category (e.g. Pizza/Burger/Bangaliyana): ");
    scanf(" %29[^\n]", item.category);
    printf("Price: ");
    scanf("%f", &item.price);
    printf("Stock quantity: ");
    scanf("%d", &item.stock);
    clearInputBuffer();

    fp = fopen(MENU_FILE, "a");
    if (fp == NULL)
    {
        printf("Error: could not open menu file.\n");
        return;
    }
    writeRecord(fp, &item);
    fclose(fp);

    printf("Item added successfully with ID %d.\n", item.id);
}

void viewMenuItems()
{
    FILE *fp = fopen(MENU_FILE, "r");
    MenuItem item;
    int any = 0;

    printf("\n====== Menu Items =========\n");
    if (fp == NULL)
    {
        printf("No menu items found yet.\n");
        return;
    }


    printf("ID\tName\t\tCategory\tPrice\tStock\n");


    while (readRecord(fp, &item))
    {

        printf("%d\t%s\t\t%s\t%.2f\t%d\n",item.id, item.name, item.category, item.price, item.stock);
        any = 1;
    }
    fclose(fp);

    if (!any)
        printf("No menu items found yet.\n");
}

int loadMenuItemById(int id, MenuItem *result)
{
    FILE *fp = fopen(MENU_FILE, "r");
    MenuItem item;

    if (fp == NULL)
        return 0;

    while (readRecord(fp, &item))
    {
        if (item.id == id)
        {
            *result = item;
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void updateMenuItem()
{
    int targetId, found = 0;
    MenuItem item;
    FILE *fp,*temp;

    printf("\n======= Update Menu Item ==========\n");
    printf("Enter the ID of the item to update: ");
    scanf("%d", &targetId);
    clearInputBuffer();

    fp = fopen(MENU_FILE, "r");
    if (fp == NULL)
    {
        printf("No menu items found yet.\n");
        return;
    }
    temp = fopen(TEMP_FILE, "w");
    if (temp == NULL)
    {
        printf("Error: could not create temporary file.\n");
        fclose(fp);
        return;
    }

    while (readRecord(fp, &item))
    {
        if (item.id == targetId)
        {
            found = 1;

            printf("Current name: %s\n", item.name);
            printf("Current category: %s\n", item.category);
            printf("Current price: %.2f\n", item.price);
            printf("Current stock: %d\n", item.stock);

            printf("New price: ");
            scanf("%f", &item.price);
            printf("New stock quantity: ");
            scanf("%d", &item.stock);
            clearInputBuffer();
        }
        writeRecord(temp, &item);
    }
    fclose(fp);
    fclose(temp);

    remove(MENU_FILE);
    rename(TEMP_FILE, MENU_FILE);

    if (found)
        printf("Item updated successfully.\n");
    else
        printf("No item found with that ID.\n");
}

void deleteMenuItem()
{
    int targetId, found = 0;
    MenuItem item;
    FILE *fp, *temp;

    printf("\n--- Delete Menu Item ---\n");
    printf("Enter the ID of the item to delete: ");
    scanf("%d", &targetId);
    clearInputBuffer();

    fp = fopen(MENU_FILE, "r");
    if (fp == NULL)
    {
        printf("No menu items found yet.\n");
        return;
    }
    temp = fopen(TEMP_FILE, "w");
    if (temp == NULL)
    {
        printf("Error: could not create temporary file.\n");
        fclose(fp);
        return;
    }

    while (readRecord(fp, &item))
    {
        if (item.id == targetId)
        {
            found = 1;
            continue;
        }
        writeRecord(temp, &item);
    }
    fclose(fp);
    fclose(temp);

    remove(MENU_FILE);
    rename(TEMP_FILE, MENU_FILE);

    if (found)
        printf("Item deleted successfully.\n");
    else
        printf("No item found with that ID.\n");
}

void searchMenuItem()
{
    char keyword[50];
    FILE *fp = fopen(MENU_FILE, "r");
    MenuItem item;
    int any = 0;

    printf("\n======== Search Menu Item ==========\n");
    printf("Enter name or category keyword: ");
    scanf(" %49[^\n]", keyword);
    clearInputBuffer();

    if (fp == NULL)
    {
        printf("No menu items found yet.\n");
        return;
    }

    while (readRecord(fp, &item))
    {
        if (strstr(item.name, keyword) != NULL || strstr(item.category, keyword) != NULL)
        {
            if (!any)
            {
                printf("ID\tName\t\tCategory\tPrice\tStock\n");

            }
            printf("%d\t%s\t\t%s\t%.2f\t%d\n",item.id, item.name, item.category, item.price, item.stock);

            any = 1;
        }
    }
    fclose(fp);

    if (!any)
        printf("No matching item found.\n");
}

void updateStock(int id, int newStock)
{
    MenuItem item;
    FILE *fp = fopen(MENU_FILE, "r");
    FILE *temp;

    if (fp == NULL)
        return;
    temp = fopen(TEMP_FILE, "w");
    if (temp == NULL)
    {
        fclose(fp);
        return;
    }

    while (readRecord(fp, &item))
    {
        if (item.id == id)
            item.stock = newStock;
        writeRecord(temp, &item);
    }
    fclose(fp);
    fclose(temp);

    remove(MENU_FILE);
    rename(TEMP_FILE, MENU_FILE);
}
