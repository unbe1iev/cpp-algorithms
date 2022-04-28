#ifndef DYNAMO_H
#define DYNAMO_H

#include <stdlib.h>

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

    ExObj* generateObj();
};

class Comparator {
public:
	bool compare(ExObj* o1, ExObj* o2) {
		return o1->getVal() > o2->getVal();
	}
};

template <class T>
class Dynamo {
	T* arr;

	int capacity = 1;
	int usage = 0;
	float factor = 2.0;
public:
	void setDynamo();
	void add(const T& val);
	int getVal(const int id);
	void printAll();
	void printBriefly();
	void deleteAll();
	void change(const int id, T& val);
	void bubbleSort(Comparator* comp);

	Dynamo() = default;
	~Dynamo() {
		delete arr;
		//arr = nullptr;
	}
};


#endif // DYNAMO_H
