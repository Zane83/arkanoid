#include "../include/ball.h"

arkanoid::Ball::Ball():Drawable('o', 21, 39, 21, 39, 5){
    is_moving = false;
}

bool arkanoid::Ball::is_ball_moving(){
    return is_moving;
}

void arkanoid::Ball::move(){
    is_moving = true;
}

void arkanoid::Ball::stop(){
    is_moving = false;
}