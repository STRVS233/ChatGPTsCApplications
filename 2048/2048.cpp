#include <iostream>
#include <conio.h>

const int SIZE = 4;

class Game2048 {
private:
    int board[SIZE][SIZE];

public:
    Game2048() {
        // Initialize the board with zeros
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                board[i][j] = 0;
            }
        }
    }

    // Function to display the board
    void display() {
        system("cls"); // Clear the console (Windows specific)
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                std::cout << board[i][j] << "\t";
            }
            std::cout << std::endl;
        }
    }

    // Function to check if the game is over (no more valid moves)
    bool isGameOver() {
        // Check for any empty cell
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == 0) {
                    return false;
                }
            }
        }

        // Check for any possible merges
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE - 1; j++) {
                if (board[i][j] == board[i][j + 1] || board[j][i] == board[j + 1][i]) {
                    return false;
                }
            }
        }

        return true;
    }

    // Function to add a random tile (either 2 or 4) to an empty cell
    void addRandomTile() {
        int emptyCells[SIZE * SIZE][2];
        int count = 0;

        // Find all empty cells
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == 0) {
                    emptyCells[count][0] = i;
                    emptyCells[count][1] = j;
                    count++;
                }
            }
        }

        if (count > 0) {
            // Choose a random empty cell
            int index = rand() % count;
            int value = (rand() % 2 + 1) * 2; // Randomly choose 2 or 4
            board[emptyCells[index][0]][emptyCells[index][1]] = value;
        }
    }

    // Function to perform left swipe
    void swipeLeft() {
        for (int i = 0; i < SIZE; i++) {
            int writeIdx = 0;
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] != 0) {
                    if (writeIdx > 0 && board[i][j] == board[i][writeIdx - 1]) {
                        // Merge tiles if they are the same
                        board[i][writeIdx - 1] *= 2;
                        board[i][j] = 0;
                    } else {
                        // Move the tile to the leftmost empty position
                        board[i][writeIdx] = board[i][j];
                        if (j != writeIdx) {
                            board[i][j] = 0;
                        }
                        writeIdx++;
                    }
                }
            }
        }
    }
    void swipeUp() {
        for (int j = 0; j < SIZE; j++) {
            int writeIdx = 0;
            for (int i = 0; i < SIZE; i++) {
                if (board[i][j] != 0) {
                    if (writeIdx > 0 && board[i][j] == board[writeIdx - 1][j]) {
                        // Merge tiles if they are the same
                        board[writeIdx - 1][j] *= 2;
                        board[i][j] = 0;
                    } else {
                        // Move the tile to the topmost empty position
                        board[writeIdx][j] = board[i][j];
                        if (i != writeIdx) {
                            board[i][j] = 0;
                        }
                        writeIdx++;
                    }
                }
            }
        }
    }
    void swipeDown() {
        for (int j = 0; j < SIZE; j++) {
            int writeIdx = SIZE - 1;
            for (int i = SIZE - 1; i >= 0; i--) {
                if (board[i][j] != 0) {
                    if (writeIdx < SIZE - 1 && board[i][j] == board[writeIdx + 1][j]) {
                        // Merge tiles if they are the same
                        board[writeIdx + 1][j] *= 2;
                        board[i][j] = 0;
                    } else {
                        // Move the tile to the bottommost empty position
                        board[writeIdx][j] = board[i][j];
                        if (i != writeIdx) {
                            board[i][j] = 0;
                        }
                        writeIdx--;
                    }
                }
            }
        }
    }
    void swipeRight() {
        for (int i = 0; i < SIZE; i++) {
            int writeIdx = SIZE - 1;
            for (int j = SIZE - 1; j >= 0; j--) {
                if (board[i][j] != 0) {
                    if (writeIdx < SIZE - 1 && board[i][j] == board[i][writeIdx + 1]) {
                        // Merge tiles if they are the same
                        board[i][writeIdx + 1] *= 2;
                        board[i][j] = 0;
                    } else {
                        // Move the tile to the rightmost empty position
                        board[i][writeIdx] = board[i][j];
                        if (j != writeIdx) {
                            board[i][j] = 0;
                        }
                        writeIdx--;
                    }
                }
            }
        }
    }
    // Function to handle user input
    void handleInput() {
        char ch = getch(); // Read a character from the console
        switch (ch) {
            case 'a':
            case 'A':
                swipeLeft();
                break;
            case 'd':
            case 'D':
                swipeRight();
                break;
            case 'w':
            case 'W':
                swipeUp();
                break;
            case 's':
            case 'S':
                swipeDown();
                break;
            default:
                break;
        }
    }

    // Function to start the game
    void play() {
        // Add two random tiles to start the game
        addRandomTile();
        addRandomTile();

        while (!isGameOver()) {
            display();
            handleInput();
            addRandomTile();
        }

        display();
        std::cout << "Game Over! No more valid moves." << std::endl;
    }
};

int main() {
    srand(static_cast<unsigned>(time(0))); // Seed the random number generator
    Game2048 game;
    game.play();
    system("pause");
    return 0;
}
