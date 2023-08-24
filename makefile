CC = g++ -std=c++11 -c -Wall 
proj5.x: hashtable.hpp proj5.cpp passserver.cpp hashtable.h passserver.h
	$(CC) passserver.cpp
	$(CC) proj5.cpp
	g++ -std=c++11 proj5.o passserver.o  -lcrypt -o proj5.x
	


clean: 
	rm *.o 