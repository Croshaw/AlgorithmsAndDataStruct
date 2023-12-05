#pragma once
#include <utility>
struct Node {
	Node* parent;
	int key;
	Node* left;
	Node* right;
};
class BinTree
{
private:
	Node* root;
	void swap(Node* x1, Node* parent1, Node* x2, Node* parent2);
	void remove(Node* node, Node* parent);
	void printHelper(Node* node, int level);
	void freeHelper(Node* node);

	void preorderTraversalHelper(Node* node);
	void postorderTraversalHelper(Node* node);
	void inorderTraversalHelper(Node* node);
	void breadthFirstSearchHelper(Node* node);
	std::pair<Node*, Node*> findWithParent(int key);
public:
	~BinTree();
	void add(int key);
	void remove(int key);
	bool contains(int key);

	void preorderTraversal();
	void postorderTraversal();
	void inorderTraversal();
	void breadthFirstSearch();

	void print();
};