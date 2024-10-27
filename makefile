publicKeySystem: main.o publicKeySystem.o test generate timing
	g++ -std=c++14 main.o publicKeySystem.o -o publicKeySystem -lgmp

clean:
	rm *.o publicKeySystem test generate timing

publicKeySystem.o: publicKeySystem.cpp publicKeySystem.h
	g++ -std=c++14 -c publicKeySystem.cpp 

main.o: main.cpp publicKeySystem.h
	g++ -std=c++14 -c main.cpp 

test: test_publicKeySystem.cpp publicKeySystem.o 
	g++ -std=c++14 -Wall -g -pthread test_publicKeySystem.cpp publicKeySystem.o -lgtest_main -lgtest -lpthread -o test -lgmp

generate: generate.cpp publicKeySystem.o
	g++ -std=c++14 generate.cpp publicKeySystem.o -o generate -lgmp

timing: Timing.cpp publicKeySystem.o
	g++ -std=c++14 Timing.cpp publicKeySystem.o -o timing -lgmp -lboost_chrono