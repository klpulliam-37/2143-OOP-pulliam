/*****************************************************************************
*                    
*  Author:           Kolten Pulliam
*  Email:            klpulliam44@gmail.com
*  Label:            A04
*  Title:            Basic Project Organization
*  Course:           2143-Object-Oriented-Programming
*  Semester:         Fall 2021
* 
*  Description:
*        This program
* 
*  Usage:
*        N/A
* 
*  Files:            (list of all source files used in this program)
                      main.cpp
*****************************************************************************/

#include <iostream>

using namespace std;

/**
 * Class Name
 * 
 * Description:
 *      This class creates an array that acts as a circular queue by taking a value
 *      given in the constructor and setting the size of the array to said value.
 *      The array can then recieve values or remove them in the same manner as 
 *      a queue would.
 * 
 * Public Methods:
 *                          CircularArrayQue()
 *                          CircularArrayQue(int size)
 *      void                Push(int item)
 *      int                 Pop()
 * 
 * Private Methods:
 *      void                init(int size = 0)
 *      bool                Full()
 * 
 * Usage: 
 * 
 *      CircularArrayQue C1;               // Creates instance of CircularArrayQue
 *      CircularArrayQue C2(size)          // Creates instance of 
 *                                         // CircularArrayQue with size
 *      
 *      
 */
class CircularArrayQue {
private:
    int *Container;          // Pointer to allocate dynamic array
    int Front;               // An integer to track the location of Front
    int Rear;                // An integer to track the location of Rear
    int QueSize;             // amount of total items allowed in the queue
    int CurrentSize;         // Size of the array queue in its current state
/**
 * Private : init
 * 
 * Description:
 *      It is purely meant to initialize the 
 *      value of the newly created array.
 * 
 * Params:
 *      int     :  integer to set size of array
 * 
 * Returns:
 *      nothing :  void
 */
    void init(int size = 0) {
        Front = Rear = CurrentSize = 0; // Initializes all values to zero
        QueSize = size;                 // Sets the new total size
    }
/**
 * Private : Full
 * 
 * Description:
 *      This function is used to detect wether or 
 *      not the array queue has reached its maximum
 *      amount of elements.
 * 
 * Params:
 *      N/A
 * 
 * Returns:
 *      boolean : a true or false value depending on if the array is full or not
 */
    bool Full() {
        return CurrentSize == QueSize;
    }

public:
/**
 * Public : CircularArrayQue
 * 
 * Description:
 *     The default constructor of the class CircularArrayQue
 *     if no values are given when used to create an instance
 * 
 * Params:
 *      N/A
 * 
 * Returns:
 *      nothing  : N/A
 */
    CircularArrayQue() {
        Container = new int[10];// Dynamically allocates an int array queue
        init(10);               // Initializes all array queue values to zero
    }
/**
 * Public : CircularArrayQue
 * 
 * Description:
 *     The overridden version of the constructor of the class CircularArrayQue
 *     if a value is given when used to create an instance
 * 
 * Params:
 *      int     :  integer to set size of array
 * 
 * Returns:
 *      nothing  : N/A
 */
    CircularArrayQue(int size) {
        Container = new int[size];// Dynamically allocates an int array queue
        init(size);               // Initializes all array queue values to size
    }
/**
 * Public : Push
 * 
 * Description:
 *      Receives an integer value that is then stored
 *      within the next available element in the array
 *      based on the format of a queue. It also resets the
 *      "Rear" variable so it can keep tracking the array
 *      properly If the array is full, it then sends a string 
 *      to the output instead.
 * 
 * Params:
 *      int     :  integer to store in the next element of the array
 * 
 * Returns:
 *      nothing  : void
 */
    void Push(int item) {
        if (!Full()) { // Checks if the array queue is not full
            Container[Rear] = item;         // Puts new item at end of queue
            Rear = (Rear + 1) % QueSize;    // Updates the Rear to new item
            CurrentSize++;                  // Updates the size of array queue
        } else { // Checks if the array queue is full
            cout << "FULL!!!!" << endl;
        }
    }
/**
 * Public : Pop
 * 
 * Description:
 *      Takes the value that was inserted into the first element 
 *      of the array and removes it. The function then resets the 
 *      "Front" variable in order to properly track it. It also receives
 *      access to the 
 * 
 * Params:
 *      N/A
 * 
 * Returns:
 *      int      :  the integer that was just removed
 */
    int Pop() {
        int temp = Container[Front];
        Front = (Front + 1) % QueSize;
        CurrentSize--;
        return temp;
    }
    friend ostream &operator<<(ostream &os, const CircularArrayQue &other);
};

/**
 * Public : operator
 * 
 * Description:
 *      Allows the values within the class CircularArrayQue to be
 *      sent directly to the out stream by using "cout" instead of 
 *      using the "Pop" function.
 * 
 * Params:
 *      ostream  :  object passed by reference to be sent to the out stream
 * 
 * Returns:
 *      nothing  : void
 */
ostream &operator<<(ostream &os, const CircularArrayQue &other) {

    for (int i = other.Front; i < other.CurrentSize; i = (i + 1) % other.QueSize) {
        os << other.Container[i] << " ";
    }
    os << endl;
    return os;
}

/**
 * Main Driver
 * 
 * For this program, the main driver was used to test the CircularArrayQue class
 * 
 */
int main() {
    CircularArrayQue C1(5);

    // C1.Push(34);
    // C1.Push(38);
    // C1.Push(44);
    // C1.Push(22);
    // C1.Push(99);
    // C1.Push(100);

    C1.Push(1);
    C1.Push(2);
    C1.Push(3);
    
    // C1.Push(6);
    // C1.Push(7);
    cout << C1 << endl;
    C1.Pop();
    // C1.Push(1);
    // C1.Push(2);
    // C1.Push(3);

    cout << C1 << endl;
}