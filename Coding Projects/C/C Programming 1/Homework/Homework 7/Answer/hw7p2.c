#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define COL 5
#define ROW 2

//Author: Luke Katsel
//Date created: 10/25/2021
//Brief description of the program: This program is a memory (add to 9) game
//input(s): user inputs card selection
//output(s): none

void print_board(int x[ROW][COL], int show[ROW][COL]) { // this program prints the current array of cards
    int i, j;
    char que = '?';


    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            if (j != 4) {
                if (show[i][j] == 100) { //this inside if-statement is needed to print either '?' or a number
                    printf("%c ", que); 
                }
                else {
                    printf("%d ", x[i][j]);
                }
            }
            else { // this else statement is needed to make it appear as 2 rows
                if (show[i][j] == 100) {
                    printf("%c\n", que);
                }
                else {
                    printf("%d\n", x[i][j]);
                }
            }
        }
    }
    
}

void generate_game(int x[][COL], int choice) { // this generates the random game numbers
    int count = 0; int i, j, r, c;

    if (choice == 1) {
        x[0][0] = 3; x[0][1] = 2; x[0][2] = 1; x[0][3] = 8; x[0][4] = 7; x[1][0] = 0; x[1][1] = 4; x[1][2] = 6; x[1][3] = 9; x[1][4] = 5;
    }
    else { 
        for (i = 0; i < ROW; i++)
            for (j = 0; j < COL; j++)
                x[i][j] = 100; 
        for (i = 0; i < 10; i++) { 
            while (1) {
                r = rand(0, ROW - 1) % ROW;               
                c = rand(0, COL - 1) % COL;  
                if (x[r][c] == 100) {
                    x[r][c] = i;
                    break;
                }
            }
        }
    }
    return(0);
}



int main(void) {
    srand((int)time(0));
    int quit = 'o';
    int x[ROW][COL];
    int show[ROW][COL];
    int r1 = -1, r2 = -1, c1 = -1, c2 = -1;
    int i, j;
    char que = '?';
    int win = 0;
    int sum;

    printf("Let's play Memory (Sum to 9) game\n");
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            if (j != 4) {
                printf("%c ", que);
            }
            else {
                printf("%c\n", que);
            }
        }
    }

    generate_game(x, 2);

    while (quit != 'q' && win != 1) { // this keeps the game going until user enters q or wins

        while (r1 < 1 || r1 > 2 && c1 < 1 || c1 > 5) { // this keeps looping if user enters number outside range
            printf("enter first position: row(1-2) and column(1-5):");
            scanf("%d %d", &r1, &c1);

            if (show[r1 - 1][c1 - 1] <= 9 && show[r1 - 1][c1 - 1] >= 0 && !(r1 < 1 || r1 > 2 && c1 < 1 || c1 > 5)) {
                printf("%d already open at(row,col) = (%d,%d)\n", show[r1 - 1][c1 - 1], r1, c1);
                r1 = -1;
                c1 = -1;
            }
        }
        while (r2 < 1 || r2 > 2 && c2 < 1 || c2 > 5) { // these two while loops were the most challenging
            printf("enter second position: row(1-2) and column(1-5):");
            scanf("%d %d", &r2, &c2);
            if (r1 == r2 && c1 == c2) {
                printf("first and second positions CANNOT be the same\n");
                r2 = -1;
                c2 = -1;
            }
            else if (show[r2 - 1][c2 - 1] <= 9 && show[r2 - 1][c2 - 1] >= 0 && !(r2 < 1 || r2 > 2 && c2 < 1 || c2 > 5)) {
                printf("%d already open at(row,col) = (%d,%d)\n", show[r2 - 1][c2 - 1], r2, c2);
                r2 = -1;
                c2 = -1;
            }
        }

        for (i = 0; i < ROW; i++) {
            for (j = 0; j < COL; j++) { 
                if (i == (r1 - 1) && j == (c1 - 1) || i == (r2 - 1) && j == (c2 - 1) || show[i][j] == x[i][j]) {
                    show[i][j] = x[i][j];// this changes the display based on if the user got it right
                }
                else { 
                    show[i][j] = 100;
                }
            }
        }

        print_board(x, show);
        sum = x[r1 - 1][c1 - 1] + x[r2 - 1][c2 - 1];

        printf("%d + %d = %d.", x[r1 - 1][c1 - 1], x[r2 - 1][c2 - 1], sum);
        if (sum == 9)// checks if user got it right
            printf("Good job\n"); 
        else {
            printf("(not 9)\n");

            show[r1 - 1][c1 - 1] = 100;
            show[r2 - 1][c2 - 1] = 100;

            print_board(x, show);
        }
        r1 = 0; r2 = 0; c1 = 0; c2 = 0;

        if (show[0][0] == x[0][0] && show[0][1] == x[0][1] && show[0][2] == x[0][2] &&
            show[0][3] == x[0][3] && show[0][4] == x[0][4] && show[1][0] == x[1][0] &&
            show[1][1] == x[1][1] && show[1][2] == x[1][2] && show[1][3] == x[1][3] && 
            show[1][4] == x[1][4]) {
            win = 1;
            printf("Congratulations, You win the game\n"); // checks if user won game or asks if want to quit
        }
        else {
            printf("continue (q to quit)? ");
            scanf(" %c", &quit);
        }
    }

    printf("Good Bye");

    return;
}