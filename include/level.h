#ifndef LEVEL_H
#define LEVEL_H
#include <ctime>
#include <random>
#include <ncurses.h>
#include "brick.h"
namespace arkanoid {

    class Level {
        //characteristics of each Level's instance
        //caratteristiche di ogni istanza di Level
        unsigned brick_nr, level_nr, slots, heights, combinations, map_num_rows, map_num_cols;

        //the level's map saved in a matrix
        //la mappa del livello salvata in una matrice
        int **M;
        
        //initializes the level's map
        //inizializza la mappa del livello
        void init_map();

        //positions the elements starting by the left or right corner
        //positiona gli elementi partendo dall'angolo sinistro o destro
        bool corner_elements_positioning(int element_number, int col_shift, int row_shift);

        //positions the elements in a random way
        //positiona gli elementi in modo casuale
        void random_elements_positioning(int element_number);

        //positions the winning brick' and the bricks near to it
        //posiziona il 'winning brick' e i mattoncini vicino ad esso
        void winning_block_positioning();

        public:

        //default constructor
        //costruttore di default
        Level();

        //the class' destructor, used to delete the dynamic matrix
        //il distruttore della classe, usato per eliminare la matrice dinamica
        ~Level();

        //initializes the level
        //inizializza il livello
        void init_level(unsigned difficulty);

        //returns the number of bricks that there are within the map
        //ritorna il numero di mattncini che ci sono nella mappa
        unsigned get_brick_nr();

        //returns the map's rows number
        //ritorna il numero di righe della mappa
        unsigned get_map_num_rows();

        //returns the map's cols number
        //ritorna il numero di colonne della mappa
        unsigned get_map_num_cols();

        //mark the map's cells with the brick's id
        //evidenzia le celle della mappa con l'id del mattoncino
        void mark_element(int start_r, int start_c, int element_number);

        //returns an element of a matrix
        //ritorna un elemento della matrice
        int get_matrix(unsigned r_idx, unsigned c_idx);
    };
}
#endif