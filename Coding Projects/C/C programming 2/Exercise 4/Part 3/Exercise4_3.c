#include <stdio.h>

#define ADULT_TICKET_PRICE 69.00
#define CHILD_TICKET_PRICE 35.00

int PurchaseTickets(double *pRemainingCash, int adultTickets,int childTickets);

int main(void){
    double *cashPointer;
    double cash;
    int adultTickets, childTickets, tixPurchased;

    cashPointer = &cash;                                // point pointer to location of cash

    printf("How much cash do you have? ");
    if(scanf("%lf", &cash) != 1){
        printf("Not a valid input\n");
    }
    printf("How many child tickets do you want? ");     // prompt user
    if(scanf("%d", &childTickets) != 1){
        printf("Not a valid input\n");
    }
    printf("How many Adult tickets do you want? ");
    if(scanf("%d", &adultTickets) != 1){
        printf("Not a valid input\n");
    }
    
    else{
        tixPurchased = PurchaseTickets(cashPointer, adultTickets, childTickets);    // how many tickets purchased?                       
        if (tixPurchased == 0){                         // if none - if didnt have enough money
            printf("You do not have enough money\n\n");
        }
        else{                                           // if successful 
            printf("You have purchased %d tickets, and you have $%.2f remaining\n\n", tixPurchased, cash);
        }
    }
    return 0;
}

/*****************************************************************
*
* Function: PurchaseTickets
*
* Parameters:
*
* pRemainingCash - points to a variable containing the
* amount of cash the user has
*
* adultTickets - specifies the number of adult tickets
* the user wants to purchase.
*
* childTickets - specifies the number of child tickets
* the user wants to purchase.
*
*
* Description:
* The function will determine if the user has enough
* money to purchase the specified number of tickets.
* If they do, then the function deducts the proper
* funds from their remaining cash and returns
* the total number of tickets purchased. If they do not
* the function returns 0.
*
******************************************************************/
int PurchaseTickets(double *pRemainingCash, int adultTickets,int childTickets){

    int totalCost, totalTickets;

    totalCost = ((adultTickets * ADULT_TICKET_PRICE) + (childTickets * CHILD_TICKET_PRICE));
    totalTickets = adultTickets + childTickets;

    if (totalCost <= *pRemainingCash){                      // if they have enough money
        *pRemainingCash = *pRemainingCash - totalCost;      // update wallet
        return totalTickets;                                // return number of tickets
    }
    else {
        return 0;                                           // return 0 if they couldnt buy tickets
    }
}

