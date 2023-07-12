
HEADERS = ./items/items.h ./blocks/blocks.h ./snake/snake.h ./map/map.h ./renders/renders.h ./special_modes/word_snake_mode/word_snake.h
OBJECTS = items.o blocks.o snake.o map.o renders.o word_snake.o main.o

MySnakeGame: $(OBJECTS) $(HEADERS)
	g++ -o MySnakeGame $(OBJECTS) -lcurses

main.o: ./main.cpp $(HEADERS)
	g++ -c ./main.cpp -o main.o

word_snake.o: ./special_modes/word_snake_mode/word_snake.cpp ./special_modes/word_snake_mode/word_snake.h ./items/items.h ./blocks/blocks.h ./snake/snake.h ./map/map.h
	g++ -c ./special_modes/word_snake_mode/word_snake.cpp -o word_snake.o

renders.o: ./renders/renders.cpp $(HEADERS)
	g++ -c ./renders/renders.cpp -o renders.o

map.o: ./map/map.cpp ./items/items.h ./blocks/blocks.h ./snake/snake.h ./map/map.h
	g++ -c ./map/map.cpp -o map.o

snake.o: ./snake/snake.cpp ./items/items.h ./blocks/blocks.h ./snake/snake.h ./map/map.h
	g++ -c ./snake/snake.cpp -o snake.o

blocks.o: ./blocks/blocks.cpp ./items/items.h ./blocks/blocks.h
	g++ -c ./blocks/blocks.cpp -o blocks.o

items.o: ./items/items.cpp ./items/items.h ./blocks/blocks.h
	g++ -c ./items/items.cpp -o items.o


.PHONY: clean

clean:
	-rm *.o MySnakeGame

