#include <stdio.h>

int main() {
char board[3][3];
int i, j;

// initialize empty spaces
for(i = 0; i < 3; i++) {
    for(j = 0; j < 3; j++) {
         board[i][j] = ' ';
    }
}

// display the board
printf("=== TIC TAC TOE ===\n\n");
for(i = 0; i < 3; i++) {
    for(j = 0; j < 3; j++) {
        printf(" %c ", board[i][j]);
    }
    printf("\n");
}

return 0;
}
