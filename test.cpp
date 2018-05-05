#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cstdio>

#include "hashing.h"
#define ARRAYSIZE 5000
#define NUM_MAX 10000000

using namespace std;

void testFunction(baseHash *s, const pair<int, int> array[], ofstream &fout) {

	clock_t begin, end;
	begin = clock();
	for(int i = 0; i < ARRAYSIZE; i++) 
		s->set(array[i].first, array[i].second);
	end = clock();
	double set_time = 1000000 * (end - begin) / CLOCKS_PER_SEC;

	float f = s->loadFactor();
	//s->printHashmap();

	begin = clock();
	for(int i = 0; i < ARRAYSIZE; i++) 
		s->search(array[i].first);
	end = clock();
	double search_time = 1000000 * (end - begin) / CLOCKS_PER_SEC;

	begin = clock();
	for(int i = 0; i < ARRAYSIZE; i++) 
		s->remove(array[i].first);
	end = clock();
	double delete_time = 1000000 * (end - begin) / CLOCKS_PER_SEC;


	
	fout.precision(8); 
	fout << "Current load factor is: " << f << endl;
	fout << "Set: " << fixed << set_time << "\n";
	fout << "Search: " << fixed << search_time << "\n";
	fout << "Delete: " << fixed << delete_time << "\n";


	return;
} 


int main() {

	srand(time(nullptr));


	// prime number for the hash table size: (10177, 15121), (101293, 128971)
	int size_1 = 10177, size_2 = 10177;
	pair<int, int> testArray[ARRAYSIZE];
	for(int i = 0; i < ARRAYSIZE; i++) {
		int key = rand() % NUM_MAX + 1;
		int value = rand() % NUM_MAX + 1;
		testArray[i].first = key;
		testArray[i].second = value;
	}

	
	ofstream fout;
	fout.open("Test result.txt", ios::out|ios::app);
	fout << "Current array size: " << ARRAYSIZE << "\n";
	fout << "Current hash map size: " << size_1 << ", " << size_2 << "\n";

	// Linear Hash Test
	baseHash *s1 = new linearHash(size_1);
	fout << "\n";
	fout << "Linear Hash: " << "\n";
	testFunction(s1, testArray, fout);
	fout << "\n";
	delete s1;
	s1 = nullptr;

	// Hash Chain Test
	baseHash *s2 = new hashChain(size_1);
	fout << "\n";
	fout << "Hash Chain: " << "\n";
	testFunction(s2, testArray, fout);
	fout << "\n";
	delete s2;
	s2 = nullptr;

	// Cuckoo Hash Test
	baseHash *s3 = new cuckooHash(size_1, size_2);
	fout << "\n";
	fout << "Cuckoo Hash: " << "\n";
	testFunction(s3, testArray, fout);
	fout << "\n";
	delete s3;
	s3 = nullptr;

	// Quadratic Hash Test 
	baseHash *s4 = new quadraticHash(size_1);
	fout << "\n";
	fout << "Quadratic Hash: " << "\n";
	testFunction(s4, testArray, fout);
	fout << "\n";
	delete s4;
	s4 = nullptr;


	fout << flush;
	fout.close();

	return 0;
}