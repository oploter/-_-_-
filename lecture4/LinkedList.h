#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <cstdio>
#include <exception>
#include <optional>
#include <iostream>

template<typename T>
class List{
    struct Node{
        Node* next = nullptr;
        T data;
        Node(){}
        Node(const T& val) : data(val){}
    };
    Node* head_m = nullptr;
    std::size_t size_m = 0;

public:
    List(){}

    List(List&& other){
        head_m = other.head_m;
        size_m = other.size_m;
        other.head_m = nullptr;
    }

    ~List(){
        Node* curr = head_m;
        while(curr != nullptr){
            Node* nextN = curr->next;
            delete curr;
            curr = nextN;
        }
    }

    void InsertNode(Node* newNode, int pos){
        if(pos < 0 || size_m < pos){
            throw std::invalid_argument("Wrong position");
        }
        Node* prev = nullptr;
        for(int i = 0; i < pos; ++i){
            if(prev != nullptr) prev = prev->next;
            else prev = head_m;
        }
        Node *nextN = (prev == nullptr ? head_m : prev->next);
        if(prev != nullptr) prev->next = newNode;
        else head_m = newNode;
        newNode->next = nextN;
        ++size_m;
    }

    void RemoveNode(int pos){
        if(pos < 0 || size_m <= pos){
            throw std::invalid_argument("Wrong position");       
        }

        Node *prev = nullptr;
        for(int i = 0; i < pos; ++i){
            if(prev != nullptr) prev = prev->next;
            else prev = head_m;
        }
        Node *curr = (prev == nullptr ? head_m : prev->next);
        Node *nextN = curr->next;
        delete curr;
        if(prev != nullptr) prev->next = nextN;
        else head_m = nextN;
        --size_m;
    }

    void PrintList() const {
        std::cout << '{';
        for(Node *node = head_m; node != nullptr; node = node->next){
            std::cout << node->data << ' ';
        }
        std::cout << "}\n";
    }

    static Node* getNode(const T& val){
        return new Node(val);
    }

    T& GetElement(std::size_t pos) const {
        if(pos < 0 || size_m <= pos){
            throw std::invalid_argument("Invalid position");
        }
        Node *curr = head_m;
        for(std::size_t i = 0; i < pos; ++i){
            curr = curr->next;
        }
        return curr->data;
    }

};

#endif
