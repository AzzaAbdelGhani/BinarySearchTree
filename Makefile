CXX = g++
EXE = bst
BENCHMARK= benchmark
CXXFLAGS = -I include -std=c++14 -Wall -Wextra -g

all: $(EXE)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(BENCHMARK): benchmark.o
	$(CXX) $^ -o $(BENCHMARK)

$(EXE): main.o #src/bst.o 
	$(CXX) $^ -o $(EXE) 

main.o: include/bst.hpp
benchmark.o: include/bst.hpp

#main.o: src/bst.o include/bst.hpp

#src/bst.o: include/bst.hpp

clean:
	rm -rf src/*.o *.o $(EXE) $(BENCHMARK) */*~ *~ a.out*

#.PHONY: clean all format

