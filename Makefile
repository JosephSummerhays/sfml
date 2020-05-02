make:
	g++ -c *.cpp
	g++ main.o Collision.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

run:
	./sfml-app
