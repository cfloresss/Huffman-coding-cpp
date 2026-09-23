// * Filename : pq_zero.H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <map>
#include <iomanip>
#include <utility>
#include <vector>

using namespace std;

template< class Item > 
class pq_zero {
private:
  vector<Item> heap; // The heap expands/shrinks to fit data
  typedef int indx;  // index with heap
  map<Item,indx> index;  // records each Item's place in heap
  map<Item,float> priority; // records each Item's priority
  void percolate_up( indx i ); 
  void percolate_down( indx i );
  
  map<Item,int> order;
  int nextOrder = 0;
  void build_heap();
  
public: 
  // These use the min-heap functions above.
  int size( ) const;
  bool empty( ) const;
  const Item& front( ) const;
  void pop( );
  void push( const Item& w, float prio );
  
  pq_zero(){}
  pq_zero(const vector<Item>& items, const vector<float>& priorities);
};

template<class Item>
int pq_zero<Item>::size() const{
  return heap.size();
}

template<class Item>
bool pq_zero<Item>::empty() const{
  return heap.empty();
}

template<class Item>
const Item& pq_zero<Item>::front() const{
  return heap[0];
}


  template<class Item>
  void pq_zero<Item>:: percolate_up(indx i){
    while(i > 0){
      indx parent = (i - 1) /2;
      
      bool smallerPriority = priority[heap[i]] < priority[heap[parent]];
      
      bool smallerAndEarlyPriority = priority[heap[i]] == priority[heap[parent]] &&
      order[heap[i]] < order[heap[parent]];
      
      if(!smallerPriority && !smallerAndEarlyPriority) {
        break;
      }
      
      swap(heap[i], heap[parent]);
      
      index[heap[i]] = i;
      index[heap[parent]] = parent;
      i = parent;
    }
  }
  
  template<class Item>
  void pq_zero<Item>::percolate_down(indx i) {
    indx heapSize = static_cast<indx>(heap.size());
    
    while (true) {
      indx left = (2 * i) + 1;
      indx right = (2 * i) + 2;
      indx smallest = i;
      
      if (left < heapSize) {
        bool smallerPriority = priority[heap[left]] < priority[heap[smallest]];
      
        bool smallerAndEarlyPriority = priority[heap[left]] == priority[heap[smallest]] &&
        order[heap[left]] < order[heap[smallest]];
      
        if(smallerPriority || smallerAndEarlyPriority) {
          smallest = left;
        }
      }
      if (right < heapSize) {
        bool smallerPriority = priority[heap[right]] < priority[heap[smallest]];
      
        bool smallerAndEarlyPriority = priority[heap[right]] == priority[heap[smallest]] &&
        order[heap[right]] < order[heap[smallest]];
      
        if(smallerPriority || smallerAndEarlyPriority) {
          smallest = right;
        }
      }
      if(smallest == i){
        break;
      }
      swap(heap[i], heap[smallest]);
      
      index[heap[i]] = i;
      index[heap[smallest]] = smallest;
      i = smallest;
    }
  }
  
  template<class Item>
  void pq_zero<Item>::push(const Item& w, float prio){
    if(index.find(w) != index.end()) {
      float oldPriority = priority[w];
      priority[w] = prio;
      
      if (prio < oldPriority) {
        percolate_up(index[w]);
      }
      else if(prio > oldPriority) {
        percolate_down(index[w]);
      }
      return;
    }
    heap.push_back(w);
    indx newIndex = static_cast<indx>(heap.size()) - 1; 
    
    index[w] = newIndex;
    priority[w] = prio;
    order[w] = nextOrder;
    nextOrder++;
    percolate_up(newIndex);
  }
  
  template<class Item>
  void pq_zero<Item>::pop() {
    if(heap.empty()) {
      return;
    }
    Item removedItem = heap[0];
    if(heap.size() == 1) {
      heap.pop_back();
      index.erase(removedItem);
      priority.erase(removedItem);
      order.erase(removedItem);
      return;
    }
    
    heap[0] = heap.back();
    index[heap[0]] = 0;
    heap.pop_back();
    
    index.erase(removedItem);
    priority.erase(removedItem);
    order.erase(removedItem);
    
    percolate_down(0);
  }
  
  template<class Item>
  pq_zero<Item>::pq_zero(const vector<Item>& items, const vector<float>& priorities) {
    heap = items;
    
    for(indx i = 0; i < static_cast<indx>(heap.size()); i++) {
      index[heap[i]] = i;
      priority[heap[i]] = priorities[i];
      order[heap[i]] = nextOrder;
      nextOrder++;
    }
    
    build_heap();
  }
  
  template<class Item>
  void pq_zero<Item>::build_heap() {
    indx start = static_cast<indx>(heap.size()) / 2 - 1;
    for (indx i = start; i >= 0; i--) {
      percolate_down(i);
    }
  }
  
  
  template<class Item>
  using priority_queue = pq_zero<Item>;
