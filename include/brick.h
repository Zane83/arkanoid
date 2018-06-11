#ifndef BRICK_H
#define BRICK_H
#include "drawable.h"
namespace arzanoid {

    //Brick inherits Drawable with 'public' as the most accessible level
    //Brick eredita Drawable usando 'public' come livello più accessibile
    class Brick: public Drawable {

        //true if an instance of 'Brick' is a 'bonus brick'
        //assume il valore true se un'istanza di Brick è un 'bonus brick'
        bool bonus_br;

        public:
        //static height and width of each brick
        //altezza e  larghezza statica di ogni mattoncino
        static const unsigned height = 3;
        static const unsigned width = 6;
        
        //override of Drawable's default constructor
        //override del costruttore di default di Drawable
        Brick(int y_pos, int x_pos, int color);

        //sets the instance as 'bonus brick'
        //imposta l'istanza come 'bonus brick'
        void set_as_bonus_brick();

        //sets the instance as a normal brick
        //imposta l'istanza come un normale mattone
        void set_as_normal_brick();

        //checks if the instance is a 'bonus brick'
        //controlla se l'istanza è un 'bonus brick'
        bool is_bonus_brick();
    };
}
#endif