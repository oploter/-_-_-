#include "LinkedList.h"
#include <iostream>

int main(){
    List<int> l;
    l.InsertNode(List<int>::getNode(1), 0);
    l.InsertNode(List<int>::getNode(2), 1);
    l.InsertNode(List<int>::getNode(3), 2);
    l.PrintList(); //
    l.InsertNode(List<int>::getNode(4), 0);
    l.InsertNode(List<int>::getNode(5), 3);
    std::cout << l.GetElement(0) << ' ' << l.GetElement(1) << '\n';
    l.PrintList(); //
    l.RemoveNode(0);
    l.PrintList(); //
    l.RemoveNode(2);
    l.RemoveNode(2);
    l.PrintList(); //
    l.RemoveNode(1);
    l.RemoveNode(0);
    l.PrintList(); //
}
