#include <chrono>
#pragma once
class WeatherReporter
{
private:
	long duration;
public:
	long getSumEven(int* array, int size) {
		auto start = std::chrono::high_resolution_clock::now();
		long sum = 0;
		for (int i = 0; i < size; i++)
			if ((i + 1) % 2 == 0)
				sum += array[i];
		auto stop = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
		return sum;
	}
	long getSumEvenAnother(int* array, int size) {
		auto start = std::chrono::high_resolution_clock::now();
		long sum = 0;
		int mid = size / 2;
		for (int i = 0; i < mid; i++)
		{
			if ((i + 1) % 2 == 0) {
				sum += array[i];
			}
			if ((mid+i+1) % 2 == 0) {
				sum += array[mid+i];
			}
		}
		auto stop = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
		return sum;
	}
	long getExecuteTime() {
		return duration;
	}
};



