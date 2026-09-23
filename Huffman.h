// Filename : Huffman.H

#ifndef HUFFMAN_H_
#define HUFFMAN_H_

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <list>
#include <stack>
#include <queue>
#include <string>
#include <map>
#include "heap/pq_zero.H"
#include "Node.h"

using namespace std;

class Huffman {
public:
  Huffman();
  Huffman(const string& inputFile);
  ~Huffman();
  void PrintCharFrequencies(); // prints char=>char_frequency
  void BuildPQ(); // adds Node pointers to priority queue with frequency counts
  void BuildHuffmanTree(); // combines lowest count nodes into Huffman Tree 
  void SetBitsPerChar(); // calls private function
  void DisplayPrefixTree(); // optional, calls private function
  void SetBitCodes();  // preorder traversal, calls private function
  void Stats(); // prints the num bits used: non-compressed/compressed format
  void BitMap(); // prints char, bitstream
  void PrintMessage(); //prints original message in huffman codes
  
private:
  list<string> message_list; // stores multiple input files if needed
  string message;      // stores a single input file
  map<char,int> mymap; // maps frequency "count" indexed by char 'c'
  map<char,string> mymap_compress; // maps frequency "count" to bitstream
  pq_zero<Node*> pq;   // binary heap priority queue stores node pointers with priority
  Node* root; // root of prefix tree
  void DisplayPrefixTree(Node* t); // optional, use for debugging, display tree
  void SetBitCodes(Node* n); // sets string bits for leaf nodes
  void SetBitsPerChar(Node* n); // maps bitstream to char
};

#endif /* HUFFMAN_H_ */




