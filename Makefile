make: main.o goFish.o
	g++ main.o goFish.o -o game

main.o: main.cpp
	g++ -c main.cpp

goFish.o: goFish.cpp
	g++ -c goFish.cpp

clean: 
	rm -rf *.o ./game
