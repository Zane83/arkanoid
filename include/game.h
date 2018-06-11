#ifndef GAME_H
#define GAME_H
#include <ncurses.h>
#include <algorithm>
#include <vector>
#include <cmath>
#include "drawable.h"
#include "bar.h"
#include "ball.h"
#include "level.h"


namespace arkanoid {

	class Game {

		//they save the size properties of the terminal
		//salbano le proprietà di dimensione del terminale
		int default_max_row, default_max_col, actual_max_row, actual_max_col;

		//it saves the character given by the input stream
		//salva il carattere dato da input
		int g_input;

		//the ball's position modifiers
		//i modificatori di posizione della pallina
		int row_mod, col_mod;

		//the Vector where Brick's instances are saved
		//il Vector dove le istanze di Brick sono salvate
		std::vector<arkanoid::Brick> bricks;

		//a Vector used to save the 'bonus balls' that give bonus to the player 
		//un Vector usato per salvare le 'bonus balls' che danno bonus al giocatore
		std::vector<arkanoid::Ball> bonusballs;

		//a Vector used to assign the 'bonus brick' role to a brick
		//un Vector usato per assegnare il ruolo di 'bonus brick' ad un mattoncino
		std::vector<unsigned> bonus_index;

		//cycles passed from the instance of the class
		//cicli passati dall'istanza della classe
		unsigned ticks;
		
		//how often the ball moves
		//frequenza con la quale la palla si muove
		unsigned ball_ticks;
		
		//total healths of the player
		//vite totali del giocatore
		unsigned health;
		
		//the current level
		//il livello attuale
		unsigned level_nr;
		
		unsigned bar_speed;

		//if true stops the execution of the game
		//se true ferma l'esecuzione del gioco
		bool stop;

		//a pointer to the current Level's instance
		//un puntatore all'istanza del Level attuale
		Level *alevel;

		Bar bar;
		Ball ball1;

		//shows the introduction screen
		//mostra la schermata di introdutione
		void introduction();

		//shows the ending screen
		//mostra la schermata finale
		void ending_message();

		//shows the new level's screen
		//mostra la schermata del nuovo livello
		void new_level_message();

		//initializes game's startup setting (executed once)
		//inizializza le impostazioni di avvio del gioco (eseguita una volta sola)
		void init_startup_settings();

		//initializes game's setting (executed for each level)
		//inizializza le impostazioni del gioco (eseguita per ogni livello)
		void init_game_settings();

		//initializes game's colors
		//inizializza i colori di gioco 
		void init_colors();

		//checks if terminal's size is changed
		//controlla se la grandezza del terminale è cambiata
		bool is_scrsize_changed();

		//applicates a color to the print function
		//applica un colore alla funzione di stampa
		void use_color(int color);

		//draws the game border
		//disegna il bordo di gioco
		void draw_border();

		//deletes the game border
		//elimina il bordo di gioco
		void delete_border();

		//updates the game's scene
		//aggiora la scena di gioco
		unsigned update_scene();

		//erases all bricks
		//elimina tutti i mattoncini
		void erase_bricks();

		//draws all bricks
		//disegna tutti i mattoncini
		void draw_bricks();

		//updates bar position in base of the conditions
		//aggiorna la posizione della barra in base alle condizioni
		void update_bar_position();

		//updates ball position in base of the conditions
		//aggiorna la posizione della pallina in base alle condizioni
		unsigned update_ball_position();

		//updates 'bonusballs' position in base of the conditions
		//aggiorna la posizione delle 'bonusballs' in base alle condizioni
		void update_bonusballs_position();

		//draws the elements that there are in the level's map
		//disegna gli elementi che ci sono nella mappa del livello
		bool load_level();

		//draws player's healths
		//disegna le vite del giocatore
		void draw_health();

		//draws the current level
		//disegna il livello attuale
		void draw_level_nr();

		public:

		Game();
		~Game();

		//returns true if the game is running
		//ritorna vero se il gioco è in esecuzione
		bool is_running();

		//terminates the execution of the game
		//termina l'esecuzione del gioco
		void exit();

		//gets a character from input
		//ottiene un carattere da input
		void get_input();

		//manages the game execution
		//gestisce l'esecuzione del gioco
		void update_all();

		//draws a Drawable object
		//disegna un oggetto di tipo Drawable
		void draw_object(Drawable &dr);

		//erases a Drawable object
		//cancella un oggetto di tipo Drawable
		void erase_object(Drawable dr);

		//terminates the actual level
		//termina il livello attuale
		void end_actual_game();

		//starts a new level
		//avvia un nuovo livello
		void new_game();
	};
}
#endif