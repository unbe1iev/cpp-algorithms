#ifndef RBT_H
#define RBT_H

class ExObj {
	int val;
public:
	int getVal() { return val; }
	void setVal(int _val) { val = _val; }

	ExObj() = default;
	ExObj(int _val) {
		val = _val;
	}
};

template<class T>
class Item {
public:
	T val;
	bool color; // true - black, false - red

	Item<T>* left;
	Item<T>* right;
	Item<T>* parent;

	Item() = default;

    Item(ExObj *_val) {
       val = _val;
       left = right = parent = nullptr;
       color = false;
    }
};

template <class T>
class RBT {
	Item<T>* root = nullptr;
	int sizeRBT = 0;
public:
    // Adding
    void addItem(const T& val);
	Item<T>* addItem(Item<T>* root, Item<T>* item, bool(*cmpT)(Item<T>* item1, Item<T>* item2));

	// Fixing
    void rotLeft(Item<T>* item);
    void rotRight(Item<T>* item);
    void fixRBT(Item<T>* item);

	// Finding
	Item<T>* findItem(Item<T>* item, int val, int(*cmpInt)(Item<T>* item, int val));
    Item<T>* findItem(int val);

    // Displaying
    void dInorder(Item<T>* item);
    void dPreorder(Item<T>* item);
    void displayAtOrder(bool order);

    void displayItems(Item<T>* item);
	void display();

	// Removing
    void remOneByOne(Item<T>* item);
    void remAll();

    // Getting
	int getHeight(Item<T>* item);
	int getSize();

	// Setting
	void setColor(Item<T> *item, bool color);
	void swapColors(Item<T>* a, Item<T>* b);
};

#endif // RBT_H
