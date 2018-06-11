#include "../include/ball.h"

//calls Drawable's default constructor with the following values
/*
/ param:
/ 'ch' is the character that will be printed
/ 'color' is the int that indicates the color and that will be passed in the Drawable's default ctor
*/

//richiama il costruttore di default di Drawable con i seguenti valori
/*
/ param:
/ 'ch' è il carattere che verrà passato al costruttore di default di Drawable
/ 'color' è l'intero indicante il colore che verrà passato al costruttore di default di Drawable
*/
arkanoid::Ball::Ball(char ch, int color):Drawable(ch, 21, 39, 21, 39, color){
    is_moving = false;
}

//see ball.h
//guarda ball.h
bool arkanoid::Ball::is_ball_moving(){
    return is_moving;
}

//see ball.h
//guarda ball.h
void arkanoid::Ball::move(){
    is_moving = true;
}

//see ball.h
//guarda ball.h
void arkanoid::Ball::stop(){
    is_moving = false;
}