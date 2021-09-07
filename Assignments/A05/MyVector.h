#include <iostream>
#include <fstream>

class MyVector {
private:
    node* head;  // base pointer of list
public:
    MyVector();
    MyVector(int A[], int size);

    void Push(int x);
    void Print();

    ~MyVector();
};