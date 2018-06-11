#include "../include/brick.h"

//calls Drawable's default constructor with the following values
/*
/ param:
/ 'y_pos' is the row index of brick's top-left angle
/ 'x_pos' is the column index of brick's top-left angle
/ 'color' is the int that indicates the color and that will be passed in the Drawable's default ctor
*/

//richiama il costruttore di default di Drawable con i seguenti valori
/*
/ param:
/ 'y_pos' è l'indice di riga dell'angolo in alto a destra del mattoncino
/ 'x_pos' è l'indice di colonna dell'angolo in alto a destra del mattoncino
/ 'color' è l'intero indicante il colore che verrà passato al costruttore di default di Drawable
*/
arkanoid::Brick::Brick(int y_pos, int x_pos, int color):Drawable('#', y_pos, x_pos, (y_pos + height) - 1, (x_pos + width) - 1, color){
    bonus_br = false;
}

//see brick.h
//guarda brick.h 
void arkanoid::Brick::set_as_bonus_brick(){
    bonus_br = true;
}

//see brick.h
//guarda brick.h 
void arkanoid::Brick::set_as_normal_brick(){
    bonus_br = false;
}

//see brick.h
//guarda brick.h 
bool arkanoid::Brick::is_bonus_brick(){
    return bonus_br;
}