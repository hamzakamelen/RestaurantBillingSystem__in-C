//===============FUNCTIONS Define=============
int generateBillID()
{
    // Seed the random number generator with the current time
    srand(time(NULL));

    // Generate a random number between 1000 and 9999
    int billID = rand() % 9000 + 1000;

    return billID;
}
void BillGenerateHead(char name[50], char date[30], char time[30],int ID)
{
    printf("\n");
    printf("\n\t-----------------------------");
    printf("\n\t Welcome to Hamza Restaurant ");
    printf("\n\t-----------------------------");
    printf("\n%s", time);
    printf("\nBill ID: %d", ID);
    printf("\nCustomer Name: %s", name);
    printf("\n");
    printf("----------------------------------------\n");
    printf("Items\t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
    printf("\n----------------------------------------");
    printf("\n\n");
}
void BillGenerateBody(char item[30], int qty, float price)
{
    printf("%s\t\t", item);
    printf("%d\t\t", qty);
    printf("%.2f\t\t", qty * price);
    printf("\n");
}
void BillGenerateFooter(float total)
{
    printf("\n");
    float discount = 0.1 * total;
    float netTotal = total - discount;
    float GST = 0.09 * netTotal;
    float amountPayable = netTotal + GST;
    printf("-------------------------------------------\n");
    printf("\nSub Total   \t\t\t%.2f", total);
    printf("\nDiscount @10%s\t\t\t%.2f", "%", discount);
    printf("\n\t\t\t       -----------");
    printf("\nNet Total    \t\t\t%.2f", netTotal);
    printf("\nGST @9%s  \t\t\t%.2f", "%", GST);
    printf("\n-------------------------------------------");
    printf("\nAmount Payable \t\t\t%.2f", amountPayable);
    printf("\n-------------------------------------------");
}
// Successful tone
void playSuccessTone() {
    Beep(800, 200); // Frequency: 800Hz, Duration: 200ms
}

// Error tone
void playErrorTone() {
    Beep(400, 500); // Frequency: 400Hz, Duration: 500ms
}
