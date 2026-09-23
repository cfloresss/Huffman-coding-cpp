// * Filename : Node.H

#include <string>

using namespace std;

#ifndef __NODE_H_
#define __NODE_H_

class Node {
public:
  Node();
  Node(char c, int count);
  Node(Node* left, Node* right, char c, int count);
  ~Node();
  Node* left;
  Node* right;
  char c;
  int count;
  string bits;
};

#endif /* NODE_H_ */


