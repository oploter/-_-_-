#include "unique_ptr.h"
#include <iostream>

bool destructorCalledWithoutDeleteKeyword = false;

struct A{
    A(){
        std::cout << "A constructed\n";
    }
    
    ~A(){
        std::cout << "A destructed\n";
        destructorCalledWithoutDeleteKeyword = true;
    }
};

void foo(){
    unique_ptr<A> aObj(new A());
    
}

int main(){
    foo();
    if(destructorCalledWithoutDeleteKeyword){
        std::cout << "Unique_ptr worked\n";
    }else{
        std::cout << "Unique_ptr didn't work\n";
    }
}
