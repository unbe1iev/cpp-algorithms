#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>

#include "linkedlist.cpp"

using namespace std;

// Testing class
class ExObj {
	int val1;
	char val2;
public:
	ExObj() = default;
	ExObj(int _val1, int _val2) {
		val1 = _val1;
		val2 = _val2;
	}
	void print() { cout << val1 << " " << val2 << endl; }

	int getVal1() { return val1; }
	char getVal2() { return val2; }

	void setValues(int _val1, char _val2) {
		val1 = _val1;
		val2 = _val2;
	}

	void randValues() {
		val1 = rand() % 90 + 10;
		val2 = 'a' + rand() % 26;
	}
};

//Helpful function to generate object and randomize values in it
ExObj* generateObj() {
	ExObj* exobj = new ExObj;
	exobj->randValues();
	return exobj;
}

//---------------------- TIMING -----------------------------------------------
//Timer variables:
//chrono::time_point<std::chrono::system_clock> x1;
//chrono::time_point<std::chrono::system_clock> x2;
clock_t x1, x2;

void startTimer() {
	x1 = clock(); //chrono::high_resolution_clock::now();
}

void stopTimer() {
	x2 = clock(); //chrono::high_resolution_clock::now();
	double micros = (x2 - x1) / (double)CLOCKS_PER_SEC; //chrono::duration_cast<chrono::microseconds>(x2 - x1).count();
	cout << setprecision(5) << "[Timing: " << micros << " micros" << " = " << micros / 1000 << " ms" << " = " << micros / 1000000 << " s]" << endl;
}
//------------------------------------------------------------------------------

int main() {
	List<ExObj*>* l = new List<ExObj*>();
	srand(time(NULL));

	// Add operations  and printing --------------------------------------------
	for (int i = 0; i < 20; i++) {
		startTimer();
		l->addItem_first(generateObj());
		stopTimer();
	}
	cout << endl;

	l->addItem_last(generateObj());
	l->addItem_first(generateObj());

	cout << "Size of list: " << l->getSize() << endl;
	startTimer();
	l->display();
	stopTimer();
	cout << endl;

	// Delete operation and printing -------------------------------------------
	l->delItem_first();

	for (int i = 0; i < 15; i++) {
		startTimer();
		l->delItem_last();
		stopTimer();
	}

	cout << endl << "Size of list after deleting: " << l->getSize() << endl;
	startTimer();
	l->display();
	stopTimer();
	cout << endl;

	// Get operation and printing ----------------------------------------------
	cout << "Element nr 4: ";
	l->getItemById(4)->val->print();

	// Change operation and printing -------------------------------------------
	ExObj* exobj = new ExObj(99, 'x');
	l->changeItem(0, exobj);

	l->display();

	// Find operation and printing ----------------------------------------------
	ExObj* pattern_obj = new ExObj(99, 'x');
	cout << "Found element: ";
	startTimer();
	l->findItem(pattern_obj)->val->print();
	stopTimer();
	cout << endl;

	// Find and delete operation then printing ----------------------------------
	cout << "Found item deleted? [1/0]: " << l->findAndDelete(pattern_obj) << endl;
	cout << "Size of list after deleting: " << l->getSize() << endl;

	delete pattern_obj;
	pattern_obj = nullptr;

	l->display();

	// Add to id operation and printing -----------------------------------------
	ExObj* objToAdd = new ExObj;
	objToAdd->setValues(11, 'y');

	l->addItemToId(2, objToAdd);

	cout << "Size of list after adding: " << l->getSize() << endl;
	l->display();

	// Delete operation and printing --------------------------------------------
	startTimer();
	l->deleteAll();
	stopTimer();
	cout << endl;

	cout << "Size of list after deleting: " << l->getSize() << endl;
	l->display();

	delete l;
	l = nullptr;
	return 0;
}
