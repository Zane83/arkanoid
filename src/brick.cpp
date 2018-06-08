#include "../include/brick.h"

arkanoid::Brick::Brick(int y_pos, int x_pos, int color):Drawable('#', y_pos, x_pos, (y_pos + height) - 1, (x_pos + width) - 1, color){
    bonus_br = false;
}

void arkanoid::Brick::set_as_bonus_brick(){
    bonus_br = true;
}

void arkanoid::Brick::set_as_normal_brick(){
    bonus_br = false;
}

bool arkanoid::Brick::is_bonus_brick(){
    return bonus_br;
}