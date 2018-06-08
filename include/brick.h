#ifndef BRICK_H
#define BRICK_H
#include "drawable.h"
namespace arkanoid {

    class Brick: public Drawable {

        bool bonus_br;

        public:
        static const unsigned height = 3;
        static const unsigned width = 6;
        
        Brick(int y_pos, int x_pos, int color);
        void set_as_bonus_brick();
        void set_as_normal_brick();
        bool is_bonus_brick();
    };
}
#endif