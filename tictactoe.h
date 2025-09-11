//Tic Tac Toe Header File
 #ifndef TICTACTOE_H
 #define TICTACTOE_H

 #include <stdio.h>
 #include <stdlib.h>

 // ===== function prototypes =====
 int   check_win(char **box, int size, char player_mark);
 void  display_board(char **grid, int size);
 int   is_draw(int move_count, int game_win, int size);
 int   valid_move(int row_no, int col_no, int size);
 void  play_game(int size);
 void  instruct(void);

 #endif
 