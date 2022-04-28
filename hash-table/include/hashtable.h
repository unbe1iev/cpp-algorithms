#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <math.h>

using namespace std;

struct Reg{
  string key;
  int val;

  Reg(){
    // generating the key:
    for (int i=0; i<6; i++)
    key += 'a' + rand()%26;
  }
};

template <class T>
class Item {
public:
    T reg;

	Item<T>* next;
	Item<T>* prev;

	Item(T& reg) : reg{ reg } {};
	~Item() {}
};

template <class T>
class List {
	int amount = 0;
public:
	Item<T>* first;
	Item<T>* last;

	bool addItem_first(Reg reg);
    bool addItem_last(Reg reg);
    bool addItem(Item<T>*);
    Item<T>* getItemById(int id) const;
    int getAmount();
    bool findAndDelete(string key);
    bool delItem_first();
	bool delItem_last();
	bool clearAll();

	List() = default;
	~List() {
		delete first; first = nullptr;
		delete last; last = nullptr;
	}
};

template <class T>
class HashTable {
    List<T>** l;
    int capacity = 1;
    float limit = 0.75;
	int usage = 0;
	float factor = 2.0;

public:
    void setHashTable();
    void add(Reg reg);
    int getHash(string key);
    void reHashAll();
    void print();
    void printStats();
    Item<T>* findElement(string key);
    bool remElement(string key);
    bool clearAll();

    HashTable() = default;
	~HashTable() {
		delete l;
	}
};

#endif // HASHTABLE_H
