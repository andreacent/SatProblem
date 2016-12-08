main:	main.cpp
		g++ -O3 -Wall -std=c++11 -o main main.cpp

clean:
		rm -f main core *~

