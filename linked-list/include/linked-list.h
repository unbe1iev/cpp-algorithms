#ifndef LINKED-LIST_H
#define LINKED-LIST_H

// We need one item class to handle the list that is below
template <class T>
class Item {
public:
	T val;

	Item<T>* next;
	Item<T>* prev;

	Item(T val) : val{ val } {};
};

// List class
template <class T>
class List {
	int amount;
public:
	Item<T>* first;
	Item<T>* last;

	List() = default;
	~List() {
		delete first; first = nullptr;
		delete last; last = nullptr;
	}

	bool addItem_first(const T& val);
	bool addItem_last(const T& val);
	bool addItemToId(int id, const T& val);
	bool delItem_first();
	bool delItem_last();
	bool deleteAll();
	bool changeItem(int id, const T& val);
	bool findAndDelete(const T& val);

	Item<T>* getItemById(int id) const;
	Item<T>* findItem(const T& val) const;
	int getSize() const;
	void display() const;
};


#endif // LINKED-LIST_H
