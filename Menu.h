#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

typedef struct
{
    int id;
    char name[50];
    char category[30];
    float price;
    int stock;
} MenuItem;

void addMenuItem();
void viewMenuItems();
void updateMenuItem();
void deleteMenuItem();
void searchMenuItem();


int loadMenuItemById(int id, MenuItem *item);
void updateStock(int id, int newStock);



#endif // MENU_H_INCLUDED
