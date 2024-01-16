#ifndef TYPES_H
#define TYPES_H


#include <inttypes.h>
#include <stdbool.h>

#define MAX_X           50
#define MAX_Y           30
#define BOUNDARY_HEIGHT 4
#define BALL_SPEED      0.05
#define PADDLE_WIDTH    9
#define PADDLE_POS_Y    6


// ball position
typedef struct {
    double x;
    double y;
    double angle;
} ball_t;

// paddle position
typedef int32_t paddle_t;
typedef int8_t  round_t;
typedef bool    quitflag_t;

typedef struct {
    round_t    round;
    ball_t     ball_pos;
    paddle_t   op_paddle_pos;
    quitflag_t op_is_connected;
    quitflag_t game_finish;
} to_client_t;

typedef struct {
    paddle_t   paddle_pos;
    quitflag_t is_connected;
} to_server_t;


#endif // TYPES_H