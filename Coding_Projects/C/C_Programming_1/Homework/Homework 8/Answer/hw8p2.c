#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>

typedef struct UserAccount_ {
    char FirstName[50];
    char LastName[50];
    int AccountNumber;
    int Pin;
    float SavingsBalance;
    float CheckingBalance;
} UserAccount;


void ReadBankData(FILE* inp, UserAccount AccountInfo[]);
void WriteBankData(FILE* inp, UserAccount AccountInfo[]);
void DepositWithdraw(UserAccount* CurrentUser);
void MoneyTransfer(UserAccount* CurrentUser);
void PinReset(UserAccount* CurrentUser);
void PrintBalance(UserAccount CurrentUser);

int main(void) {
    UserAccount info[10];
    FILE* input;
    UserAccount user;
    int i, select = 0, corinfo = 0;
    char no = 'Y';

    input = fopen("BankData.dat", "r");

    if (input == NULL)
        printf("file not found\n");

    else {
        ReadBankData(input, info);

        while (corinfo == 0) {
            printf("Welcome to ECE 175 ATMS\n");
            printf("Enter your account number: ");
            scanf("%d", &user.AccountNumber);
            printf("Enter your pin number: ");
            scanf("%d", &user.Pin);

            for (i = 0; i < 10; i++) {
                if (user.AccountNumber == info[i].AccountNumber && user.Pin == info[i].Pin) {
                    printf("\nHello %s %s\n", info[i].FirstName, info[i].LastName);
                    corinfo = 1;

                    do {
                        printf("Select Transaction:\n1. Account Balance\n2. Deposit or Withdrawal\n3. Money Transfer\n4. PIN Reset\n");
                        scanf("%d", &select);
                        if (select == 1) {

                            PrintBalance(info[i]);
                            printf("Would you like to perform another transaction? (Y/N):");
                            scanf(" %c", &no);
                            printf("\n");
                        }
                        else if (select == 2) {

                            DepositWithdraw(&info[i]);
                            PrintBalance(info[i]);
                            printf("Would you like to perform another transaction? (Y/N):");
                            scanf(" %c", &no);
                            printf("\n");
                        }
                        else if (select == 3) {

                            MoneyTransfer(&info[i]);
                            PrintBalance(info[i]);
                            printf("Would you like to perform another transaction? (Y/N):");
                            scanf(" %c", &no);
                            printf("\n");
                        }
                        else if (select == 4) {

                            PinReset(&info[i]);
                            printf("Would you like to perform another transaction? (Y/N):");
                            scanf(" %c", &no);
                            printf("\n");
                        }
                    } while (no != 'N' && no != 'n');
                    printf("Goodbye\n");
                }
                else if (i == 9 && select == 0) {
                    printf("Incorrect Information\n");
                }
            }
        }
        fclose(input);
        input = fopen("BankData.dat", "w+");
        WriteBankData(input, info);
        fclose(input);
    }
    return;
}


void ReadBankData(FILE* inp, UserAccount AccountInfo[]) { // Read info from file
    int i;
    do {
        for (i = 0; i < 10; i++) {
            fscanf(inp, "%s %s %d %d %f %f", AccountInfo[i].FirstName, AccountInfo[i].LastName,
                &AccountInfo[i].AccountNumber, &AccountInfo[i].Pin, &AccountInfo[i].SavingsBalance,
                &AccountInfo[i].CheckingBalance);
        }
    } while (i != 10);

    return;
}

void WriteBankData(FILE* inp, UserAccount AccountInfo[]) { // Write info to file
    int i;
    do {
        for (i = 0; i < 10; i++) {
            fprintf(inp, "%s\n%s\n%d\n%d\n%.2f\n%.2f\n", &AccountInfo[i].FirstName, &AccountInfo[i].LastName,
                AccountInfo[i].AccountNumber, AccountInfo[i].Pin, AccountInfo[i].SavingsBalance,
                AccountInfo[i].CheckingBalance);
        }
    } while (i != 10);
    return;
}

void DepositWithdraw(UserAccount* CurrentUser) {// deposit or withdraw
    int dop, wa, hm;

    printf("** Deposit or Withdraw **\n1. Deposit\n2. Withdraw\n");
    scanf("%d", &dop);

    if (dop == 1) {

        printf("Which Account?\n1. Checking Account\n2. Savings Account\n");
        scanf("%d", &wa);

        if (wa == 1) {

            printf("How much? ");
            scanf("%d", &hm);
            CurrentUser->CheckingBalance += hm;
        }
        else if (wa == 2) {

            printf("How much? ");
            scanf("%d", &hm);
            CurrentUser->SavingsBalance += hm;
        }
    }
    else if (dop == 2) {

        printf("Which Account?\n1. Checking Account\n2. Savings Account\n");
        scanf("%d", &wa);

        if (wa == 1) {

            printf("How much? ");
            scanf("%d", &hm);

            if (hm > CurrentUser->CheckingBalance) {
                printf("Insufficient Funds. Request Denied!!!\n");
            }
            else {
                CurrentUser->CheckingBalance += hm;
            }
        }
        else if (wa == 2) {

            printf("How much? ");
            scanf("%d", &hm);

            if (hm > CurrentUser->SavingsBalance) {
                printf("Insufficient Funds. Request Denied!!!\n");
            }
            else {
                CurrentUser->SavingsBalance += hm;
            }
        }
    }

    return;
}

void MoneyTransfer(UserAccount* CurrentUser) {// xfer money
    int cssc, hm;
    printf("** Transfer **\n1. From Checking to Savings\n2. From Savings to Checking\n");
    scanf("%d", &cssc);

    if (cssc == 1) {
        printf("How much? ");
        scanf("%d", &hm);

        if (hm > CurrentUser->CheckingBalance) {
            printf("Insufficient Funds. Request Denied!!!\n");
        }
        else {
            CurrentUser->SavingsBalance += hm;
            CurrentUser->CheckingBalance -= hm;
        }
    }
    else if (cssc == 2) {
        printf("How much? ");
        scanf("%d", &hm);

        if (hm > CurrentUser->SavingsBalance) {
            printf("Insufficient Funds. Request Denied!!!\n");
        }
        else {
            CurrentUser->SavingsBalance -= hm;
            CurrentUser->CheckingBalance += hm;
        }
    }
    return;
}

void PinReset(UserAccount* CurrentUser) {// reset pin
    int pin = 0;

    do {
        printf("Enter new pin number > 1000 and < 9999: ");
        scanf("%d", &pin);
    } while (pin >= 9999 || pin <= 1000);

    printf("Pin Reset Successful\n");
    CurrentUser->Pin = pin;
    return;
}

void PrintBalance(UserAccount CurrentUser) {// print balance

    printf("Your Savings Account Balance is: %.2f\n", CurrentUser.SavingsBalance);
    printf("Your Checking Account Balance is: %.2f\n", CurrentUser.CheckingBalance);


    return;
}