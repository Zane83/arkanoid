#include "../include/game.h"

void arkanoid::Game::introduction(){

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

void arkanoid::Game::ending_message(){

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

void arkanoid::Game::new_level_message(){
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

void arkanoid::Game::init_startup_settings(){

	initscr();
	start_color();
	init_colors();
	cbreak();
	noecho();
	curs_set(0);
	introduction();
	keypad(stdscr, TRUE);
	srand (time(NULL));
	default_max_col = 80;
	default_max_row = 24;
	health = 3;
	level_nr = 0;

}

void arkanoid::Game::init_game_settings(){

	nodelay(stdscr, TRUE);
	getmaxyx(stdscr, actual_max_row, actual_max_col);
	stop = false;
	dr_counter = 0;
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
	ball2.not_visible();
	draw_border();
	load_level();
	draw_object(bar);
	draw_object(ball1);
	draw_health();
	draw_level_nr();

}

bool arkanoid::Game::is_scrsize_changed(){
	int n_max_row, n_max_col;
	getmaxyx(stdscr, n_max_row, n_max_col);
	if(n_max_row != actual_max_row || n_max_col != actual_max_col)
		return true;

	return false;
}

void arkanoid::Game::init_colors(){
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_WHITE, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_GREEN, COLOR_BLACK);
}

void arkanoid::Game::use_color(int color){
	attrset(COLOR_PAIR(color));
}

void arkanoid::Game::draw_border(){

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

void arkanoid::Game::delete_border(){
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

void arkanoid::Game::update_bonusball_position(){
	if(ball2.is_ball_moving()){
		if(ticks % (200000 - (level_nr * 2500)) == 0){

			erase_object(ball2);
			ball2.d_start_row++;
			ball2.d_end_row++;

			if(ball2.d_start_row >= bar.d_start_row && !(ball2.d_start_col >= bar.d_start_col && ball2.d_start_col <= bar.d_end_col)){
				ball2.visible = false;
				ball2.stop();
			} else if(ball2.d_start_row == bar.d_start_row && ball2.d_start_col >= bar.d_start_col && ball2.d_start_col <= bar.d_end_col) {
				ball2.visible = false;
				ball2.stop();
				erase_bricks();
				draw_bricks();
				unsigned power = rand() % 3;
				switch(power){
					case 0:
						health++;
						draw_health();
						use_color(5);
						mvprintw(0, (actual_max_col / 2) - 3, "+1 Vita");
						break;
					case 1:
						bar_speed += 2;
						use_color(5);
						mvprintw(0, (actual_max_col / 2) - 12, "Velocità barra aumentata");
						break;
					case 2:
						ball_ticks = 170000;
						use_color(5);
						mvprintw(0, (actual_max_col / 2) - 13, "Velocità pallina diminuita"); 
						break;
					default:
						break;
				}
			} else {
				draw_object(ball2);
			}
		}
	}
}

unsigned arkanoid::Game::update_ball_position(){

	if(!ball1.is_ball_moving() && g_input == ' '){

		ball1.move();

	}

	int ob_id;
	bool anglex = false, angley = false;

	if(ball1.is_ball_moving()){
		if(ticks % (ball_ticks - (level_nr * 2500)) == 0){

			ball_px = ball1.d_start_col;
			ball_py = ball1.d_start_row;
			erase_object(ball1);
			ball1.d_start_col += col_mod;
			ball1.d_end_col += col_mod;
			ball1.d_start_row += row_mod;
			ball1.d_end_row += row_mod;
			if(alevel->M[ball1.d_start_row][ball1.d_start_col] == 0){
				if((ball1.d_start_row >= bar.d_start_row) && (ball1.d_start_col >= bar.d_start_col) && (ball1.d_start_col <= bar.d_end_col)){
					row_mod = -row_mod;
					ball1.d_start_col += col_mod;
					ball1.d_end_col += col_mod;
					ball1.d_start_row += row_mod;
					ball1.d_end_row += row_mod;
					draw_object(ball1);

				} else if((ball1.d_start_row >= bar.d_start_row) && !((ball1.d_start_col >= bar.d_start_col) && (ball1.d_start_col <= bar.d_end_col))){
					if(health > 1){
						ball1.stop();
						ball1.d_start_col = (bar.d_end_col + bar.d_start_col) / 2;
						ball1.d_end_col = (bar.d_end_col + bar.d_start_col) / 2;
						ball1.d_start_row = 21;
						ball1.d_end_row = 21;
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
				ob_id = alevel->M[ball1.d_start_row][ball1.d_start_col];
				if(alevel->M[ball_py + row_mod][ball_px] != 0){
					row_mod = -row_mod;
				} else {
					angley = true;
				}

				if(alevel->M[ball_py][ball_px + col_mod] != 0){
					col_mod = -col_mod;
				} else {
					anglex = true;
				}

				if(anglex && angley){
					row_mod = -row_mod;
					col_mod = -col_mod;
				}

				if(ob_id != -1){
					if(bricks[ob_id - 1].is_bonus_brick()){
						ball2.d_start_row = bricks[ob_id - 1].d_start_row;
						ball2.d_end_row = bricks[ob_id - 1].d_start_row;
						ball2.d_start_col = bricks[ob_id - 1].d_start_col;
						ball2.d_end_col = bricks[ob_id - 1].d_start_col;
						ball2.visible = true;
						ball2.move();
					} 

					erase_object(bricks[ob_id - 1]);
					bricks[ob_id - 1].not_visible();
					alevel->mark_element(bricks[ob_id - 1].d_start_row, bricks[ob_id - 1].d_start_col, 0);
					if(ob_id == 1){
						return 2;
					}
				}
				
				ball1.d_start_col += col_mod;
				ball1.d_end_col += col_mod;
				ball1.d_start_row += row_mod;
				ball1.d_end_row += row_mod;

				if(alevel->M[ball1.d_start_row][ball1.d_start_col] != -1){
					if((ball1.d_start_row == bar.d_start_row) && (ball1.d_start_col >= bar.d_start_col) && (ball1.d_start_col <= bar.d_end_col)){
						if(anglex){
							col_mod = -col_mod;
							ball1.d_start_col += col_mod;
							ball1.d_end_col += col_mod;
							ball1.d_start_row += row_mod;
							ball1.d_end_row += row_mod;
							draw_object(ball1);
						} else if(angley){
							row_mod = -row_mod;
							ball1.d_start_col += col_mod;
							ball1.d_end_col += col_mod;
							ball1.d_start_row += row_mod;
							ball1.d_end_row += row_mod;
							draw_object(ball1);
						}
					} else if((ball1.d_start_row > bar.d_start_row) && (ball1.d_start_col >= bar.d_start_col) && (ball1.d_start_col <= bar.d_end_col)){
						if(angley)
							row_mod = -row_mod;
						else if(anglex)
							col_mod = -col_mod;
							
						ball1.d_start_col = ball_px + col_mod;
						ball1.d_end_col = ball_px + col_mod;
						ball1.d_start_row = ball_py + row_mod;
						ball1.d_end_row = ball_py + row_mod;
						draw_object(ball1);
					} else if((ball1.d_start_row >= bar.d_start_row) && !((ball1.d_start_col >= bar.d_start_col) && (ball1.d_start_col <= bar.d_end_col))){
						ball1.stop();
						ball1.d_start_col = (bar.d_end_col + bar.d_start_col) / 2;
						ball1.d_end_col = (bar.d_end_col + bar.d_start_col) / 2;
						ball1.d_start_row = 21;
						ball1.d_end_row = 21;
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
						ball1.d_start_col += col_mod;
						ball1.d_end_col += col_mod;
						ball1.d_start_row += row_mod;
						ball1.d_end_row += row_mod;
					} else if(angley){
						row_mod = -row_mod;
						ball1.d_start_col += col_mod;
						ball1.d_end_col += col_mod;
						ball1.d_start_row += row_mod;
						ball1.d_end_row += row_mod;
					}
					draw_object(ball1);
				}
			}
		}
	}
	return 0;
}

void arkanoid::Game::update_bar_position(){

	float xdiff;
	if(g_input == KEY_LEFT){
		if(bar.d_start_col > bar_speed){
			erase_object(bar);
			bar.d_start_col -= bar_speed;
			bar.d_end_col -= bar_speed;
			draw_object(bar);
			if(!ball1.is_ball_moving()){
				erase_object(ball1);
				ball1.d_start_col -= bar_speed;
				ball1.d_end_col -= bar_speed;
				draw_object(ball1);
			}
		} else {
			if(bar.d_start_col > 1){
				erase_object(bar);
				bar.d_start_col --;
				bar.d_end_col --;
				draw_object(bar);
				if(!ball1.is_ball_moving()){
					erase_object(ball1);
					ball1.d_start_col --;
					ball1.d_end_col --;
					draw_object(ball1);
				}
			}
		}
	} else if(g_input == KEY_RIGHT){
		
		if(bar.d_end_col < default_max_col - bar_speed - 2){
			erase_object(bar);
			bar.d_start_col += bar_speed;
			bar.d_end_col += bar_speed;
			draw_object(bar);
			if(!ball1.is_ball_moving()){
				erase_object(ball1);
				ball1.d_start_col += bar_speed;
				ball1.d_end_col += bar_speed;
				draw_object(ball1);
			}
		} else {
			if(bar.d_end_col < default_max_col - 2){
				erase_object(bar);
				bar.d_start_col ++;
				bar.d_end_col ++;
				draw_object(bar);
				if(!ball1.is_ball_moving()){
					erase_object(ball1);
					ball1.d_start_col ++;
					ball1.d_end_col ++;
					draw_object(ball1);
				}
			}
		}
	}
}

void arkanoid::Game::draw_health(){
	use_color(5);
	mvprintw(actual_max_row - 1, (actual_max_col / 4) - 6, "Vite: %d", health);
	refresh();
}

void arkanoid::Game::draw_level_nr(){
	use_color(5);
	mvprintw(actual_max_row - 1, round(actual_max_col * (static_cast<float>(3)/static_cast<float>(4))) - 9, "Livello: %d", level_nr);
	refresh();
}

arkanoid::Game::Game() {

	alevel = new arkanoid::Level();
	init_startup_settings();
	init_game_settings();
	
}

arkanoid::Game::~Game(){
	delete alevel;
}

void arkanoid::Game::new_game(){
	new_level_message();
	alevel->init_level(level_nr);
	init_game_settings();
}

void arkanoid::Game::end_actual_game(){
	clear();
	ball1.d_start_col = 39;
	ball1.d_end_col = 39;
	ball1.d_start_row = 21;
	ball1.d_end_row = 21;
	bar.d_start_col = 34;
	bar.d_end_col = 44;
	bar.d_start_row = 22;
	bar.d_end_row = 22;
	bricks.erase(bricks.begin(), bricks.end());
	bonus_index.erase(bonus_index.begin(), bonus_index.end());
}

void arkanoid::Game::get_input(){
	g_input = getch();
}

bool arkanoid::Game::is_running(){
	
	if(g_input != 27)
		return true;

	return false;
}

void arkanoid::Game::exit(){
	endwin();
}

bool arkanoid::Game::load_level(){

	unsigned br_count = 0;
	unsigned bonus_br = alevel->brick_nr / 9;

	for(unsigned i = 0; i < bonus_br; i++){

		unsigned index = rand() % (alevel->brick_nr - 1) + 1;
		while(std::find(bonus_index.begin(), bonus_index.end(), index) != bonus_index.end()){
			index = rand() % (alevel->brick_nr - 1) + 2;
		}
		bonus_index.push_back(index);

	}

	for(int k = 1; k < alevel->brick_nr; k++){
		for(int i = 1; i < arkanoid::Level::map_num_rows; i+= arkanoid::Brick::height){
			for(int j = 1; j < arkanoid::Level::map_num_cols; j+= arkanoid::Brick::width){
				if(alevel->M[i][j] == k){
					if(k == 1)
						bricks.push_back(WinningBrick(i,j));
					else
						bricks.push_back(NormalBrick(i,j));

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

void arkanoid::Game::update_all(){

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

void arkanoid::Game::erase_bricks(){
	for(unsigned i = 0; i < bricks.size(); i++){
		erase_object(bricks[i]);
	}
}

void arkanoid::Game::draw_bricks(){
	for(unsigned i = 0; i < bricks.size(); i++){
		draw_object(bricks[i]);
	}
}

unsigned arkanoid::Game::update_scene(){

	if(is_scrsize_changed()){
		delete_border();
		erase_bricks();
		erase_object(ball1);
		erase_object(ball2);
		erase_object(bar);
		getmaxyx(stdscr, actual_max_row, actual_max_col);
		
		draw_border();
		draw_bricks();
		draw_object(ball1);
		draw_object(ball2);
		draw_object(bar);
		draw_health();
		draw_level_nr();
	}

	update_bar_position();
	update_bonusball_position();

	return update_ball_position();
}

void arkanoid::Game::draw_object(Drawable &dr){
	if(dr.is_visible()){

		float xdiff = static_cast<float>(actual_max_col) / static_cast<float>(default_max_col);
		float ydiff = static_cast<float>(actual_max_row) / static_cast<float>(default_max_row);
		unsigned start_r = round(dr.d_start_row * ydiff);
		unsigned end_r = round(dr.d_end_row * ydiff);
		unsigned start_c = round(dr.d_start_col * xdiff);
		unsigned end_c = round(dr.d_end_col* xdiff);

		use_color(dr.d_color);

		for(unsigned i = start_r; i <= end_r; i++)
		{
			for(unsigned j = start_c; j <= end_c; j++)
			{
		
				mvprintw(i, j, "%c", dr.d_ch);
				refresh();
		
			}
		}
	}
}

void arkanoid::Game::erase_object(Drawable dr){
	if(dr.is_visible()){
		float xdiff = static_cast<float>(actual_max_col) / static_cast<float>(default_max_col);
		float ydiff = static_cast<float>(actual_max_row) / static_cast<float>(default_max_row);
		unsigned start_r = round(dr.d_start_row * ydiff);
		unsigned end_r = round(dr.d_end_row * ydiff);
		unsigned start_c = round(dr.d_start_col * xdiff);
		unsigned end_c = round(dr.d_end_col* xdiff);

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