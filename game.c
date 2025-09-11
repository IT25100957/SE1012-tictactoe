#include "tictactoe.h"

int main() {
int user_choice, size;
int keep_playing = 1;

while (keep_playing) {
    printf("\n=== TIC TAC TOE MENU ===\n");
    printf("1. Play Game\n");
    printf("2. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &user_choice);

        if (user_choice == 1) {
            printf("Enter board size (3–10): ");
            scanf("%d", &size);
            if (size < 3 || size > 10) {
                printf("Invalid size! Defaulting to 3x3.\n");
                size = 3;
            }
            play_game(size);
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













