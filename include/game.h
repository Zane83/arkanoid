#ifndef GAME_H
#define GAME_H
#include <ncurses.h>
#include <algorithm>
#include <vector>
#include <cmath>
#include "drawable.h"
#include "n_brick.h"
#include "w_brick.h"
#include "bar.h"
#include "bonus_ball.h"
#include "ball.h"
#include "level.h"


namespace arkanoid {

	class Game {

		int default_max_row, default_max_col, actual_max_row, actual_max_col, g_input, row_mod, col_mod;
		std::vector<arkanoid::Brick> bricks;
		std::vector<unsigned> bonus_index;
		unsigned int dr_counter, ticks, ball_ticks, ball_px, ball_py, health, level_nr, bar_speed;
		bool stop;
		Level *alevel;
		Bar bar;
		BonusBall ball2;
		Ball ball1;

		void introduction();

		void ending_message();

		void new_level_message();

		void init_startup_settings();

		void init_game_settings();

		void init_colors();

		bool is_scrsize_changed();

		void use_color(int color);

		void draw_border();

		void delete_border();

		unsigned update_scene();

		void erase_bricks();

		void draw_bricks();

		void update_bar_position();

		unsigned update_ball_position();

		void update_bonusball_position();

		bool load_level();

		void draw_health();

		void draw_level_nr();

		public:
		Game();

		~Game();

		bool is_running();

		void exit();

		void get_input();

		void update_all();

		void draw_object(Drawable &dr);

		void end_actual_game();

		void new_game();

		void erase_object(Drawable dr);
	};
}
#endif