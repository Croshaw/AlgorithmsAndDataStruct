#include <iostream>
#include <vector>
#include <algorithm>

void convertToMirroredTime(int& h, int& m) {
	h = h < 0 && h > 11 ? -1 : h == 0 ? 0 : 12 - h;
	m = m < 0 && m > 59 ? -1 : m == 0 ? 0 : 60 - m;
}

void FirstTask() {
	int h = 12, m = 60;
	while (h > 11 || h < 0) {
		std::cout << "Введите часы(0-11): ";
		std::cin >> h;
	}
	while (m > 59 || m < 0) {
		std::cout << "Введите минуты(0-59): ";
		std::cin >> m;
	}
	convertToMirroredTime(h, m);
	std::cout << "Отзеркаленное время " << h << ":" << m << std::endl;
}

void printVector(std::vector<int> arr) {
	for (int i = 0; i < arr.size(); i++)
		std::cout << arr[i] << " ";
}

void findDivisors(int n, std::vector<int>& divisors, int d = 1) {
	if (d > sqrt(n)) {
		std::sort(divisors.begin(), divisors.end());
		return;
	}

	if (n % d == 0) {
		divisors.push_back(d);
		if(n/d != d)
			divisors.push_back(n/d);
	}
	
	findDivisors(n, divisors, d+1);
}

void SecondTask() {
	int n;
	std::cout << "Введите число: ";
	std::cin >> n;
	std::vector<int> divisors(0);
	findDivisors(n, divisors);
	printVector(divisors);
}

int main()
{
	setlocale(LC_ALL, "rus");
	FirstTask();
	SecondTask();
}