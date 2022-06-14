#!make -f

CXX=clang++ 
CXXFLAGS=-std=c++2a -Werror -Iimgui -Iimgui/backends -I/usr/include/SDL2 -lSDL2 -lGL

HEADERS=Game.hpp Team.hpp Leauge.hpp Schedule.hpp 
OBJECTS=Game.o Team.o Leauge.o Schedule.o 
SOURCES=Game.cpp Team.cpp Leauge.cpp Schedule.cpp 



run: main
	./$^

demo: main.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o main

test: TestRunner.o Test.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o test

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-* --warnings-as-errors=-* --

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o demo test
