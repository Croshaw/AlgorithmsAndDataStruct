#include <SFML/Graphics.hpp>
#include "RBTree.h"
#include <thread>
#include <iostream>

using namespace sf;

#define windowW 1280
#define windowH 720

RBTree bst;
void drawArrow(sf::RenderWindow& window, sf::Vector2f end, sf::Vector2f naprav, sf::Color color)
{
	const double cos1 = 0.866;
	const double sin1 = 0.500;
	Vertex triangle[] = {
				Vertex(end, Color::Black),
				Vertex(Vector2f(end.x+(naprav.x*cos1+naprav.y*(-sin1)), end.y + (naprav.x*sin1+ naprav.y*cos1)), Color::Black),
				Vertex(Vector2f(end.x + (naprav.x * cos1 + naprav.y * sin1), end.y + (naprav.x * (-sin1) + naprav.y * cos1)), Color::Black)

	};
	window.draw(triangle, 3, Triangles);
}

void drawTree(sf::RenderWindow& window, Node* root, float x, float y, float xSpacing, float ySpacing, int size, Font font,int fontSize = 9, bool drawNull = false) {
	//std::string str = root->data == -842150451 ? "NL" : std::to_string(root->data);
	std::string str = root == nullptr ? "NL" : std::to_string(root->data);
	if (str == "NL" && !drawNull)
		return;
	bool isRed = root == nullptr ? false : root->isRed;
	CircleShape circle(size);
	circle.setOutlineThickness(1);
	circle.setOutlineColor(isRed ? Color(200,59,59) : Color::Black);
	circle.setPosition(x - size, y - size);
	circle.setFillColor(isRed ? Color(250, 170, 170) : Color(170, 170, 170));
	Text text(str, font, fontSize);
	text.setPosition(x - (text.getLocalBounds().width/2), y - text.getLocalBounds().height);
	text.setFillColor(isRed ? Color(200, 59, 59) : Color::Black);

	float nextLevelY = y + ySpacing;

	if (root != nullptr) {
		// Рисуем связи между узлами
		if (root->left != nullptr) {
			if (root->left->data == -842150451 && drawNull || root->left->data != -842150451) {
				Vertex line[] = {
					Vertex(Vector2f(x, y), Color::Black),
					Vertex(Vector2f(x - xSpacing, nextLevelY - size), Color::Black)
				};
				window.draw(line, 2, Lines);
				float dx = line[0].position.x - line[1].position.x;
				float dy = line[0].position.y - line[1].position.y;
				float len = sqrt(dx * dx + dy * dy);
				drawArrow(window, line[1].position, Vector2f(dx / len * size / 2, dy / len * size / 2), Color::Black);
			}
		}

		if (root->right != nullptr) {
			if (root->right->data == -842150451 && drawNull || root->right->data != -842150451) {
				Vertex line[] = {
					Vertex(Vector2f(x, y), Color::Black),
					Vertex(Vector2f(x + xSpacing, nextLevelY - size), Color::Black)
				};
				window.draw(line, 2, Lines);
				float dx = line[0].position.x - line[1].position.x;
				float dy = line[0].position.y - line[1].position.y;
				float len = sqrt(dx * dx + dy * dy);
				drawArrow(window, line[1].position, Vector2f(dx / len * size / 2, dy / len * size / 2), Color::Black);
			}
		}
	}
	window.draw(circle);
	window.draw(text);

	if (root == nullptr) {
		return;
	}

	// Рекурсивно рисуем левое и правое поддеревья
	drawTree(window, root->left, x - xSpacing, nextLevelY, xSpacing / 2, ySpacing, size, font, fontSize, drawNull);
	drawTree(window, root->right, x + xSpacing, nextLevelY, xSpacing / 2, ySpacing, size, font, fontSize, drawNull);

	
}

void windowRendering() {
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	RenderWindow window(VideoMode(windowW, windowH), "Test", Style::Default, settings);
	bst.setStartPosition(windowW / 2, 15);
	window.setFramerateLimit(60);
	Font font;
	font.loadFromFile("arial.ttf");
	bst.setFont(font);
	bool isClick = false;
	Vector2f lastPos(-1, -1);
	Clock doubleClickClock;
	bst.setSize(20);
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case Event::Closed:
				window.close();
				exit(0);
			case Event::MouseMoved:
				if (Mouse::isButtonPressed(Mouse::Middle))
				{
					if (lastPos.x != -1 && lastPos.y != -1)
						bst.mouseMove((event.mouseMove.x - lastPos.x), (event.mouseMove.y - lastPos.y));
					lastPos.x = event.mouseMove.x;
					lastPos.y = event.mouseMove.y;
				}
				else {
					lastPos.x = -1;
					lastPos.y = -1;
				}
			case Event::MouseButtonPressed:
				if (event.mouseButton.button == 2)
				{
					if (doubleClickClock.getElapsedTime().asMilliseconds() < 200)
						bst.setStartPosition(windowW / 2, 15);
					doubleClickClock.restart();
				}
			case Event::MouseWheelScrolled: {
				float d = event.mouseWheelScroll.delta;
				if ((int)d == d) {
					d *= Keyboard::isKeyPressed(Keyboard::LShift) ? 5 : 1;
					std::cout << d << std::endl;
					bst.mouseScroll(d);
				}
			}
			}
		}
		window.clear(Color::White);

		bst.drawTo(window);

		window.display();
	}
}

void consoleHandler() {
	setlocale(0, "rus");
	int i=-1;
	while (true) {
		system("cls");
		std::cout << "[1] - Добавить\n[2] - Удалить\n\n[0] - Завершить работу\n";
		if (std::cin >> i) {
			system("cls");
			if (i == 0) {
				exit(0);
			}
			else if (i == 1) {
				std::cout << "Введите число: ";
				if (std::cin >> i)
					bst.insert(i);
				else {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					bool validData = false;
					while (!validData) {
						std::cout << "Введите корректное число: ";
						if (std::cin >> i) {
							bst.insert(i);
							validData = true;
						}
						else {
							std::cin.clear();
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						}
					}
				}
			}
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
}

int main()
{
	std::thread windowThread(windowRendering);
	std::thread consoleThread(consoleHandler);

	windowThread.join();
	consoleThread.join();
}
