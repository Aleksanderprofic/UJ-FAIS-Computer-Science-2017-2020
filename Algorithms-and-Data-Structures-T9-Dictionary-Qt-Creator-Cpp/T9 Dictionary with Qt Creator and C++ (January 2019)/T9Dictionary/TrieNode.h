#pragma once
#include <iostream>
#include <forward_list>
#include <QTextStream>

struct TrieNode {
     TrieNode* nodes[8];
     std::vector<QString> vector;

     TrieNode() {
          for(int i = 0; i < 8; i++)
            nodes[i] = nullptr;
     }

     bool addWord(QString s) {
          if(std::find(vector.begin(), vector.end(), s) != vector.end()) {
               return false;
          }
          vector.push_back(s);

          return true;
     }
};
