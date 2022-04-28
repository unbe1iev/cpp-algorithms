#include "dynamo.h"
#include <iostream>

using namespace std;

template <class T>
void Dynamo<T>::setDynamo() { arr = new T[capacity]; }

template <class T>
void Dynamo<T>::add(const T& val) {
	if (usage == capacity) {
		capacity *= factor;
		T* temp = new T[capacity];

		for (int i = 0; i < usage; i++)
			temp[i] = arr[i];

		delete arr;
		arr = temp;
	}
	arr[usage] = val;
	usage++;
}

template <class T>
int Dynamo<T>::getVal(const int id) {
	if ((id < 0) || (id > usage - 1))
		throw invalid_argument("Received id out of bounds!");
	else return arr[id]->getVal();
}

template <class T>
void Dynamo<T>::printAll() {
	cout << "Usage: " << usage << "/" << capacity << endl;
	cout << "---" << endl;
	for (int i = 0; i < usage; i++)
		cout << arr[i]->getVal() << endl;
	cout << "---" << endl;
}

template <class T>
void Dynamo<T>::printBriefly() {
	cout << "Usage: " << usage << "/" << capacity << endl << "---" << endl;

	// Print first 5 elements:
	for (int i = 0; i < 5; i++)
		cout << arr[i]->getVal() << endl;

	cout << "..\n..\n.." << endl;

	// Print last 5 elements:
	for (int i = usage - 5; i < usage - 1; i++)
		cout << arr[i]->getVal() << endl;

	cout << "---" << endl;
}

template <class T>
void Dynamo<T>::deleteAll() {
	T* temp = new T[1];

	for (int i = 0; i < capacity; i++) {
		delete arr[i];
	}
	arr = temp;
	capacity = 1;
	usage = 0;
}

template <class T>
void Dynamo<T>::change(const int id, T& val) {
	delete arr[id];
	arr[id] = val;
}

template <class T>
void Dynamo<T>::bubbleSort(Comparator* comp) {
	for (int i = 0; i < usage; i++)
		for (int j = 1; j < usage - i; j++)
			if (comp->compare(arr[j - 1], arr[j]))
				swapElements(arr[j - 1], arr[j]);
}
