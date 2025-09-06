#include "tictactoe.h"

// checks all win conditions
int check_win(char box[3][3]) {
int row_i, col_i;

// check rows
for (row_i = 0; row_i < 3; row_i++) {
    if (box[row_i][0] == box[row_i][1] &&
        box[row_i][1] == box[row_i][2] &&
        box[row_i][0] != ' ')
return 1;
    }

// check columns
for (col_i = 0; col_i < 3; col_i++) {
    if (box[0][col_i] == box[1][col_i] &&
        box[1][col_i] == box[2][col_i] &&
        box[0][col_i] != ' ')
return 1;
    }

if (box[0][0] == box[1][1] && box[1][1] == box[2][2] && box[0][0] != ' ')
    return 1;
if (box[0][2] == box[1][1] && box[1][1] == box[2][0] && box[0][2] != ' ')
    return 1;

    return 0;
}

// prints the current game board
void display_board(char grid[3][3]) {
int row_i, col_i;

printf("\nCurrent board:\n\n");

for (row_i = 0; row_i < 3; row_i++) {
    for (col_i = 0; col_i < 3; col_i++) {
        printf(" %c ", grid[row_i][col_i]);
        if (col_i < 2) printf("|");
    }
printf("\n");
if (row_i < 2) printf("---|---|---\n");
    }
}

// checks for draw condition
int is_draw(int move_count, int game_win) {
    if (!game_win && move_count == 9)
        return 1;
    return 0;
}

// validates if a move is inside 0–2 range
int valid_move(int row_no, int col_no) {
    if (row_no < 0 || row_no > 2 || col_no < 0 || col_no > 2)
        return 0;
    return 1;
}
