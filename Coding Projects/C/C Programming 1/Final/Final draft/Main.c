#include "Header.h"

//////////////////////////////////////////////////main///////////////////////////////////////////////////////////////

int main(void) {
    char name[50];
    int i, playerpurse = 100, bet = 0, discard = 0, tobediscarded[5];
    card* cards, * hand;
    char cont = '\n';
    char sym[4], dolla = 36;

    sym[0] = 3; //Heart
    sym[1] = 4; //Diamond
    sym[2] = 5; //Club
    sym[3] = 6; //Spade

    printf("Let's Play A Game...\n\n\t\t\t");
    for (i = 0; i < 6; i++) 
        printf("%c%c%c%c", sym[0], sym[1], sym[2], sym[3]);
    
    printf(" TWO PAIRS OR BETTER ");
    for (i = 0; i < 6; i++) 
        printf("%c%c%c%c", sym[0], sym[1], sym[2], sym[3]);
    

    printf("\n\nWhat's your name? ");
    fgets(name, 50, stdin);
    name[strlen(name) - 1] = '\0';

    printf("\nHello %s,\n\t\t", name);
    for (i = 0; i < 24; i++) 
        printf("%c", dolla);

    printf(" You'll start the game with 100 coins ");
    for (i = 0; i < 24; i++) 
        printf("%c", dolla);


    printf("\n\n\nWinning Hand:\t\t Example:\t\tPay:\n\n");
    printf("Royal Flush\t\t 10%c J%c Q%c K%c A%c\t250*bet\n", sym[1], sym[1], sym[1], sym[1], sym[1]);
    printf("Straight Flush\t\t J%c 10%c 8%c 9%c 7%c\t100*bet\n", sym[0], sym[0], sym[0], sym[0], sym[0]);
    printf("Four of a Kind\t\t 10%c 2%c 10%c 10%c 10%c\t50*bet\n", sym[3], sym[1], sym[0], sym[1], sym[3]);
    printf("Full House\t\t 2%c 2%c 10%c 10%c 10%c\t25*bet\n", sym[3], sym[1], sym[0], sym[1], sym[3]);
    printf("Flush\t\t\t 5%c 10%c 4%c J%c 8%c\t10*bet\n", sym[2], sym[2], sym[2], sym[2], sym[2]);
    printf("Straight\t\t A%c 2%c 3%c 4%c 5%c\t\t5*bet\n", sym[1], sym[1], sym[3], sym[0], sym[2]);
    printf("Three of a Kind\t\t 2%c 6%c 10%c 10%c 10%c\t4*bet\n", sym[2], sym[1], sym[0], sym[1], sym[3]);
    printf("Two Pairs\t\t 2%c 2%c 10%c 10%c 5%c\t2*bet\n\n\n", sym[2], sym[1], sym[3], sym[1], sym[1]);


#ifndef WORKINPROGRESS
    my_rand(0);
#endif

    newDeck(&cards);
    hand = playerHand();

#ifndef WORKINPROGRESS
    ShuffleCards(&cards);
#endif


    while (cont == '\n') {

        if (CountNodes(cards) <= 20) {     //*if less than 20 cards in "cards" make new deck and shuffle
            freee(cards);
            newDeck(&cards);
            ShuffleCards(&cards);
        }

        printf("\t\t\t\t\t\t You have %d coins\n\n", playerpurse);       //Display playerpurse

        bet = 0;
        while (bet > playerpurse || bet < 1) {          //*move betting here*
            printf("Place your bet (1-%d) coins (-1 to quit playing):", playerpurse);
            scanf("%d", &bet);
            if (bet == -1)
                return(0);
        }

        DealHand(&cards, &hand);

        printf("\n%s, your cards are:\n", name);        //Display playerhand
        PrintCards(hand);
        printf("\n\n");

        for (i = 0; i < 5; i++)
            tobediscarded[i] = 0;

        discard = 0;
        while (discard != -1) {
            printf("Pick card to discard (1-5)(-1 to stop picking)");          //let user pick cards to hold
            scanf("%d", &discard);
            if (discard == 1) {
                tobediscarded[0] = 1;
            }
            else if (discard == 2) {
                tobediscarded[1] = 1;
            }
            else if (discard == 3) {
                tobediscarded[2] = 1;
            }
            else if (discard == 4) {
                tobediscarded[3] = 1;
            }
            else if (discard == 5) {
                tobediscarded[4] = 1;
            }
        }

        for (i = 0; i < 5; i++) {           //swap topcard with cards user doesn't keep
            if (tobediscarded[i] == 1) {
                NewCard(&cards, &hand, i);
            }
        }                             // FIX!!! - cards shift down one when card is discarded 

        printf("\nYour new hand is:\n");      //display playerhand
        PrintCards(hand);
        printf("\n\n");

        WinOrNo(hand);
        playerpurse = Adjustplayerpurse(playerpurse, bet, hand);
        printf(" You now have %d coins\n", playerpurse);

        if (playerpurse > 0) {
            printf("\nDo you want to continue? (Enter to continue)");
            getchar();
            scanf("%c", &cont);
        }
        else {
            printf("Out of coin :( GAME OVER \n\n");
            cont = 'q';
        }
    }

    freee(cards);
    freee(hand);
    return 0;
}

