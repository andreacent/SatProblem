main:	main.cpp
		g++ -O3 -Wall -std=c++11 -o cnf main.cpp

clean:
		rm -f main core *~

