#ifndef DRAWABLE_H
#define DRAWABLE_H
namespace arkanoid {

	class Drawable {

		//the character that will be printed with ncurses' mvprintw function
		//il carattere che verrà stampato utilizzando la funzione mvprintw di ncurses
        char d_ch;

		//row and column limits within the Drawable exists
		//limiti di riga e colonna entro i quali il Drawable esiste
		int d_start_row, d_start_col, d_end_row, d_end_col;

		//the Drawable color
		//il colore del Drawable
		int d_color;

		//true if the instance is visible
		//assume il valore true se l'instanza è visibile
		bool visible;
        
        public:

		//class' constructor
		//il costruttore della classe
		Drawable(char ch, int start_row, int start_col, int end_row, int end_col, int color);

		//sets the instance as not visible
		//imposta l'istanza come non visible
		void not_visible();

		//sets the instance as visible
		//imposta l'istanza come visibile
		void set_visible();

		//sets the Drawable's start row index
		//imposta l'indice di inizio riga del Drawable
		void set_start_row(int);

		//sets the Drawable's end row index
		//imposta l'indice di fine riga del Drawable
		void set_end_row(int);

		//sets the Drawable's start column index
		//imposta l'indice di inizio colonna del Drawable
		void set_start_col(int);

		//sets the Drawable's end column index
		//imposta l'indice di fine colonna del Drawable
		void set_end_col(int);

		//returns the Drawable's start row index
		//ritorna l'indice di inizio riga del Drawable
		int get_start_row();

		//returns the Drawable's end row index
		//ritorna l'indice di fine riga del Drawable
		int get_end_row();

		//returns the Drawable's start column index
		//ritorna l'indice di inizio colonna del Drawable
		int get_start_col();

		//returns the Drawable's end column index
		//ritorna l'indice di fine colonna del Drawable
		int get_end_col();

		//returns the Drawable's color
		//ritorna il colore del Drawable
		int get_color();

		//returns the Drawable's character that will be printed
		//ritorna il carattere del Drawable che verrà stampato
		char get_char();

		//checks if the Drawable is visible
		//controlla se il Drawable è visibile
		bool is_visible();

    };

}
#endif