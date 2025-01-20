#include "ui.h"
#include <ncurses.h>

void init_ui() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
}

void end_ui() {
    endwin();
}

void get_user_guess(char *guess) {
    // Handle user input using ncurses
    printw("Enter your guess: ");
    scanw("%5s", guess);
    // Clear the screen after input
    clear();
}

void print_game_status(char *guess, int attempts) {
    printw("Attempt %d: %s\n", attempts, guess);
    refresh();
}

void print_win_message() {
    printw("Congratulations! You guessed the word!\n");
    refresh();
}

void print_loss_message(char *secret_word) {
    printw("You lost! The secret word was: %s\n", secret_word);
    refresh();
}

