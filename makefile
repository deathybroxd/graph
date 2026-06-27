CXX = g++
CXXFLAGS = -g -Wall

graph: main.cpp GraphSystem.o Graph.h
	$(CXX) $(CXXFLAGS) main.cpp GraphSystem.o Graph.h -o graph

GraphSystem.o: GraphSystem.cpp GraphSystem.h Graph.h
	$(CXX) $(CXXFLAGS) -c GraphSystem.cpp

Graph.o: Graph.h
	$(CXX) $(CXXFLAGS) -c Graph.h

run:
	./graph

val:
	valgrind ./graph