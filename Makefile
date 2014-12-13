CXX = g++
SUFFIXES = .cpp .o
INCS = -Iinclude/
FLAGS = -O3

drafter: Player.o Team.o src/main.cpp
	${CXX} ${INCS} src/main.cpp Player.o Team.o ${FLAGS} -o $@

.cpp.o:
	${CXX} ${INCS} ${FLAGS} -c $< 

run:
	./comb

clean: 
	rm src/*.o *.o drafter
