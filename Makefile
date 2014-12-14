CXX = g++
SUFFIXES = .cpp .o
INCS = -Iinclude/
FLAGS = -O3 -std=c++11

.cpp.o:
	${CXX} ${INCS} ${FLAGS} -c $< 

drafter: src/Player.o src/Team.o src/main.cpp
	${CXX} ${INCS} src/main.cpp Player.o Team.o ${FLAGS} -o $@

run:
	./comb

comb: combination.cpp
	g++ combination.cpp -o ./comb -O3
	
comb_debug: combination.cpp
	g++ combination.cpp -DDEBUG -o $@ -O3

clean: 
	rm src/*.o *.o drafter
