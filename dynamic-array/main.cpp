#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <iomanip>
#include <time.h>

#include "src/dynamo.cpp"

using namespace std;

template <class T>
void swapElements(T& a, T& b) {
	T c(a); a = b; b = c;
}

//Helpful function to generate object and randomize value in it
ExObj* generateObj() {
	ExObj* exobj = new ExObj;
	exobj->randVal();
	return exobj;
}

//---------------------- TIMING -----------------------------------------------
//Timer variables:
clock_t main1, main2, element1, element2;

void startMainTimer() {
	//main1 = chrono::high_resolution_clock::now();
	main1 = clock();
}

void startElemTimer() {
	//element1 = chrono::high_resolution_clock::now();
	element1 = clock();
}

double stopMainTimer() {
	//main2 = chrono::high_resolution_clock::now();
	main2 = clock();
	//double microsx = chrono::duration_cast<chrono::microseconds>(main2 - main1).count();
	double microsx = (main2 - main1) / (double)CLOCKS_PER_SEC;
	return microsx;
}

double stopElemTimer() {
	//element2 = chrono::high_resolution_clock::now();
	clock_t element2 = clock();
	//double microsy = chrono::duration_cast<chrono::microseconds>(element2 - element1).count();
	double microsy = (element2 - element1) / (double)CLOCKS_PER_SEC;
	return microsy;
}
//------------------------------------------------------------------------------

int main() {
	srand(time(NULL));

	Dynamo<ExObj*>* darray = new Dynamo<ExObj*>();
	darray->setDynamo();

	const int exponent = 5;
	const int n = pow(5, exponent);

	double elementTime = 0;
	double maxElementTime = 0;
	int noticed_n = 0;

	startMainTimer();
	for (int i = 0; i < n; i++) {
		startElemTimer();
		darray->add(generateObj());
		elementTime = stopElemTimer();
		if (elementTime > maxElementTime) {
			maxElementTime = elementTime;
			noticed_n = n;
		}
	}
	double addingMainTime = stopMainTimer();

	cout << "Max element time (" << setprecision(5) << maxElementTime << " micros) noticed at: " << noticed_n << " element of table." << endl;
	cout << "Adding total time: " << setprecision(5) << addingMainTime << " micros / " << addingMainTime / 1000 << " ms / " << addingMainTime / 1000000 << " s" << endl;

	//Printing first and last 5 elements of table by briefly printing function
	//But can also use printAll() function to see all elements
	darray->printBriefly();
	//darray->printAll();
	cout << endl << "Getting [0] element: " << darray->getVal(0) << endl;

	//Changing [0] element:
	ExObj* exobj = new ExObj(99);
	darray->change(0, exobj);

	//Printing first and last 5 elements of table by briefly printing function
	//to see that [0] element changed into another created before
	darray->printBriefly();
	//darray->printAll();
	cout << endl << "Getting [0] element: " << darray->getVal(0) << endl;

	//Sorting elements in table by Bubble Sort algorithm and printing result:
	Comparator comp;
	darray->bubbleSort(&comp);

	darray->printBriefly();
	//darray->printAll();

	//Deleting all capacity elements and that you can start from scratch
	darray->deleteAll();

	//Deleting all and finishing program
	delete darray;

	return 0;
}
