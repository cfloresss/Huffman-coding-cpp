// * Filename : Node.cpp

#include "Node.h"

 Node::Node(){
    left = nullptr;
    right = nullptr;
    c = '\0';
    count = 0;
    bits = "";
 }
 
 
 Node::Node(char c, int count){
     left = nullptr;
     right = nullptr;
     this->c = c;
     this->count = count;
     bits = "";
 }
 Node::Node(Node* left, Node* right, char c, int count){
     this->left = left;
     this->right = right;
     this->c = c;
     this->count = count;
     bits = "";
 }
 Node::~Node(){
     
 }
