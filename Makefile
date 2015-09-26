all:
	@g++ -std=c++11 graph.cpp dijkstra.cpp example.cpp -o dijkstra

run:
	./dijkstra

clear:
	@rm dijkstra
