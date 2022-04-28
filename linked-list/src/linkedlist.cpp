#include "linkedlist.h"

// Constructors and destructors

// Methods
template <class T>
bool List<T>::addItem_first(const T& val) {
	Item<T>* item = new Item<T>{ val };

	if (first != nullptr) {
		item->next = first;
		first->prev = item;
	}
	first = item;
	if (amount == 0) last = first;

	amount++;
	return true;
}

template <class T>
bool List<T>::addItem_last(const T& val) {
	if (amount == 0) return addItem_first(val);
	else {
		Item<T>* item = new Item<T>{ val };
		last->next = item;
		item->prev = last;
		last = item;

		amount++;
		return true;
	}
}

template <class T>
bool List<T>::addItemToId(int id, const T& val) {
	if (id < 0 || id > amount) return false;
	else if (id == 0) return addItem_first(val);
	else if (id == amount) return addItem_last(val);
	else {
		Item<T>* prevItem = first;

		for (int i = 0; i < id - 1; ++i) prevItem = prevItem->next;

		Item<T>* nextItem = prevItem->next;
		Item<T>* item = new Item<T>{ val };

		item->next = nextItem;
		item->prev = prevItem;
		prevItem->next = item;
		nextItem->prev = item;

		amount++;
		return true;
	}
}

template <class T>
bool List<T>::delItem_first() {
	if (amount != 0) {
		if (amount == 1) delete first;
		else {
			Item<T>* item = first;
			first = first->next;
			delete item;

			if (first != nullptr) first->prev = nullptr;
		}
		amount--;
		return true;
	}
	else return false;
}

template <class T>
bool List<T>::delItem_last() {
	if (amount != 0) {
		if (amount == 1) return delItem_first();
		else {
			Item<T>* item = last;
			last = last->prev;
			last->next = nullptr;
			delete item;

			amount--;
			return true;
		}
	}
	else return false;
}

template <class T>
Item<T>* List<T>::getItemById(int id) const {
	if (id < 0 || id > amount) return nullptr;
	else if (id == 0) return first;
	else if (id == amount - 1) return last;

	Item<T>* item = first;

	int i = 0;
	while (i != id) { item = item->next; i++; }

	return item;
}

template <class T>
Item<T>* List<T>::findItem(const T& val) const {
	for (int i = 0; i < amount; i++) {
		if ((getItemById(i)->val->getVal1() == val->getVal1()) && (getItemById(i)->val->getVal2() == val->getVal2())) {
			return getItemById(i);
		}
	}
	return nullptr;
}

template <class T>
bool List<T>::findAndDelete(const T& val) {
	for (int i = 0; i < amount; i++) {
		if ((getItemById(i)->val->getVal1() == val->getVal1()) && (getItemById(i)->val->getVal2() == val->getVal2())) {
			if (i == 0) return delItem_first();
			else if (i == amount - 1) return delItem_last();
			else {
				getItemById(i - 1)->next = getItemById(i + 1);
				getItemById(i + 1)->prev = getItemById(i - 1);

				delete getItemById(i);
				getItemById(i)->val = nullptr;

				return true;
			}
		}
	}
	return false;
}

template <class T>
int List<T>::getSize() const {
	return amount;
}

template <class T>
void List<T>::display() const {
	for (int i = 0; i < amount; i++) getItemById(i)->val->print();
}

template <class T>
bool List<T>::deleteAll() {
	if (amount == 0) return false;
	else {
		int i = 0;
		while (i != amount) { delete getItemById(i); getItemById(i)->val = nullptr; amount--; }
		return true;
	}
}

template <class T>
bool List<T>::changeItem(int id, const T& val) {
	if (id < 0 || id > amount) return false;
	else {
		getItemById(id)->val = val;
		return true;
	}
}

