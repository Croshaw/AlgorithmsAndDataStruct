#pragma once
#include <SFML/Graphics.hpp>
#include"Control.h"

using namespace sf;
enum TextAligment
{
	Right, Center, Left
};

class Button {
private:
	Color color;
	float x, y;
	Text text;
	RectangleShape rectangle;
	TextAligment aligment;
public:
	Button()
	{
		x = y = 0;
	}
	void setAligment(TextAligment aligment) {
		this->aligment = aligment;
	}
	void setBorderColor(Color color) {
		rectangle.setOutlineColor(color);
	}
	void setBorderThickness(float thickness) {
		rectangle.setOutlineThickness(thickness);
	}
	bool inBounds(Vector2i vect) {
		return inBounds(vect.x, vect.y);
	}
	bool inBounds(float x, float y) {
		return x >= this->x && x <= this->x + rectangle.getSize().x && y >= this->y && y <= this->y + rectangle.getSize().y;
	}
	void setPosition(float x, float y) {
		this->x = x;
		this->y = y;
		rectangle.setPosition(x, y);
	}
	void setFont(Font& font) {
		text.setFont(font);
	}
	void setWidth(float width) {
		rectangle.setSize(Vector2f(width, rectangle.getSize().y));
	}
	void setHeight(float heigth) {
		rectangle.setSize(Vector2f(rectangle.getSize().x, heigth));
	}
	void setFontSize(int size) {
		text.setCharacterSize(size);
	}
	void setForecolor(Color color) {
		text.setFillColor(color);
	}
	void setBackgroundColor(Color color) {
		this->color = color;
		rectangle.setFillColor(color);
	}
	void setText(const String& str) {
		Text temp;
		temp.setFont(*text.getFont());
		temp.setCharacterSize(text.getCharacterSize());
		temp.setString(str);
		if (temp.getLocalBounds().width <= rectangle.getSize().x)
			this->text.setString(str);
	}
	String getText() {
		return text.getString();
	}
	void drawTo(RenderWindow& window) {
		float tX = aligment == TextAligment::Left ? x : aligment == TextAligment::Center ? x + ((rectangle.getSize().x - text.getLocalBounds().width) / 2) : x + (rectangle.getSize().x - text.getLocalBounds().width);
		float tY = y + ((rectangle.getSize().y - text.getCharacterSize()) / 2);
		text.setPosition(tX, tY);
		window.draw(rectangle);
		window.draw(text);
	}
};