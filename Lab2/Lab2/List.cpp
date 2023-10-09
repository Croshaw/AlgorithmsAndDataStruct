#include "Element.cpp"
template <class T>
class List {
private:
	Element<T>* begin;
	Element<T>* end;
	int count;
public:
	List<T>()
	{
		begin = nullptr;
		count = 0;
	}
	List<T>(T _data) {
		begin = new Element<T>;
		begin->data = _data;
		begin->next = nullptr;
		end = begin;
		count = 1;
	}

	void removeAt(int index) {
		if (count == 0 || index < 0 || index >= count)
			return;
		if (index == 0) {
			Element<T>* t = begin;
			begin = begin->next;
			delete t;
		}
		else {
			Element<T>* t1 = get(index-1);
			Element<T>* t2 = t1->next;
			t1->next = t2->next;
			delete t2;
		}
		count--;
	}

	void add(T _data) {
		Element<T>* elem = new Element<T>;
		elem->data = _data;
		elem->next = nullptr;
		if (begin == nullptr) {
			begin = end = elem;
		}
		else {
			end->next = elem;
			end = elem;
		}
		count++;
	}

	Element<T>* get(int index) {
		if (count == 0 || index < 0 || index >= count)
			return nullptr;
		Element<T>* t = begin;
		for (int i = 0; i < index; i++)
			t = t->next;
		return t;
	}

	Element<T>* first() {
		return this->begin;
	}

	Element<T>* last() {
		return this->end;
	}

	int getCount() {
		return this->count;
	}
};