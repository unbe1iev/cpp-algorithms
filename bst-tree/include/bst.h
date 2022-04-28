#ifndef BST_H
#define BST_H

#include <stdlib.h>
#include <iostream>

using namespace std;

class ExObj {
	int val;
public:
	int getVal() { return val; }
	void setVal(int _val) { val = _val; }

	void randVal() { val = rand() % 100 + 1; }

	ExObj() = default;
	ExObj(int _val) {
		val = _val;
	}
};

template<class T>
class Item {
public:
	T val;

	Item<T>* left;
	Item<T>* right;
	Item<T>* parent;
};

template <class T>
bool compareT(Item<T>* item, const T& val) {
    return item->val->getVal() < val->getVal();
}

template <class T>
int compareInt(Item<T>* item, int val) {
    if (item->val->getVal() == val) return 0;
    else if (item->val->getVal() < val) return 1;
    else return 2;
}

template <class T>
class BST {
	Item<T>* root;
public:
    void addItem(const T& val);
	Item<T>* addItem(Item<T>* item, const T& val, bool(*compareT)(Item<T>* item, const T& val));

	Item<T>* findItem(Item<T>* item, int val, int(*cmpInt)(Item<T>* item, int val));
    Item<T>* findItem(int val);

    void dInorder(Item<T>* item);
    void dPreorder(Item<T>* item);
    void displayAtOrder(bool order);

    Item<T>* remItem(Item<T>* item, int val, int(*cmpInt)(Item<T>* item, int val));
    void rem(int val);

    void remOneByOne(Item<T>* item);
    void remAll(Item<T>** item);
    void clearAll();

	int getHeight(Item<T>* item);
	int getSize(Item<T>* item);

	void displayItems(Item<T>* item);
	void display();
};

#endif // BST_H
