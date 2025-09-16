#include "tictactoe.h"

int main() {
int menu_choice, size;
int keep_playing = 1;

while (keep_playing) {
    printf("\n=== TIC TAC TOE MENU ===\n");
    printf("1. Two Players (User vs User)\n");
    printf("2. User vs Computer\n");
    printf("3. Three Players (Experimental)\n");  // 3 player option added here - not complete yet - just only placeholders
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &menu_choice);

        if (menu_choice == 1 || menu_choice == 2) {
            printf("Enter board size (3–10): ");
            scanf("%d", &size);
            if (size < 3 || size > 10) {
                printf("Invalid size! Defaulting to 3x3.\n");
                size = 3;
            }
            play_game(size, menu_choice);
        }
        else if (menu_choice == 3) {
        // just placeholder for now   ------ when i add 3 player mode
        printf("Third player menu test\n\n");
        }
        else if (menu_choice == 4) {
            printf("\nExiting... Goodbye!\n");
            keep_playing = 0;
        }
        else {
            printf("\nInvalid choice! Please select 1–4.\n");
        }
    }

    return 0;
}













