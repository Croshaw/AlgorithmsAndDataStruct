#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

// Define keys:
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

using namespace sf;

class Textbox {
private:
	float width;
	Text text;
	RectangleShape rectangle;
	float x, y;
	bool _isSelect;
	RectangleShape cursor;
	int curFrame;
	int frameBlink;
	int curCursorPosition;
	int limit;
	void inputLogic(int charTyped) {
		if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) {
			if ((limit == 0 || limit > getText().getSize()) && (charTyped >= 48 && charTyped <= 57) || charTyped == 46) {
				String str = getText();
				if (str.getSize() == 0) {
					setText(static_cast<char>(charTyped));
				} else
				if(str.getSize() != curCursorPosition)
					setText(str.substring(0, curCursorPosition) + static_cast<char>(charTyped) + str.substring(curCursorPosition, str.getSize() - curCursorPosition));
				else
					setText(getText() + static_cast<char>(charTyped));
				curCursorPosition++;
			}
		}
		else if (charTyped == DELETE_KEY) {
			String str = getText();
			int size = str.getSize();
			if (size > 0) {
				if (curCursorPosition == size) {
					setText(str.substring(0, size - 1));
					curCursorPosition--;
				}
				else if (curCursorPosition == 1) {
					setText(str.substring(curCursorPosition, str.getSize() - curCursorPosition));
					curCursorPosition--;
				}
				else if (curCursorPosition != 0) {
					setText(str.substring(0, curCursorPosition - 1) + str.substring(curCursorPosition, str.getSize() - curCursorPosition));
					curCursorPosition--;
				}
			}
		}
	}
public:
	Textbox()
	{
		x = 0;
		y = 0;
		_isSelect = false;
		frameBlink = 8;
		curFrame = 0;
		curCursorPosition = text.getString().getSize();
		limit = 0;
	}
	void setLimit(int limit) {
		this->limit = limit;
	}
	void deleteBack() {
		String str = getText();
		if(curCursorPosition != str.getSize())
			setText(str.substring(0, curCursorPosition) + str.substring(curCursorPosition+1, str.getSize() - curCursorPosition-1));
	}
	void moveCursor(bool forward) {
		if (forward) {
			if (curCursorPosition + 1 <= text.getString().getSize())
				curCursorPosition++;
		}
		else {
			if (curCursorPosition - 1 >= 0)
				curCursorPosition--;
		}
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
	void select() {
		_isSelect = true;
	}
	bool isSelect() {
		return _isSelect;
	}
	void disSelect() {
		_isSelect = false;
	}
	void setPosition(float x, float y) {
		this->x = x;
		this->y = y;
	}
	void setFont(Font& font) {
		text.setFont(font);
	}
	void setWidth(float width) {
		this->width = width;
	}
	void setFontSize(int size) {
		text.setCharacterSize(size);
	}
	void setForecolor(Color color) {
		text.setFillColor(color);
	}
	void setBackgroundColor(Color color) {
		rectangle.setFillColor(color);
		Color col((unsigned short)255 - color.r, (unsigned short)255 - color.g, (unsigned short)255 - color.b);
		cursor.setFillColor(col);
	}
	void drawTo(RenderWindow &window) {
		rectangle.setPosition(x, y);
		text.setPosition(x, y);
		rectangle.setSize(Vector2f(width, text.getCharacterSize() + text.getCharacterSize()/2));
		cursor.setSize(Vector2f(1, text.getCharacterSize() + text.getCharacterSize() / 4));
		float charWidth = text.getString().getSize() == 0 ? 0 : text.getLocalBounds().width / text.getString().getSize();
		cursor.setPosition(x + curCursorPosition * charWidth + 2, y + (rectangle.getSize().y - cursor.getSize().y) / 2);
		curFrame++;
		window.draw(rectangle);
		window.draw(text);
		if (curFrame < frameBlink) {
			if(isSelect())
				window.draw(cursor);
		}
		else {
			if (curFrame == frameBlink * 2)
				curFrame = 0;
		}
	}
	void setText(const String& str) {
		Text temp;
		temp.setFont(*text.getFont());
		temp.setCharacterSize(text.getCharacterSize());
		temp.setString(str);
		if (temp.getLocalBounds().width <= width) {
			this->text.setString(str);
			if(str == "")
				curCursorPosition = 0;
		}
	}
	String getText() {
		return text.getString();
	}
	void typedOn(Event input) {
		if (isSelect()) {
			int charTyped = input.text.unicode;
			if (charTyped < 128) {
				inputLogic(charTyped);
			}
		}
	}

	void keyPress(Event input) {
		int code = input.key.code;
		if (isSelect()) {
			if (code == 66)
				deleteBack();
			else if (code == 71)
				moveCursor(false);
			else if (code == 72)
				moveCursor(true);
		}
	}

	void mousePress(Event input) {
		Event::MouseButtonEvent ms = input.mouseButton;
		if (ms.button == 0) {
			if (inBounds(ms.x, ms.y))
				select();
			else
				disSelect();
		}
	}
};