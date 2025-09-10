#include "tictactoe.h"

int main() {
int user_choice;
int keep_playing = 1;

while (keep_playing) {
    printf("\n=== TIC TAC TOE MENU ===\n");
    printf("1. Play Game\n");
    printf("2. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &user_choice);

        if (user_choice == 1) {
            play_game();
        } 
        else if (user_choice == 2) {
            printf("\nExiting... Goodbye!\n");
            keep_playing = 0;
        } 
        else {
            printf("\nInvalid choice! Please select 1 or 2.\n");
        }
    }

return 0;
}













