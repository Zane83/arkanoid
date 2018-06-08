#include "../include/bonus_ball.h"

arkanoid::BonusBall::BonusBall():Drawable('*', 0, 0, 0, 0, 4){
    
}

bool arkanoid::BonusBall::is_ball_moving(){
    return is_moving;
}

void arkanoid::BonusBall::move(){
    is_moving = true;
}

void arkanoid::BonusBall::stop(){
    is_moving = false;
}