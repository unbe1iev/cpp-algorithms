#include "avlt.h"

// - - - - - - - - - - - - - HELPFUL FUNCTIONS - - - - - - - - - - - - -
// Function checks if operation string is valid
// Checks if it is one digit (by length and ASCII characters of digits)
bool operationValid(string op) {
    if ((op.length() == 1) && (op[0] >= 48 && op[0] <= 57)) return true;
    else return false;
}

// Function checks if it is a integer natural value:
bool naturalIsValid(string number) {
    for (int i = 0; i < number.length(); i++)
        if ((number.length() > 1 && number[0] == '0') || !(number[i] >= 48 && number[i] <= 57)) return false;
    return true;
}

// Function checks if it is a integer value (-/0/+):
bool integerIsValid(string number) {
    // Negative number case:
    if (number[0] == '-') {
        string rest = number.substr(1);
        return naturalIsValid(rest);
    }
    // 0 or positive number case:
    else return naturalIsValid(number);
}

// Sorting swap function (just for swaping two integers):
void myswap(int* xp, int* yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Function to sort the elements by priority in operation 5: (bubbleS v.)
void mysort(int* arr, int m) {
    int i, j;
    for (i = 0; i < m - 1; i++)

        // Last i elements are already in place 
        for (j = 0; j < m - i - 1; j++)
            if (arr[j] > arr[j + 1])
                myswap(&arr[j], &arr[j + 1]);
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

int main() {
    //AVLT* avlTree = new AVLT();
    string operation = "";
    string input; // every line input

    int num; // integer for consle user input
    // Variables used to printing (ASCII values of symbols):
    //  - - - - - - - - - - - - - - - - - - - - - - - - - -
    AVLT* avlTree = new AVLT[125]();

    avlTree->s1 = avlTree->s2 = avlTree->s3 = "  ";

    // connection of nodes:
    avlTree->s1[0] = 218;
    avlTree->s1[1] = 196;

    avlTree->s2[0] = 192;
    avlTree->s2[1] = 196;

    avlTree->s3[0] = 179;

    int arr[5] = { 1, 2, 3, 4, 5 };
    int k = 0;

    while (true) {
        system("cls");
        cout << "\nAVL tree management program\n";
        cout << "-------------------------------------------\n";
        cout << "[0] Exit the programu\n";
        cout << "[1] Add a node recursively\n";
        cout << "[2] Add a node iteratively\n";
        cout << "[3] Delete a node iteratively\n";
        cout << "[4] Display the tree with VLR method\n";
        cout << "[5] Display the tree with LVR method\n";
        cout << "[6] Display the tree with LRV method\n";
        cout << "-------------------------------------------\n\n";
        cout << "Option: "; cin >> operation; cout << endl;

        if (operationValid(operation)) {
            switch (operation[0]) {
            case '0':
                // Exit statement (providing that queue will be flushed until we leave):
                avlTree->clearAll();
                //delete avlTree; what exactly will happen...
                avlTree = nullptr;
                exit(0);
                break;
            case '1':
                do { // Loop for validation of user inputs
                    cout << "Value: "; cin >> input;
                    if (!integerIsValid(input)) cout << "Entered incorectly. Please re-enter!" << endl;
                } while (!integerIsValid(input));

                num = atoi(input.c_str());
                avlTree->addItem(num);
                cout << "A value has been entered into the AVL tree.";
                break;
            case '2':
                do { // Loop for validation of user inputs
                    cout << "Value: "; cin >> input;
                    if (!integerIsValid(input)) cout << "Entered incorectly. Please re-enter!" << endl;
                } while (!integerIsValid(input));

                num = atoi(input.c_str());
                avlTree->addItem2(num);
                cout << "A value has been entered into the AVL tree.";
                break;
            case '3':
                do { // Loop for validation of user inputs
                    cout << "Wartosc: "; cin >> input;
                    if (!integerIsValid(input)) cout << "Entered incorectly. Please re-enter!" << endl;
                } while (!integerIsValid(input));

                num = atoi(input.c_str());
                if (avlTree->getSize() != 0) {
                    avlTree->delItem(num);
                }
                else cout << "Operation failed. Tree is empty!";
                break;
            case '4':
                avlTree->dPreorder();
                if (avlTree->getSize() == 0) cout << "Tree is empty.";
                break;
            case '5':
                avlTree->dInorder();
                if (avlTree->getSize() == 0) cout << "Tree is empty.";
                break;
            case '6':
                avlTree->dPostorder();
                if (avlTree->getSize() == 0) cout << "Tree is empty.";
                break;
            case '7':
                sort(arr, arr + 5);
                do {
                    for (int i = 0; i < 5; i++) {
                        int num = arr[i];
                        avlTree[k].addItem(num);
                    }
                    k++;
                } while (next_permutation(arr, arr + 5));

                for (int k = 0; k < 125; k++) {
                    avlTree[k].dPreorder();
                    cout << endl;
                }

                break;
            default:
                cout << "~An invalid operation has been entered!";
                break;

            }
        }
        else cout << "~An invalid operation has been entered!";

        //To stop to hit the enter:
        getchar();
        getchar();
    }
}