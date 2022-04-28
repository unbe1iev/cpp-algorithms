#include <iomanip>
#include <time.h>

#include "src/hashtable.cpp"

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

    HashTable<Reg>* ht = new HashTable<Reg>();
    ht->setHashTable();

    startMainTimer();
    for (int i=1; i < 30; i++) {
        Reg toAdd;
        toAdd.val = i;
        ht->add(toAdd);
    }
    mainTimer = stopMainTimer();
    cout << "Adding total time: " << setprecision(5) << mainTimer << " micros / " << mainTimer / 1000 << " ms / " << mainTimer / 1000000 << " s" << endl;

    Reg example;
    example.key = "abcdef";
    example.val = 0;
    ht->add(example);

    ht->printStats();

    cout << endl << "Found element's value is: " << ht->findElement("abcdef")->reg.val << endl;

    cout << "Removing one element..." << endl;
    ht->remElement("abcdef");
    cout << endl << "Element with this key removed..." << endl << endl;

    ht->printStats();

    cout << endl << "Clearing hash table..." << endl;
    ht->clearAll();
    cout << endl << "All elements has been removed..." << endl << endl;

    ht->printStats();

    delete ht;
    return 0;
}
