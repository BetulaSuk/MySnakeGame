g++ -g -c ./items/items.cpp -o items.o

g++ -g -c ./blocks/blocks.cpp -o blocks.o

g++ -g -c ./snake/snake.cpp -o snake.o

g++ -g -c ./map/map.cpp -o map.o

g++ -g -c ./renders/renders.cpp -o renders.o

g++ -g -c ./debug/debug_2.cpp -o debug.o

g++ -g debug.o renders.o map.o snake.o blocks.o items.o -o debugExe -lcurses

./debugExe

rm *.o debugExe
