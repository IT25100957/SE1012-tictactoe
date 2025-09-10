#include "tictactoe.h"

int check_win(char box[3][3], char player_mark) {
    int row_i, col_i;

// check rows
for (row_i = 0; row_i < 3; row_i++) {
    if (box[row_i][0] == player_mark &&
        box[row_i][1] == player_mark &&
        box[row_i][2] == player_mark)
return 1;
    }

// check columns
for (col_i = 0; col_i < 3; col_i++) {
    if (box[0][col_i] == player_mark &&
        box[1][col_i] == player_mark &&
        box[2][col_i] == player_mark)
return 1;
    }

    // diagonals
    if (box[0][0] == player_mark && box[1][1] == player_mark && box[2][2] == player_mark)
        return 1;
    if (box[0][2] == player_mark && box[1][1] == player_mark && box[2][0] == player_mark)
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

// main game logic separated into its own function
void play_game() {
    char board[3][3] = {
        {' ',' ',' '},
        {' ',' ',' '},
        {' ',' ',' '}
    };
    int player_turn = 1;
    int move_count  = 0;
    int row_no, col_no;
    int game_win    = 0;

    while (move_count < 9 && !game_win) {
    printf("\nPlayer %d enter row and column (0-2): ", player_turn);
    scanf("%d %d", &row_no, &col_no);

    if (!valid_move(row_no, col_no)) {
        printf("Invalid position! Enter values between 0 and 2.\n");
        continue;
        }

     if (board[row_no][col_no] == ' ') {
        board[row_no][col_no] = (player_turn == 1) ? 'X' : 'O';
        move_count++;

        display_board(board);

        if (check_win(board, (player_turn == 1) ? 'X' : 'O')) {
            printf("\nPlayer %d wins!\n", player_turn);
            game_win = 1;
         } else if (is_draw(move_count, game_win)) {
             printf("\nGame draw! No more moves left.\n");
            break;
        } else {
            player_turn = (player_turn == 1) ? 2 : 1;
        }
    } else {
        printf("That cell is already filled. Try again!\n");
    }
}

printf("\n=== Game Over ===\n");
}
