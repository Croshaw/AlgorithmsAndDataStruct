#include<ctime>
#pragma once
class WeatherReporter
{
private:
	int iterations = 0;
	int needIterations = 0;
	double time;
public:
	long getSumEven(int* array, int size) {
		clock_t start = clock();
		long sum = 0;
		needIterations = 0;
		for (int i = 0; i < size; i++)
		{
			if ((i + 1) % 2 == 0) {
				needIterations++;
				sum += array[i];
			}
		}
		iterations = size;
		time = (double(clock() - start)) / CLOCKS_PER_SEC;
		return sum;
	}
	long getSumEvenAnother(int* array, int size) {
		clock_t start = clock();
		long sum = 0;
		iterations = 0;
		needIterations = 0;
		int mid = size / 2;
		for (int i = 0; i < mid; i++)
		{
			if ((i + 1) % 2 == 0) {
				needIterations++;
				sum += array[i];
			}
			if ((mid+i+1) % 2 == 0) {
				needIterations++;
				sum += array[mid+i];
			}
			iterations++;
		}
		time = (double(clock() - start)) / CLOCKS_PER_SEC;
		return sum;
	}
	int getIterations() {
		return iterations;
	}
	int getNeedIterations() {
		return needIterations;
	}
	double getTime() {
		return time;
	}
};



