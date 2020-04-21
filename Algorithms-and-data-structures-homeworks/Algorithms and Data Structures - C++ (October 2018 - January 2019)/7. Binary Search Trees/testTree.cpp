#include "binaryTree.h"


int main(/* int argc, char * argv[] */) {

     // if(argc < 2) {
     //      std::cerr << "Not enough arguments" << std::endl;
     //      exit(-1);
     // }

     int n;

     std::cin >> n;
     BinaryTree bt;
     int x;

     for(int i = 0; i < n; i++) {
          std::cin >> x;
          bt.insert(x);
     }

     bt.printInorder(bt.getRoot());
     //bt.treeIterative();

     std::cout << bt.sizeRecursive(bt.getRoot()) << " " << bt.depth(bt.getRoot()) << " " << bt.minimum(bt.getRoot()) << " " << bt.maximum(bt.getRoot()) << std::endl;

     for(int i = 1; i <= 10; i++) {
          if(bt.search(bt.getRoot(), i) == nullptr) std::cout << "No" << std::endl;
          else std::cout << "Yes" << std::endl;
     }

     return 0;
}