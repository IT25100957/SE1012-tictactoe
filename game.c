#include "tictactoe.h"

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












