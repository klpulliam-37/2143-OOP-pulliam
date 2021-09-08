#include <iostream>
#include <fstream>
#include <string>

// Node for our linked list
struct node {
    int data;  // data value (could be a lot more values)

    node* next;  // we always need a "link" in a linked list

    node(int x) {  // cunstructor to make adding values easy
        data = x;
        next = NULL;
    }
};

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