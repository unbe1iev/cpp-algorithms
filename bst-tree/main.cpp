#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <time.h>
#include <string>

#include "src/bst.cpp"

using namespace std;

//Helpful function to generate object and randomize value in it
ExObj* generateObj(int val) {
	ExObj* exobj = new ExObj;
	exobj->setVal(val);
	return exobj;
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

    BST<ExObj*>* t = new BST<ExObj*>();

    double timer = 0;

    //Adding some objects to our tree:
    startMainTimer();
	t->addItem(generateObj(20));
	t->addItem(generateObj(15));
	t->addItem(generateObj(25));
    t->addItem(generateObj(17));
	t->addItem(generateObj(18));
    t->addItem(generateObj(3));
	t->addItem(generateObj(13));
	timer = stopMainTimer();
    cout << "Adding total time: " << setprecision(5) << timer << " micros / " << timer / 1000 << " ms / " << timer / 1000000 << " s" << endl;

	t->display();

	//Searching for specific element:
	cout << endl << endl << "Element odnaleziony: ";
	startMainTimer();
	cout << t->findItem(15)->val->getVal();
    timer = stopMainTimer();
    cout << endl << "Finding total time: " << setprecision(5) << timer << " micros / " << timer / 1000 << " ms / " << timer / 1000000 << " s" << endl;

	//Displaying inorder/preorder:
	cout << endl << "InOrder: "; t->displayAtOrder(true);
	cout << endl;
	cout << "PreOrder: "; t->displayAtOrder(false);
	cout << endl;

	//Deleting one element:
	startMainTimer();
	t->rem(17);
	timer = stopMainTimer();
    cout << endl << "InOrder after deleting: "; t->displayAtOrder(true);
    cout << endl << "Deleting total time: " << setprecision(5) << timer << " micros / " << timer / 1000 << " ms / " << timer / 1000000 << " s" << endl;

	//Deleting all elements in tree with root
	t->clearAll();

	//Lets see if we have deleted everything:
	cout << endl;
    t->display();

    delete t;
	return 0;
}
