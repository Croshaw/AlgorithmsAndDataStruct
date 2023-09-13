#include <iostream>
#include "WeatherReporter.h"
#include "ArrayHelper.h"

using namespace std;

const int maxNumber = 150;
const int minNumber = 10;

int main()
{
	setlocale(LC_ALL, "rus");
	srand(0);
	cout << "Enter days count: ";
	int n;
	cin >> n;
	ArrayHelper helper(n, minNumber, maxNumber);
	helper.printArray();
	WeatherReporter reporter;
	cout << "Общее кол-во осадков в чётные дни: " << reporter.getSumEven(helper.getArray(), helper.getSize()) << endl;
	cout << "Кол-во итераций: " << reporter.getIterations() << "\tКол-во итераций присваивания: " << reporter.getNeedIterations() << endl;
	printf("Время выполнения: %.2f сек.\n", reporter.getTime());
}
