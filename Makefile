CXX = g++
EXE = bst
BENCHMARK= benchmark
CXXFLAGS = -I include -std=c++14 -Wall -Wextra -g

all: $(EXE)

%.o: %.cc
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(BENCHMARK): benchmark.o
	$(CXX) $^ -o $(BENCHMARK)

$(EXE): main.o 
	$(CXX) $^ -o $(EXE) 

main.o: include/bst.hpp
benchmark.o: include/bst.hpp

clean:
	rm -rf src/*.o *.o $(EXE) $(BENCHMARK) */*~ *~ a.out*

#.PHONY: clean all format

