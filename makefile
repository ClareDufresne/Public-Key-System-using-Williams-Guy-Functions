publicKeySystem: main.o publicKeySystem.o
	g++ main.o publicKeySystem.o -I jacobi/include -l jacobi -L ./jacobi -o publicKeySystem
	
build: publicKeySystem
	cargo build  --manifest-path=jacobi/Cargo.toml

clean:
	rm *.o publicKeySystem

clean_all: clean
	cargo clean  --manifest-path=jacobi/Cargo.toml

publicKeySystem.o: publicKeySystem.cpp publicKeySystem.h
	g++ -c publicKeySystem.cpp 

main.o: main.cpp publicKeySystem.h
	g++ -c main.cpp 
