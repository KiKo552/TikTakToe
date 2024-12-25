#include <stdlib.h>
#include "Settings.h"

int Board[9] = {0};

// Converting the position (of the player's choice) to the board
int PlayerChoice(int position) {
    if (position < 1 || position > 9) return 0;
    
    if (Board[position - 1] == 0) {
        Board[position - 1] = PLAYER;
        printf("Position %d is selected\n", (position - 1));
        return 1;
    }
    return 0;
}

// Selecting a random position (too lazy to write a whole algorithm)
int BotChoice() {
    int available_positions[9];
    int count = 0;
    
    // find all available positions
    for (int i = 0; i < 9; i++) {
        if (Board[i] == 0) {
            available_positions[count++] = i;
        }
    }
    
    if (count == 0) return 0;
    
    // choose random available position
    int choice = available_positions[rand() % count];
    Board[choice] = BOT;
    
    return choice;
}

// Checking if the game is over
int CheckWinner() {
    // Check diagonals
    if (Board[0] == Board[4] && Board[4] == Board[8] && Board[0] != 0) {
        return Board[0];
    }
    if (Board[2] == Board[4] && Board[4] == Board[6] && Board[2] != 0) {
        return Board[2];
    }

    // Check rows
    for (int i = 0; i < 9; i += 3) {
        if (Board[i] == Board[i+1] && Board[i+1] == Board[i+2] && Board[i] != 0) {
            return Board[i];
        }
    }

    // Check columns
    for (int i = 0; i < 3; i++) {
        if (Board[i] == Board[i+3] && Board[i+3] == Board[i+6] && Board[i] != 0) {
            return Board[i];
        }
    }
    
    return 0;
}
