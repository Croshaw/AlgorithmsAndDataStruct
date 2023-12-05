#include <iostream>
#include "BinTree.h"

BinTree tree;
bool clearScreen = true;

void traversalsInfo() {
	char ch;
	while (true) {
		if (clearScreen)
			system("cls");
		std::cout << "[1] - Префиксный обход\n[2] - Постфиксный обход\n[3] - Инфиксный обход\n[4] - Обход в ширину\n\n[0] - Назад\n";
		if (std::cin >> ch) {
			if (ch == '0')
				break;
			if (clearScreen)
				system("cls");
			switch (ch)
			{
			case('1'):
				tree.preorderTraversal();
				std::cout << "Введите любую клавишу, чтоб продолжить ";
				std::cin >> ch;
				break;
			case('2'):
				tree.postorderTraversal();
				std::cout << "Введите любую клавишу, чтоб продолжить ";
				std::cin >> ch;
				break;
			case('3'):
				tree.inorderTraversal();
				std::cout << "Введите любую клавишу, чтоб продолжить ";
				std::cin >> ch;
				break;
			case('4'):
				tree.breadthFirstSearch();
				std::cout << "Введите любую клавишу, чтоб продолжить ";
				std::cin >> ch;
				break;
			default:
				break;
			}
		}
	}
}

int main()
{
	setlocale(0, "rus");
	char ch;
	int key = 0;
	bool wrongInput = false;
	while (true) {
		if(clearScreen)
			system("cls");
		wrongInput = false;
		std::cout << "[1] - Добавить ноду\n[2] - Удалить ноду\n[3] - Проверить существует ли нода\n[4] - Обходы\n[5] - Вывести на экран\n\n[6] - Очищать экран(" << (clearScreen ? "True" : "False") << ")\n\n[0] - Завершить программу\n";
		if (std::cin >> ch) {
			if (ch == '0')
				break;
			if (clearScreen)
				system("cls");
			switch (ch) {
			case('1'):
				std::cout << "Введите ключ, который хотите добавить: ";
				if (std::cin >> key) {
					tree.add(key);
				}
				else {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					wrongInput = true;
					while (wrongInput) {
						if (std::cin >> key) {
							tree.add(key);
							wrongInput = false;
						}
						else {
							std::cin.clear();
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						}
					}
				}
				break;
			case('2'):
				std::cout << "Введите ключ, который хотите удалить: ";
				try {
					if (std::cin >> key) {
						tree.remove(key);
					}
					else {
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						wrongInput = true;
						while (wrongInput) {
							std::cout << "Введите ключ, который хотите удалить: ";
							if (std::cin >> key) {
								tree.remove(key);
								wrongInput = false;
							}
							else {
								std::cin.clear();
								std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							}
						}
					}
				}
				catch (...) {
					std::cout << "Такого ключа нет!\nВведите любую клавишу, чтоб продолжить ";
					std::cin >> ch;
				}
				break;
			case('3'):
				std::cout << "Введите ключ, который хотите проверить: ";
				if (std::cin >> key) {
					if(tree.contains(key))
						std::cout << "Нода с ключом равным " << key << " существует\n";
					else
						std::cout << "Такого ключа нет\n";
				}
				else {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					wrongInput = true;
					while (wrongInput) {
						std::cout << "Введите ключ, который хотите проверить: ";
						if (std::cin >> key) {
							if (tree.contains(key))
								std::cout << "Нода с ключом равным " << key << "существует\n";
							else
								std::cout << "Такого ключа нет\n";
							wrongInput = false;
						}
						else {
							std::cin.clear();
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						}
					}
				}
				std::cout << "Введите любую клавишу, чтоб продолжить ";
				std::cin >> ch;
				break;
			case('4'):
				traversalsInfo();
				break;
			case('5'):
				tree.print();
				std::cout << "\nВведите любую клавишу, чтоб продолжить ";
				std::cin >> ch;
				break;
			case('6'):
				clearScreen = !clearScreen;
				break;
			}
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
}