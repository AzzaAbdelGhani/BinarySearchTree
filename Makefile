CXX = g++
EXE = bst
CXXFLAGS = -I include -std=c++14

all: $(EXE)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(EXE): main.o src/bst.o 
	$(CXX) $^ -o $(EXE) 

main.o: src/bst.o

src/bst.o: include/bst.hpp

clean:
	rm -rf src/*.o *.o $(EXE) */*~ *~ a.out*

#.PHONY: clean all format

