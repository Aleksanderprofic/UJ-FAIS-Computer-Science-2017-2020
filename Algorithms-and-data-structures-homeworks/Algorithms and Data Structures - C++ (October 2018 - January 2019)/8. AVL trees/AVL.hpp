#pragma once
#include <iostream>

struct Node {
     std::string key;
     Node* left;
     Node* right;
     int height;

     Node(std::string key) {
          this->key = key;
          this->left = nullptr;
          this->right = nullptr;
          this->height = 1;
     }

     ~Node() {
          delete left;
          delete right;
     }
};

class AVL {
private:
     Node* root;
     int numberOfNodes;

     int getHeight(Node* node) {
          if(node == nullptr) return 0;
          return node->height;
     }

     int depth(Node *node) {
          if (node == nullptr)
               return 0;
          else {
               int leftHeight = depth(root->left);
               int rightHeight = depth(root->right);

               if (leftHeight > rightHeight) return leftHeight + 1;
               else return rightHeight + 1;
          }
     }

     Node *search(Node *node, std::string x) {
        if (node == nullptr)
            return nullptr;
        int compareValue = x.compare(node->key);
        if (compareValue == 0)
            return node;
        if (compareValue < 0)
            return search(node->left, x);
        else
            return search(node->right, x);
    }

    int getBalance(Node * node) {
        if(node != nullptr)
            return getHeight(node->left) - getHeight(node->right);
        return 0;
     }

    void printInOrder(Node* node) {
          if(node != nullptr) {
               printInOrder(node->left);
               std::cout << node->key << std::endl;
               printInOrder(node->right);
          }
     }

     Node* rightRotate(Node* node) {
          Node* nodeOnLeft = node->left;
          Node* temp = nodeOnLeft->right;

          nodeOnLeft->right = node;
          node->left = temp;

          node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
          nodeOnLeft->height = std::max(getHeight(nodeOnLeft->left), getHeight(nodeOnLeft->right)) + 1;

          return nodeOnLeft;
     }

     Node* leftRotate(Node* node) {
          Node* nodeOnRight = node->right;
          Node* temp = nodeOnRight->left;

          nodeOnRight->left = node;
          node->right = temp;

          node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
          nodeOnRight->height = std::max(getHeight(nodeOnRight->left), getHeight(nodeOnRight->right)) + 1;

          return nodeOnRight;
     }

     Node* insert(Node* node, std::string x) {
          if (node == nullptr) {
               node = new Node(x);
               numberOfNodes++;
               return node;
          }
          
          if (node->key.compare(x) <= 0) 
               node->right = insert(node->right, x);
          else node->left = insert(node->left, x);

          node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;

          int balance = getBalance(node);

          if(balance > 1) {
               if(x.compare(node->left->key) > 0) 
                    node->left = leftRotate(node->left);
               return rightRotate(node);
          }
          if(balance < -1) {
               if(x.compare(node->right->key) < 0)
                    node->right = rightRotate(node->right);
               return leftRotate(node);
          }
          return node;
     }
     
public:
     AVL(): root(nullptr), numberOfNodes(0) { }

     ~AVL() {
          delete root;
     }

     int depth() {
          return depth(this->root);
     }

     int size() {
          return numberOfNodes;
     }
     
     Node* search(std::string s) {
          return search(root, s);
     }

     void printInOrder() {
          printInOrder(root);
     }

     void insert(std::string x) {
          root = insert(root, x);
     }
};