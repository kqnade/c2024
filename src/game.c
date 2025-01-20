#include "game.h"
#include <string.h>

void play_game(char *secret_word) {
    char guess[6];
    int attempts = 0;

    while (attempts < MAX_ATTEMPTS) {
        get_user_guess(guess);

        if (check_guess(guess, secret_word)) {
            print_win_message();
            break;
        }

        attempts++;
        print_game_status(guess, attempts);
    }

    if (attempts == MAX_ATTEMPTS) {
        print_loss_message(secret_word);
    }
}

int check_guess(char *guess, char *secret_word) {
    return strcmp(guess, secret_word) == 0;
}

