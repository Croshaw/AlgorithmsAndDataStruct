#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;



struct Node {
	float x;
	float y;
	int data;
	Node* parent;
	Node* left;
	Node* right;
	bool isRed;
	CircleShape shape;
	Vector2f getTopCenterPoint() {
		Vector2f v(shape.getPosition().x+shape.getRadius(), shape.getPosition().y);
		return v;
	}
	Vector2f getBottomCenterPoint() {
		Vector2f v(shape.getPosition().x + shape.getRadius(), shape.getPosition().y+shape.getRadius()*2);
		return v;
	}
	Vector2f getCenterPoint() {
		Vector2f v(shape.getPosition().x + shape.getRadius(), shape.getPosition().y + shape.getRadius());
		return v;
	}
};

class RBTree {
private:
	float xSpacing = 50;
	float ySpacing = 50;
	float rad=15;
	float characterSize=12;
	Font font;
	float x;
	float y;
	Node* root;
	void moveNode(Node* node, float xOffset, float yOffset) {
		if (node == nullptr)
			return;
		node->x += xOffset;
		node->y += yOffset;
		node->shape.setPosition(node->shape.getPosition().x + xOffset, node->shape.getPosition().y + yOffset);
		moveNode(node->left, xOffset, yOffset);
		moveNode(node->right, xOffset, yOffset);
	}
	int getCountRightNode(Node* node) {
		if (node == nullptr)
			return 0;
		int c = 0;
		Node* cur = node;
		while (cur != nullptr) {
			c++;
			cur = cur->right;
		}
		c--;
		return c + getCountRightNode(node->left);
	}
	int getCountLeftNode(Node* node) {
		if (node == nullptr)
			return 0;
		int c = 0;
		Node* cur = node;
		while (cur != nullptr) {
			c++;
			cur = cur->left;
		}
		c--;
		return c + getCountLeftNode(node->right);
	}
	Node* getGrandParent(Node* node) {
		return node->parent == nullptr ? nullptr : node->parent->parent;
	}
	Node* getUncle(Node* node) {
		Node* grandParent = getGrandParent(node);
		if (grandParent == nullptr)
			return nullptr;
		return grandParent->left == node->parent ? grandParent->right : grandParent->left;
	}
	void fixCoords(Node* x) {
		if (x == nullptr)
			return;
		if (x == root) {
			x->x = this->x;
			x->y = this->y;
		}
		if (x->left != nullptr) {
			x->left->x = x->x - xSpacing*(getCountRightNode(x->left)+1);
			x->left->y = x->y + ySpacing;
			fixCoords(x->left);
		}
		if (x->right != nullptr) {
			x->right->x = x->x + xSpacing *(getCountLeftNode(x->right)+ 1);
			x->right->y = x->y + ySpacing;
			fixCoords(x->right);
		}
	}
	void leftRotate(Node* x) {
		Node* y = x->right;
		y->x = x->x;
		y->y = x->y;
		x->right = y->left;
		if (y->left != nullptr) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			root = y;
		}
		else if (x == x->parent->left) {
			x->parent->left = y;
		}
		else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
		fixCoords(y);
	}
	void rightRotate(Node* x) {
		Node* y = x->left;
		y->x = x->x;
		y->y = x->y;
		x->left = y->right;
		if (y->right != nullptr) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			root = y;
		}
		else if (x == x->parent->right) {
			x->parent->right = y;
		}
		else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
		fixCoords(y);
	}
	void swapColors(Node* x) {
		if (x == nullptr)
			return;
		x->isRed = !x->isRed;
		if(x->left != nullptr)
			x->left->isRed = !x->left->isRed;
		if (x->right != nullptr)
			x->right->isRed = !x->right->isRed;
	}
	void balance(Node* node) {
		if (node->parent == nullptr) {
			node->isRed = false;
			return;
		}
		if (!node->parent->isRed)
			return;

		auto grandParent = getGrandParent(node);
		auto uncle = getUncle(node);
		if (uncle != nullptr && uncle->isRed) {
			swapColors(grandParent);
			balance(grandParent);
		}
		else {
			if (node->parent->right == node && grandParent->left == node->parent) {
				leftRotate(node->parent);
				node = node->left;
			}
			else if(node->parent->left == node && grandParent->right == node->parent) {
				rightRotate(node->parent);
				node = node->right;
			}
			node->parent->isRed = false;
			grandParent->isRed = true;
			if (node == node->parent->left) {
				rightRotate(node->parent->parent);
			}
			else {
				leftRotate(node->parent->parent);
			}
		}
	}
	void drawNode(RenderWindow& window, Node* node) {
		if (node == nullptr)
			return;
		node->shape.setFillColor(node->isRed ? Color(250, 170, 170) : Color(170, 170, 170));
		node->shape.setOutlineThickness(rad/15);
		node->shape.setOutlineColor(node->isRed ? Color(200, 59, 59) : Color::Black);
		Text t;
		t.setString(std::to_string(node->data));
		t.setFont(font);
		t.setCharacterSize(characterSize);
		t.setPosition(node->shape.getPosition().x + ((node->shape.getRadius()*2 - t.getLocalBounds().width )/ 2), node->shape.getPosition().y + (node->shape.getRadius() - t.getLocalBounds().height));
		t.setFillColor(node->isRed ? Color(200, 59, 59) : Color::Black);

		if (node->left != nullptr) {
			Vertex line[] = {
					Vertex(node->getCenterPoint(), Color::Black),
					Vertex(node->left->getCenterPoint(), Color::Black)
			};
			window.draw(line, 2, Lines);
		}
		if (node->right != nullptr) {
			Vertex line[] = {
					Vertex(node->getCenterPoint(), Color::Black),
					Vertex(node->right->getCenterPoint(), Color::Black)
			};
			window.draw(line, 2, Lines);
		}

		window.draw(node->shape);
		window.draw(t);

		if(node->x != node->shape.getPosition().x)
			node->shape.move(0.1*(node->x - node->shape.getPosition().x), 0);
		if (node->y != node->shape.getPosition().y)
			node->shape.move(0, 0.1 * (node->y - node->shape.getPosition().y));

		drawNode(window, node->left);
		drawNode(window, node->right);
	}
	void changeNodeSize(Node* node, float size) {
		if (node == nullptr)
			return;
		node->shape.setRadius(size);
		changeNodeSize(node->left, size);
		changeNodeSize(node->right, size);
	}
public: 
	RBTree()
	{
		root = nullptr;
	}
	void setFont(Font& font) {
		this->font = font;
	}
	Node* find(int data) {
		if (root == nullptr)
			return nullptr;
		Node* cur = root;
		Node* parrent = nullptr;
		while (cur != nullptr || cur->data != data) {
			parrent = cur;
			if (cur->data == data)
				return cur;
			cur = data >= cur->data ? cur->right : cur->left;
		}
		return nullptr;
	}
	void insert(int data) {
		Node* cur = root;
		Node* parent = nullptr;
		while (cur != nullptr) {
			parent = cur;
			cur = data >= cur->data ? cur = cur->right : cur = cur->left;
		}
		cur = new Node();
		cur->data = data;
		cur->isRed = true;
		cur->parent = parent;
		cur->shape.setRadius(rad);
		cur->shape.setPosition(1, 1);
		if (parent == nullptr) {
			root = cur;
			root->x = x;
			root->y = y;
		}
		else if (data >= parent->data) {
			parent->right = cur;
			parent->right->x = parent->x + xSpacing;
			parent->right->y = parent->y + ySpacing;
		}
		else {
			parent->left = cur;
			parent->left->x = parent->x - xSpacing;
			parent->left->y = parent->y + ySpacing;
		}
		sleep(sf::milliseconds(1000));
		balance(cur);
		fixCoords(root);
	}
	Node* getRoot() {
		return root;
	}
	void drawTo(RenderWindow& window) {
		drawNode(window, root);
	}
	void setStartPosition(float x, float y) {
		this->x = x;
		this->y = y;
		fixCoords(root);
	}
	void setSize(float size) {
		rad = size;
		ySpacing = xSpacing = size * (1 / 3 + 3);
		characterSize = 0.8 * size;
		changeNodeSize(root, size);
		fixCoords(root);
	}
	void mouseMove(float xOffset, float yOffset) {
		moveNode(root, xOffset, yOffset);
		x += xOffset;
		y += yOffset;
	}
	void mouseScroll(float offset) {
		if (rad + offset > 0)
			setSize(rad + offset / 2);
		else if (rad != 1)
			setSize(1);
	}
};