all:
	@g++ graph.cpp dijkstra.cpp -o dijkstra

run:
	./dijkstra

clear:
	@rm dijkstra
