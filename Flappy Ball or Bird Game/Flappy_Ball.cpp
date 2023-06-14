#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 640
#define HEIGHT 480
#define PIPE_WIDTH 50
#define PIPE_HEIGHT 400
#define BIRD_WIDTH 20
#define BIRD_HEIGHT 20

void draw_bird(int x, int y) {
setfillstyle(SOLID_FILL, YELLOW);
fillellipse(x, y, BIRD_WIDTH / 2, BIRD_HEIGHT / 2);
}

void draw_pipe(int x, int y) {
rectangle(x, 0, x + PIPE_WIDTH, y);
rectangle(x, y + 200, x + PIPE_WIDTH, HEIGHT);
}

void update_bird(int &y, int &y_speed) {
y += y_speed;
y_speed += 1;
if (y > HEIGHT) {
y = HEIGHT;
y_speed = 0;
}
if (y < 0) {
y = 0;
y_speed = 0;
}
}

int main() {
int gd = DETECT, gm;
initgraph(&gd, &gm, "");

int bird_x = 50;
int bird_y = HEIGHT / 2;
int bird_y_speed = 0;
int pipe_x = WIDTH;
int pipe_y = rand() % (HEIGHT - 200) + 100;
int score = 0;

while (1) {
    cleardevice();
    draw_bird(bird_x, bird_y);
    draw_pipe(pipe_x, pipe_y);

    if (kbhit()) {
        char ch = getch();
        if (ch == ' ') {
            bird_y_speed = -7;
        }
    }

    update_bird(bird_y, bird_y_speed);
    pipe_x -= 2;
    if (pipe_x + PIPE_WIDTH < 0) {
        pipe_x = WIDTH;
        pipe_y = rand() % (HEIGHT - 200) + 100;
        score++;
    }

    if (bird_y - BIRD_HEIGHT / 2 < pipe_y || bird_y + BIRD_HEIGHT / 2 > pipe_y + 200) {
        if (bird_x + BIRD_WIDTH / 2 > pipe_x && bird_x - BIRD_WIDTH / 2 < pipe_x + PIPE_WIDTH) {
            outtextxy(WIDTH / 2 - 50, HEIGHT / 2, "Game Over");
            break;
        }
    }

    char score_str[32];
    sprintf(score_str, "Score: %d", score);
    outtextxy(10, 10, score_str);

    delay(17);
}

getch();
closegraph();
}
