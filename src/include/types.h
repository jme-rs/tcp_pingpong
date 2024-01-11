#ifndef TYPES_H_
#define TYPES_H_


#define MAX_X           100
#define MAX_Y           30
#define BOUNDARY_HEIGHT 4
#define BALL_SPEED      2
#define PADDLE_WIDTH    9
#define PADDLE_POS_Y    6


// ball position
typedef struct {
    double x;
    double y;
    double angle;
} ball_t;

// paddle position
typedef int paddle_t;


#endif // TYPES_H_