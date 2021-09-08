#include "MyVector.h"

/**
 * @brief Default Constructor 
 * 
 * Creates a new Linked List object.
 * 
 * @param void
 * @return void
 */
MyVector::MyVector() {
    head = NULL;  // NULL = zeros
                    // and zeros imply empty
}

/**
 * @brief Overloaded Constructor 
 * 
 * Creates a new MyVector object from 
 * an array of values.
 * 
 * @param int* A - array of values
 * @param int size - size of array
 * 
 * @return void
 */
MyVector::MyVector(int A[], int size) {
    head = NULL;  // NULL = zeros
                    // and zeros imply empty

    for (int i = 0; i < size; i++) {
        Push(A[i]);
    }
}

/**
 * @brief Overloaded Constructor 
 * 
 * Creates a new MyVector object from 
 * an array of values.
 * 
 * @param string fileName - data from an input file
 * 
 * @return void
 */
MyVector::MyVector(string fileName) {
    ifstream inFile(fileName);
    head = NULL;  // NULL = zeros
                    // and zeros imply empty
    
    while(!fileName.eof()) {

    }
}


void Push(int x) {
    node* tempPtr = new node(x);  // create a new node and
                                    // add data to it

    if (!head) {  // `!head` implies empty list
                    // So does `head == NULL`

        head = tempPtr;  // `head = tempPtr` places addrress of
                            // tempPtr in head (points head to tempPtr)

    } else {                   // list not empty
        tempPtr->next = head;  // point tempPtr's next to what head points to
        head = tempPtr;        // now point head to tempPtr
    }
}

void print() {
    node* temp = head;  // temp pointer copies head

    while (temp) {  // this loops until temp is NULL
                    // same as `while(temp != NULL)`

        cout << temp->data;  // print data from node
        if (temp->next) {
            cout << "->";
        }
        temp = temp->next;  // move to next node
    }
    cout << endl;
}

~LinkedList() {
}