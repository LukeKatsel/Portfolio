#include "Final Header.h"

///////////////////////////////////////////////////newDeck//////////////////////////////////////////////////////////////

card* newDeck(void) {
    card* topCard, * tmp;
    int i, j;

    topCard = (card*)calloc(1, sizeof(card));

    tmp = topCard;

    for (int i = 2; i <= 52; i++) {
        tmp->next = (card*)calloc(1, sizeof(card));
        tmp = tmp->next;
    }

    tmp = topCard;

    for (i = 3; i <= 6; i++) {
        for (j = 1; j <= 13; j++) {
            if (topCard != NULL) {
                tmp->face = j;
                tmp->suit = i;

                tmp = tmp->next;
            }
        }
    }


    return(topCard);
}

///////////////////////////////////////////////////playerHand//////////////////////////////////////////////////////////////

card* playerHand(void) {
    card* topCard, * tmp;

    topCard = (card*)calloc(1, sizeof(card));

    tmp = topCard;

    for (int i = 2; i <= 5; i++) {
        tmp->next = (card*)calloc(1, sizeof(card));
        tmp = tmp->next;
    }



    return(topCard);
}

///////////////////////////////////////////////////freee//////////////////////////////////////////////////////////////

void freee(card* topCard) {
    card* tmp;

    while (topCard != NULL) {
        tmp = topCard->next;
        free(topCard);
        topCard = tmp;
    }

    return;
}

//////////////////////////////////////////////////my_rand///////////////////////////////////////////////////////////////

int my_rand(int input) {
    time_t t;

    if (input == 0) {
        srand((unsigned)time(&t));
        return(0);
    }
    else
        return(rand() % input);
}

//////////////////////////////////////////////////MemLocofNthNode///////////////////////////////////////////////////////////////

card* MemLocofNthNode(card* topCard, int N) {

    assert(N <= CountNodes(topCard) && N > 0);//make sure that there are N nodes

    for (int i = 2; i <= N; i++)
        topCard = topCard->next;

    return(topCard);
}

/////////////////////////////////////////////////InsertNthNode////////////////////////////////////////////////////////////////

void InsertNthNode(card** topCard, card* Node, int N) {
    card* tmp;

    assert(N > 0 && N <= CountNodes(topCard) + 1);// make sure N is meaningful 

    if (N > 1) {
        tmp = MemLocofNthNode(*topCard, N - 1);//Assume N > 1. tmp is the node before 
        Node->next = tmp->next;// now both point to next one down
        tmp->next = Node;
    }
    else {
        Node->next = *topCard;
        *topCard = Node;
    }

    return;
}

///////////////////////////////////////////////////RemoveNthNode//////////////////////////////////////////////////////////////

card* RemoveNthNode(card** topCard, int N) {
    card* tmp, * tmp2;

    if (N > 1) {
        tmp = MemLocofNthNode(*topCard, N - 1);
        tmp2 = tmp->next;

        tmp->next = tmp2->next;  // causes problem after first card has been delt WHY???
    }                            // I think if the count nodes function is fixed this problem will go away
    else {
        tmp2 = *topCard;
        *topCard = tmp2->next;
    }
    tmp2->next = NULL;

    return(tmp2);
}

/////////////////////////////////////////////////SwapCards////////////////////////////////////////////////////////////////

void SwapCards(card** topCard, int P1, int P2) {
    card* tmplow, * tmphigh;
    int Plow, Phigh;

    if (P2 > P1) {
        Plow = P1;
        Phigh = P2;
    }
    else {
        Plow = P2;
        Phigh = P1;
    }

    tmphigh = RemoveNthNode(topCard, Phigh);
    tmplow = RemoveNthNode(topCard, Plow);
    InsertNthNode(topCard, tmphigh, Plow);
    InsertNthNode(topCard, tmplow, Phigh);

    return;
}

/////////////////////////////////////////////////ShuffleCards////////////////////////////////////////////////////////////////

void ShuffleCards(card** topCard) {
    int N, i, j, k;
    N = CountNodes(topCard);

    for (k = 0; k < 10000; k++) {
        for (i = 1; i <= N; i++) {
            do {
                j = my_rand(N) + 1;
            } while (i == j);
            SwapCards(topCard, i, j);
        }
    }

    return;
}

//////////////////////////////////////////////////PrintCards///////////////////////////////////////////////////////////////

void PrintCards(card* topCard) {
    int i = 1;

    while (topCard != NULL) {
        if (topCard->face == 1)
            printf("A%c", topCard->suit);

        else if (topCard->face == 11)
            printf("J%c", topCard->suit);

        else if (topCard->face == 12)
            printf("Q%c", topCard->suit);

        else if (topCard->face == 13)
            printf("K%c", topCard->suit);

        else
            printf("%d%c", topCard->face, topCard->suit);

        if (i % 13 != 0)
            printf("\t");

        else
            printf("\n");

        topCard = topCard->next;
        i++;
    }


    return;
}

///////////////////////////////////////////////////DealHand//////////////////////////////////////////////////////////////

void DealHand(card** topCard, card** playerHand) {


    InsertNthNode(playerHand, RemoveNthNode(topCard, 1), 1);
    InsertNthNode(playerHand, RemoveNthNode(topCard, 2), 2);
    InsertNthNode(playerHand, RemoveNthNode(topCard, 3), 3);
    InsertNthNode(playerHand, RemoveNthNode(topCard, 4), 4);
    InsertNthNode(playerHand, RemoveNthNode(topCard, 5), 5);
    RemoveNthNode(playerHand, 6);
    RemoveNthNode(playerHand, 7);
    RemoveNthNode(playerHand, 8);
    RemoveNthNode(playerHand, 9);
    RemoveNthNode(playerHand, 10);

    return;
}

///////////////////////////////////////////////////CountNodes//////////////////////////////////////////////////////////////

int CountNodes(card* topCard) {
    int cnt = 0;

    /*while (topCard != NULL) {
        cnt++;
        topCard = topCard->next;
    }*/
    return(52);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////