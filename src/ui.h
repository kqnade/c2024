#ifndef UI_H
#define UI_H

// Function to initialize the ncurses environment
void init_ui();

// Function to clean up and end the ncurses session
void end_ui();

// Function to get the user's guess from the terminal
void get_user_guess(char *guess);

// Function to print the current game status (guess and attempts)
void print_game_status(char *guess, int attempts);

// Function to print a win message to the user
void print_win_message();

// Function to print a loss message with the secret word
void print_loss_message(char *secret_word);

#endif  // UI_H

