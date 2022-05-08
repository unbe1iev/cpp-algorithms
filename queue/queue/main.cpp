#include "queue.h"

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
    Queue* q = new Queue();
    string operation = "";
    string input; // every line input

    // - - - Helpful to enter numbers soon:
    int m;
    string* nms;
    int* nums;
    // - - - - - - - - - - - - - - - - - -

    while (true) {
        system("cls");
        cout << "\nProgram for managing priority queue : size 10\n";
        cout << "-------------------------------------------\n";
        cout << "[0] Quit the program\n";
        cout << "[1] Add a number to the queue\n";
        cout << "[2] Take a number off the queue\n";
        cout << "[3] Display the queue\n";
        cout << "[4] Display the queue in reverse order\n";
        cout << "[5] Add n numbers to the queue\n";
        cout << "[6] Take n numbers off from the queue\n";
        cout << "[7] Clear the queue\n";
        cout << "-------------------------------------------\n\n";
        cout << "Option: "; cin >> operation; cout << endl;

        if (operationValid(operation)) {
            switch (operation[0]) {
            case '0':
                // Exit statement (providing that queue will be flushed until we leave):
                q->deleteAll();
                delete q;
                q = nullptr;
                exit(0);
                break;
            case '1':
                if (q->possibleToAdd(1)) {
                    do { // Loop for validation of user inputs
                        cout << "Number: "; cin >> input;
                        if (!integerIsValid(input)) cout << "Entered incorrectly. Re-enter!" << endl;
                    } while (!integerIsValid(input));

                    int num = atoi(input.c_str());
                    q->addValue(num);
                    cout << "A number has been entered into the queue.";

                }
                else cout << "The operation could not be performed. The queue has reached the limit of size = 10!";
                break;
            case '2':
                if (q->getAmount() != 0) {
                    q->deleteValue();
                    cout << "Item successfully deleted.";
                }
                else cout << "Not realized. There is nothing in the queue!";
                break;
            case '3':
                if (q->getAmount() != 0) {
                    cout << "[FIRST] ";
                    q->print();
                    cout << " [LAST] ";
                }
                else cout << "The queue is empty.";
                break;
            case '4':
                if (q->getAmount() != 0) {
                    cout << "[LAST] ";
                    q->printReversed();
                    cout << "[FIRST] ";
                }
                else cout << "The queue is empty.";
                break;
            case '5':
                do {
                    cout << "How many numbers do you want to add?: "; cin >> input;
                    if (!naturalIsValid(input) || input[0] == '0') cout << "Entered incorrectly. Re-enter!" << endl;
                } while (!naturalIsValid(input) || input[0] == '0');

                m = atoi(input.c_str()); // String conversion to integer
                nms = new string[m]; // We need a string buffers to provide user wrong inputs
                nums = new int[m]; // And also int dynamic table to rewrite theses numbers and operate on them for ease

                if (q->possibleToAdd(m)) {
                    cout << "Enter the numbers (separated by enter):: " << endl;
                    for (int i = 0; i < m; i++) {
                        do {
                            cin >> nms[i];
                            nums[i] = atoi(nms[i].c_str());
                            if (!integerIsValid(nms[i])) cout << "Entered incorrectly. Re-enter!" << endl;
                        } while (!integerIsValid(nms[i]));
                    }

                    // Sorting to prepare numbers to queue entering
                    mysort(nums, m);

                    // Entering numbers by priority:
                    for (int i = 0; i < m; i++)
                        q->addValue(nums[i]);
                    cout << "Successfully entered by priority.";

                }
                else cout << "Unfortunately, the operation was rejected. The queue has only [" << size - q->getAmount() << "] free slots.";
                break;
            case '6':
                do {
                    cout << "How many numbers do you want to add?: "; cin >> input;
                    if (!naturalIsValid(input) || input[0] == '0') cout << "Entered incorrectly. Re-enter!" << endl;
                } while (!naturalIsValid(input) || input[0] == '0');

                m = atoi(input.c_str());

                if (q->possibleToDelete(m)) {
                    for (int i = 0; i < m; i++)
                        q->deleteValue();
                    cout << "Successfully removed " << m << " numbers.";
                }
                else cout << "Unfortunately, the operation was rejected. The queue has only [" << size - q->getAmount() << "] free slots.";
                break;
            case '7':
                q->deleteAll();
                cout << "Cleared.";
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
