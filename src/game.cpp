#include "../include/game.h"

void arzanoid::Game::introduction(){

	//prints an introduction message in a black background
	//stampa un messaggio di introduzione in uno sfondo nero
	getmaxyx(stdscr, actual_max_row, actual_max_col);
	use_color(5);
	mvprintw(actual_max_row / 2, (actual_max_col / 2) - 9, "Benvenuti su Arzanoid");
	mvprintw(round(actual_max_row * (static_cast<float>(3)/static_cast<float>(4))), round(actual_max_col * (static_cast<float>(1)/static_cast<float>(4))) - 15, "Developed by Antonio Agostino");
	mvprintw(round(actual_max_row * (static_cast<float>(3)/static_cast<float>(4))), round(actual_max_col * (static_cast<float>(3)/static_cast<float>(4))) - 12, "https://github.com/Zane83");
	use_color(2);
	mvprintw(round(actual_max_row * (static_cast<float>(9)/static_cast<float>(10))), (actual_max_col / 2) - 14, "Premi un tasto per continuare");
	refresh();
	getch();
	clear();
}

void arzanoid::Game::ending_message(){

	//prints an ending message in a black background
	//stampa un messaggio finale in uno sfondo nero
	clear();
	use_color(5);
	mvprintw(actual_max_row / 2, (actual_max_col / 2) - 6, "Hai perso! :(");
	use_color(2);
	mvprintw(round(actual_max_row * (static_cast<float>(9)/static_cast<float>(10))), (actual_max_col / 2) - 12, "Premi un tasto per uscire");
	refresh();
	nodelay(stdscr, FALSE);
	getch();
	clear();
}

void arzanoid::Game::new_level_message(){

	//prints a new level message in a black background
	//stampa un messaggio di nuovo livello in uno sfondo nero
	clear();
	use_color(5);
	mvprintw(actual_max_row / 2, (actual_max_col / 2) - 5, "Livello: %d", level_nr + 1);
	use_color(2);
	mvprintw(round(actual_max_row * (static_cast<float>(9)/static_cast<float>(10))), (actual_max_col / 2) - 15, "Premi un tasto per continuare");
	refresh();
	nodelay(stdscr, FALSE);
	getch();
	clear();
}

void arzanoid::Game::init_startup_settings(){

	//some ncurses settings
	//alcune impostazioni di ncurses
	initscr();
	start_color();
	init_colors();
	cbreak();
	noecho();
	curs_set(0);
	introduction();
	keypad(stdscr, TRUE);
	srand (time(NULL));

	//sets terminal's default sizes
	//imposta le dimensioni di default del terminale
	default_max_col = 80;
	default_max_row = 24;

	health = 3;
	level_nr = 0;

}

void arzanoid::Game::init_game_settings(){

	nodelay(stdscr, TRUE);
	getmaxyx(stdscr, actual_max_row, actual_max_col);
	stop = false;
	ball1.stop();
	ticks = 0;
	ball_ticks = 100000;
	if(level_nr < 50)
		level_nr++;
		
	bar_speed = 5;
	if(rand() % 2 == 0)
		col_mod = -1;
	else
		col_mod = 1;

	row_mod = -1;
	for(int i = 0; i < bonusballs.size(); i++){
		bonusballs[i].not_visible();
	}

	//calls all 'draw' member functions
	//chiama tutte le funzioni di stampa
	draw_border();
	load_level();
	draw_object(bar);
	draw_object(ball1);
	draw_health();
	draw_level_nr();

}

bool arzanoid::Game::is_scrsize_changed(){
	int n_max_row, n_max_col;
	getmaxyx(stdscr, n_max_row, n_max_col);
	if(n_max_row != actual_max_row || n_max_col != actual_max_col)
		return true;

	return false;
}

void arzanoid::Game::init_colors(){
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_WHITE, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_GREEN, COLOR_BLACK);
}

void arzanoid::Game::use_color(int color){
	attrset(COLOR_PAIR(color));
}

void arzanoid::Game::draw_border(){

	use_color(4);
	for(unsigned i = 0; i < actual_max_row; i++){
		mvprintw(i, 0, "+");
		mvprintw(i, actual_max_col - 1, "+");
		refresh();
	}	

	for(unsigned j = 0; j < actual_max_col; j++){
		mvprintw(0, j, "+");
		mvprintw(actual_max_row - 1, j, "+");
		refresh();
	}
	
}

void arzanoid::Game::delete_border(){
	for(unsigned i = 0; i < actual_max_row; i++){
		mvprintw(i, 0, " ");
		mvprintw(i, actual_max_col - 1, " ");
		refresh();
	}	

	for(unsigned j = 0; j < actual_max_col; j++){
		mvprintw(0, j, " ");
		mvprintw(actual_max_row - 1, j, " ");
		refresh();
	}
}

void arzanoid::Game::update_bonusballs_position(){
	
	for(int i = 0; i < bonusballs.size(); i++){
		if(bonusballs[i].is_ball_moving()){
			//each level the ball move more frequently
			//ogni livello la palla si muove più frequentemente
			if(ticks % (200000 - (level_nr * 2500)) == 0){
				erase_object(bonusballs[i]);
				bonusballs[i].set_start_row(bonusballs[i].get_start_row() + 1);
				bonusballs[i].set_end_row(bonusballs[i].get_end_row() + 1);

				if(bonusballs[i].get_start_row() >= bar.get_start_row() && !(bonusballs[i].get_start_col() >= bar.get_start_col() && bonusballs[i].get_start_col() <= bar.get_end_col())){
					bonusballs[i].not_visible();
					bonusballs[i].stop();
					erase_bricks();
					draw_bricks();
				} else if(bonusballs[i].get_start_row() == bar.get_start_row() && bonusballs[i].get_start_col() >= bar.get_start_col() && bonusballs[i].get_start_col() <= bar.get_end_col()) {
					
					//if the bar touches a bonus ball powerups are activeted
					//se la barra tocca una bonus ball i powerup vengono attivati
					bonusballs[i].not_visible();
					bonusballs[i].stop();
					erase_bricks();
					draw_bricks();
					unsigned power = rand() % 3;
					switch(power){
						case 0:
							use_color(4);
							for(unsigned j = 0; j < actual_max_col; j++){
								mvprintw(0, j, "+");
								refresh();
							}
							health++;
							draw_health();
							use_color(5);
							mvprintw(0, (actual_max_col / 2) - 3, "+1 Vita");
							break;
						case 1:
							use_color(4);
							for(unsigned j = 0; j < actual_max_col; j++){
								mvprintw(0, j, "+");
								refresh();
							}
							bar_speed += 2;
							use_color(5);
							mvprintw(0, (actual_max_col / 2) - 12, "Velocità barra aumentata");
							break;
						case 2:
							use_color(4);
							for(unsigned j = 0; j < actual_max_col; j++){
								mvprintw(0, j, "+");
								refresh();
							}
							ball_ticks = 170000;
							use_color(5);
							mvprintw(0, (actual_max_col / 2) - 13, "Velocità pallina diminuita"); 
							break;
						default:
							break;
					}
				} else {
					draw_object(bonusballs[i]);
				}
			}
		}
	}
}

unsigned arzanoid::Game::update_ball_position(){

	if(!ball1.is_ball_moving() && g_input == ' '){

		ball1.move();

	}

	bool anglex = false, angley = false;
	unsigned ball_px, ball_py;

	//each level the ball move more frequently
	//ogni livello la palla si muove più frequentemente
	if(ball1.is_ball_moving()){
		if(ticks % (ball_ticks - (level_nr * 2500)) == 0){

			ball_px = ball1.get_start_col();
			ball_py = ball1.get_start_row();
			erase_object(ball1);
			ball1.set_start_col(ball1.get_start_col() + col_mod);
			ball1.set_end_col(ball1.get_end_col() + col_mod);
			ball1.set_start_row(ball1.get_start_row() + row_mod);
			ball1.set_end_row(ball1.get_end_row() + row_mod);

			//if the ball doesn't touch any brick or the border...
			//se la pallina non tocca nessun mattone o il bordo...
			if(alevel->get_matrix(ball1.get_start_row(), ball1.get_start_col()) == 0){

				//if the ball touches the bar, inverts the vertical progress of the ball
				if((ball1.get_start_row() == bar.get_start_row()) && (ball1.get_start_col() >= bar.get_start_col()) && (ball1.get_start_col() <= bar.get_end_col())){
					row_mod = -row_mod;
					ball1.set_start_col(ball1.get_start_col() + col_mod);
					ball1.set_end_col(ball1.get_end_col() + col_mod);
					ball1.set_start_row(ball1.get_start_row() + row_mod);
					ball1.set_end_row(ball1.get_end_row() + row_mod);
					//if the new position is outside of the screen limits (left-side-border or right-side-border), inverts the horizontal progress of the ball
					//se la nuova posizione è fuori dai limiti dello schermo (il bordo al lato destro o il bordo al lato sinistro), inverte l'andamento orizzontale della pallina
					if(alevel->get_matrix(ball1.get_start_row(), ball1.get_start_col()) == -1){
						col_mod = -col_mod;
						ball1.set_start_col(ball1.get_start_col() + col_mod);
						ball1.set_end_col(ball1.get_end_col() + col_mod);
						ball1.set_start_row(ball1.get_start_row() + row_mod);
						ball1.set_end_row(ball1.get_end_row() + row_mod);
					}

					//and then draws the ball with the new coordinates
					//e successivamente disegna la pallina con le nuove coordinate
					draw_object(ball1);
				//else if the ball goes under the bar
				//altrimenti se la pallina va sotto la barra
				} else if(ball1.get_start_row() >= bar.get_start_row() && !((ball1.get_start_col() >= bar.get_start_col()) && (ball1.get_start_col() <= bar.get_end_col()))){
					//if the health is higher then 1 blocks it movement and draws it on the bar, decreasing the health
					//se la vita è maggiore di 1 blocca il movimento della pallina e la posizione sopra la barra, decrementando la vita
					if(health > 1){
						ball1.stop();
						ball1.set_start_col((bar.get_end_col() + bar.get_start_col()) / 2);
						ball1.set_end_col((bar.get_end_col() + bar.get_start_col()) / 2);
						ball1.set_start_row(21);
						ball1.set_end_row(21);
						draw_object(ball1);
						if(rand() % 2 == 0)
							col_mod = -1;
						else
							col_mod = 1;
						row_mod = -1;
						health--;
						draw_health();
						
					} else {
						return 1;
					}
				} else {
					draw_object(ball1);
				}
			} else {

				//...else if the ball touches a brick or the border
				//...oppure se la pallina tocca un mattone o il bordo

				/*
				/ it saves the id of the brick touched (ob_id) or the border (-1) and the x and 
				/ y coordinates(c_id1 and c_id2) of the objects that would be touched if the ball moves 
				/ only with an horizontal, or vertical, progress in this frame
				*/

				/*
				/ salva l'id del mattone toccato (ob_id) o il bordo (-1) e le coordinate x e y (c_id1 e c_id2)
				/ degli oggetti che verrebbero toccati se la palla si muovesse solo con un avanzamento 
				/ orizzontale o verticale in questo frame
				*/

				int ob_id = alevel->get_matrix(ball1.get_start_row(), ball1.get_start_col());
				int c_id1 = alevel->get_matrix(ball_py + row_mod, ball_px);
				int c_id2 = alevel->get_matrix(ball_py, ball_px + col_mod);
				bool bothx = false, bothy = false;

				if(c_id1 != 0){
					row_mod = -row_mod;
					bothy = true;
				} else {
					angley = true;
				}

				if(c_id2 != 0){
					col_mod = -col_mod;
					bothx = true;
				} else {
					anglex = true;
				}
				//if the ball touches a convex corner not composed by the borders
				//se la palla tocca un angolo convesso non formato unicamente dai bordi
				if(bothx && bothy){
					if(c_id1 != -1){
						erase_object(bricks[c_id1 - 1]);
						bricks[c_id1 - 1].not_visible();
						alevel->mark_element(bricks[c_id1 - 1].get_start_row(), bricks[c_id1 - 1].get_start_col(), 0);
						if(c_id1 == 1){
							return 2;
						}
					}

					if(c_id2 != -1){
						erase_object(bricks[c_id2 - 1]);
						bricks[c_id2 - 1].not_visible();
						alevel->mark_element(bricks[c_id2 - 1].get_start_row(), bricks[c_id2 - 1].get_start_col(), 0);
						if(c_id2 == 1){
							return 2;
						}
					}
				}

				//if the ball touches a concave corner
				//se la palla tocca un angolo concavo
				if(anglex && angley){
					row_mod = -row_mod;
					col_mod = -col_mod;
				}

				//if the object touched is a brick, the game erases it and if it's the winning brick stops the level
				//se l'oggetto toccato è un mattone lo cancella e se è un mattone vincente (mattone verde) ferma il livello
				if(ob_id != -1){
					if(bricks[ob_id - 1].is_bonus_brick()){
						bonusballs.push_back(Ball('*', 3));
						bonusballs[bonusballs.size() - 1].set_start_row(bricks[ob_id - 1].get_start_row());
						bonusballs[bonusballs.size() - 1].set_end_row(bricks[ob_id - 1].get_start_row());
						bonusballs[bonusballs.size() - 1].set_start_col(bricks[ob_id - 1].get_start_col());
						bonusballs[bonusballs.size() - 1].set_end_col( bricks[ob_id - 1].get_start_col());
						bonusballs[bonusballs.size() - 1].set_visible();
						bonusballs[bonusballs.size() - 1].move();
					} 

					erase_object(bricks[ob_id - 1]);
					bricks[ob_id - 1].not_visible();
					alevel->mark_element(bricks[ob_id - 1].get_start_row(), bricks[ob_id - 1].get_start_col(), 0);
					if(ob_id == 1){
						return 2;
					}
				}
				
				//updates ball's coordinates...
				//aggiorna le cooridnate della pallina...
				ball1.set_start_col(ball1.get_start_col() + col_mod);
				ball1.set_end_col(ball1.get_end_col() + col_mod);
				ball1.set_start_row(ball1.get_start_row() + row_mod);
				ball1.set_end_row(ball1.get_end_row() + row_mod);

				//...but if it is inside the borders or outside of them corrects the ball's movement
				//...ma se si trova all'interno dei bordi o fuori ad essi corregge il movimento della pallina
				if(alevel->get_matrix(ball1.get_start_row(), ball1.get_start_col()) != -1){
					if((ball1.get_start_row() == bar.get_start_row()) && (ball1.get_start_col() >= bar.get_start_col()) && (ball1.get_start_col() <= bar.get_end_col())){
						if(anglex){
							col_mod = -col_mod;
							ball1.set_start_col(ball1.get_start_col() + col_mod);
							ball1.set_end_col(ball1.get_end_col() + col_mod);
							ball1.set_start_row(ball1.get_start_row() + row_mod);
							ball1.set_end_row(ball1.get_end_row() + row_mod);
							draw_object(ball1);
						} else if(angley){
							row_mod = -row_mod;
							ball1.set_start_col(ball1.get_start_col() + col_mod);
							ball1.set_end_col(ball1.get_end_col() + col_mod);
							ball1.set_start_row(ball1.get_start_row() + row_mod);
							ball1.set_end_row(ball1.get_end_row() + row_mod);
							draw_object(ball1);
						}
					} else if((ball1.get_start_row() > bar.get_start_row()) && (ball1.get_start_col() >= bar.get_start_col()) && (ball1.get_start_col() <= bar.get_end_col())){
						if(angley)
							row_mod = -row_mod;
						else if(anglex)
							col_mod = -col_mod;
							
						ball1.set_start_col(ball_px + col_mod);
						ball1.set_end_col(ball_px + col_mod);
						ball1.set_start_row(ball_py + row_mod);
						ball1.set_end_row(ball_py + row_mod);
						draw_object(ball1);
					} else if((ball1.get_start_row() >= bar.get_start_row()) && !((ball1.get_start_col() >= bar.get_start_col()) && (ball1.get_start_col() <= bar.get_end_col()))){
						ball1.stop();
						ball1.set_start_col((bar.get_end_col() + bar.get_start_col()) / 2);
						ball1.set_end_col((bar.get_end_col() + bar.get_start_col()) / 2);
						ball1.set_start_row(21);
						ball1.set_end_row(21);
						draw_object(ball1);
						if(rand() % 2 == 0)
							col_mod = -1;
						else
							col_mod = 1;
						row_mod = -1;
						health--;
						draw_health();
					} else {
						draw_object(ball1);
					}
				} else {
					if(anglex){
						col_mod = -col_mod;
						ball1.set_start_col(ball1.get_start_col() + col_mod);
						ball1.set_end_col(ball1.get_end_col() + col_mod);
						ball1.set_start_row(ball1.get_start_row() + row_mod);
						ball1.set_end_row(ball1.get_end_row() + row_mod);
					} else if(angley){
						row_mod = -row_mod;
						ball1.set_start_col(ball1.get_start_col() + col_mod);
						ball1.set_end_col(ball1.get_end_col() + col_mod);
						ball1.set_start_row(ball1.get_start_row() + row_mod);
						ball1.set_end_row(ball1.get_end_row() + row_mod);
					}
					draw_object(ball1);
				}
			}
		}
	}
	return 0;
}


//it moves correctly the bar
//fa muovere correttamente la barra
void arzanoid::Game::update_bar_position(){

	float xdiff;
	//if the pressed key is left arrow...
	//se il tasto premuto è la frecca sinistra...
	if(g_input == KEY_LEFT){
		if(bar.get_start_col() > bar_speed){
			erase_object(bar);
			bar.set_start_col(bar.get_start_col() - bar_speed);
			bar.set_end_col(bar.get_end_col() - bar_speed);
			draw_object(bar);
			if(!ball1.is_ball_moving()){
				erase_object(ball1);
				ball1.set_start_col(ball1.get_start_col() - bar_speed);
				ball1.set_end_col(ball1.get_end_col() - bar_speed);
				draw_object(ball1);
			}
		} else {
			//if the bar hasn't the space to move at the standard speed it moves with a slower speed (1 step)
			//se la barra non ha lo spazio per muoversi alla velocità standard, si muove con una velocità inferiore (un passo)
			if(bar.get_start_col() > 1){
				erase_object(bar);
				bar.set_start_col(bar.get_start_col() - 1);
				bar.set_end_col(bar.get_end_col() - 1);
				draw_object(bar);
				if(!ball1.is_ball_moving()){
					erase_object(ball1);
					ball1.set_start_col(ball1.get_start_col() - 1);
					ball1.set_end_col(ball1.get_end_col() - 1);
					draw_object(ball1);
				}
			}
		}

	//if the pressed key is right arrow...
	//se il tasto premuto è la frecca destra...
	} else if(g_input == KEY_RIGHT){
		
		if(bar.get_end_col() < default_max_col - bar_speed - 2){
			erase_object(bar);
			bar.set_start_col(bar.get_start_col() + bar_speed);
			bar.set_end_col(bar.get_end_col() + bar_speed);
			draw_object(bar);
			if(!ball1.is_ball_moving()){
				erase_object(ball1);
				ball1.set_start_col(ball1.get_start_col() + bar_speed);
				ball1.set_end_col(ball1.get_end_col() + bar_speed);
				draw_object(ball1);
			}
		} else {

			//if the bar hasn't the space to move at the standard speed it moves with a slower speed (1 step)
			//se la barra non ha lo spazio per muoversi alla velocità standard, si muove con una velocità inferiore (un passo)
			if(bar.get_end_col() < default_max_col - 2){
				erase_object(bar);
				bar.set_start_col(bar.get_start_col() + 1);
				bar.set_end_col(bar.get_end_col() + 1);
				draw_object(bar);
				if(!ball1.is_ball_moving()){
					erase_object(ball1);
					ball1.set_start_col(ball1.get_start_col() + 1);
					ball1.set_end_col(ball1.get_end_col() + 1);
					draw_object(ball1);
				}
			}
		}
	}
}


//draws player's healts
//disegna la vita del giocatore
void arzanoid::Game::draw_health(){
	use_color(5);
	mvprintw(actual_max_row - 1, (actual_max_col / 4) - 6, "Vite: %d", health);
	refresh();
}

//draws actual level's number
//disegna il numero del livello attuale
void arzanoid::Game::draw_level_nr(){
	use_color(5);
	mvprintw(actual_max_row - 1, round(actual_max_col * (static_cast<float>(3)/static_cast<float>(4))) - 9, "Livello: %d", level_nr);
	refresh();
}

//initilizes the Game object and loads all settings
//inizializza l'oggetto Game e carica tutte le impostazioni
arzanoid::Game::Game():ball1('o', 5) {

	alevel = new arzanoid::Level();
	init_startup_settings();
	init_game_settings();
	
}

//destroys the memory that was allocated for the actual level (pointed by alevel)
//distrugge la memoria allocata per il livello attuale (puntata da alevel)
arzanoid::Game::~Game(){
	delete alevel;
}


//each time a new level starts, this member function is called
//ogni volta che un nuovo livello inizia viene chiamata questa funzione membro
void arzanoid::Game::new_game(){
	new_level_message();
	alevel->init_level(level_nr);
	init_game_settings();
}

void arzanoid::Game::end_actual_game(){
	clear();
	ball1.set_start_col(39);
	ball1.set_end_col(39);
	ball1.set_start_row(21);
	ball1.set_end_row(21);
	bar.set_start_col(34);
	bar.set_end_col(44);
	bar.set_start_row(22);
	bar.set_end_row(22);
	bricks.erase(bricks.begin(), bricks.end());
	bonus_index.erase(bonus_index.begin(), bonus_index.end());
	bonusballs.erase(bonusballs.begin(), bonusballs.end());
}

void arzanoid::Game::get_input(){
	g_input = getch();
}

bool arzanoid::Game::is_running(){
	
	if(g_input != 27)
		return true;

	return false;
}

void arzanoid::Game::exit(){
	endwin();
}

bool arzanoid::Game::load_level(){

	unsigned br_count = 0;
	unsigned bonus_br = alevel->get_brick_nr() / 9;

	for(unsigned i = 0; i < bonus_br; i++){

		unsigned index = rand() % (alevel->get_brick_nr() - 1) + 1;
		while(std::find(bonus_index.begin(), bonus_index.end(), index) != bonus_index.end()){
			index = rand() % (alevel->get_brick_nr() - 1) + 2;
		}
		bonus_index.push_back(index);

	}

	for(int k = 1; k < alevel->get_brick_nr(); k++){
		for(int i = 1; i < alevel->get_map_num_rows(); i+= arzanoid::Brick::height){
			for(int j = 1; j < alevel->get_map_num_cols(); j+= arzanoid::Brick::width){
				if(alevel->get_matrix(i, j) == k){
					if(k == 1)
						bricks.push_back(Brick(i,j, 5));
					else
						bricks.push_back(Brick(i,j, 1));

					draw_object(bricks[br_count]);
					br_count++;
				}
			}
		}
	}

	for(unsigned i = 0; i < bonus_index.size(); i++){

		bricks[bonus_index[i]].set_as_bonus_brick();

	}

}

void arzanoid::Game::update_all(){

	int r = update_scene();
	
	if(r == 2){
		end_actual_game();
		new_game();
	} else if(r == 1){
		ending_message();
		g_input = 27;
	} else {
		g_input = 0;
		get_input();
		ticks++;
	}
}

void arzanoid::Game::erase_bricks(){
	for(unsigned i = 0; i < bricks.size(); i++){
		erase_object(bricks[i]);
	}
}

void arzanoid::Game::draw_bricks(){
	for(unsigned i = 0; i < bricks.size(); i++){
		draw_object(bricks[i]);
	}
}

unsigned arzanoid::Game::update_scene(){

	if(is_scrsize_changed()){
		delete_border();
		erase_bricks();
		erase_object(ball1);
		for(int i = 0; i < bonusballs.size(); i++){
			erase_object(bonusballs[i]);
		}	
		
		erase_object(bar);
		getmaxyx(stdscr, actual_max_row, actual_max_col);
		
		draw_border();
		draw_bricks();
		draw_object(ball1);
		for(int i = 0; i < bonusballs.size(); i++){
			draw_object(bonusballs[i]);
		}
		draw_object(bar);
		draw_health();
		draw_level_nr();
	}

	update_bar_position();
	update_bonusballs_position();

	return update_ball_position();
}

void arzanoid::Game::draw_object(Drawable &dr){
	if(dr.is_visible()){

		//data used to make an upscaled scene
		//dati utilizzato per creare una scena up-scalata
		float xdiff = static_cast<float>(actual_max_col) / static_cast<float>(default_max_col);
		float ydiff = static_cast<float>(actual_max_row) / static_cast<float>(default_max_row);

		//does a multiplication of the object's coordinates for the difference between the previous and the current screen sizes
		//fa una moltiplicazione delle coordinate dell'oggetto per la differenza tra la dimensione della schermata precedente e quella corrente

		unsigned start_r = round(dr.get_start_row() * ydiff);
		unsigned end_r = round(dr.get_end_row() * ydiff);
		unsigned start_c = round(dr.get_start_col() * xdiff);
		unsigned end_c = round(dr.get_end_col() * xdiff);


		use_color(dr.get_color());

		//draws pixel for pixel
		//disegna pixel per pixel

		for(unsigned i = start_r; i <= end_r; i++)
		{
			for(unsigned j = start_c; j <= end_c; j++)
			{
		
				mvprintw(i, j, "%c", dr.get_char());
				refresh();
		
			}
		}
	}
}


//does the same operations of 'draw_object' but it erases the object passed
//fa le stesse operazioni di 'draw_object' ma cancella l'oggetto passato
void arzanoid::Game::erase_object(Drawable dr){
	if(dr.is_visible()){
		float xdiff = static_cast<float>(actual_max_col) / static_cast<float>(default_max_col);
		float ydiff = static_cast<float>(actual_max_row) / static_cast<float>(default_max_row);
		unsigned start_r = round(dr.get_start_row() * ydiff);
		unsigned end_r = round(dr.get_end_row() * ydiff);
		unsigned start_c = round(dr.get_start_col() * xdiff);
		unsigned end_c = round(dr.get_end_col() * xdiff);

		for(unsigned i = start_r; i <= end_r; i++)
		{
			for(unsigned j = start_c; j <= end_c; j++)
			{
		
				mvprintw(i, j, " ");
				refresh();
		
			}
		}
	}
}