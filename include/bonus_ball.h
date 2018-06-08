#ifndef BBALL_H
#define BBALL_H
#include "drawable.h"

namespace arkanoid{

    class BonusBall: public Drawable{

        bool is_moving;

        public:
        bool is_ball_moving();
        void move();
        void stop();
        BonusBall();

    };

}

#endif