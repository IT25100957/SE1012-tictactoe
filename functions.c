#include "tictactoe.h"

// ===== instructions =====
void instruct(void) {
    printf("========================================\n");
    printf("        WELCOME  TO  TIC  TAC  TOE!\n");
    printf("========================================\n");
    printf("- Player 1 uses 'X'.\n");
    printf("- Player 2 uses 'O'.\n");
    printf("- In 3-Player mode, Player 3 uses 'Z'.\n");
    printf("- Enter two numbers (row column) starting from 0.\n");
    printf("- Example: 1 2 means row 1, column 2.\n");
    printf("- First to fill a row, column or diagonal wins!\n");
    printf("- Every move is recorded in game_log.txt.\n");
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
            move_no, player_turn,
            (player_turn == 1) ? 'X' :
            (player_turn == 2) ? 'O' : 'Z',
            row_no, col_no);

// Print column labels
    fprintf(fp, "Board state:\n\n   ");
    for (int c = 0; c < size; c++) fprintf(fp, " %d  ", c);
    fprintf(fp, "\n");

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
    int ok = 0;
    while (!ok) {
        *row_no = rand() % size;
        *col_no = rand() % size;
        if (board[*row_no][*col_no] == ' ')
            ok = 1;
    }
}

/* ---------- main gameplay ---------- */
void play_game(int size, int mode) {
    int row_no, col_no;
    int player_turn = 1;
    int move_count = 0, game_win = 0;
    char **board;

    board = malloc(size * sizeof(char *));
    for (int i = 0; i < size; i++)
        board[i] = malloc(size * sizeof(char));

    for (int r = 0; r < size; r++)
        for (int c = 0; c < size; c++)
            board[r][c] = ' ';

    instruct();
    srand(time(NULL));
    FILE *fp = fopen("game_log.txt", "w");
    if (!fp) return;
    fprintf(fp, "Mode %d | Board %dx%d\n\n", mode, size, size);

while (move_count < size * size && !game_win) {
    if (mode == 2 && player_turn == 2) {
        /* Computer's turn */
        generate_computer_move(board, size, &row_no, &col_no);
        printf("\nComputer chooses: %d %d\n", row_no, col_no);
    } else {
            printf("\nPlayer %d enter row and column (0-%d): ", player_turn, size - 1);
            scanf("%d %d", &row_no, &col_no);
        }

     if (!valid_move(row_no, col_no, size) || board[row_no][col_no] != ' ') {
         printf("Invalid move! Cell [%d,%d] is %s\n", 
                row_no, col_no, 
                (!valid_move(row_no, col_no, size)) ? "out of bounds" : "already occupied");
         continue;
         }

        board[row_no][col_no] = (player_turn == 1) ? 'X' : 'O';
        move_count++;

            display_board(board, size);
            log_move(fp, move_count, player_turn, row_no, col_no, board, size);

        if (check_win(board, size, (player_turn == 1) ? 'X' : 'O')) {
            printf("\nPlayer %d wins!\n", player_turn);
            fprintf(fp, "Player %d wins!\n", player_turn);
            game_win = 1;
        } else if (is_draw(move_count, game_win, size)) {
            printf("\nGame draw!\n");
            fprintf(fp, "Draw!\n");
            break;
        } else player_turn = (player_turn == 1) ? 2 : 1;
    }

    fclose(fp);
for (int i = 0; i < size; i++) free(board[i]);
    free(board);
}

// 3 player mode ------------------Added computer mode
void play_three_players(int size) {

int row_no, col_no;
int player_turn = 1;
int move_count  = 0;
int game_win    = 0;
char marks[3]   = {'X', 'O', 'Z'};
int is_human[3];

// choose which players are human
printf("\n=== 3 PLAYER MODE ===\n");
printf("Board Size: %dx%d\n", size, size);
printf("Marks: Player1 = X, Player2 = O, Player3 = Z\n");
printf("\n--- Player Type Selection ---\n");
printf("For each player, enter 1 for Human or 0 for Computer.\n");

for (int i = 0; i < 3; i++) {
    printf("Is Player %d (%c) human? (1=Yes, 0=No): ", i + 1, marks[i]);
    scanf("%d", &is_human[i]);
    if (is_human[i] != 0 && is_human[i] != 1) {
        printf("Invalid input - human will be selected.\n");
        is_human[i] = 1;
    }
}

// ensure at least one human
if (is_human[0] == 0 && is_human[1] == 0 && is_human[2] == 0) {
    printf("\nAt least one player must be human! Forcing Player 1 to be human.\n");
    is_human[0] = 1;
}

// allocate memory
char **board = malloc(size * sizeof(char *));
for (int i = 0; i < size; i++)
   board[i] = malloc(size * sizeof(char));
for (int r = 0; r < size; r++)
     for (int c = 0; c < size; c++)
         board[r][c] = ' ';

    FILE *fp = fopen("game_log.txt", "w");
    if (!fp) {
        printf("Error opening log file!\n");
        return;
    }

    fprintf(fp, "=== 3 PLAYER TIC-TAC-TOE ===\n");
    fprintf(fp, "Board Size: %dx%d\n", size, size);
    fprintf(fp, "Player Types: ");
    for (int i = 0; i < 3; i++)
        fprintf(fp, "P%d=%s  ", i + 1, (is_human[i]) ? "Human" : "Computer");
    fprintf(fp, "\n\n");

    srand(time(NULL));
    printf("\nGame Start!\n");

    while (move_count < size * size && !game_win) {

        printf("\nPlayer %d (%c) [%s] turn:\n",
               player_turn, marks[player_turn - 1],
               (is_human[player_turn - 1]) ? "Human" : "Computer");

        if (is_human[player_turn - 1]) {
            printf("Enter row and column (0-%d): ", size - 1);
            scanf("%d %d", &row_no, &col_no);
        } else {
            generate_computer_move(board, size, &row_no, &col_no);
            printf("Computer chose: %d %d\n", row_no, col_no);
        }

        if (!valid_move(row_no, col_no, size) || board[row_no][col_no] != ' ') {
            printf("Invalid or filled cell! Try again.\n");
            continue;
        }

        board[row_no][col_no] = marks[player_turn-1];
        move_count++;

        display_board(board, size);
        log_move(fp, move_count, player_turn, row_no, col_no, board, size);

        if (check_win(board, size, marks[player_turn - 1])) {
            printf("\nPlayer %d (%c) wins!\n", player_turn, marks[player_turn - 1]);
            fprintf(fp, "\nPlayer %d (%c) wins!\n", player_turn, marks[player_turn - 1]);
            game_win = 1;
        }
        else if (is_draw(move_count, game_win, size)) {
            printf("\nGame Draw!\n");
            fprintf(fp, "\nGame Draw!\n");
            break;
        }
        else {
            player_turn++;
            if (player_turn > 3) player_turn = 1;
        }
    }

    fprintf(fp, "\n=== End of Game ===\n");
    fclose(fp);

    for (int i = 0; i < size; i++) free(board[i]);
    free(board);

    printf("\nGame saved to game_log.txt\n");
}




