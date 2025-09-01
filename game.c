#include <stdio.h>

int main() {

char board[3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
int turn = 1;      // 1 = Player X, 2 = Player O
int moves = 0;
int row, col;
int i, j;

printf("=== TIC TAC TOE ===\n");
printf("Enter row (space) column, ((row,column = 0, 1, 2))\n");
printf("Player 1 (X) and Player 2 (O)\n");

while(moves < 9) {
    printf("\nPlayer %d enter row and column (0-2): ", turn);
    scanf("%d %d", &row, &col);

    // only place mark if the cell is empty
    if(board[row][col] == ' ') {
        if(turn == 1)
            board[row][col] = 'X';
        else
            board[row][col] = 'O';

        moves++;
        // switch turn
        turn = (turn == 1) ? 2 : 1;
    } else {
        printf("That cell is already used. Try again!\n");
    }

    // display board after every move
    printf("\n");
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++)
            printf("|%c", board[i][j]);
        printf("|\n");
    }
}

return 0;
}





