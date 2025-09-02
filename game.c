#include <stdio.h>

int check_row(char grid[3][3]) {
    for (int row_i = 0; row_i < 3; row_i++) {
        if (grid[row_i][0] == grid[row_i][1] &&
            grid[row_i][1] == grid[row_i][2] &&
            grid[row_i][0] != ' ')
            return 1;     // a row has the same mark
    }
    return 0;
}

int main() {
char board[3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
int player_turn = 1;
int move_count = 0;
int row_no, col_no;
int row_i, col_i;
int game_win = 0;

printf("=== TIC TAC TOE ===\n");

    while (move_count < 9 && !game_win) {
        printf("\nPlayer %d enter row and column (0-2): ", player_turn);
        scanf("%d %d", &row_no, &col_no);

    if (board[row_no][col_no] == ' ') {
        board[row_no][col_no] = (player_turn == 1) ? 'X' : 'O';
        move_count++;

        if (check_row(board)) {
            printf("\nPlayer %d wins by row!\n", player_turn);
            game_win = 1;
        } else {
            player_turn = (player_turn == 1) ? 2 : 1;
        }
    } else {
        printf("That cell is already filled. Try again!\n");
    }

    // print board after each move
    for (row_i = 0; row_i < 3; row_i++) {
        for (col_i = 0; col_i < 3; col_i++)
            printf("|%c", board[row_i][col_i]);
        printf("|\n");
        }
    }

    if (!game_win && move_count == 9)
        printf("\nGame draw!\n");

    return 0;
}






