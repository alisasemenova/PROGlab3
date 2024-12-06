#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "lab3.h"

int main() {

    setlocale(LC_ALL, "");

    // Последовательный контейнер (вектор)

   My_vector<int> A;

    // Добавление элементов

    for (int i = 0; i < 10; ++i)
    {
        A.push_back(i);
    }

    std::cout << "My vector: ";

    A.print();

    std::cout << "Size of my vector: " << A.size() << std::endl;

    // Удаление элементов

    A.erase(2); 
    A.erase(4); 
    A.erase(5); 

    std::cout << "After deleting: ";

    A.print();

    // Добавление в начало

    A.insert(0, 10); 

    std::cout << "Afler additing 10: ";

    A.print();

    // Добавление в середину

    A.insert(4, 20); 

    std::cout << "Afler additing 20: ";

    A.print();

    // Добавление в конец

    A.push_back(30); 

    std::cout << "Afler additing 30: ";

    A.print();

    std::cout << std::endl;

    // Списковый контейнер двузвязный список

    Double_list<int> B;

    // Добавление элементов

    for (int i = 0; i < 10; ++i) 
    {
        B.push_back(i);
    }

    std::cout << "Double list: ";

    B.print();

    std::cout << "Size of double list: " << B.size() << std::endl;

    // Удаление элементов

    B.erase(2); 
    B.erase(4); 
    B.erase(5); 

    std::cout << "Afler deleting: ";

    B.print();

    // Добавление в начало

    B.insert(0, 10); 
    
    std::cout << "Afler additing 10: ";

    B.print();

    // Добавление в cередину

    B.insert(4, 20);

    std::cout << "Afler additing 20: ";

    B.print();

    // Добавление в конец

    B.push_back(30);
    
    std::cout << "Afler additing 30: ";

    B.print();  

    // Списковый контейнер односвязный список

    Solo_list<int> C;

    // Добавление элементов

    for (int i = 0; i < 10; ++i) 
    {
        C.push_back(i);
    }

    std::cout << "Sololist: ";

    C.print();

    std::cout << std::endl;

    std::cout << "Size of sololist: " << C.size() << std::endl;

    // Удаление элементов

    C.erase(2); 
    C.erase(4); 
    C.erase(5); 

    std::cout << "Afler deleting: ";

    C.print();

    // Добавление в начало

    C.insert(0, 10); 

    std::cout << "After additing 10: ";

    C.print();

    // Добавление в середину

    C.insert(4, 20); 

    std::cout << "After additing 20: ";

    C.print();

    // Добавление в конец

    C.push_back(30); 

    std::cout << "After additing 30: ";

    C.print();  

}