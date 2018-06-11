#include "../include/level.h"

//default contructor
//sets the characteristics of the class' instance

//costruttore di default
//imposta le caratteritiche dell'istanza della classe
arzanoid::Level::Level(){
    map_num_rows = 19;
    map_num_cols = 80;
    //number of horizontal slots where bricks can be placed
    //numero degli slot orizzontali dove i mattoncini possono essere inseriti
    slots = (map_num_cols - 2) / arzanoid::Brick::width;

    //number of vertical slots where bricks can be placed
    //numero degli slot verticali dove i mattoncini possono essere inseriti
    heights = (map_num_rows - 1) / arzanoid::Brick::height;
    
    //number of total slots within the map
    //numero di slot totali all'interno della mappa
    combinations = slots * heights;
    M = new int*[map_num_rows + 5];
    for(int i = 0; i < (map_num_rows + 5); i++){
        M[i] = new int[map_num_cols];
    }
    init_level(1);

}


//see level.h
//guarda level.h
arzanoid::Level::~Level(){
    for(int i = 0; i < map_num_rows + 4; i++){
        delete[] M[i];
    }

    delete[] M;
}


void arzanoid::Level::init_level(unsigned difficulty){
    level_nr = difficulty;
    srand (time(NULL));
    init_map();
    //the number of total bricks incrase each level by 1.5 (the +10 at the end indicates the winning block)
    //il numero totale di mattoni aumenta ogni livello di 1.5 (il +10 alla fine indica il blocco vincente)
    brick_nr = round(difficulty * (static_cast<float>(3) / static_cast<float>(2))) + 10;
    winning_block_positioning();
    
    //positions in random way the other bricks
    //positiona in modo casuale gli altri mattoni
    for(int i = 10; i < brick_nr && i <= combinations; i++){
        random_elements_positioning(i);
    }

}

void arzanoid::Level::winning_block_positioning(){
    int row = rand() % (heights - 2 - (level_nr / 16)) + 1;
    int col = rand() % (slots - 2) + 1;

    //positions the winning brick in a frame of normal bricks, in a random position in the map
    //positiona il mattone vincente in una cornice di mattoni normali, in una posizione casuale nella mappa
    corner_elements_positioning(1, col, row);
    corner_elements_positioning(2, col - 1, row);
    corner_elements_positioning(3, col + 1, row);
    corner_elements_positioning(4, col, row + 1);
    corner_elements_positioning(5, col, row - 1);
    corner_elements_positioning(6, col + 1, row + 1);
    corner_elements_positioning(7, col - 1, row - 1);
    corner_elements_positioning(8, col - 1, row + 1);
    corner_elements_positioning(9, col + 1, row - 1);
}

//see level.h
//guarda level.h
void arzanoid::Level::init_map(){
    for(int i = 1; i < map_num_rows + 5; i++){
        for(int j = 1; j < map_num_cols; j++){
            M[i][j] = 0;
        }
    }

    for(int i = 0; i < map_num_rows + 5; i++){
        M[i][0] = -1;
        M[i][map_num_cols - 1] = -1;
    }

    for(int j = 0; j < map_num_cols; j++){
        M[0][j] = -1;
    }
    
}

bool arzanoid::Level::corner_elements_positioning(int element_number, int col_shift, int row_shift){

    //it takes the row and column spacing from first slots (top-left corner) using a parameter
    //prende lo spaziamento dal primo slot (angolo in alto a destra) usando un parametro
    for(int i = row_shift; i < heights; i++){
        for(int j = col_shift; j < slots; j++){
            if(M[1 + (arzanoid::Brick::height * i)][1 + (arzanoid::Brick::width * j)] == 0){
                mark_element(1 + (i * arzanoid::Brick::height), 1 + (arzanoid::Brick::width * j), element_number);
                return true;
            }
        }  
    }

    return false;
}

void arzanoid::Level::random_elements_positioning(int element_number){

    unsigned i, slot;
    bool positionated = false;

    while(!positionated){

        //it takes the row and column spacing from first slots (top-left corner) in a random way
        //prende lo spaziamento dal primo slot (angolo in alto a destra) in modo casuale
        i = rand() % heights;
        slot = rand() % slots;
        if(M[1 + (i * arzanoid::Brick::height)][1 + (arzanoid::Brick::width * slot)] == 0){
            mark_element(1 + (i * arzanoid::Brick::height), 1 + (arzanoid::Brick::width * slot), element_number);
            positionated = true;
        }
    }
}

//see level.h
//guarda level.h
void arzanoid::Level::mark_element(int start_r, int start_c, int element_number){
    
    for(int i = start_r; i < start_r + arzanoid::Brick::height; i++){
        for(int j = start_c; j < start_c + arzanoid::Brick::width; j++){
            M[i][j] = element_number;
        }
    }
}

//see level.h
//guarda level.h
unsigned arzanoid::Level::get_brick_nr(){
    return brick_nr;
}

//see level.h
//guarda level.h
unsigned arzanoid::Level::get_map_num_rows(){
    return map_num_rows;
}

//see level.h
//guarda level.h
unsigned arzanoid::Level::get_map_num_cols(){
    return map_num_cols;
}

//see level.h
//guarda level.h
int arzanoid::Level::get_matrix(unsigned r_idx, unsigned c_idx){
    return M[r_idx][c_idx];
}