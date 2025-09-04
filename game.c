#include <stdio.h>

// ====== Function Prototypes ======
int check_win(char box[3][3]);
void display_board(char grid[3][3]);
int is_draw(int move_count, int game_win);

// =================================
int main() {
    char board[3][3] = {
        {' ',' ',' '},
        {' ',' ',' '},
        {' ',' ',' '}
    };
    int player_turn = 1;
    int move_count = 0;
    int row_no, col_no;
    int game_win = 0;

    printf("=== TIC TAC TOE ===\n");

    while (move_count < 9 && !game_win) {
        printf("\nPlayer %d enter row and column (0-2): ", player_turn);
        scanf("%d %d", &row_no, &col_no);

        if (board[row_no][col_no] == ' ') {
            board[row_no][col_no] = (player_turn == 1) ? 'X' : 'O';
            move_count++;

            display_board(board);

            if (check_win(board)) {
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
    return 0;
}

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

    // check diagonals
    if (box[0][0] == box[1][1] &&
        box[1][1] == box[2][2] &&
        box[0][0] != ' ')
        return 1;

    if (box[0][2] == box[1][1] &&
        box[1][1] == box[2][0] &&
        box[0][2] != ' ')
        return 1;

    return 0;
}

void display_board(char grid[3][3]) {
    int row_i, col_i;
    printf("\nCurrent board:\n");
    for (row_i = 0; row_i < 3; row_i++) {
        for (col_i = 0; col_i < 3; col_i++)
            printf("|%c", grid[row_i][col_i]);
        printf("|\n");
    }
}

int is_draw(int move_count, int game_win) {
    if (!game_win && move_count == 9)
        return 1;
    return 0;
}










