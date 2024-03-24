#include "AVLTree.h"
#include <algorithm>
#include <fstream>
#include <iostream>

AVLTree::AVLTree() {
    root = nullptr;
}

AVLTree::~AVLTree() {
    makeEmpty(root);
}

void AVLTree::insert(const EmployeeInfo& empl) {
    root = insert(empl, root);
}

void AVLTree::remove(int sin) {
    root = remove(sin, root);
}

void AVLTree::display() {
    std::ofstream outfile("inorder.txt");
    inorder(root, outfile);
    outfile.close();
}

Node* AVLTree::GetRoot() {
    return root;
}

Node* AVLTree::insert(const EmployeeInfo& empl, Node* t) {
    if (t == nullptr) {
        t = new Node;
        t->empl = empl;
        t->height = 0;
        t->left = t->right = nullptr;
    } else if (empl.sin < t->empl.sin) {
        t->left = insert(empl, t->left);
        if (height(t->left) - height(t->right) == 2) {
            if (empl.sin < t->left->empl.sin)
                t = singleRightRotate(t);
            else
                t = doubleRightRotate(t);
        }
    } else if (empl.sin > t->empl.sin) {
        t->right = insert(empl, t->right);
        if (height(t->right) - height(t->left) == 2) {
            if (empl.sin > t->right->empl.sin)
                t = singleLeftRotate(t);
            else
                t = doubleLeftRotate(t);
        }
    }

    t->height = std::max(height(t->left), height(t->right)) + 1;
    return t;
}

Node* AVLTree::singleRightRotate(Node*& t) {
    Node* u = t->left;
    t->left = u->right;
    u->right = t;
    t->height = std::max(height(t->left), height(t->right)) + 1;
    u->height = std::max(height(u->left), t->height) + 1;
    return u;
}

Node* AVLTree::singleLeftRotate(Node*& t) {
    Node* u = t->right;
    t->right = u->left;
    u->left = t;
    t->height = std::max(height(t->left), height(t->right)) + 1;
    u->height = std::max(height(t->right), t->height) + 1;
    return u;
}

Node* AVLTree::doubleLeftRotate(Node*& t) {
    t->right = singleRightRotate(t->right);
    return singleLeftRotate(t);
}

Node* AVLTree::doubleRightRotate(Node*& t) {
    t->left = singleLeftRotate(t->left);
    return singleRightRotate(t);
}

Node* AVLTree::remove(int sin, Node* t) {
   if (t == nullptr) {
        // Element not found
        return nullptr;
    }

    if (sin < t->empl.sin) {
        // Go to the left subtree
        t->left = remove(sin, t->left);
    } else if (sin > t->empl.sin) {
        // Go to the right subtree
        t->right = remove(sin, t->right);
    } else {
        // Element found
        if (t->left != nullptr && t->right != nullptr) {
            // Node with two children
            Node* temp = findMin(t->right);
            t->empl = temp->empl;
            t->right = remove(t->empl.sin, t->right);
        } else {
            // Node with one or no child
            Node* temp = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete temp;
        }
    }

    if (t == nullptr) {
        // No need to balance if the tree is empty
        return t;
    }

    // Update height of the current node
    t->height = std::max(height(t->left), height(t->right)) + 1;

    // Check for imbalance and perform rotations
    int balance = getBalance(t);

    // Left heavy
    if (balance > 1) {
        if (getBalance(t->left) >= 0) {
            return singleRightRotate(t);
        } else {
            return doubleRightRotate(t);
        }
    }

    // Right heavy
    if (balance < -1) {
        if (getBalance(t->right) <= 0) {
            return singleLeftRotate(t);
        } else {
            return doubleLeftRotate(t);
        }
    }

    return t;
}

Node* AVLTree::findMin(Node* t) {
    if (t == nullptr)
        return nullptr;
    else if (t->left == nullptr)
        return t;
    else
        return findMin(t->left);
}

Node* AVLTree::findMax(Node* t) {
    if (t == nullptr)
        return nullptr;
    else if (t->right == nullptr)
        return t;
    else
        return findMax(t->right);
}

int AVLTree::height(Node* t) {
    return (t == nullptr ? -1 : t->height);
}

int AVLTree::getBalance(Node* t) {
    if (t == nullptr)
        return 0;
    else
        return height(t->left) - height(t->right);
}

void AVLTree::makeEmpty(Node* t) {
    if (t == nullptr)
        return;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
}

void AVLTree::inorder(Node* t, std::ofstream& outfile) {
    if (t == nullptr)
        return;
    inorder(t->left, outfile);
    outfile << " height:" << t->height << " sin:" << t->empl.sin << " employee number:" << t->empl.emplNumber << " salary:" << t->empl.salary << " age:" << t->empl.age << std::endl;
    inorder(t->right, outfile);
}

Node* AVLTree::Find(Node* node, int sin) {
    if (node == nullptr) {
        return nullptr;
    }
    if (sin > node->empl.sin) {
        return Find(node->right, sin);
    } else if (sin < node->empl.sin) {
        return Find(node->left, sin);
    } else {
        return node;
    }
}
