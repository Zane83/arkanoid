#include <iostream>
#include "../include/game.h"

int main(){

	arzanoid::Game g;
	
	while(g.is_running()){
		g.update_all();
	}
	g.exit();	
}