all:
	@g++ -std=c++11 graph.cpp dijkstra.cpp -o dijkstra

run:
	./dijkstra

clear:
	@rm dijkstra
