all:
	g++ -std=c++11 -o test main.cpp MemoryManager/*.cpp -lpthread -pthread
