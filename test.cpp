#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "mydeque.h"

int main ()
{
    MyDeque<int> obj;
    MyDeque<int> L;
    obj.push_back(2);
    obj.push_back(3);
    obj.push_front(12);
    obj.push_front(14);
    std::cout << "Rozmiar kolejki wynosi " << obj.size() << "\n";
    obj.display();
    std::cout <<"head = " <<obj.retHead() << " tail = " << obj.retTail() <<"\n";
    
    L = obj;
    std::cout << "Rozmiar kolejki wynosi " << obj.size() << "\n";
    L.display();
    L.pop_back();
    L.pop_front();
    obj.display();
    L.display();

    L.push_back(7);
    L.push_back(8);
    L.push_front(14);
    L.push_front(15);
    L.display();

    std::cout << "Indeks wynosi " <<L.index(14) << "\n";
    std::cout << "Front to " << L.front() <<" back to " << L.back() << "\n";

    L.erase(9);
    L.display();
    L.insert(9, 16);
    L.display();

    L[1] = 13;
    L.display();
    std::cout <<"head = " <<L.retHead() << " tail = " << L.retTail() <<"\n";
    
    return 0;
}