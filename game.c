#include <stdio.h>

int main() {

char board[3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
int row, col;
int i, j;

printf("=== TIC TAC TOE ===\n");
printf("Player 1 uses X\n");
printf("Enter row (space) column, ((row,column = 0, 1, 2)):  ");

// take input for X
scanf("%d %d", &row, &col);

// place X on the board
board[row][col] = 'X';

// show updated board
printf("\nCurrent board:\n");
for(i = 0; i < 3; i++) {
    for(j = 0; j < 3; j++) {
        printf("|%c", board[i][j]);
    }
    printf("|\n");
}

return 0;
}



