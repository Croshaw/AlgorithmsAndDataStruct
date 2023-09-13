#pragma once
#include <stdlib.h>
#include <iostream>
class ArrayHelper
{
private:
	int size;
	int minNumber;
	int maxNumber;
	int* array;
	bool isFill;
	void fillArray() {
		srand(0);
		if (size <= 0)
			return;
		for (int i = 0; i < size; i++)
			array[i] = rand() % (maxNumber - minNumber) + minNumber;
		isFill = true;
	}
public:
	ArrayHelper(int size, int minNumber, int maxNumber)
	{
		this->size = size;
		this->maxNumber = maxNumber;
		this->minNumber = minNumber;
		this->array = new int[size];
		fillArray();
	}

	int* getArray() {
		if (!isFill)
			fillArray();
		return array;
	}
	void printArray() {
		int* arr = getArray();
		std::cout << "Array[" << size << "] { ";
		for (int i = 0; i < size; i++)
			std::cout << arr[i] << (i == size - 1 ? "" : ", ");
		std::cout << " }" << std::endl;
	}
	int getSize() {
		return size;
	}
};

