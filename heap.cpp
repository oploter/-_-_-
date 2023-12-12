#include <vector>
#include <iostream>
#include "avl_tree.h"

void Heap::siftUp(int i){
    while(i > 1 && heap[i/2].x_high > heap[i].x_high){
        std::swap(heap[i], heap[i/2]);
        i /= 2;
    }
}

void Heap::siftDown(int i){
    while(1){
        int l = 2 * i;
        if(l + 1 <= n && heap[l + 1].x_high < heap[l].x_high) ++l;
        if(!(l <= n && heap[l].x_high < heap[i].x_high)) break;
        std::swap(heap[l], heap[i]);
        i = l;
    }
}

void Heap::add(const Component& c){
    ++n;
    if((int) heap.size() <= n){
        heap.push_back(c);
    }else{
        heap[n] = c;
    }
    siftUp(n);
}

float Heap::getMinX(){
    return n == 0 ? 100000000 : heap[1].x_high;
}

void Heap::extractMin(){
    std::swap(heap[1], heap[n--]);
    siftDown(1);
}

std::unordered_map<char, std::vector<std::string>> Heap::intersections(const Component& c){
    std::unordered_map<char, std::vector<std::string>> ans;
    for(int i = 1; i <= n; ++i){
        if(c.intersects(heap[i])){
            ans[heap[i].type].push_back(heap[i].name);
        }
    }
    return ans;
}


bool Component::intersects(const Component& c) const {
    return !(y_low > c.y_high || c.y_low > y_high);
}