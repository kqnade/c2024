#ifndef GAME_H
#define GAME_H
#define MAX_ATTEMPTS 6

void play_game(char *secret_word);
int check_guess(char *guess, char *secret_word);
void print_win_message();
void print_loss_message(char *secret_word);
void print_game_status(char *guess, int attempts);

#endif

