test: test.o hashing.o
	g++ test.o hashing.o -o test

test.o: test.cpp hashing.h
	g++ -c test.cpp

hashing.o: hashing.cpp hashing.o
	g++ -c hashing.cpp

clean:
	rm *.o