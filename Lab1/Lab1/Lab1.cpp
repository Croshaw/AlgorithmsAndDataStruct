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
	std::cout << "Кол-во итераций: " << reporter.getIterations() << "\tКол-во итераций присваивания: " << reporter.getNeedIterations() << std::endl;
	printf("Время выполнения: %.2f сек.\n\n", reporter.getTime());
	std::cout << "Общее кол-во осадков в чётные дни: " << reporter.getSumEvenAnother(helper.getArray(), helper.getSize()) << std::endl;
	std::cout << "Кол-во итераций: " << reporter.getIterations() << "\tКол-во итераций присваивания: " << reporter.getNeedIterations() << std::endl;
	printf("Время выполнения: %.2f сек.\n", reporter.getTime());
}
