#include <graphics.h>
#include <conio.h>

const int width = 400;
const int height = 400;
const int gridSize = 100;
const int gridOffset = 50;

char grid[3][3] = { { ' ', ' ', ' ' }, { ' ', ' ', ' ' }, { ' ', ' ', ' ' } };
bool gameOver = false;
char currentPlayer = 'X';

void drawGrid() {
    setcolor(WHITE);
    for (int i = 1; i <= 2; ++i) {
        line(gridOffset, i * gridSize + gridOffset, width - gridOffset, i * gridSize + gridOffset);
        line(i * gridSize + gridOffset, gridOffset, i * gridSize + gridOffset, height - gridOffset);
    }
}

void drawSymbol(int row, int col) {
    int x = col * gridSize + gridOffset + gridSize / 2;
    int y = row * gridSize + gridOffset + gridSize / 2;

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
    setcolor(WHITE);
    char symbol = currentPlayer;  // Use currentPlayer directly
    outtextxy(x - textwidth(&symbol) / 2, y - textheight(&symbol) / 2 , &symbol);
}

bool isMoveValid(int row, int col) {
    if (row < 0 || row >= 3 || col < 0 || col >= 3 || grid[row][col] != ' ') {
        return false;
    }
    return true;
}

bool checkWin() {
    // Check rows
    for (int i = 0; i < 3; ++i) {
        if (grid[i][0] != ' ' && grid[i][0] == grid[i][1] && grid[i][0] == grid[i][2]) {
            return true;
        }
    }

    // Check columns
    for (int i = 0; i < 3; ++i) {
        if (grid[0][i] != ' ' && grid[0][i] == grid[1][i] && grid[0][i] == grid[2][i]) {
            return true;
        }
    }

    // Check diagonals
    if (grid[0][0] != ' ' && grid[0][0] == grid[1][1] && grid[0][0] == grid[2][2]) {
        return true;
    }
    if (grid[0][2] != ' ' && grid[0][2] == grid[1][1] && grid[0][2] == grid[2][0]) {
        return true;
    }

    return false;
}

void resetGame() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            grid[i][j] = ' ';
        }
    }
    gameOver = false;
    currentPlayer = 'X';
    cleardevice();
    drawGrid();
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
    outtextxy(width / 2 - textwidth("Tic-Tac-Toe") / 2, 10, "Tic-Tac-Toe");

    drawGrid();

    while (!gameOver) {
        if (kbhit()) {
            char key = getch();
            if (key == 27) {
                break;  // Escape key to exit
            }
        }

        if (ismouseclick(WM_LBUTTONDOWN)) {
            int mx = mousex();
            int my = mousey();

            int row = (my - gridOffset) / gridSize;
            int col = (mx - gridOffset) / gridSize;

            if (isMoveValid(row, col)) {
                grid[row][col] = currentPlayer;
                drawSymbol(row, col);

                if (checkWin()) {
                    setcolor(WHITE);
                    settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
                    char winMessage[15];
                    sprintf(winMessage, "Player %c Wins!", currentPlayer);  // Use currentPlayer directly
                    outtextxy(width / 8 - textwidth(winMessage) / 8, (height + 20) - (textheight(&currentPlayer) + 20), winMessage);
                    gameOver = true;
                } else {
                    bool isTie = true;
                    for (int i = 0; i < 3; ++i) {
                        for (int j = 0; j < 3; ++j) {
                            if (grid[i][j] == ' ') {
                                isTie = false;
                                break;
                            }
                        }
                    }
                    if (isTie) {
                        setcolor(WHITE);
                        settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
                        outtextxy(width / 8 - textwidth("It's a Tie!") / 8, (height + 20) - (textheight("X") + 20), "It's a Tie!");
                        gameOver = true;
                    }
                }

                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }

            clearmouseclick(WM_LBUTTONDOWN);
        }
    }

    getch();
    closegraph();
    return 0;
}
