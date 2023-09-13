#pragma once
#include <stdlib.h>
#include <iostream>
using namespace std;
class ArrayHelper
{
private:
	int size;
	int minNumber;
	int maxNumber;
	int* array;
	bool isFill;
	void fillArray() {
		if (size <= 0)
			return;
		for (int i = 0; i < size; i++)
			array[i] = rand() % (maxNumber - minNumber) + minNumber;
	}
public:
	ArrayHelper(int size, int minNumber, int maxNumber)
	{
		this->size = size;
		this->maxNumber = maxNumber;
		this->minNumber = minNumber;
		this->array = new int[size];
		isFill = false;
	}

	int* getArray() {
		if (!isFill)
			fillArray();
		return array;
	}
	void printArray() {
		int* arr = getArray();
		cout << "Array[" << size << "] { ";
		for (int i = 0; i < size; i++)
			cout << arr[i] << (i == size - 1 ? "" : ", ");
		cout << " }" << endl;
	}
	int getSize() {
		return size;
	}
};

