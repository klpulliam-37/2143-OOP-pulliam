/*****************************************************************************
*                    
*  Author:           Kolten Pulliam
*  Email:            klpulliam44@gmail.com
*  Label:            A05
*  Title:            Program 1 - MyVector Class
*  Course:           2143-Object-Oriented-Programming
*  Semester:         Fall 2021
* 
*  Description:
*        
* 
*  Usage:
*        N/A
* 
*  Files:            (list of all source files used in this program)
                      main.cpp
                      MyVector.cpp
                      MyVector.h
*****************************************************************************/
#include <fstream>
#include <iostream>
#include <string>
#include "MyVector.h"

using namespace std;

/**
 * @brief Load array with values from a file
 * 
 * @param string filename 
 * @param int*& arr 
 * @param int& size 
 */
void loadArr(string filename, int*& arr, int& size) {
    ifstream fin;         // stream reference
                          //
    fin.open(filename);   // open the file
                          //
    fin >> size;          // get first value which contains
                          // number of remaining values in file
                          //
    arr = new int[size];  // allocate new array of correct size
                          //
    int i = 0;            // need an array index for our while loop
                          //
    // Can also use for loop since we know the exact count in file.
    // eof = end of file flag
    // `!fin.eof()` evaulates to true when we hit end of file.
    while (!fin.eof()) {
        fin >> arr[i];  // read file value straight into array
                        // at index i
        i++;            // increment array index
    }
}

/**
 * @brief Prints an array
 * 
 * @param int arr 
 * @param int size
 * 
 * @returns void
 */
void printArr(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << "[" << arr[i] << "]";
    }
    cout << "\n";
}

int main() {
    int        A[] = {1, 2, 3, 4, 5, 6};    // array initialized with 1-6
    MyVector L(A, 6);                     // linked list built with array

    L.Print();  // print the list

    int* B;     // Int pointer to reference a linked list
    int  size;  // used to hold a count for list and array

    loadArr("input.dat", B, size);  // Stand alone function to
                                    //    read values in from file
    printArr(B, size);              // Stand alone function to print array
    MyVector L2(B, size);         // Create 2nd instance of list
    L2.Print();                     // Print list 2
}

/*
Test
int x = 0;

MyVector v1;
v1.pushFront(18);
v1.pushFront(20);
v1.pushFront(25);
v1.pushRear(18);
v1.pushRear(20);
v1.pushRear(25);
v1.print();
// [25, 20, 18, 18, 20, 25]

int A[] = {11,25,33,47,51};
MyVector v2(A,5);
v2.print();
// [11, 25, 33, 47, 51]

v2.pushFront(9);
v2.inOrderPush(27);
v2.pushRear(63);
v2.print();
// [9, 11, 25, 27, 33, 47, 51, 63]

v1.pushRear(v2);
v1.print();
// [25, 20, 18, 18, 20, 25, 9, 11, 25, 27, 33, 47, 51, 63]

x = v1.popFront();
x = v1.popFront();
x = v1.popFront();
v1.print();
// [18, 20, 25, 9, 11, 25, 27, 33, 47, 51, 63]
cout<<x<<endl;
// 18

x = v1.popRear();
x = v1.popRear();
x = v1.popRear();
v1.print();
// [18, 20, 25, 9, 11, 25, 27, 33]
cout<<x<<endl;
// 47

x = v2.popAt(3);
v2.print();
// [9, 11, 25, 33, 47, 51, 63]
cout<<x<<endl;
// 27

x = v2.find(51);
cout<<x<<endl;
// 5

x = v2.find(99);
cout<<x<<endl;
// -1

MyVector v3(v1);
v3.print();
// [18, 20, 25, 9, 11, 25, 27, 33]

v3.pushFront(v2);
v3.print();
//[9, 11, 25, 33, 47, 51, 63, 18, 20, 25, 9, 11, 25, 27, 33]

MyVector v4("input.dat");
v4.pushRear(v3);
v4.print();
// [56, 61, 97, 66, 83, 25, 26, 11, 53, 49, 62, 18, 10, 18, 14, 3, 4, 23, 18, 24, 26, 27, 54, 14, 12, 45, 65, 98, 56, 97, 15, 84, 98, 9, 11, 25, 33, 47, 51, 63, 18, 20, 25, 9, 11, 25, 27, 33]
*/