#pragma once

#include <iostream>

class BinaryTree {
     public: 
     struct node {
          int key;
          node* left;
          node* right;
     };

     private:
     node* root;
     int numberOfNodes;

     int max(int a, int b);

     public:
     BinaryTree();
     ~BinaryTree();
     void insert(int);                  // wstawia element ‘x’ do drzewa
     node* search(node*, int);
     node* searchRecursive(node*, int); // sprawdza czy element należy do drzewa, zwraca wskaźnik do węzła lub nullptr. 
     int size();                        // zwraca liczbę węzłów
     int sizeRecursive(node *n);
     int minimum(node*);                // zwraca wartość najmniejszego elementu
     int maximum(node*);                // zwraca wartość największego elementu
     int depth(node*);                       // zwraca wysokość drzewa
     void printInorder(node*);          // wypisuje zawartość wszystkich węzłów odpowiednio w porządku: inorder
     void printPreorder(node*);         // preorder
     void printPostorder(node*);        // postorder
     void treeIterative();
     node* getRoot();
};

     BinaryTree::BinaryTree() {
          root = nullptr;
          numberOfNodes = 0;
     }

     BinaryTree::~BinaryTree() {
          
     }

     int BinaryTree::max(int a, int b) {
          return (a>b ? a : b);
     }

     // usuniecie wszystkich wezlow w destruktorze

     void BinaryTree::insert(int x) {
          if (root == nullptr) {
               root = new node;
               root->key = x;
               root->right = nullptr;
               root->left = nullptr;
               numberOfNodes++;
          } else {
               node* temp, *actualNode = root;
               while(actualNode != nullptr) {
                    temp = actualNode;
                    if (actualNode->key > x ) 
                         actualNode = actualNode->left;
                    else if (actualNode->key <= x) 
                         actualNode = actualNode->right;
               }
               actualNode = new node;
               actualNode->left = nullptr;
               actualNode->right = nullptr;
               actualNode->key = x;
               numberOfNodes++;

               if(temp->key > x) temp->left = actualNode;
               else temp->right = actualNode;
          }
     }           

     BinaryTree::node* BinaryTree::search(node* n, int x) {
          while(n != nullptr) {

               if (n->key > x) n = n->left;
               else if (n->key < x) n = n->right;
               else {
                    //std::cout << "Znalazlem: " << n->key << std::endl;
                    return n;
               }
          }
          return nullptr;
     }

     BinaryTree::node* BinaryTree::searchRecursive(node* n, int x) {
          if(n == nullptr) return nullptr;
          if(n->key == x) {
               //std::cout << "Znalazlem: " << n->key << std::endl;
               return n;
          }
          
          if(n->key > x) searchRecursive(n->left, x);
          else searchRecursive(n->right, x);
     }

     int BinaryTree::size() {
          return numberOfNodes;
     }

     int BinaryTree::sizeRecursive(node* n) {
          if(n == nullptr) return 0;
          else return 1 + sizeRecursive(n->left) + sizeRecursive(n->right);
     }

     int BinaryTree::minimum(node* n) {
          while(n->left != nullptr) {
               n = n->left;
          }
          return n->key;
     }

     int BinaryTree::maximum(node* n) {
          while(n->right != nullptr) {
               n = n->right;
          }
          return n->key;
     }

     int BinaryTree::depth(node* n) {
          if(n == nullptr) return 0;

          int length_left = depth(n->left);
          int length_right = depth(n->right);

          return 1 + max(length_left, length_right);
     }

     void BinaryTree::printInorder(node* n) {
          if(n->left != nullptr) printInorder(n->left);
          std::cout << n->key << std::endl;
          if(n->right != nullptr) printInorder(n->right);
     }

     void BinaryTree::printPreorder(node* n) {
          std::cout << n->key << std::endl;
          if(n->left != nullptr) printPreorder(n->left);
          if(n->right != nullptr) printPreorder(n->right);
     }

     void BinaryTree::printPostorder(node* n) {
          if(n->left != nullptr) printPostorder(n->left);
          if(n->right != nullptr) printPostorder(n->right);
          std::cout << n->key << std::endl;
     }

     void BinaryTree::treeIterative() {
          node* stack[size()];
          node* temp = root;
          int top = 0;

          while(temp != nullptr || top > 0) {
               while(temp != nullptr) {
                    stack[top++] = temp;
                    temp = temp->left;
               }
               temp = stack[--top];
               std::cout << temp->key << std::endl;

               temp = temp->right;
          }
     }

     BinaryTree::node* BinaryTree::getRoot() {
          return root;
     }