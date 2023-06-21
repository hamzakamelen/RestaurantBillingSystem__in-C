#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

void BillGenerateHead(char name[50], char date[30], char time[30]);
void BillGenerateBody(char item[30], int qty, float price);
void BillGenerateFooter(float total);
void playSuccessTone();
void playErrorTone();

struct items
{
    char item[30];
    float price;
    int qty;
};

struct orders
{
    char customerName[50];
    char date[50];
    int QuantityofItems;
    struct items itm[50];
};
