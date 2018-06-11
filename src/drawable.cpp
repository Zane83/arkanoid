#include "../include/drawable.h"

/*
/ param:
/ 'ch' is the character that will be printed
/ 'start_row' is the row index where ncurses' mvprintw function starts to draw
/ 'end_row' is the row index where ncurses' mvprintw function ends to draw
/ 'start_col' is the column index where ncurses' mvprintw function starts to draw
/ 'end_col' is the column index where ncurses' mvprintw function ends to draw
/ 'color' is the int that indicates the color with which the Drawable will be printed
*/

//richiama il costruttore di default di Drawable con i seguenti valori
/*
/ param:
/ 'ch' è il carattere che verrà passato al costruttore di default di Drawable
/ 'start_row' è l'indice di riga dove la funzione di ncurses mvprintw inizia a disegnare
/ 'end_row' è l'indice di riga dove la funzione di ncurses mvprintw termina di disegnare
/ 'start_col' è l'indice di colonna dove la funzione di ncurses mvprintw inizia a disegnare
/ 'end_col' è l'indice di colonna dove la funzione di ncurses mvprintw termina di disegnare
/ 'color' è l'intero indicante il colore che verrà passato al costruttore di default di Drawable
*/

arzanoid::Drawable::Drawable(char ch, int start_row, int start_col, int end_row, int end_col, int color):
 d_ch(ch), d_start_row(start_row), d_start_col(start_col), d_end_row(end_row), d_end_col(end_col), d_color(color), visible(true){
	 
}

//see drawable.h
//guarda drawable.h 
void arzanoid::Drawable::not_visible(){
    visible = false;
}

//see drawable.h
//guarda drawable.h 
void arzanoid::Drawable::set_visible(){
    visible = true;
}

//see drawable.h
//guarda drawable.h 
bool arzanoid::Drawable::is_visible(){
    return visible;
}

//see drawable.h
//guarda drawable.h 
void arzanoid::Drawable::set_start_row(int sr){
    d_start_row = sr;
}

//see drawable.h
//guarda drawable.h 
void arzanoid::Drawable::set_end_row(int er){
    d_end_row = er;
}

//see drawable.h
//guarda drawable.h 
void arzanoid::Drawable::set_start_col(int sc){
    d_start_col = sc;
}

//see drawable.h
//guarda drawable.h 
void arzanoid::Drawable::set_end_col(int ec){
    d_end_col = ec;
}

//see drawable.h
//guarda drawable.h 
int arzanoid::Drawable::get_start_row(){
    return d_start_row;
}

//see drawable.h
//guarda drawable.h 
int arzanoid::Drawable::get_end_row(){
    return d_end_row;
}

//see drawable.h
//guarda drawable.h 
int arzanoid::Drawable::get_start_col(){
    return d_start_col;
}

//see drawable.h
//guarda drawable.h 
int arzanoid::Drawable::get_end_col(){
    return d_end_col;
}

//see drawable.h
//guarda drawable.h 
int arzanoid::Drawable::get_color(){
    return d_color;
}

//see drawable.h
//guarda drawable.h 
char arzanoid::Drawable::get_char(){
    return d_ch;
}
