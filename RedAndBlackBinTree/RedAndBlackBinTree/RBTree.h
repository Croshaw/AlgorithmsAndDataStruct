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
	bool isRightPlace() {
		return abs(x - shape.getPosition().x) < 1 && abs(y - shape.getPosition().y) < 1;
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
	bool drawNullLeaves;
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
			x->left->x = x->x - xSpacing*(getCountRightNode(x->left) + 1 + (drawNullLeaves ? 1 : 0));
			x->left->y = x->y + ySpacing;
			fixCoords(x->left);
		}
		if (x->right != nullptr) {
			x->right->x = x->x + xSpacing *(getCountLeftNode(x->right) + 1 + (drawNullLeaves ? 1 : 0));
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
		try {
			node->shape.setFillColor(node->isRed ? Color(250, 170, 170) : Color(170, 170, 170));
			node->shape.setOutlineThickness(rad / 15);
			node->shape.setOutlineColor(node->isRed ? Color(200, 59, 59) : Color::Black);
			Text t;
			t.setString(std::to_string(node->data));
			t.setFont(font);
			t.setCharacterSize(characterSize);
			t.setPosition(node->shape.getPosition().x + ((node->shape.getRadius() * 2 - t.getLocalBounds().width) / 2), node->shape.getPosition().y + (node->shape.getRadius() - t.getLocalBounds().height));
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



			if (node->x != node->shape.getPosition().x)
				node->shape.move(0.1 * (node->x - node->shape.getPosition().x), 0);
			if (node->y != node->shape.getPosition().y)
				node->shape.move(0, 0.1 * (node->y - node->shape.getPosition().y));

			if (drawNullLeaves && node->left == nullptr) {
				CircleShape shape(rad);
				shape.setPosition(node->shape.getPosition().x - xSpacing, node->shape.getPosition().y + ySpacing);
				shape.setFillColor(Color(170, 170, 170));
				shape.setOutlineThickness(rad / 15);
				shape.setOutlineColor(Color::Black);
				Text tl;
				tl.setString("NULL");
				tl.setFont(font);
				tl.setCharacterSize(characterSize * 0.7);
				tl.setPosition(shape.getPosition().x + ((shape.getRadius() * 2 - tl.getLocalBounds().width) / 2), shape.getPosition().y + (shape.getRadius() - tl.getLocalBounds().height));
				tl.setFillColor(Color::Black);
				Vertex line[] = {
						Vertex(node->getCenterPoint(), Color::Black),
						Vertex(Vector2f(shape.getPosition().x + shape.getRadius(), shape.getPosition().y + shape.getRadius()), Color::Black)
				};
				window.draw(line, 2, Lines);
				window.draw(shape);
				window.draw(tl);
			}
			if (drawNullLeaves && node->right == nullptr) {
				CircleShape shape(rad);
				shape.setPosition(node->shape.getPosition().x + xSpacing, node->shape.getPosition().y + ySpacing);
				shape.setFillColor(Color(170, 170, 170));
				shape.setOutlineThickness(rad / 15);
				shape.setOutlineColor(Color::Black);
				Text tl;
				tl.setString("NULL");
				tl.setFont(font);
				tl.setCharacterSize(characterSize * 0.7);
				tl.setPosition(shape.getPosition().x + ((shape.getRadius() * 2 - tl.getLocalBounds().width) / 2), shape.getPosition().y + (shape.getRadius() - tl.getLocalBounds().height));
				tl.setFillColor(Color::Black);
				Vertex line[] = {
						Vertex(node->getCenterPoint(), Color::Black),
						Vertex(Vector2f(shape.getPosition().x + shape.getRadius(), shape.getPosition().y + shape.getRadius()), Color::Black)
				};
				window.draw(line, 2, Lines);
				window.draw(shape);
				window.draw(tl);
				
			}
			window.draw(node->shape);
			window.draw(t);
			drawNode(window, node->left);
			drawNode(window, node->right);
		}
		catch (...) {

		}
	}
	void changeNodeSize(Node* node, float size) {
		if (node == nullptr)
			return;
		node->shape.setRadius(size);
		changeNodeSize(node->left, size);
		changeNodeSize(node->right, size);
	}
	Node* getMinimal(Node* node) {
		Node* cur = node;
		while (cur->left != nullptr)
			cur = cur->left;
		return cur;
	}
	void swapNodes(Node* x1, Node* x2) {
		if (x1->parent == nullptr) {
			root = x2;
		}
		else if (x1 == x1->parent->left) {
			x1->parent->left = x2;
		}
		else {
			x1->parent->right = x2;
		}
		if(x2 != nullptr)
			x2->parent = x1->parent;
	}
	void removeBalancer(Node* node) {
		if (node == nullptr)
			return;
		Node* s;
		while (node != root && !node->isRed) {
			if (node == node->parent->left) {
				s = node->parent->right;
				if (s->isRed) {
					s->isRed = false;
					node->parent->isRed = true;
					leftRotate(node->parent);
					s = node->parent->right;
				}
				if (!s->left->isRed && !s->right->isRed) {
					s->isRed = true;
					node = node->parent;
				}
				else {
					if (!s->right->isRed) {
						s->left->isRed = false;
						s->isRed = true;
						rightRotate(s);
						s = node->parent->right;
					}
					s->isRed = node->parent->isRed;
					node->parent->isRed = false;
					s->right->isRed = false;
					leftRotate(node->parent);
					node = root;
				}
			}
			else {
				s = node->parent->left;
				if (s->isRed) {
					s->isRed = false;
					node->parent->isRed = true;
					rightRotate(node->parent);
					s = node->parent->left;
				}

				if (!s->right->isRed && !s->right->isRed) {
					s->isRed = true;
					node = node->parent;
				}
				else {
					if (!s->left->isRed) {
						s->right->isRed = false;
						s->isRed = true;
						leftRotate(s);
						s = node->parent->left;
					}

					s->isRed = node->parent->isRed;
					node->parent->isRed = false;
					s->left->isRed = false;
					rightRotate(node->parent);
					node = root;
				}
			}
		}
		node->isRed = false;
	}
	void removeHelper(Node* node) {
		bool isRed = node->isRed;
		Node* child = nullptr;
		Node* min = nullptr;
		if (node->left == nullptr) {
			child = node->right;
			swapNodes(node, node->right);
		}
		else if (node->right == nullptr) {
			child = node->left;
			swapNodes(node, node->left);
		}
		else {
			min = getMinimal(node->right);
			isRed = min->isRed;
			child = min->right;
			if (min->parent == node) {
				if(child != nullptr)
					child->parent = min;
			}
			else {
				swapNodes(min, min->right);
				min->right = node->right;
				min->right->parent = min;
			}
			swapNodes(node, min);
			min->left = node->left;
			min->left->parent = min;
			min->isRed = node->isRed;
		}
		delete node;
		if (!isRed) {
			removeBalancer(child);
		}
	}
public: 
	Node* curWaitNode;
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
		while (cur != nullptr) {
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
		curWaitNode = cur;
	}
	void remove(int data) {
		Node* remNode = find(data);
		if (remNode == nullptr)
			throw ("Node with data = " + std::to_string(data) + " not found");
		removeHelper(remNode);
		fixCoords(root);
	}
	void drawTo(RenderWindow& window) {
		drawNode(window, root);
	}
	void setStartPosition(float x, float y) {
		this->x = x;
		this->y = y;
		fixCoords(root);
	}
	void setDrawNullLeaves(bool value) {
		drawNullLeaves = value;
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