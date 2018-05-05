#ifndef HASHING_H
#define HASHING_H

#include <climits>

//Linear Hashing node
struct Lnode {
	int key;
	int value;

	Lnode(void) {key = INT_MIN; value = INT_MIN;}
	Lnode(int x, int y) {key = x; value = y;}
};

//Hash Chaining node
struct Cnode {
	int key;
	int value;
	Cnode *next;

	Cnode(void) {key = INT_MIN; value = INT_MIN; next = nullptr;}
	Cnode(int x, int y) {key = x; value = y; next = nullptr;}
};

class baseHash {
public:
	baseHash();
	virtual ~baseHash();

	// Base hashing API
	virtual int search(const int& key);
	virtual bool set(const int& key, const int& value);
	virtual bool remove(const int& key);
	virtual void printHashmap();
	virtual float loadFactor();

private:
	virtual int hashFunction(const int& key);

};

class linearHash : public baseHash {
public:
	linearHash(const int& size);
	~linearHash();

	//basic API
	int search(const int& key);
	bool set(const int& key, const int& value);
	bool remove(const int& key);
	void printHashmap();
	float loadFactor();

private:
	Lnode **store;
	int hash_size;
	int cur_size;

	int hashFunction(const int& key);
	
};

class hashChain : public baseHash {
public:
	hashChain(const int& size);
	~hashChain();

	//basic API
	int search(const int& key);
	bool set(const int& key, const int& value);
	bool remove(const int& key);
	void printHashmap();
	float loadFactor();

private:
	int hashFunction(const int& key);

	Cnode **store;
	int hash_size;
	int cur_size;
};

class cuckooHash : public baseHash {
public:
	cuckooHash(const int& size_1, const int& size_2);
	~cuckooHash();

	//basic API
	int search(const int& key);
	bool set(const int& key, const int& value);
	bool remove(const int& key);
	void printHashmap();
	float loadFactor();

private:
	int hashFunction_1(const int& key);
	int hashFunction_2(const int& key);
	float loadFactor_1();
	float loadFactor_2();

	Lnode **store_1;
	Lnode **store_2;
	int hash_size_1;
	int hash_size_2;
	int cur_size_1;
	int cur_size_2;
};

class quadraticHash : public baseHash {
public:
	quadraticHash(const int& size);
	~quadraticHash();

	//baisc API 
	int search(const int& key);
	bool set(const int& key, const int& value);
	bool remove(const int& key);
	void printHashmap();
	float loadFactor();

private:
	int hashFunction(const int& key, int num);

	Lnode **store;
	int hash_size;
	int cur_size;
};



#endif 