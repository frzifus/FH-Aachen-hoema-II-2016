CXX=g++
CXXFLAGS=-std=c++14 -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion # -O3
LDFLAGS= 

.PHONY: lesson1 lesson2 lesson3 lesson4 lesson5 clean

all: lesson1 lesson2 lesson3 lesson4 lesson5

lesson1: 
	mkdir -p bin
	@$(CXX) $(LDFLAGS) $(CXXFLAGS) lesson1/main.cc lesson1/util.cc vendor/vector.cc -I lesson1 -I vendor -o bin/l1

lesson2:
	mkdir -p bin
	@$(CXX) $(LDFLAGS) $(CXXFLAGS) lesson2/main.cc lesson2/util.cc vendor/vector.cc vendor/matrix.cc -I lesson2 -I vendor -o bin/l2

lesson3:
	mkdir -p bin
	@$(CXX) $(LDFLAGS) $(CXXFLAGS) lesson3/main.cc lesson3/util.cc vendor/vector.cc vendor/matrix.cc vendor/dgl_solver.cc -I lesson3 -I vendor -o bin/l3

lesson4:
	mkdir -p bin
	cp -r resources bin/
	@$(CXX) $(LDFLAGS) $(CXXFLAGS) lesson4/main.cc lesson4/complex.cc lesson4/compression.cc -I lesson4 -o bin/l4

lesson5:
	mkdir -p bin
	@$(CXX) $(LDFLAGS) $(CXXFLAGS) lesson5/main.cc lesson5/lotto.cc lesson5/zufall.cc -I lesson5 -I vendor -o bin/l5

format:
	find . -iname *.h -o -iname *.cc | xargs clang-format -i

clean:
	rm -rf bin
	rm -f *.o

distclean:
	rm -fr build
	git ls-files --others | xargs rm -rf
