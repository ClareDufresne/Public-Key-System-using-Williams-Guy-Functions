publicKeySystem: main.o publicKeySystem.o test
	g++ -std=c++14 main.o publicKeySystem.o -o publicKeySystem -lgmp

clean:
	rm *.o publicKeySystem test

publicKeySystem.o: publicKeySystem.cpp publicKeySystem.h
	g++ -std=c++14 -c publicKeySystem.cpp 

main.o: main.cpp publicKeySystem.h
	g++ -std=c++14 -c main.cpp 

test: testing.cpp publicKeySystem.o
	g++ -std=c++14 testing.cpp publicKeySystem.o -o test -lgmp
