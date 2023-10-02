#include <iostream>
#include "WeatherReporter.h"
#include "ArrayHelper.h"

const int maxNumber = 15;
const int minNumber = 1;

int main()
{
	setlocale(LC_ALL, "rus");
	std::cout << "Enter days count: ";
	int n;
	std::cin >> n;
	ArrayHelper helper(n, minNumber, maxNumber);
	//helper.printArray();
	WeatherReporter reporter;
	std::cout << "Общее кол-во осадков в чётные дни: " << reporter.getSumEven(helper.getArray(), helper.getSize()) << std::endl;
	printf("Время выполнения: %i мкс.\n\n", reporter.getExecuteTime());
	std::cout << "Общее кол-во осадков в чётные дни: " << reporter.getSumEvenAnother(helper.getArray(), helper.getSize()) << std::endl;
	printf("Время выполнения: %i мкс.\n", reporter.getExecuteTime());
}
