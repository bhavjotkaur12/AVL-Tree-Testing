#include <fstream>
#ifndef AVL_TREE_H
#define AVL_TREE_H

struct EmployeeInfo {
    int salary;
    int age;
    int emplNumber;
    int sin; // search by social insurance number
};

struct Node {
    EmployeeInfo empl;
    Node* left;
    Node* right;
    int height;
};

class AVLTree {
public:
    AVLTree();
    ~AVLTree();

    void insert(const EmployeeInfo& empl);
    void remove(int sin);
    void display();
    Node* GetRoot();
    Node* Find(Node* node, int sin);


private:
    Node* root;

    Node* insert(const EmployeeInfo& empl, Node* t);
    Node* remove(int sin, Node* t);
    Node* findMin(Node* t);
    Node* findMax(Node* t);
    Node* singleRightRotate(Node*& t);
    Node* singleLeftRotate(Node*& t);
    Node* doubleLeftRotate(Node*& t);
    Node* doubleRightRotate(Node*& t);
    int height(Node* t);
    int getBalance(Node* t);
    void makeEmpty(Node* t);
    void inorder(Node* t, std::ofstream& outfile);
};

#endif // AVL_TREE_H
