
OBJECTS = items.o blocks.o snake.o map.o renders.o main.o
HEADERS = ./renders/renders.h ./snake/snake.h ./map/map.h ./blocks/blocks.h ./items/items.h

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


.PHONY: clean

clean:
	-rm $(OBJECTS) SnakeGame



