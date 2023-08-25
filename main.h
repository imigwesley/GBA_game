#ifndef MAIN_H
#define MAIN_H

#include "gba.h"

struct frog {
    int row;
    int col;
    int width;
    int height;
    int fliesEaten;
};

struct lilypad {
    int row;
    int col;
    int height;
    int width;
};

struct dragonfly {
    int row;
    int col;
    int width;
    int height;
    int isEaten;
};

struct finishLine {
    int row;
    int col;
    int height;
    int width;
};


void setLily(int r, int c, struct lilypad *l);
int leftLilypadCollision(struct frog, struct lilypad);
int rightLilypadCollision(struct frog, struct lilypad);
int bottomLilypadCollision(struct frog, struct lilypad);
int topLilypadCollision(struct frog, struct lilypad);
int leftFlyCollision(struct frog, struct dragonfly);
int rightFlyCollision(struct frog, struct dragonfly);
int bottomFlyCollision(struct frog, struct dragonfly);
int topFlyCollision(struct frog, struct dragonfly);

#endif
