//Tic Tac Toe Header File
 
 #ifndef TICTACTOE_H
 #define TICTACTOE_H
 
 #include <stdio.h>
 
 // ===== function prototypes =====
 int  check_win(char box[3][3], char player_mark);
 void display_board(char grid[3][3]);
 int  is_draw(int move_count, int game_win);
 int  valid_move(int row_no, int col_no);
 void play_game();
 
 #endif
 