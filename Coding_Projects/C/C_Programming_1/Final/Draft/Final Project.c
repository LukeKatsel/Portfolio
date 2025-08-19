#include "Final Header.h"

//////////////////////////////////////////////////main///////////////////////////////////////////////////////////////

int main(void) {
    card* x, *y;


#ifndef WORKINPROGRESS
    my_rand(0);
#endif 

    x = newDeck();

    y = playerHand();

    printf("deck before shuffling\n");
    PrintCards(x);

    printf("\n\n");
    printf("player hand before dealing\n");
    PrintCards(y);

    ShuffleCards(&x);
   
    printf("\n\n");
    printf("deck after shuffling\n");
    PrintCards(x);

    freee(x);
    freee(y);

    return;
}

/*
* 
* Needs to be implemented
* 
* user needs to be able to bet
*   - bet additions and subtractions needs to be tracked 
* 
* make game interactive
*   - deal out to user 
*   - let user pick cards to trade in 
* 
* need to determine if user wins
*   - player hand put in order 
*   - identify if user hand wins 
*   - add or subtract bet 
* 
* deallocate old deck and make new deck
* 
*/