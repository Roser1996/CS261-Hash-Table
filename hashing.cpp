#include <iostream>

#include "hashing.h"

using namespace std;

// Base Hash

baseHash::baseHash() {}

baseHash::~baseHash() {}

float baseHash::loadFactor() {
	return 0;
}

int baseHash::hashFunction(const int& key) {
	return 0;
}

int baseHash::search(const int& key) {
	return 0;
}

bool baseHash::set(const int& key, const int& value) {
	return false;
}

bool baseHash::remove(const int& key) {
	return false;
}

void baseHash::printHashmap() {}

// Linear Hashing API

linearHash::linearHash(const int& size) {
	store = new Lnode*[size];
	hash_size  = size;
	for(int i = 0; i < hash_size; i++) 
		store[i] = new Lnode();
	cur_size = 0;
}

linearHash::~linearHash() {
	for(int i = 0; i < hash_size; i++) {
		delete store[i];
		store[i] = nullptr;
	}
	delete store;
	store = nullptr;
}

float linearHash::loadFactor() {
	return float(cur_size) / float(hash_size);
}

int linearHash::hashFunction(const int& key) {
	int index = key % hash_size;
	return index;
}

int linearHash::search(const int& key) {
	int cur_index = hashFunction(key);
	for(int i = cur_index; i < hash_size; i++) {
		if(store[i]->key == key) 
			return store[i]->value;
	}
	if(cur_index > 0) {
		for(int i = 0; i < cur_index; i++) {
			if(store[i]->key == key)
				return store[i]->value;
		}
	}

	//cerr << "There is no such node in the hash map" << endl;
	return -1;
}

bool linearHash::set(const int& key, const int& value) {

	if(cur_size == hash_size) {
		cout << "Current hash table is full" << endl;
		return false;
	}
	
	int cur_index = hashFunction(key);
	for(int i = cur_index; i < hash_size; i++) {
		if(store[i]->key == INT_MIN) {
			store[i]->key = key;
			store[i]->value = value;
			cur_size++;
			return true;
		}
		if(store[i]->key == key) {
			store[i]->value = value;
			return true;
		}
	}
	if(cur_index > 0) {
		for(int i = 0; i < cur_index; i++) {
			if(store[i]->key == INT_MIN) {
				store[i]->key = key;
				store[i]->value = value;
				cur_size++;
				return true;
			}
			if(store[i]->key == key) {
				store[i]->value = value;
				return true;
			}
		}
	}

	cerr << "The hash map has no empty sapce" << endl;
	return false;
}

bool linearHash::remove(const int& key) {
	int del_index = hashFunction(key);

	for(int i = del_index; i < hash_size; i++) {
		if(store[i]->key == key) {
			store[del_index]->key = INT_MIN;
			store[del_index]->value = INT_MIN;
			cur_size--;
			return true;
		}
	}
	if(del_index > 0) {
		for(int i = 0; i < del_index; i++) {
			if(store[i]->key == key) {
				store[del_index]->key = INT_MIN;
				store[del_index]->value = INT_MIN;
				cur_size--;
				return true;
			}
		}
	}

	//cerr << "There is no such node in the hash map" << endl;
	return false;
}

void linearHash::printHashmap() {
	cout << "Current hash map is: " << endl;
	for(int i = 0; i < hash_size; i++) {
		if(store[i]->key == INT_MIN)
			cout << i + 1 << " Key: none Value: none" << endl;
		else 
			cout << i + 1 << " Key: " << store[i]->key << " " << "Value: " << store[i]->value << endl;
	}
	cout << endl;
	return;
}


// Hash Chaining API

hashChain::hashChain(const int& size) {
	store = new Cnode*[size];
	hash_size = size;
	for(int i = 0; i < hash_size; i++) {
		store[i] = new Cnode();
	}
	cur_size = 0;
}

hashChain::~hashChain() {
	for(int i = 0; i < hash_size; i++) {
		if(store[i]->next != nullptr) {
			Cnode *temp = store[i]->next;
			while(temp != nullptr) {
				Cnode *del_node = temp;
				temp = temp->next;
				delete del_node;
				del_node = nullptr;
			}
		}
		delete store[i];
		store[i] = nullptr;
	}
	delete store;
	store = nullptr;
}

float hashChain::loadFactor() {
	return (float)cur_size / (float)hash_size;
}

int hashChain::hashFunction(const int& key) {
	int index = key % hash_size;
	return index;
}

int hashChain::search(const int& key) {
	int cur_index = hashFunction(key);
	Cnode *temp = store[cur_index];
	if(temp->key == INT_MIN) {
		//cout << "There is no such node in the hash map" << endl;
		return -1;
	}
	else if(temp->key == key) 
		return temp->value;
	else {
		temp = temp->next;
		while(temp != nullptr) {
			if(temp->key == key) 
				return temp->value;
			temp = temp->next;
		}
	}

	//cout << "There is no such node in the hash map" << endl;
	return -1;
}

bool hashChain::set(const int& key, const int& value) {
	int cur_index = hashFunction(key);
	Cnode *temp = store[cur_index];
	if(temp->key == INT_MIN) {
		temp->key = key;
		temp->value = value;
		cur_size++;
		return true;
	}
	else {
		while(temp->next != nullptr) {
			if(temp->key == key) {
				temp->value = value;
				return true;
			}
			temp = temp->next;
		}
	}

	if(temp->key == key) {
		temp->value = value;
		return true;
	}
	Cnode *add = new Cnode(key, value);
	temp->next = add;
	cur_size++;
	return true;
}

bool hashChain::remove(const int& key) {
	int del_index = hashFunction(key);
	Cnode *temp = store[del_index];
	if(temp->key == INT_MIN) {
		//cout << "There is no such node in the hash map" << endl;
		return false;
	}
	else if(temp->key == key) {
		if(temp->next == nullptr) {
			temp->key = INT_MIN;
			temp->value = INT_MIN;
			cur_size--;
			return true;
		}
		else {
			Cnode *del_node = temp; 
			store[del_index] = temp->next;
			delete del_node;
			del_node = nullptr;
			cur_size--;
			return true;
		}
	}
	else {
		if(temp->next == nullptr) {
			//cout << "There is no such node in the hash map" << endl;
			return false;
		}
		while(temp->next != nullptr) {
			if(temp->next->key == key) {
				Cnode *del_node = temp->next; 
				temp->next = temp->next->next;
				delete del_node;
				del_node = nullptr;
				cur_size--;
				return true;
			}
			temp = temp->next;
		}
	}

	//cout << "There is no such node in the hash map" << endl;
	return false;
}

void hashChain::printHashmap() {
	cout << endl <<"Current hash map is: " << endl;
	for(int i = 0; i < hash_size; i++) {
		if(store[i]->key == INT_MIN) 
			cout << i + 1 <<" Key: none Value: none";
		else {
			Cnode *show = store[i];
			cout << i + 1;
			while(show != nullptr) {
				cout << " Key: " << show->key << " Value: " << show->value;
				show = show->next;
			}
		}
		cout << endl;
	}
	cout << endl;
	return;
}


// Cuckoo hash API

cuckooHash::cuckooHash(const int& size_1, const int& size_2) {
	hash_size_1 = size_1;
	hash_size_2 = size_2;
	store_1 = new Lnode*[size_1];
	store_2 = new Lnode*[size_2];
	for(int i = 0; i < hash_size_1; i++) {
		store_1[i] = new Lnode();
	}
	for(int i = 0; i < hash_size_2; i++) {
		store_2[i] = new Lnode();
	}	
	cur_size_1 = 0;
	cur_size_2 = 0;		
}

cuckooHash::~cuckooHash() {
	for(int i = 0; i < hash_size_1; i++) {
		delete store_1[i];
		store_1[i] = nullptr;
	}
	for(int i = 0; i < hash_size_2; i++) {
		delete store_2[i];
		store_2[i] = nullptr;
	}
	delete store_1;
	delete store_2;
	store_1 = nullptr;
	store_2 = nullptr;
}

int cuckooHash::hashFunction_1(const int& key) {
	int index = key % hash_size_1;
	return index;
}

int cuckooHash::hashFunction_2(const int& key) {
	int index = (key / hash_size_2) % hash_size_2;
	return index;
}

float cuckooHash::loadFactor_1() {
	return (float)cur_size_1 / float(hash_size_1);
}

float cuckooHash::loadFactor_2() {
	return (float)cur_size_2 / float(hash_size_2);
}

float cuckooHash::loadFactor() {
	return (double)(cur_size_1 + cur_size_2) / (double)(hash_size_1 + hash_size_2);
}

int cuckooHash::search(const int& key) {
	int index_1 = hashFunction_1(key);
	if(store_1[index_1]->key == key)
		return store_1[index_1]->value;
	int index_2 = hashFunction_2(key);
	if(store_2[index_2]->key == key)
		return store_2[index_2]->value;

	//cerr << "There is no such node in the hash map" << endl;
	return -1;
}

bool cuckooHash::set(const int& key, const int& value) {

	if(cur_size_1 == hash_size_1 && cur_size_2 == hash_size_2) {
		cerr << "Current hash table is full" << endl;
		return false;
	}

	double f1 = loadFactor_1(), f2 = loadFactor_2();

	// hash table 1 has more than 50 percent empty space
	if(f1 < 0.5) {
		int index_1 = hashFunction_1(key);
		if(store_1[index_1]->key == INT_MIN) {
			store_1[index_1]->key = key;
			store_1[index_1]->value = value;
			cur_size_1++;
			return true;
		}
	}
	

	// hash table 2 has more than 50 percent empty space
	if(f2 < 0.5) {
		int index_2 = hashFunction_2(key);
		if(store_2[index_2]->key == INT_MIN) {
			store_2[index_2]->key = key;
			store_2[index_2]->value = value;
			cur_size_2++;
			return true;
		}
	}
	

	// both hash table dont have empty space 
	Lnode *moved = new Lnode(key, value);
	int table_num = 1;  
	int cur_index = hashFunction_1(key); 
	int count = 0;
	while(moved != nullptr) {
		if(count > hash_size_1 + hash_size_2) {
			cerr << "Current hash table has cycle, need to rehash" << endl;
			return false;
		}
		if(table_num == 1) {
			int temp_key = store_1[cur_index]->key, temp_value = store_1[cur_index]->value;
			store_1[cur_index]->key = moved->key;
			store_1[cur_index]->value = moved->value;
			if(temp_key == INT_MIN) {
				moved = nullptr;
			}
			else {
				cur_index = hashFunction_2(temp_key);
				moved->key = temp_key;
				moved->value = temp_value;
				table_num = 2;
			}
		}
		else if(table_num == 2) {
			int temp_key = store_2[cur_index]->key, temp_value = store_2[cur_index]->value;
			store_2[cur_index]->key = moved->key;
			store_2[cur_index]->value = moved->value;
			if(temp_key == INT_MIN) {
				moved = nullptr;
			}
			else {
				cur_index = hashFunction_1(temp_key);
				moved->key = temp_key;
				moved->value = value;
				table_num = 1;
			}
		}
		count++;
	}

	delete moved;
	moved = nullptr;

	return true;

}

bool cuckooHash::remove(const int& key) {
	int index_1 = hashFunction_1(key);
	if(store_1[index_1]->key == key) {
		store_1[index_1]->key = INT_MIN;
		store_1[index_1]->value = INT_MIN;
		cur_size_1--;
		return true;
	} 
	int index_2 = hashFunction_2(key);
	if(store_2[index_2]->key == key) {
		store_2[index_2]->key = INT_MIN;
		store_2[index_2]->value = INT_MIN;
		cur_size_2--;
		return true;
	}

	//cerr << "There is no such node in the hash map" << endl;
	return false;

}

void cuckooHash::printHashmap() {

	cout << endl << "Hash table 1 is: " << endl;
	for(int i = 0; i < hash_size_1; i++) {
		if(store_1[i]->key == INT_MIN)
			cout << i + 1 << " Key: none Value: none" << endl;
		else 
			cout << i + 1 << " Key: " << store_1[i]->key << " " << "Value: " << store_1[i]->value << endl;
	}
	cout << endl << "Hash map 2 is: " << endl;
	for(int i = 0; i < hash_size_2; i++) {
		if(store_2[i]->key == INT_MIN) 
			cout << i + 1 << " Key: none Value: none" << endl;
		else
			cout << i + 1 << " Key: " << store_2[i]->key << " " << "Value: " << store_2[i]->value << endl;
	}
	cout << endl;
	return;
}



// Quadratic Hash API

quadraticHash::quadraticHash(const int& size) {
	store = new Lnode*[size];
	hash_size = size;
	for(int i = 0; i < hash_size; i++) {
		store[i] = new Lnode();
	}
	cur_size = 0;
}

quadraticHash::~quadraticHash() {
	for(int i = 0; i < hash_size; i++) {
		delete store[i];
		store[i] = nullptr;
	}
	delete store;
	store = nullptr;
}

float quadraticHash::loadFactor() {
	return (float)cur_size / (float)hash_size;
}

int quadraticHash::hashFunction(const int& key, int num) {
	int index = (key % hash_size + num * num) % hash_size;
	return index;
}

int quadraticHash::search(const int& key) {

	if(cur_size == 0) {
		cerr << "There is no such node in the hash map" << endl;
		return -1;
	}

	int i = 0;
	while(true) {
		int cur_index = hashFunction(key, i);
		if(store[cur_index]->key == key)
			return store[cur_index]->value;
		i++;
		if(i >= hash_size)
			break;
	}

	cerr << "There is no such node in the hash map" << endl;
	return -1;
}

bool quadraticHash::set(const int& key, const int& value) {
	
	if(cur_size == hash_size) {
		cerr << "Current hash table is full" << endl;
		return false;
	}

	int i = 0; 
	while(true) {
		int cur_index = hashFunction(key, i);
		if(store[cur_index]->key == INT_MIN) {
			store[cur_index]->key = key;
			store[cur_index]->value = value;
			cur_size++;
			return true;
		}
		i++;
		if(i >= hash_size)
			break;
	}

	cerr << "There is no empty sapce in the hash map" << endl;
	return false;
}

bool quadraticHash::remove(const int& key) {

	if(cur_size == 0) {
		cerr << "There is no such node in the hash map" << endl;
		return -1;
	}

	int i = 0;
	while(true) {
		int cur_index = hashFunction(key, i);
		if(store[cur_index]->key == key) {
			store[cur_index]->key = INT_MIN;
			store[cur_index]->value = INT_MIN;
			cur_size--;
			return true;
		} 
		i++;
		if(i >= hash_size) 
			break;
 	}

 	cerr << "There is no such node in the hash map" << endl;
 	return false;
}

void quadraticHash::printHashmap() {

	cout << endl << "Current hash map is: " << endl;
	for(int i = 0; i < hash_size; i++) {
		if(store[i]->key == INT_MIN) 
			cout << i + 1 << " Key: none Value: none" << endl;
		else 
			cout << i + 1 << " Key: " << store[i]->key << " " << "Value: " << store[i]->value << endl;
	}
	cout << endl;
	return;
}


 
