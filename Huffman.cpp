// * Filename : Huffman.cpp

#include "Huffman.h"

Huffman::Huffman(){
    root = nullptr;
}
Huffman::Huffman(const string& inputFile){
    root = nullptr;
    
    ifstream inFS;
    char c;
    
    inFS.open(inputFile);
    
    if(!inFS.is_open()) {
        cerr << "Error opening file." << endl;
        exit(1);
    }
    
    while(inFS.get(c)) {
        message += c;
        if(c != '\n') {
            mymap[c]++;   
        }
    }
    
    
    inFS.close();
    BuildPQ();
}
Huffman::~Huffman(){
    
}
void Huffman::PrintCharFrequencies(){
    map<char, int>::iterator it;
    
    for(it = mymap.begin(); it != mymap.end(); it++){
        cout << it->first << " => " << it->second << endl;
    }
}

void Huffman::BuildPQ() {
    map<char, int>:: iterator it;
    
    for(it = mymap.begin(); it != mymap.end(); ++it) {
        Node* temp = new Node(it->first, it->second);
        pq.push(temp, it->second);
    }
}


void Huffman::BuildHuffmanTree(){
    while(pq.size() > 1){
        Node* left = pq.front();
        pq.pop();
        
        Node* right = pq.front();
        pq.pop();
        
        int totalCount= left->count + right->count;
        
        Node* parent = new Node(left, right, '\0', totalCount);
        
        pq.push(parent, totalCount);
    }
    
    root = pq.front();
}


void Huffman::SetBitsPerChar(Node* n){
    if(n == nullptr) {
        return;
    }
    if(n->left == nullptr && n->right == nullptr) {
        mymap_compress[n->c] = n->bits;
        return;
    }
    
    SetBitsPerChar(n->left);
    SetBitsPerChar(n->right);
}

void Huffman::SetBitsPerChar(){
    SetBitsPerChar(root);
}

void DisplayPrefixTree(); // optional, calls private function

void Huffman::SetBitCodes(Node* n){
    if(n == nullptr){
        return;
    }
    if(n->left != nullptr) {
        n->left->bits = n->bits + "0";
        SetBitCodes(n->left);
    }
    if(n->right != nullptr) {
        n->right->bits = n->bits + "1";
        SetBitCodes(n->right);
    }
    
}

void Huffman::SetBitCodes() {
    root->bits = "";
    SetBitCodes(root);
}

void Huffman::Stats(){
    int totalBits = 0;
    cout << "Without compression, 8-bit characters" << endl;
    
    map<char, int>:: iterator it;
    
    for(it = mymap.begin(); it != mymap.end(); it++) {
        int cost = it->second * 8;
        totalBits += cost;
        
        cout << it->first << " occurs " << it->second
        << " times. Cost of: " << cost
        << " bits. Total so far: " << totalBits
        << " bits." << endl;
    }
    
    cout << "Total bits = " << totalBits << endl;
    cout << "Huffman codes used for lossless compression" << endl;
    
    totalBits = 0;
    
    for(it = mymap.begin(); it != mymap.end(); it++) {
        string code = mymap_compress[it->first];
        
        int cost = it->second * code.length();
        totalBits += cost;
        
        cout << it->first << " occurs " << it->second << " times. "
        << "Bit sequence: " << code << ". "
        << "Cost of: " << cost << " bits. "
        << "Total so far: " << totalBits << " bits." << endl;
    }
    
    cout << "Total bits = " << totalBits << endl;
}
void Huffman::BitMap(){
    map<char, string>::iterator it;
    
    for(it = mymap_compress.begin(); it != mymap_compress.end(); it++){
        cout << it->first << "," << it->second << endl;
    }
}
void Huffman::PrintMessage(){
    for (unsigned int i = 0; i < message.length(); i++){
        cout << mymap_compress[message.at(i)];
    }
    cout << endl;
}
