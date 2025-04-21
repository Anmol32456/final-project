#include <iostream>
#include <conio.h>  // For getch()
#include <ctime>
#include <cstdlib>

using namespace std;

const int SIZE = 10;
char maze[SIZE][SIZE];
int playerX, playerY;
int score = 0, moves = 0;
bool gameOver = false;
int level = 1;

// Level 1 and Level 2 definitions as strings
const char* level1[SIZE] = {
    "||||||||||",
    "P   |    |",
    "| |||||| |",
    "|    0|| |",
    "| |||| |||",
    "| |     | ",
    "| ||| | | ",
    "|  0  |  E",
    "||||| ||| ",
    "||||||||||"
};

const char* level2[SIZE] = {
    "||||||||||",
    "P |      E",
    "| | ||| | ",
    "| | |  0| ",
    "| |0| | | ",
    "| ||| | | ",
    "|   | | | ",
    "| |   | | ",
    "| ||||| | ",
    "||||||||||"
};

void loadMaze() {
    const char** source = (level == 1) ? level1 : level2;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            maze[i][j] = source[i][j];
}

void findPlayer() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (maze[i][j] == 'P') {
                playerX = i;
                playerY = j;
                return;
            }
}

void displayMaze() {
    system("cls");  // Clears the console (works in Dev-C++)
    cout << "Level " << level << endl;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            cout << maze[i][j];
        cout << endl;
    }
    cout << "Moves: " << moves << "  Score: " << score << endl;
}

void movePlayer(int dx, int dy) {
    int newX = playerX + dx;
    int newY = playerY + dy;

    // Bounds checking
    if (newX < 0 || newX >= SIZE || newY < 0 || newY >= SIZE)
        return;

    if (maze[newX][newY] == '|')
        return;
    if (maze[newX][newY] == 'E') {
        score += 100;  // Bonus
        if (level == 1) {
            level = 2;
            cout << "Level 1 complete! Press any key to continue to Level 2...\n";
            getch();
            loadMaze();
            findPlayer();
            return;
        } else {
            gameOver = true;
            cout << "You finished all levels!\n";
            cout << "Final Score: " << score << "  Moves: " << moves << endl;
            return;
        }
    }

    // Move the player
    maze[playerX][playerY] = ' ';
    playerX = newX;
    playerY = newY;
    maze[playerX][playerY] = 'P';
    moves++;
    score++;
    
}

void gameLoop() {
    while (!gameOver) {
        displayMaze();
        char input = getch();  // No need to press Enter
        switch (input) {
            case 'w': movePlayer(-1, 0); break;
            case 's': movePlayer(1, 0); break;
            case 'a': movePlayer(0, -1); break;
            case 'd': movePlayer(0, 1); break;
        }
    }
}

int main() {
    srand(time(0));
    loadMaze();
    findPlayer();
    gameLoop();
    system("pause");  // Keeps the console open at the end
    return 0;
}

