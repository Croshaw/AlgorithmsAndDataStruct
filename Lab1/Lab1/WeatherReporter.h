#include<ctime>
#pragma once
class WeatherReporter
{
private:
	int iterations = 0;
	int needIterations = 0;
	double time;
public:
	int getSumEven(int* array, int size) {
		int sum = 0;
		needIterations = 0;
		clock_t startTime = clock();
		for (int i = 0; i < size; i++)
		{
			if ((i + 1) % 2 == 0) {
				needIterations++;
				sum += array[i];
			}
		}
		iterations = size;
		time = (double(clock()-startTime))/CLOCKS_PER_SEC;
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



