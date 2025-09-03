#include <stdio.h>

// checks all winning conditions (rows, columns, diagonals)
int check_win(char box[3][3]) {
    int row_i, col_i;

    // check each row
    for (row_i = 0; row_i < 3; row_i++) {
        if (box[row_i][0] == box[row_i][1] &&
            box[row_i][1] == box[row_i][2] &&
            box[row_i][0] != ' ')
            return 1;
    }

    // check each column
    for (col_i = 0; col_i < 3; col_i++) {
        if (box[0][col_i] == box[1][col_i] &&
            box[1][col_i] == box[2][col_i] &&
            box[0][col_i] != ' ')
            return 1;
    }

    // check main diagonal
    if (box[0][0] == box[1][1] &&
        box[1][1] == box[2][2] &&
        box[0][0] != ' ')
        return 1;

    // check anti-diagonal
    if (box[0][2] == box[1][1] &&
        box[1][1] == box[2][0] &&
        box[0][2] != ' ')
        return 1;

    return 0; // no win yet
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

        if (check_win(board)) {
            printf("\nPlayer %d wins!\n", player_turn);
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








