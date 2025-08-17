#define _CRT_SECURE_NO_WARNINGS
//#define WORKINPROGRESS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<time.h>


typedef struct card_s {
    char suit;
    int  face;
    struct card_s* next;
} card;

void newDeck(card** HN);
card* playerHand(void);
void freee(card* topCard);
int my_rand(int input);
card* MemLocofNthNode(card* topCard, int N);
void InsertNthNode(card** topCard, card* Node, int N);
card* RemoveNthNode(card** topCard, int N);
void SwapCards(card** topCard, int P1, int P2);
void ShuffleCards(card** topCard);
void PrintCards(card* topCard);
void DealHand(card** topCard, card** playerHand);
int CountNodes(card* topCard);
void NewCard(card** topCard, card** playerHand, int i);
int DidPlayerWin(card* hand);
void Sort(int a[]);
void Swap(int* x, int* y);
void WinOrNo(card* hand);
int Adjustplayerpurse(int playerpurse, int bet, card* hand);
void Intro(char* name[]);

