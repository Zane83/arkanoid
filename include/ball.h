#ifndef BALL_H
#define BALL_H
#include "drawable.h"

namespace arkanoid{

    //Ball inherits Drawable with 'public' as the most accessible level
    //Ball eredita Drawable usando 'public' come livello più accessibile
    class Ball: public Drawable{

        //true if a Ball instance is moving
        //assume il valore vero se un'istanza di Ball si sta muovendo
        bool is_moving;

        public:
        //returns the value of the member 'bool is_moving'
        //ritorna il valore del membro 'bool is_moving'
        bool is_ball_moving();
        //sets 'bool is_moving' as true
        //imposta a true 'bool is_moving'
        void move();
        //sets 'bool is_moving' as false
        //imposta a false 'bool is_moving'
        void stop();
        //override of Drawable's default constructor
        //override del costruttore di default di Drawable
        Ball(char ch, int color);

    };

}

#endif