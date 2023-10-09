#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include "List.cpp"
#include "Cars.cpp"

List<Cars> cars;

List<std::string> getDataInBraces(std::string raw) {
	List<std::string> results;
	std::string tempResult = "";
	int countBraces = 0;
	for (int i = 0; i < raw.size(); i++) {
		if (raw[i] == '{')
			countBraces++;
		else if (raw[i] == '}' && countBraces > 0) {
			countBraces--;
			if (countBraces == 0) {
				results.add(tempResult);
				tempResult = "";
			}
		}
		if (countBraces > 0 && raw[i] != ' ' && raw[i] != '\t')
			if (!(countBraces == 1 && raw[i] == '{'))
				tempResult += raw[i];
	}
	return results;
}

List<std::string> split(std::string raw, char sep) {
	List<std::string> results;
	std::string tempRes = "";
	for (int i = 0; i < raw.size(); i++) {
		if (raw[i] == sep && tempRes != "") {
			results.add(tempRes);
			tempRes = "";
		}
		else {
			tempRes += raw[i];
		}
	}
	results.add(tempRes);
	return results;
}

List<Cars> loadFromFile(std::string fileName) {
	List<Cars> cars;
	std::ifstream in(fileName);
	std::string data;
	std::string line;
	if (in.is_open()) {
		while (std::getline(in, line)) {
			data += line;
		}
	}
	if (data != "") {
		auto lCars = getDataInBraces(getDataInBraces(data).first()->data);
		for (int i = 0; i < lCars.getCount(); i++) {
			auto lCar = split(lCars.get(i)->data, ',');
			if (lCar.getCount() != 0) {
				Cars car{ lCar.get(0)->data, stoi(lCar.get(1)->data), stoi(lCar.get(2)->data) };
				cars.add(car);
			}
		}
	}

	return cars;
}

void saveToFile(std::string fileName) {
	std::string writeInfo = "Cars\n{";
	for (int i = 0; i < cars.getCount(); i++) {
		Cars _c = cars.get(i)->data;
		writeInfo += "\n\t{\n\t\t";
		writeInfo += _c.name + ", " + std::to_string(_c.countCars) + ", " + std::to_string(_c.countTest);
		writeInfo += "\n\t}";
		if (i != cars.getCount() - 1)
			writeInfo += ",";
	}
	writeInfo += "\n}";
	std::ofstream out;
	out.open(fileName, std::ios::out);
	if (out.is_open()) {
		out << writeInfo;
	}
	out.close();
}

void carsToConsole() {
	system("cls");
	std::cout << "ID" << std::setw(20) << "Название" << std::setw(20) << "Общее кол - во" << std::setw(20) << "Тест - драйв" << std::endl << std::endl;
	for (int i = 0; i < cars.getCount(); i++) {
		Cars ca = cars.get(i)->data;
		std::cout << (i+1) << "." << std::setw(20) << ca.name << std::setw(20) << ca.countCars << std::setw(20) << ca.countTest << std::endl;
	}
	std::cout << "\n0 - Вернуться назад\n";
	char ch;
	scanf(" %c", &ch);
	if (ch != '0')
		carsToConsole();
}

int getNumberFromConsole(std::string msg = "", bool clear=false) {
	if(clear) 
		system("cls");
	if (msg != "") {
		std::cout << msg;
	}
	int num;
	scanf(" %i", &num);
	return num;
}

int getRightId() {
	int id = getNumberFromConsole("Введите id: ", true);
	id--;
	if (id < 0 || id >= cars.getCount())
		return getRightId();
	return id;
}

void changeCars() {
	int id = getRightId();
	Element<Cars>* ca = cars.get(id);
	std::cout << ca->data.name << " " << ca->data.countCars << " " << ca->data.countTest << std::endl;
	int ch = getNumberFromConsole("Что хотите изменить?\n1 - Название\n2 - Количество\n3 - Тест драйв\n");
	switch (ch)
	{
	case(1):
		std::cout << "Введите новое название: ";
		scanf("%s", &ca->data.name[0]);
		break;
	case(2):
		std::cout << "Введите кол-во: ";
		scanf("%d", &ca->data.countCars);
		break;
	case(3):
		std::cout << "Введите кол-во: ";
		scanf("%d", &ca->data.countTest);
		break;
	default:
		break;
	}
}

void requestCars() {
	std::cout << "Введите через пробел название марки и кол-во автомобилей: ";
	char name[100];
	int count = 0;
	scanf("%s %d", name, &count);
	for (int i = 0; i < cars.getCount(); i++) {
		Element<Cars>* d = cars.get(i);
		if (d->data.name == name) {
			d->data.countCars += count;
			return;
		}
	}
	cars.add(Cars{ name, count, 0 });
}

void testDriveAdder() {
	Element<Cars>* d = cars.get(getRightId());
	int num = getNumberFromConsole("Сколько тест-драйвов(!> " + std::to_string(d->data.countCars-d->data.countTest) + "): ");
	while (num + d->data.countTest > d->data.countCars) {
		num = getNumberFromConsole("Сколько тест-драйвов(!> " + std::to_string(d->data.countCars - d->data.countTest) + "): ");
	}
	d->data.countTest += num;
}

int main()
{
	setlocale(LC_ALL, "rus");
	cars = loadFromFile("data.txt");
	while (true) {
		int ch = getNumberFromConsole("1 - Вывести список автомобилей\n2 - Изменить автомобили\n3 - Запись на тест-драйв\n4 - Оставить заявку\n5 - Удалить\n0 - Выход из программы\n", true);
		if (ch == 0)
			break;
		switch (ch)
		{
		case(1):
			carsToConsole();
			break;
		case(2):
			changeCars();
			break;
		case(3):
			testDriveAdder();
			break;
		case(4):
			requestCars();
			break;
		case(5):
			cars.removeAt(getRightId());
			break;
		default:
			break;
		}
	}
	saveToFile("data.txt");
}