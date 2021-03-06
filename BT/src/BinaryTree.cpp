#include <cstddef>
#include "BinaryTree.h"
#include <vector>
#include <iostream>

using namespace std;

BinaryTree::BinaryTree() {
    _root = NULL;
}

BinaryTree::~BinaryTree() {}

void BinaryTree::insert(int value) {
    _root = _rinsert(_root, value);
}

bool BinaryTree::contains(int value) {
    return _rcontains(_root, value);
}

void BinaryTree::remove(int value) {
    _root = _rremove(_root, value);
}

vector<int> BinaryTree::inorder(){
    vector<int> v;
    _rinorder(_root, v);
    return v;
}

void BinaryTree::remove_minimum() {
    if(_root == NULL) { return; }
    _root = _rremovemin(_root);
}

Node* BinaryTree::_rinsert( Node* current, int value) {

    if (current == NULL) {
        return new Node(value);
    }
    if (value < current->data) {
        current->left = _rinsert(current->left, value);
    } else if (value > current->data) {
        current->right = _rinsert(current->right, value);
    } else {
        current->data = value;
    }
    return current;
}

Node* BinaryTree::_rminimum(Node* current){
    assert(current != NULL);

    if (current->left == NULL) {
        return current;
    }
    return _rminimum(current->left);
}

Node* BinaryTree::_rremovemin(Node* current) {
    if (current->left == NULL) {
        Node* temp = current;
        current = temp->right;
        delete temp;
        return current;
    }

    current->left = _rremovemin(current->left);
    return current;
}

Node* BinaryTree::_rremove(Node* current, int value) {
    if (current == NULL) { return NULL; }

    if (value < current->data) {
        current->left = _rremove(current->left, value);
    } else if (value > current->data) {
        current->right = _rremove(current->right, value);
    } else {
        // we've found the node which contains the value
        // that we want to delete

        // if this node has at most one child
        // return that child to parent after deleting the node
        if (current->left == NULL) {
            Node* temp = current->right;
            delete current;
            return temp;
        }

        if (current->right == NULL) {
            Node* temp = current->left;
            delete current;
            return temp;
        }

        // HIBBARD DELETION
        // replace the value of the node
        // whose value we want to delete
        // with the minimum value of its right subtree
        // after this, delete the node which contains
        // the minimum value on the said right subtree
        int data = _rminimum(current->right)->data;
        current->right = _rremovemin(current->right);
        current->data = data;
    }
    return current;
}

void BinaryTree::_rinorder(Node* current, vector<int>& v){
    if (current == NULL) { return; }

    _rinorder(current->left, v);
    v.push_back(current->data);
    _rinorder(current->right, v);
}

bool BinaryTree::_rcontains(Node* current, int value){
    if (current == NULL) { return false; }

    if (value < current->data) {
        return _rcontains(current->left, value);
    } else if (value > current->data) {
        return _rcontains(current->right, value);
    } else {
        return true;
    }
}
