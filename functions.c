#include "tictactoe.h"

// ===== instructions =====
void instruct(void) {
    printf("========================================\n");
    printf("        WELCOME  TO  TIC  TAC  TOE!\n");
    printf("========================================\n");
    printf("HOW TO PLAY:\n");
    printf("- Player 1 uses symbol 'X' and Player 2 uses 'O'.\n");
    printf("- You will take turns entering two numbers:\n");
    printf("  • First number = row position\n");
    printf("  • Second number = column position\n");
    printf("- Rows and columns start from 0.\n");
    printf("  Example: typing '1 2' means row 1, column 2.\n");
    printf("- You can choose board size between 3 and 10.\n");
    printf("- First player to fill an entire row, column or diagonal wins!\n");
    printf("- If the board fills completely with no winner, it is a draw.\n");
    printf("========================================\n\n");
}

// ===== check all winning conditions =====
int check_win(char **box, int size, char player_mark) {
    int row_i, col_i;

    // rows
for (row_i = 0; row_i < size; row_i++) {
    int match = 1;
        for (col_i = 0; col_i < size; col_i++) {
            if (box[row_i][col_i] != player_mark)
                match = 0;
        }
if (match) return 1;
    }

// columns
for (col_i = 0; col_i < size; col_i++) {
    int match = 1;
        for (row_i = 0; row_i < size; row_i++) {
            if (box[row_i][col_i] != player_mark)
                match = 0;
        }
if (match) return 1;
    }

    // diagonal
    int match = 1;
    for (row_i = 0; row_i < size; row_i++) {
        if (box[row_i][row_i] != player_mark)
            match = 0;
    }
    if (match) return 1;

    match = 1;
    for (row_i = 0; row_i < size; row_i++) {
        if (box[row_i][size - 1 - row_i] != player_mark)
            match = 0;
    }
    if (match) return 1;

    return 0;
}

// prints the current game board
void display_board(char **grid, int size) {
int row_i, col_i;

// Print column labels
printf("\n   ");
for (col_i = 0; col_i < size; col_i++) {
    printf(" %d  ", col_i);
}
printf("\n");

for (row_i = 0; row_i < size; row_i++) {
    // Row label
    printf(" %d ", row_i);
        for (col_i = 0; col_i < size; col_i++) {
            printf(" %c ", grid[row_i][col_i]);
            if (col_i < size - 1) printf("|");
        }
        printf("\n");

        // Separator line
        if (row_i < size - 1) {
            printf("   ");
            for (col_i = 0; col_i < size; col_i++) {
                printf("---");
                if (col_i < size - 1) printf("+");
            }
        printf("\n");
        }
    }
}

// ===== draw condition =====
int is_draw(int move_count, int game_win, int size) {
    return (!game_win && move_count == size * size);
}

// ===== valid move check =====
int valid_move(int row_no, int col_no, int size) {
    return !(row_no < 0 || row_no >= size || col_no < 0 || col_no >= size);
}

// ===== log move into file =====
void log_move(FILE *fp, int move_no, int player_turn, int row_no, int col_no, char **board, int size) {
    fprintf(fp, "Move %d: Player %d (%c) at [%d, %d]\n",
            move_no, player_turn, (player_turn == 1) ? 'X' : 'O', row_no, col_no);
    fprintf(fp, "Board state:\n\n");

    // Print column labels
    fprintf(fp, "   ");
    for (int c = 0; c < size; c++) {
        fprintf(fp, " %d  ", c);
    }
    fprintf(fp, "\n");

    // Print grid with row labels
    for (int r = 0; r < size; r++) {
        fprintf(fp, " %d ", r);
        for (int c = 0; c < size; c++) {
            fprintf(fp, " %c ",board[r][c]);
            if (c < size - 1) fprintf(fp, "|");
        }
        fprintf(fp, "\n");

        if (r < size - 1) {
            fprintf(fp, "   ");
            for (int c = 0; c < size; c++) {
                fprintf(fp, "---");
                if (c < size - 1) fprintf(fp, "+");
            }
            fprintf(fp, "\n");
        }
    }

    fprintf(fp, "\n--------------------------------------\n\n");
}

// ===== main game function =====
void play_game(int size) {
    int row_no, col_no;
    int player_turn = 1;
    int move_count = 0;
    int game_win = 0;

char **board = (char **)malloc(size * sizeof(char *));
for (int i = 0; i < size; i++)
    board[i] = (char *)malloc(size * sizeof(char));

// initialize with spaces
for (int r = 0; r < size; r++)
    for (int c = 0; c < size; c++)
        board[r][c] = ' ';

    instruct();
    printf("=== TIC TAC TOE %dx%d ===\n", size, size);

    FILE *fp = fopen("game_log.txt", "w");
    if (fp == NULL) {
        printf("Error opening log file!\n");
        return;
    }
    fprintf(fp, "Tic Tac Toe Game Log (%dx%d)\n\n", size, size);

while (move_count < size * size && !game_win) {
    printf("\nPlayer %d enter row and column (0-%d): ", player_turn, size - 1);
    scanf("%d %d", &row_no, &col_no);

    if (!valid_move(row_no, col_no, size)) {
        printf("Invalid position! Try within 0-%d.\n", size - 1);
        continue;
    }

     if (board[row_no][col_no] == ' ') {
        board[row_no][col_no] = (player_turn == 1) ? 'X' : 'O';
        move_count++;

            display_board(board, size);
            log_move(fp, move_count, player_turn, row_no, col_no, board, size);

        if (check_win(board, size, (player_turn == 1) ? 'X' : 'O')) {
            printf("\nPlayer %d wins!\n", player_turn);
            fprintf(fp, "\nPlayer %d wins!\n", player_turn);
            game_win = 1;
            } 
        else if (is_draw(move_count, game_win, size)) {
            printf("\nGame draw! No more moves left.\n");
            fprintf(fp, "\nGame draw! No more moves left.\n");
            break;
        } 
        else {
            player_turn = (player_turn == 1) ? 2 : 1;
            }
        } else {
            printf("That cell is already filled! Try again.\n");
        }
    }

    fprintf(fp, "\n=== End of Game ===\n");
    fclose(fp);

for (int i = 0; i < size; i++)
    free(board[i]);
    free(board);

printf("\nGame results have been saved to 'game_log.txt'.\n");
}


 




