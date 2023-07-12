
MySnakeGame: $(OBJECTS)
	g++ $(OBJECTS) -o SnakeGame -lcurses

main.o: main.cpp $(HEADERS)
	g++ -c main.cpp -o main.o

renders.o: ./renders/renders.cpp $(HEADERS) 
	g++ -c ./renders/renders.cpp -o renders.o

map.o: ./map/map.cpp ./map/map.h ./snake/snake.h ./blocks/blocks.h ./items/items.h
	g++ -c ./map/map.cpp -o map.o

snake.o: ./snake/snake.cpp ./snake/snake.h ./map/map.h ./blocks/blocks.h ./items/items.h
	g++ -c ./snake/snake.cpp -o snake.o

blocks.o: ./blocks/blocks.cpp ./blocks/blocks.h ./items/items.h
	g++ -c ./blocks/blocks.cpp -o blocks.o

items.o: ./items/items.cpp ./items/items.h ./ blocks/blocks.h
	g++ -c ./items/items.cpp -o items.o


Debug: debug.o renders.o map.o snake.o blocks.o items.o
	g++ debug.o renders.o map.o snake.o blocks.o items.o -o debugExe -lcurses

debug.o: ./debug/debug.cpp $(HEADERS)
	g++ -c ./debug/debug.cpp -o debug.o


OBJECTS = ./.o/items.o ./.o/blocks.o ./.o/snake.o ./.o/map.o ./.o/renders.o ./.o/main.o ./.o/word_snake.o
HEADERS = ./renders/renders.h ./snake/snake.h ./map/map.h ./blocks/blocks.h ./items/items.h ./special_modes/word_snake_mode/word_snake.h


.PHONY: clean

clean:
	-rm ./.o/*.o SnakeGame


