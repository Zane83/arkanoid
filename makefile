arzanoid : drawable.o brick.o ball.o  bar.o level.o game.o  main.o
	g++ -o arzanoid obj/game.o obj/drawable.o obj/level.o obj/ball.o obj/brick.o obj/bar.o obj/main.o -lncurses -std=c++11

drawable.o : include/drawable.h src/drawable.cpp
	g++ -c src/drawable.cpp -o obj/drawable.o -lncurses -std=c++11
	
brick.o : include/drawable.h src/drawable.cpp include/brick.h src/brick.cpp
	g++ -c src/brick.cpp -o obj/brick.o -lncurses -std=c++11
	
ball.o : include/drawable.h src/drawable.cpp include/ball.h src/ball.cpp
	g++ -c src/ball.cpp -o obj/ball.o -lncurses -std=c++11
	
bar.o : include/drawable.h src/drawable.cpp include/bar.h src/bar.cpp
	g++ -c src/bar.cpp -o obj/bar.o -lncurses -std=c++11
	
level.o : include/level.h src/level.cpp include/brick.h src/brick.cpp
	g++ -c src/level.cpp -o obj/level.o -lncurses -std=c++11
	
game.o : include/bar.h src/bar.cpp include/ball.h src/ball.cpp include/level.h src/level.cpp
	g++ -c src/game.cpp -o obj/game.o -lncurses -std=c++11

main.o : include/game.h src/game.cpp
	g++ -c src/main.cpp -o obj/main.o -lncurses -std=c++11