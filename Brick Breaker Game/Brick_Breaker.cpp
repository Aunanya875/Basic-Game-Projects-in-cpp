#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <time.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

int paddle_x = 300, paddle_y = 450;
int ball_x = 300, ball_y = 400;
int dx = -2, dy = -2;
int score = 0;
int bricks[5][10];
char buf[10];

void initialize() {
    int i, j;

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 10; j++) {
            bricks[i][j] = 1;
        }
    }
}

void draw() {
    int i, j;

    cleardevice();
    setfillstyle(SOLID_FILL, WHITE);
    bar(paddle_x, paddle_y, paddle_x + 100, paddle_y + 10);
    setfillstyle(SOLID_FILL, YELLOW);
    fillellipse(ball_x, ball_y, 10, 10);

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 10; j++) {
            if (bricks[i][j] == 1) {
                setfillstyle(SOLID_FILL, RED);
                bar(j * 60 + 12, i * 20 + 12, j * 60 + 57, i * 20 + 27);
            }
        }
    }

    outtextxy(5, 0, "Score: ");
    outtextxy(60, 0, itoa(score, buf, 10));
}

void input() {
    if (kbhit()) {
        switch (getch()) {
        case LEFT:
            paddle_x -= 20;
            break;
        case RIGHT:
            paddle_x += 20;
            break;
        }
    }

    if (paddle_x <= 0) {
        paddle_x = 0;
    }
    if (paddle_x >= 500) {
        paddle_x = 500;
    }
}

void move() {
    int i, j;

    ball_x += dx;
    ball_y += dy;

    if (ball_x >= paddle_x && ball_x <= paddle_x + 100 && ball_y >= paddle_y - 10 && ball_y <= paddle_y + 10) {
        dy = -dy;
    }

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 10; j++) {
            if (bricks[i][j] == 1) {
                if (ball_x >= j * 60 + 10 && ball_x <= j * 60 + 60 && ball_y >= i * 20 + 10 && ball_y <= i * 20 + 30) {
                    bricks[i][j] = 0;
                    dy = -dy;
                    score++;
                }
            }
        }
    }

    if (ball_x <= 0 || ball_x >= 590) {
        dx = -dx;
    }

    if (ball_y <= 0) {
        dy = -dy;
    }

    if (ball_y >= 490) {
        outtextxy(200, 200, "Game Over");
        outtextxy(200, 230, "Press any key to exit");
        delay(1000);
        getch();
        exit(0);
    }
    if (score == 50) {
        draw();
        outtextxy(200, 200, "Congratulations! You won the game.");
        delay(1000);
        getch();
        exit(0);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    initialize();
    draw();

    while (1) {
        move();
        input();
        draw();
        delay(10);
    }

    getch();
    closegraph();
    return 0;
}
