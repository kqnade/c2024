#include "words.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WORDLIST_SIZE 1000

char *load_secret_word() {
    FILE *file = fopen("wordlist.txt", "r");
    if (!file) {
        perror("Failed to open wordlist file");
        exit(1);
    }

    // Load the words into an array
    char words[WORDLIST_SIZE][6];
    int index = 0;
    while (fgets(words[index], sizeof(words[index]), file)) {
        words[index][strcspn(words[index], "\n")] = '\0'; // Remove newline
        index++;
    }

    fclose(file);

    // Choose a random word from the list
    srand(time(NULL));
    int rand_index = rand() % index;
    return words[rand_index];
}

