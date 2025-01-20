#include "game.h"
#include "ui.h"
#include "words.h"

int main() {
    init_ui();
    char *secret_word = load_secret_word();
    play_game(secret_word);
    end_ui();
    
    return 0;
}

