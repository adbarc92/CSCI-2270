MAIN=PQueueDriver.cpp
INCLUDES= PQueueBH.cpp PQueueLL.cpp

all:
	rm -f main
	g++ $(MAIN) -g -O0 -std=c++11 $(INCLUDES) -Wall -o main

run:
	./$(MAIN:cpp=exe)