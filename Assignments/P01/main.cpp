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
*        This program creates a more robust linked list that can prepend, 
*        append, push at, pop, pop at, find, print, etc. It can even take
*        in an entirely different list and add it to itself.
* 
*  Usage:
*        N/A
* 
*  Files:            (list of all source files used in this program)
                      main.cpp
*****************************************************************************/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Node used for the linked list
struct node{
  int data;
  node *next;
  node *prev;
  node(int x, node* n = nullptr, node *p = nullptr){
    data = x;
    next = n;
    prev = p;
  }
};

/**
 * Class Name
 * 
 * Description:
 *      This class creates a doubly linked list which is used to store integers.
 *      It can find given values within it, copy values from another linked list, 
 *      and even properly sort the value you would like to place into the list.
 * 
 * Public Methods:
 *                          MyVector()
 *                          MyVector(int A[], int size)
 *                          MyVector(string fileName)
 *                          MyVector(MyVector &L1)
 *      void                pushFront(int x)
 *      void                pushRear(int x)
 *      void                pushAt(int x, int point)
 *      void                inOrderPush(int x)
 *      int                 popFront()
 *      int                 popRear()
 *      int                 popAt(int x, int loc)
 *      int                 find(int x)
 *      void                print(ostream& outFile)
 *      void                printBackwards(ostream& outFile)
 * 
 * Private Methods:
 *      N/A
 * 
 * Usage: 
 *      
 */
class MyVector {
  private:
    node* head;
    node* tail;
    int counter = 0; // Used to traverse list and locate specific points

  public:
    MyVector() {
      head = NULL;
      tail = head;
    }

    /**
     * @brief Overloaded Constructor 
     * 
     * Creates a new Linked List object from 
     * an array of values.
     * 
     * @param int* A - array of values
     * @param int size - size of array
     * 
     * @return void
     */
    MyVector(int A[], int size) {
      head = NULL;  // NULL = zeros
                    // and zeros imply empty

      for (int i = size - 1; i >= 0; i--) { // Inserts the values from the array into the list
          pushFront(A[i]); 
      }
    }

     /**
     * @brief Overloaded Constructor 
     * 
     * Creates a new Linked List object from 
     * an infile that has the array size defined in it.
     * 
     * @param string fileName - input file for data
     * 
     * @return void
     */
    MyVector(string fileName) {
      head = NULL;  // NULL = zeros
                    // and zeros imply empty

      // int size = 0;
      int x = 0;
      ifstream inFile;
      inFile.open(fileName); // Opens the file
      // inFile >> size;        // Gets the size for the array
      // int* tempArr = new int[size];

      while (!inFile.eof()) {
        inFile >> x;
        pushRear(x);
        // i++;
      }
      // delete []tempArr;
    }

    /**
     * @brief Overloaded Constructor 
     * 
     * Creates a new Linked List object based 
     * on the data within it.
     * 
     * @param MyVector &L1 - Linked List used to copy the data over
     * 
     * @return void
     */
    MyVector(MyVector &L1) {
      head = NULL; // NULL = zeros
                   // and zeros imply empty
      
      node* tempPtr = L1.tail;

      while(tempPtr) {
          pushFront(tempPtr->data);
          tempPtr = tempPtr->prev;
      }
    }

    /**
     * @brief Deconstructor 
     * 
     * Deletes all of the values in the list
     * 
     * @param N/A
     * 
     * @return void
     */
    ~MyVector() {
      node* temp = head;
      while(temp != nullptr){
        node* deleteMe = temp;
        temp = temp->next;
        delete deleteMe;
      }
    }

    /**
     * @brief Method: pushFront
     * 
     * Adds the given value to the front of the list, and makes it
     * the new head
     * 
     * @param int x - Value to be put at the front of the list
     * 
     * @return void
     */
    void pushFront(int x) {
      if(head == nullptr){        // Checks to see if list is empty
        head = new node(x, head); // Creates a new node and sets the head
        tail = head;              // Sets tail to head since first node 
      }else{
        node *temPtr = new node(x, head);
        head->prev = temPtr; // Connects the old node to the new head
        head = temPtr;       // Sets the new head of the list
      }
    }

    /**
     * @brief Overloaded Method: pushFront
     * 
     * Adds the given list of values to the front of the list, and makes the
     * ending value the new head
     * 
     * @param MyVector &V2 - Values to be put at the front of the list
     * 
     * @return void
     */
    void pushFront(MyVector &V2) {
      node* tempPtr = V2.tail;

      while(tempPtr) {
        pushFront(tempPtr->data);
        tempPtr = tempPtr->prev;
      }      
    }

    /**
     * @brief Member Function: pushRear
     * 
     * Adds the given value to the end of the list, and makes it
     * the new tail
     * 
     * @param int x - Value to be put at the end of the list
     * 
     * @return void
     */
    void pushRear(int x) {
      if(head == nullptr){ // Checks if the list is empty
        head = new node(x);
        tail = head;
      }else{
        tail->next = new node(x, nullptr, tail); // Creates a new node and
                                                 // connects it to the previous node 
        tail = tail->next;
      }
    }

    /**
     * @brief Overloaded Member Function: pushRear
     * 
     * Adds the given list of values to the end of the list, and makes the
     * ending value the new tail
     * 
     * @param int x - Value to be put at the end of the list
     * 
     * @return void
     */
    void pushRear(MyVector &V2) {
      node* tempPtr = V2.head;

      while(tempPtr) {
        pushRear(tempPtr->data);
        tempPtr = tempPtr->next;
      }      
    }

    /**
     * @brief Member Function: pushAt
     * 
     * Adds the given value to the specified location of the list, and integrates the
     * new node into the list
     * 
     * @param int x - Value to be put at the specified location of the list
     * @param int point - index to stop at desired location
     * 
     * @return void
     */
    void pushAt(int x, int point) {
      if(head == nullptr){        // Checks to see if list is empty
        head = new node(x, head); // Creates a new node and sets the head
        tail = head;              // Sets tail to head since first node 
      }else{
        node* traverse1 = head;      // Creates our temporary pointers
        node* traverse2 = traverse1; // in order to insert a node and 
                                     // properly connect it for doubly
        while((counter + 1) != point && traverse1->next != nullptr) { // Checks if at right spot
          traverse1 = traverse1->next;
          traverse2 = traverse1;
          counter++; // Counter to keep track of location
        }
        if (point == 1) { // Just Prepends since at front
          pushFront(x);
        }
        else if (traverse1 == tail) { // Just Appends since at back
          pushRear(x);
        }else{
          traverse2 = traverse1->next;                         // Puts second treversing pointer
                                                               // on the next node
          traverse1->next = new node(x, traverse2, traverse1); // Creates a new node and
                                                               // attaches it to the surrounding nodes
          traverse2->prev = traverse1->next;                   // Attaches the node to the right of the 
                                                               // new node to the new node
        }
      }
      counter = 0;
    }

    /**
     * @brief Member Function: inOrderPush
     * 
     * Adds the given value to the correct ordered location of the list, and integrates the
     * new node into the list
     * 
     * @param int x - Value to be put at the ordered location of the list
     * 
     * @return void
     */
    void inOrderPush(int x) {
       if(head == nullptr){       // Checks to see if list is empty
        head = new node(x, head); // Creates a new node and sets the head
        tail = head;              // Sets tail to head since first node 
      }else{
        node* traverse1 = head;      // Creates our temporary pointer
        node* traverse2 = traverse1; // In order to insert a node and 
                                     // properly connect it for doubly
        if (traverse1->data >= x) {  // Just Prepends since less than or equal to data at head
          pushFront(x);
        }else{
          while(traverse1->next != nullptr && traverse1->data <= x) { // Checks if at right spot
            traverse1 = traverse1->next;
            traverse2 = traverse1;
            counter++; // Counter to keep track of location
          }
          
          if (traverse1 == tail) { // Just Appends since greater than or equal to data at tail
            pushRear(x);
          }else{
            traverse1 = traverse1->prev;                         // Moves back a node for proper placement
            traverse2 = traverse1->next;                         // Puts second treversing pointer
                                                                 // on the next node
            traverse1->next = new node(x, traverse2, traverse1); // Creates a new node and
                                                                 // attaches it to the surrounding nodes
            traverse2->prev = traverse1->next;                   // Attaches the node to the right of the 
                                                                 // new node to the new node
          }
        }
        
      }
      counter = 0;
    }

    /**
     * @brief Member Function: popFront
     * 
     * Takes the head of the list, sets it to the following node in the list, 
     * and deletes the old head while returning the value stored in it
     * 
     * @param N/A
     * 
     * @return int
     */
    int popFront() {
      node *temPtr; // Creates temporary pointer to delete removed node
      if(!head){    // Checks if the list is empty
        std::cout << "The list is empty...\n";
        return 0;
      }
      temPtr = head;          // Sets the temporary pointer
      int val = temPtr->data; // Stores the value we are returning
      head = head->next;      // Sets the new head of the list
      head->prev = nullptr;   // Resets the front of the list
      delete temPtr;          // Deletes the popped node
      return val;
    }

    int popRear() {
      node *temPtr; // Creates temporary pointer to delete removed node
      int val;      // Creates a variable to store the value of the popped data

      if (tail->prev == nullptr) { // Checks if the list is empty
        cout << "The list is empty...\n";
      }else{
        temPtr = tail;          // Sets the temporary pointer
        val = temPtr->data;     // Stores the value we are returning
        tail = tail->prev;      // Sets the new tail of the list
        tail->next = nullptr;   // Resets the end of the list
        delete temPtr;          // Deletes the popped node
      }
      return val;
    }

    /**
     * @brief Member Function: popAt
     * 
     * Finds the location of the given value, links the surrounding nodes to each other, 
     * and deletes the popped node while returning the value stored in it
     * 
     * @param int loc - Location of node to be popped
     * 
     * @return int
     */
    int popAt(int loc) {
      node *traverse = head; // Creates temporary pointer to delete removed node
      int val;               // Creates a variable to store the value of the popped data
      loc = loc + 1;
      if (!head) { // Checks if the list is empty
        // std::cout << "The list is empty...\n";
        return -1;
      }

      if (loc == 1) {
        popFront();
      }else{
        while (traverse->next != nullptr && counter != loc){ // Traverses list for value
          traverse = traverse->next;
          counter++;
        }
        if (traverse == tail) {
          popRear();
        }else{
          traverse = traverse->prev;
          val = traverse->data;                  // Stores the value we are returning
          traverse->prev->next = traverse->next; // Sets the previous nodes next pointer to the next node
          traverse->next->prev = traverse->prev; // Sets the next nodes previous pointer to the previous node
          delete traverse;                       // Deletes the popped node
        }
      }
      counter = 0; // Resets the counter
      return val;
    }

    /**
     * @brief Member Function: find
     * 
     * Traverses through the list in order to find the specified data value
     * 
     * @param int x - Given data value to look for in list
     * 
     * @return int
     */
    int find(int x) {
      if (!head) { // Checks if the list is empty before traversing
        cout << "The list is empty. \nGo add something.\n";
        return -1;
      }
      node* traverse = head; // Creates a pointer to traverse the list
      while(traverse->next != nullptr && traverse->data != x){ // Traverses the list to find the specified value
        traverse = traverse->next;
        counter++;
      }
      if (traverse == tail) { // Handles non-existent values
        return -1;
      }

      int loc = counter; // Stores the location of the specified value into a returnable variable
      counter = 0;       // Resets the counter used in tracking location
      return loc;
    }

    /**
     * @brief Member Function: print
     * 
     * Traverses through the list and outputs the data value in every node to the
     * output stream and the output file from left to right
     * 
     * @param N/A
     * 
     * @return void
     */
    void print(ofstream &outFile) const {
      if (!head) { // Checks if the list is empty
        cout << "The list is empty. Go put something in it.\n";
        outFile << "The list is empty. Go put something in it.\n";
      }else{ // If list is not empty
        node* traverse = head; // Creates a pointer to traverse the list
        cout << '[';
        outFile << '[';
        while(traverse != nullptr){ // Traversers the list and prints out the values
          if (traverse->next == nullptr) {
            std::cout << traverse->data;
            outFile << traverse->data;
            traverse = traverse->next;
          }else{
            std::cout << traverse->data << ',' << " ";
            outFile << traverse->data <<  ',' << " ";
            traverse = traverse->next;
          }
        }
        cout << ']';
        cout << "\n";
        outFile << ']';
        outFile << "\n";
      }
    }

    /**
     * @brief Member Function: print
     * 
     * Traverses through the list and outputs the data value in every node to the
     * output stream and the output file from right to left
     * 
     * @param N/A
     * 
     * @return void
     */
    void printBackwards(ofstream &outFile) const {
      node* traverse = tail; // Creates a pointer to traverse the list
      while(traverse != nullptr) { // Traverses the list
        std::cout << traverse->data << " ";
        outFile << traverse->data << " ";
        traverse = traverse->prev;
      }
      cout << "\n";
      outFile.close();
    }
    
};

int main() {

  int x = 0;
  ofstream outFile("test.out");

  outFile << "2143\n"
            << "P01\n"
            << "Kolten Pulliam\n\n";

  MyVector v1;
  v1.pushFront(18);
  v1.pushFront(20);
  v1.pushFront(25);
  v1.pushRear(18);
  v1.pushRear(20);
  v1.pushRear(25);
  v1.print(outFile);
  // [25, 20, 18, 18, 20, 25]

  int A[] = {11,25,33,47,51};
  MyVector v2(A,5);
  v2.print(outFile);
  // [11, 25, 33, 47, 51]

  v2.pushFront(9);
  v2.inOrderPush(27);
  v2.pushRear(63);
  v2.print(outFile);
  // [9, 11, 25, 27, 33, 47, 51, 63]

  v1.pushRear(v2);
  v1.print(outFile);
  // [25, 20, 18, 18, 20, 25, 9, 11, 25, 27, 33, 47, 51, 63]

  x = v1.popFront();
  x = v1.popFront();
  x = v1.popFront();
  v1.print(outFile);
  // [18, 20, 25, 9, 11, 25, 27, 33, 47, 51, 63]
  cout<<x<<endl;
  outFile << x << endl;
  // 18

  x = v1.popRear();
  x = v1.popRear();
  x = v1.popRear();
  v1.print(outFile);
  // [18, 20, 25, 9, 11, 25, 27, 33]
  cout<<x<<endl;
  outFile << x << endl;
  // 47

  x = v2.popAt(3);
  v2.print(outFile);
  // [9, 11, 25, 33, 47, 51, 63]
  cout<<x<<endl;
  outFile << x << endl;
  // 27

  x = v2.find(51);
  cout<<x<<endl;
  outFile << x << endl;
  // 5

  x = v2.find(99);
  cout<<x<<endl;
  outFile << x << endl;
  // -1

  MyVector v3(v1);
  v3.print(outFile);
  // [18, 20, 25, 9, 11, 25, 27, 33]

  v3.pushFront(v2);
  v3.print(outFile);
  //[9, 11, 25, 33, 47, 51, 63, 18, 20, 25, 9, 11, 25, 27, 33]

  MyVector v4("input.dat");
  v4.pushRear(v3);
  v4.print(outFile);
  // [56, 61, 97, 66, 83, 25, 26, 11, 53, 49, 62, 18, 10, 18, 14, 3, 4, 23, 18, 24, 26, 27, 54, 14, 12, 45, 65, 98, 56, 97, 15, 84, 98, 9, 11, 25, 33, 47, 51, 63, 18, 20, 25, 9, 11, 25, 27, 33]

  outFile.close();
  return 0;
}