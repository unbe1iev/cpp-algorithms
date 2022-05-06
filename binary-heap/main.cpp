#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <iomanip>
#include <time.h>
#include <string>
#include <math.h>

using namespace std;

class Obj {
	int val;
public:
	int getVal() { return val; }
	void setVal(int _val) { val = _val; }

	Obj() {
        val = rand() % 100 + 1;
	}
	Obj(int _val) {
		val = _val;
	}
};

class Comparator {
public:
	bool compare(Obj* o1, Obj* o2) {
		return o1->getVal() < o2->getVal();
	}
};

template <class T>
class Dynamo {
	T* arr;

	int capacity = 1;
	int usage = 0;
	float factor = 2.0;
public:
	void add(const T& val);
	void deleteAll();
	T& getElement(int id);
	int getUsage();
    void printAll();
    void print();
	void swapValues(T& a, T& b);
	void deleteLast();

	Dynamo() {
        arr = new T[capacity];
	}
	~Dynamo() {
		delete arr;
	}
};

template <class T>
void Dynamo<T>::deleteLast() {
    T* temp = new T[capacity];

    for (int i = 0; i < usage-1; i++)
        temp[i] = arr[i];

    delete arr;

    arr = temp;
	usage--;
}

template <class T>
void Dynamo<T>::print() {
	cout << "Usage: " << usage << "/" << capacity << endl;
	cout << "---" << endl;
	for (int i = 0; i < usage; i++)
		cout << arr[i]->getVal() << endl;
	cout << "---" << endl;
}

template <class T>
int Dynamo<T>::getUsage() {
    return usage;
}

template <class T>
T& Dynamo<T>::getElement(int id) {
    return arr[id];
}

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
void Dynamo<T>::swapValues(T& a, T& b) {
	int c(a->getVal());
	a->setVal(b->getVal());
	b->setVal(c);
}

template <class T>
class BinaryHeap {
    Dynamo<T>* tab;
    int length = 0;
    string r, l, p; //I need these three strings-memory to printing nicely tree
public:
    void add(const T& val, Comparator* cmp);
    void findAndRemoveMax(Comparator* cmp);
    void clearAll();
    void printAll(int id, string s1, string s2);
    void print();

    int getLeftChildId(int id);
    int getRightChildId(int id);
    int getParentId(int id);

    void heapUp(int id, Comparator* cmp);
    void heapDown(int id, Comparator* cmp);

	BinaryHeap() {
	    tab = new Dynamo<T>();
        length = 0;
        r = l = p = "  ";

        //Setting the editor characters to be displayed nicely
        r[0] = 218;
        r[1] = 196;
        l[0] = 192;
        l[1] = 196;
        p[0] = 179;
	}
	~BinaryHeap() {
		delete tab;
	}
};

template <class T>
void BinaryHeap<T>::clearAll() {
    length = 0;
}

template <class T>
void BinaryHeap<T>::print() {
    tab->print();
}

template <class T>
int BinaryHeap<T>::getLeftChildId(int id) {
	return 2*id+1;
}

template <class T>
int BinaryHeap<T>::getRightChildId(int id) {
	return 2*id+2;
}

template <class T>
int BinaryHeap<T>::getParentId(int id) {
	return (id-1)/2;
}

template <class T>
void BinaryHeap<T>::heapUp(int id, Comparator* cmp) {
	if ((id > 0) && cmp->compare(tab->getElement(getParentId(id)), tab->getElement(id))){

		int temp = tab->getElement(id)->getVal();
		tab->getElement(id)->setVal(tab->getElement(getParentId(id))->getVal());
        tab->getElement(getParentId(id))->setVal(temp);

		heapUp(getParentId(id), cmp);
	}
}

template <class T>
void BinaryHeap<T>::findAndRemoveMax(Comparator* cmp) {
    if (length == 0) {
        throw out_of_range("There is nothing to remove! Binary Heap is empty.");
    } else {
        tab->getElement(0)->setVal(tab->getElement(length-1)->getVal());
        tab->deleteLast();
        length = tab->getUsage();
        heapDown(0, cmp);
    }
}

template <class T>
void BinaryHeap<T>::heapDown(int id, Comparator* cmp) {
    int lChildId = getLeftChildId(id);
	int rChildId = getRightChildId(id);
	int pickedChildId = id;

    if ((lChildId != -1) || (rChildId != -1)) {
        if ((lChildId < length) && cmp->compare(tab->getElement(id), tab->getElement(lChildId)))
            pickedChildId = lChildId;

        if ((rChildId < length) && cmp->compare(tab->getElement(pickedChildId), tab->getElement(rChildId)))
            pickedChildId = rChildId;

        if (pickedChildId != id) {
            tab->swapValues(tab->getElement(id), tab->getElement(pickedChildId));
            heapDown(pickedChildId, cmp);
        }
    }
}

template <class T>
void BinaryHeap<T>::printAll(int id, string s1, string s2) {
  string s;

  if(id < length) {
    s = s1;
    if(s2 == r)
        s[s.length()-2] = ' ';
    printAll(2*id+2, s+p, r);

    s = s.substr(0, s1.length()-2);
    cout << s << s2 << tab->getElement(id)->getVal() << endl; // Element value
    s = s1;
    if(s2 == l)
        s[s.length()-2] = ' ';
    printAll(2*id+1, s+p, l);
  }
}

template <class T>
void BinaryHeap<T>::add(const T& val, Comparator* cmp) {
    tab->add(val);
    length = tab->getUsage();
    heapUp(length-1, cmp);
}

//---------------------- TIMING -----------------------------------------------
//Timer variables:
clock_t main1, main2, element1, element2;

void startMainTimer() {
	main1 = clock();
}

void startElemTimer() {
	element1 = clock();
}

double stopMainTimer() {
	main2 = clock();
	double microsx = (main2 - main1) / (double)CLOCKS_PER_SEC;
	return microsx;
}

double stopElemTimer() {
	clock_t element2 = clock();
	double microsy = (element2 - element1) / (double)CLOCKS_PER_SEC;
	return microsy;
}
//------------------------------------------------------------------------------

int main() {
    srand(time(NULL));
    double mainTimer = 0;

    BinaryHeap<Obj*>* bh = new BinaryHeap<Obj*>();

    Comparator cmp;
    startMainTimer();
    cout << "Adding elements..." << endl;
    for (int i=0; i<20; i++)
        bh->add(new Obj(), &cmp);

    mainTimer = stopMainTimer();
    cout << "Adding total time: " << setprecision(5) << mainTimer << " micros / " << mainTimer / 1000 << " ms / " << mainTimer / 1000000 << " s" << endl;

    bh->printAll(0, "", "");

    cout << "Removing elements one by one (root)..." << endl;

    startMainTimer();
    for (int i=0; i<20; i++)
        bh->findAndRemoveMax(&cmp);

    mainTimer = stopMainTimer();
    cout << "Removing total time: " << setprecision(5) << mainTimer << " micros / " << mainTimer / 1000 << " ms / " << mainTimer / 1000000 << " s" << endl;

    cout << endl << endl;
    bh->printAll(0, "", "");

    cout << "Confirmation below that table is empty: ..." << endl;
    bh->print();

    bh->clearAll();

    delete bh;
    return 0;
}
