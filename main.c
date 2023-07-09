#include "dec.h"
#include "def.h"

int main()
{
    // DECLARATION
    int choice, qtyofitems;
    struct orders order;
    struct orders ord;
    char saveBill = 'y', startAgain = 'y';
    char name[50];
    FILE *fp;
    while (startAgain == 'y')
    {
        float total = 0;
        int BillFound = 0;
        // Get the current time
          time_t currentTime;
          time(&currentTime);
         char *timeString = ctime(&currentTime);
         timeString[strlen(timeString) - 1] = '\0'; // Remove the newline character
         order.time = timeString;
        // START
        system("cls");
        printf("\n\t----------------");
        printf("\n\tHamza Restaurant ");
        printf("\n\t----------------");
        // Option Show
        printf("\nPlease Select Your Prefered Choice");
        printf("\n1: Generate Bill.");
        printf("\n2: Show All Bills.");
        printf("\n3: Search Bill By Name.");
        printf("\n4: Delete Bill by Name.");
        printf("\n5: Exit.\n");
        printf("\nYour Choice? ");
        scanf("%d", &choice);
        fgetc(stdin);
        playSuccessTone();
        switch(choice)
        {
            // Generate Bills
        case 1:
            system("cls");
            printf("-----Generate New Bill-----");
            order.billID = generateBillID();
            printf("\nPlease Enter Customer Name: ");
            fgets(order.customerName, 50, stdin);
            // Removing \n from fgets func
            order.customerName[strlen(order.customerName) - 1] = 0;
            strcpy(order.date, __DATE__);
            printf("Please Enter the Number of Items: ");
            scanf("%d", &qtyofitems);
            order.QuantityofItems = qtyofitems;
            for (int i = 0; i < qtyofitems; i++)
            {
                fgetc(stdin);
                printf("\n\n");
                printf("Please Enter Item %d: ", i + 1);
                fgets(order.itm[i].item, 20, stdin);
                order.itm[i].item[strlen(order.itm[i].item) - 1] = 0;
                printf("Please Enter the Quantity: ");
                scanf("%d", &order.itm[i].qty);
                printf("Please Enter the unit price: ");
                scanf("%f", &order.itm[i].price);
                total += order.itm[i].qty * order.itm[i].price;
            }
            system("cls");
            BillGenerateHead(order.customerName, order.date,timeString,order.billID);
            for (int i = 0; i < order.QuantityofItems; i++)
            {
                BillGenerateBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
            }
            BillGenerateFooter(total);
            printf("\nDo You Want to save the Bill(y/n)?  ");
            scanf("%s", &saveBill);
            if (saveBill == 'y')
            {
                fp = fopen("RestaurantBill.txt", "a+");
                fwrite(&order, sizeof(struct orders), 1, fp);
                if (fwrite != 0)
                {
                    playSuccessTone();
                    printf("Successfully Saved!!");
                }
                else
                {
                    playErrorTone();
                    printf("\nTrouble in Saving..!");
                    fclose(fp);
                }
                 fclose(fp);
                break;
            }
            // Show Bills
        case 2:
            system("cls");
            fp = fopen("RestaurantBill.txt", "r");
            printf("\n");
            printf("----------All Bills----------\n");
            while (fread(&ord, sizeof(struct orders), 1, fp))
            {
                float tot = 0;
                BillGenerateHead(ord.customerName, ord.date,timeString,order.billID);
                for (int i = 0; i < ord.QuantityofItems; i++)
                {
                    BillGenerateBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
                    tot += ord.itm[i].qty * ord.itm[i].price;
                }
                BillGenerateFooter(tot);
            }
            fclose(fp);
            break;
            // Search Bill By Name
        case 3:
            system("cls");
            printf("-----Search Bill By Name-----");
            printf("\nEnter the Name of the Customer ");
            fgets(name, 50, stdin);
            name[strlen(name) - 1] = 0;
            system("cls");
            fp = fopen("RestaurantBill.txt", "r");
            printf("\n");
            printf("********Bill of %s********\n", name);
            while(fread(&ord, sizeof(struct orders), 1, fp))
            {
                float tot = 0;
                // strcmp to compare two strings
                if (strcmp(ord.customerName, name) == 0)
                {
                     playSuccessTone();
                    BillGenerateHead(ord.customerName, ord.date,timeString,order.billID);
                    for (int i = 0; i < ord.QuantityofItems; i++)
                    {
                        BillGenerateBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
                        tot += ord.itm[i].qty * ord.itm[i].price;
                    }
                    BillGenerateFooter(tot);
                    BillFound = 1;
                }
            }
            if (!BillFound)
            {
                playErrorTone();
                printf("\n%s Not Found..!", name);
            }
            break;
        // Delete Bill By Name
case 4:
    system("cls");
    printf("-----Delete Bill By Name-----");
    printf("\nEnter the Name of the Customer: ");
    fgets(name, 50, stdin);
    name[strlen(name) - 1] = '\0';
    system("cls");
    fp = fopen("RestaurantBill.txt", "r+");
    FILE *tempFile = fopen("temp.txt", "w"); // Create a temporary file for writing
    struct orders ord;
    int found = 0;
    while (fread(&ord, sizeof(struct orders), 1, fp))
    {
        if (strcmp(ord.customerName, name) != 0)
        {
            // Write the non-matching bill entries to the temporary file
            fwrite(&ord, sizeof(struct orders), 1, tempFile);
        }
        else
        {
            found = 1;
        }
    }
    fclose(fp);
    fclose(tempFile);
    remove("RestaurantBill.txt"); // Remove the original file
    rename("temp.txt", "RestaurantBill.txt"); // Rename the temporary file to the original file name

    if (found)
    {
        playSuccessTone();
        printf("\nBill of %s deleted successfully!", name);
    }
    else
    {
        playErrorTone();
        printf("\n%sBill Not Found..!", name);
    }
    break;
//Exit
        case 5:
             playSuccessTone();
            printf("\n\t\t Bye Bye.........!");
            exit(0);
            break;

        default:
            playErrorTone();
            printf("\nInvalid Choice");
            break;
        }
        printf("\nStart Again? [y/n] ");
        scanf(" %c", &startAgain);
    }
    printf("\n\n");
    printf("\n\t\tByeee....!");
    return 0;
}

