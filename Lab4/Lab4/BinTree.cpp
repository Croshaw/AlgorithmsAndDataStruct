#include "BinTree.h"
#include <iostream>
#include <queue>

void BinTree::swap(Node* x1, Node* parent1, Node* x2, Node* parent2)
{
    if (x1 == root) {
        root = x2;
        if(x1->left != nullptr)
            x2->left = x1->left;
        if (x1->right != nullptr)
            x2->right = x1->right;
    }
    else if (x1 == parent1->left) {
        parent1->left = x2;
    }
    else {
        parent1->right = x2;
    }
}

void BinTree::remove(Node* node, Node* parent)
{
    Node* child = nullptr;
    if (node->left == nullptr) {
        child = node->right;
        swap(node, parent, node->right, node);
    }
    else if (node->right == nullptr) {
        child = node->left;
        swap(node, parent, node->left, node);
    }
    else {
        Node* next = node->right;
        Node* nextParent = node;
        while (next->left != nullptr) {
            nextParent = next;
            next = next->left;
        }
        child = next->right;
        if (nextParent != node) {
            swap(next, nextParent, next->right, next);
            next->right = node->right;
        }
        swap(node, parent, next, nextParent);
        next->left = node->left;
    }
    delete node;
}

void BinTree::printHelper(Node* node, int l)
{
    if (node != nullptr) {
        printHelper(node->right, l + 5);
        for (int i = 1; i <= l; i++)
            std::cout << " ";
        std::cout << node->key << std::endl;
        printHelper(node->left, l + 5);
    }
}

void BinTree::freeHelper(Node* node)
{
    if (node != nullptr) {
        freeHelper(node->left);
        freeHelper(node->right);
        delete node;
    }
}

void BinTree::preorderTraversalHelper(Node* node)
{
    if (node == nullptr)
        return;
    std::cout << node->key << " ";
    preorderTraversalHelper(node->left);
    preorderTraversalHelper(node->right);
}

void BinTree::postorderTraversalHelper(Node* node)
{
    if (node == nullptr)
        return;
    postorderTraversalHelper(node->left);
    postorderTraversalHelper(node->right);
    std::cout << node->key << " ";
}

void BinTree::inorderTraversalHelper(Node* node)
{
    if (node == nullptr)
        return;
    inorderTraversalHelper(node->left);
    std::cout << node->key << " ";
    inorderTraversalHelper(node->right);
}

void BinTree::breadthFirstSearchHelper(Node* node)
{
    if (node == NULL) return;

    std::queue<Node*> q;
    q.push(node);

    while (!q.empty()) {
        Node* current = q.front();
        std::cout << current->key << " ";
        if (current->left != NULL) q.push(current->left);
        if (current->right != NULL) q.push(current->right);
        q.pop();
    }
}

std::pair<Node*, Node*> BinTree::findWithParent(int key)
{
    Node* parent = root;
    Node* curNode = root;
    while (curNode != nullptr && curNode->key != key) {
        parent = curNode;
        curNode = key >= curNode->key ? curNode->right : curNode->left;
    }
    return std::make_pair(curNode, parent);
}

BinTree::~BinTree()
{
    freeHelper(root);
}

void BinTree::add(int key)
{
    Node* newNode = new Node();
    newNode->key = key;
    newNode->left = newNode->right = nullptr;
    if (root == nullptr) {
        root = newNode;
    }
    else {
        Node* curNode = root;
        Node* parentNode = nullptr;
        while (curNode) {
            parentNode = curNode;
            curNode = key >= curNode->key ? curNode->right : curNode->left;
        }
        if (key >= parentNode->key)
            parentNode->right = newNode;
        else 
            parentNode->left = newNode;
    }
}

void BinTree::remove(int key)
{
    auto pair = findWithParent(key);
    if (pair.first == nullptr)
        throw "Key don't exists!";
    remove(pair.first, pair.second);
}

bool BinTree::contains(int key)
{
    return findWithParent(key).first != nullptr;
}

void BinTree::preorderTraversal()
{
    preorderTraversalHelper(root);
    std::cout << std::endl;
}

void BinTree::postorderTraversal()
{
    postorderTraversalHelper(root);
    std::cout << std::endl;
}

void BinTree::inorderTraversal()
{
    inorderTraversalHelper(root);
    std::cout << std::endl;
}

void BinTree::breadthFirstSearch()
{
    breadthFirstSearchHelper(root);
    std::cout << std::endl;
}

void BinTree::print()
{
	return printHelper(root, 0);
}
