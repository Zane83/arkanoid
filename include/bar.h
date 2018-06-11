#ifndef BAR_H
#define BAR_H
#include "drawable.h"
namespace arkanoid{

    //Bar inherits Drawable with 'public' as the most accessible level
    //Bar eredita Drawable usando 'public' come livello più accessibile
    class Bar: public Drawable {
        public:
        //override of Drawable's default constructor
        //override del costruttore di default di Drawable
        Bar();
    };

}
#endif