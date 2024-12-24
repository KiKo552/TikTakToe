#include <stdlib.h>

int Board[3][3] = {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
};

// Checking if the game is over
int CheckWinner() {
    // checking diagonals
    if (Board[0][0] == Board[1][1] && Board[1][1] == Board[2][2] && Board[0][0] != 0) {
        return Board[0][0];
    }
    if (Board[0][2] == Board[1][1] && Board[1][1] == Board[2][0] && Board[0][2] != 0) {
        return Board[0][2];
    }
    
    // checking rows
    for (int i = 0; i < 3; i++) {
        if (Board[i][0] == Board[i][1] && Board[i][1] == Board[i][2] && Board[i][0] != 0) {
            return Board[i][0];
        }
    }

    // checking columns
    for (int i = 0; i < 3; i++) {
        if (Board[0][i] == Board[1][i] && Board[1][i] == Board[2][i] && Board[0][i] != 0) {
            return Board[0][i];
        }
    }

    return 0;
}

// Selecting a random position (too lazy to write a whole algorithm)
void BotChoice() {
    int x, y;    
    int amount = 0;

    // filtering out the taken positions
    while (Board[x][y] != 2 || Board[x][y] != 1) {
        x = rand() % 3;
        y = rand() % 3;

        amount += 1;
        if (amount > 100) return; // to avoid infinite loops, we'll draw the board if it happens
    } 
    
    Board[x][y] = 2;
}

