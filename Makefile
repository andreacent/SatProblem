main:	main.cpp
		g++ -O3 -Wall -std=c++11 -o main main.cc

clean:
		rm -f main core *~
