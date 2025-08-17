#include "Header.h"

///////////////////////////////////////////////////newDeck//////////////////////////////////////////////////////////////

void newDeck(card** HN) {
    card* topCard, * tmp;
    int i, j;

    topCard = (card*)calloc(1, sizeof(card));

    tmp = topCard;

    *HN = tmp;

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


    return;
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

    assert(N > 0 && N <= CountNodes(*topCard) + 1);// make sure N is meaningful 

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
    N = CountNodes(*topCard);

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
        switch (topCard->face){
            case 1:
                printf("A%c", topCard->suit);
                break;
            case 11:
                printf("J%c", topCard->suit);
                break;
            case 12:
                printf("Q%c", topCard->suit);
                break;
            case 13:
                printf("K%c", topCard->suit);
                break;
            default:
                printf("%d%c", topCard->face, topCard->suit);
                break;
        }

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

    for (int i = 1; i < 6; i++) 
        InsertNthNode(playerHand, RemoveNthNode(topCard, 1), i);

    for (int i = 0; i < 5; i++)
        free(RemoveNthNode(playerHand, 6));

    return;
}

///////////////////////////////////////////////////CountNodes//////////////////////////////////////////////////////////////

int CountNodes(card* topCard) {
    int cnt = 0;

    while (topCard != NULL) {
        cnt++;
        topCard = topCard->next;
    }

    return(cnt);
}

////////////////////////////////////////////////////////NewCard/////////////////////////////////////////////////////////

void NewCard(card** topCard, card** playerHand, int i) {
    i += 1;
   
    InsertNthNode(playerHand, RemoveNthNode(topCard, 1), i);

    free(RemoveNthNode(playerHand, i + 1));

    return;
}

////////////////////////////////////////////////////////DidPlayerWin/////////////////////////////////////////////////////////

int DidPlayerWin(card* hand) {
    int i, N = 0;
    int face[5];
    int suit[5];

    for (i = 0; i < 5; i++) {
        face[i] = hand->face;
        suit[i] = hand->suit;
        hand = hand->next;
    }

    Sort(face);

    if ((suit[0] == suit[1] && suit[1] == suit[2] && suit[2] == suit[3] && suit[3] == suit[4]) &&
        (face[1] == (face[2] - 1) && face[2] == (face[3] - 1) && face[3] == (face[4] - 1)) && (face[0] == 1 && face[1] == 10))
        N = 1;
    else if ((suit[0] == suit[1] && suit[1] == suit[2] && suit[2] == suit[3] && suit[3] == suit[4]) &&
        (face[0] == (face[1] - 1) && face[1] == (face[2] - 1) && face[2] == (face[3] - 1) && face[3] == (face[4] - 1)))
        N = 2;
    else if ((face[0] == face[1] && face[1] == face[2] && face[2] == face[3]) || (face[1] == face[2] && face[2] == face[3] && face[3] == face[4]))
        N = 3;
    else if ((face[0] == face[1] && face[2] == face[3] && face[3] == face[4]) || (face[0] == face[1] && face[1] == face[2] && face[3] == face[4]))
        N = 4;
    else if (suit[0] == suit[1] && suit[1] == suit[2] && suit[2] == suit[3] && suit[3] == suit[4])
        N = 5;
    else if (((face[1] == (face[2] - 1) && face[2] == (face[3] - 1) && face[3] == (face[4] - 1))) && ((face[0] == 1 && face[1] == 10) ||
        (face[0] == (face[1] - 1) && face[1] == (face[2] - 1) && face[2] == (face[3] - 1) && face[3] == (face[4] - 1))))
        N = 6;
    else if ((face[0] == face[1] && face[1] == face[2]) || (face[1] == face[2] && face[2] == face[3]) || (face[2] == face[3] && face[3] == face[4]))
        N = 7;
    else if ((face[0] == face[1] && (face[2] == face[3] || face[3] == face[4])) || (face[1] == face[2] && face[3] == face[4]) ||
        (face[2] == face[3] && face[0] == face[1]) || (face[3] == face[4] && (face[0] == face[1] || face[1] == face[2])))
        N = 8;
    else
        N = 0;


    return(N);
}

/////////////////////////////////////////////////////////Sort////////////////////////////////////////////////////////

void Sort(int a[]) {
    int i, j, min;

    for (i = 0; i < 4; i++) {
        min = i;
        for (j = i + 1; j < 5; j++)
            if (a[j] < a[min])
                min = j;
        Swap(&a[min], &a[i]);
    }

    return;
}

//////////////////////////////////////////////////////////Swap///////////////////////////////////////////////////////

void Swap(int* x, int* y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;

    return;
}

////////////////////////////////////////WinOrNo/////////////////////////////////////////////////////////////////////////

void WinOrNo(card* hand) {
    char smile = 2;


    if (DidPlayerWin(hand) == 0)
        printf("\t\t\t\t\tYou Lost :(");
    else {

        for (int i = 0; i < 220; i++)
            printf("%c", smile);
        printf("\n");

        switch (DidPlayerWin(hand)) {
            case 1:
                printf("\t\t\t\t THAT'S A ROYAL FLUSH! YOU WON!");
                break;
            case 2:
                printf("\t\t\t\t THAT'S A STRAIGHT FLUSH! YOU WON!");
                break;
            case 3:
                printf("\t\t\t\t THAT'S A FOUR OF A KIND! YOU WON!");
                break;
            case 4:
                printf("\t\t\t\t THAT'S A FULL HOUSE! YOU WON!");
                break;
            case 5:
                printf("\t\t\t\t THAT'S A FLUSH! YOU WON!"); 
                break;
            case 6:
                printf("\t\t\t\t THAT'S A STRAIGHT! YOU WON!");
                break;
            case 7:
                printf("\t\t\t\t THAT'S A THREE OF A KIND! YOU WON!");
                break;
            case 8:
                printf("\t\t\t\t THAT'S A TWO PAIR! YOU WON!");
                break;

        }
    }

    return;
}

////////////////////////////////////////Adjustplayerpurse/////////////////////////////////////////////////////////////////////////

int Adjustplayerpurse(int playerpurse, int bet, card* hand) {
    int tmp= playerpurse;

    switch(DidPlayerWin(hand)){
        case 0:
            tmp = playerpurse - bet;
            break;
        case 1:
            tmp = playerpurse + (bet * 250);
            break;
        case 2:
            tmp = playerpurse + (bet * 100);
            break;
        case 3:
            tmp = playerpurse + (bet * 50);
            break;
        case 4:
            tmp = playerpurse + (bet * 25);
            break;
        case 5:
            tmp = playerpurse + (bet * 10);
            break;
        case 6:
            tmp = playerpurse + (bet * 5);
            break;
        case 7:
            tmp = playerpurse + (bet * 4);
            break;
        case 8:
            tmp = playerpurse + (bet * 2);
            break;

    }

    return(tmp);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

