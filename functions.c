#include "tictactoe.h"

// ===== instructions =====
void instruct(void) {
    printf("========================================\n");
    printf("        WELCOME  TO  TIC  TAC  TOE!\n");
    printf("========================================\n");
    printf("HOW TO PLAY:\n");
    printf("- Player 1 uses 'X'. Player 2 (or Computer) uses 'O'.\n");
    printf("- Enter two numbers: row and column (starting from 0).\n");
    printf("- Example: '1 2' means row 1, column 2.\n");
    printf("- You can choose board size between 3 and 10.\n");
    printf("- First to fill an entire row, column or diagonal wins.\n");
    printf("- Every move is saved to 'game_log.txt'.\n");
    printf("========================================\n\n");
}

// ===== check all winning conditions =====
int check_win(char **box, int size, char player_mark) {
int r, c, match;
    for (r = 0; r < size; r++) {
        match = 1;
        for (c = 0; c < size; c++)
            if (box[r][c] != player_mark) match = 0;
        if (match) return 1;
    }
    for (c = 0; c < size; c++) {
        match = 1;
        for (r = 0; r < size; r++)
            if (box[r][c] != player_mark) match = 0;
        if (match) return 1;
    }
    match = 1;
    for (r = 0; r < size; r++)
        if (box[r][r] != player_mark) match = 0;
    if (match) return 1;
    match = 1;
    for (r = 0; r < size; r++)
        if (box[r][size-1-r] != player_mark) match = 0;
    if (match) return 1;
    return 0;
}

// prints the current game board
void display_board(char **grid, int size) {
int r, c;
printf("\n   ");
for (c = 0; c < size; c++) printf(" %d  ", c);
printf("\n");
for (r = 0; r < size; r++) {
    printf(" %d ", r);
    for (c = 0; c < size; c++) {
        printf(" %c ", grid[r][c]);
        if (c < size - 1) printf("|");
    }
        printf("\n");
        if (r < size - 1) {
            printf("   ");
            for (c = 0; c < size; c++) {
                printf("---");
                if (c < size - 1) printf("+");
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
    for (int c = 0; c < size; c++) fprintf(fp, " %d  ", c);
    fprintf(fp, "\n");

    // Print grid with row labels
    for (int r = 0; r < size; r++) {
        fprintf(fp, " %d ", r);
        for (int c = 0; c < size; c++) {
            fprintf(fp, " %c ", board[r][c]);
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

// Computer move generation using rand
void generate_computer_move(char **board, int size, int *row_no, int *col_no) {
    int valid = 0;
    int r, c;
    while (!valid) {
        r = rand() % size;
        c = rand() % size;
        if (board[r][c] == ' ') {
            valid = 1;
            *row_no = r;
            *col_no = c;
        }
    }
}

/* ---------- main gameplay ---------- */
void play_game(int size, int mode) {
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
    srand(time(NULL));
    FILE *fp = fopen("game_log.txt", "w");
    if (!fp) { printf("File open error!\n"); return; }
    fprintf(fp, "Tic Tac Toe (%dx%d) - Mode %d\n\n", size, size, mode);

    printf("=== TIC TAC TOE %dx%d ===\n", size, size);

while (move_count < size * size && !game_win) {
    if (mode == 2 && player_turn == 2) {
        /* Computer's turn */
        generate_computer_move(board, size, &row_no, &col_no);
        printf("\nComputer chooses: %d %d\n", row_no, col_no);
    } else {
            printf("\nPlayer %d enter row and column (0-%d): ", player_turn, size - 1);
            scanf("%d %d", &row_no, &col_no);
        }

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
            if (mode == 2 && player_turn == 2)
                printf("\nComputer wins!\n");
            else
                printf("\nPlayer %d wins!\n", player_turn);
            fprintf(fp, "\nPlayer %d wins!\n", player_turn);
            game_win = 1;
        } else if (is_draw(move_count, game_win, size)) {
            printf("\nGame draw! No more moves left.\n");
            fprintf(fp, "\nGame draw!\n");
            break;
        } else {
            player_turn = (player_turn == 1) ? 2 : 1;
            }
        } else if (mode == 1 || (mode == 2 && player_turn == 1)) {
            printf("That cell is already filled! Try again.\n");
        }
    }

    fprintf(fp, "\n=== End of Game ===\n");
    fclose(fp);
for (int i = 0; i < size; i++) free(board[i]);
    free(board);
printf("\nGame results saved to 'game_log.txt'.\n");
}

// 3 player mode ------------------test
void play_three_players(int size) {

int row_no, col_no;
int player_turn = 1;
int move_count  = 0;
int game_win    = 0;

char marks[3] = {'X', 'O', 'Z'};     
char **board;

board = (char **)malloc(size * sizeof(char *));
    for (int i = 0; i < size; i++)
        board[i] = (char *)malloc(size * sizeof(char));

    for (int r = 0; r < size; r++)
        for (int c = 0; c < size; c++)
            board[r][c] = ' ';

    printf("\n Three Player \n");
    printf("Players:\n  P1 = X\n  P2 = O\n  P3 = Z\n\n");

    while (move_count < size * size && !game_win) {
        printf("Player %d (%c) enter row and column (0-%d): ",
               player_turn, marks[player_turn - 1], size - 1);
        scanf("%d %d", &row_no, &col_no);

        if (row_no < 0 || row_no >= size || col_no < 0 || col_no >= size) {
            printf("Invalid! Try again.\n");
            continue;
        }

        if (board[row_no][col_no] == ' ') {
            board[row_no][col_no] = marks[player_turn - 1];
            move_count++;
            display_board(board, size);

            if (check_win(board, size, marks[player_turn - 1])) {
                printf("\nPlayer %d wins!\n", player_turn);
                game_win = 1;
            } else {
                // rotate turns 1→2→3→1
                player_turn++;
                if (player_turn > 3) player_turn = 1;
            }
        } else {
            printf("Cell already filled.\n");
        }
    }

    if (!game_win)
        printf("\nGame draw!\n");

    for (int i = 0; i < size; i++)
        free(board[i]);
    free(board);
}




