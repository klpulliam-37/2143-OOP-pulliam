/*****************************************************************************
*                    
*  Author:           Kolten Pulliam
*  Email:            klpulliam44@gmail.com
*  Label:            P02
*  Title:            Program 2 - MyVector Class 2
*  Course:           2143-Object-Oriented-Programming
*  Semester:         Fall 2021
* 
*  Description:
*        This program creates a more robust linked list that can prepend, 
*        append, push at, pop, pop at, find, print, etc. It can also take
*        in an entirely different list and add it to itself by using
*        overloaded operators.
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
#include <iomanip>
#include <array>

using namespace std;

// Node used for the linked list
template <typename T>
struct node{
  T data;
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
 *      This class creates a doubly linked list 
 *      which is used to store integers.
 *      It can find given values within it, 
 *      copy values from another linked list, 
 *      and even properly sort the value you would 
 *      like to place into the list.
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
 *      void                backwardsPrint(ostream& outFile)
 *      T                   &operator[](int loc)
 *      friend ostream      &operator<<(ostream& cout, const MyVector& V)
 *      friend ofstream     &operator<<(ofstream& cout, const MyVector& V)
 *      MyVector            &operator=(const MyVector &V)
 *      MyVector            operator+(MyVector& other)
 *      MyVector            operator-(MyVector& other)
 *      MyVector            operator/(MyVector& other)
 *      MyVector            operator*(MyVector& other)
 *      bool                operator==(const MyVector& other)
 * 
 * Private Methods:
 *      N/A
 * 
 * Usage: 
 *      
 */
template <typename T>
class MyVector {
  private:
    node<T>* head;
    node<T>* tail;
    // Used to traverse list and locate specific points
    int counter = 0; 
    // Used to get the size of the list for overloaded operators
    int listSize = 0; 

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
    MyVector(T A[], int size) {
      head = NULL;  // NULL = zeros
                    // and zeros imply empty

      // Inserts the values from the array into the list
      for (int i = size - 1; i >= 0; i--) { 
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

      T x;
      ifstream inFile;
      inFile.open(fileName); // Opens the file

      while (!inFile.eof()) {
        inFile >> x; // Reads in the value from the file
        pushRear(x); // Creates a new node at the end of the list 
                     // containing the value we just read in
      }
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
      
      node<T>* tempPtr = L1.tail;

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
      node<T>* temp = head;
      while(temp != nullptr){
        node<T>* deleteMe = temp;
        listSize--;
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
     * @param T x - Value to be put at the front of the list
     * 
     * @return void
     */
    void pushFront(T x) {
      if(head == nullptr){           // Checks to see if list is empty
        head = new node<T>(x, head); // Creates a new node and sets the head
        tail = head;                 // Sets tail to head since first node 
        listSize++;
      }else{
        node<T> *temPtr = new node<T>(x, head);
        head->prev = temPtr; // Connects the old node to the new head
        head = temPtr;       // Sets the new head of the list
        listSize++;
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
      node<T>* tempPtr = V2.tail;

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
     * @param T x - Value to be put at the end of the list
     * 
     * @return void
     */
    void pushRear(T x) {
      if(head == nullptr){ // Checks if the list is empty
        head = new node<T>(x);
        tail = head;
        listSize++;
      }else{
        // Creates a new node and connects it to the previous node
        tail->next = new node<T>(x, nullptr, tail);  
        tail = tail->next;
        listSize++;
      }
    }

    /**
     * @brief Overloaded Member Function: pushRear
     * 
     * Adds the given list of values to the end of the list, and makes the
     * ending value the new tail
     * 
     * @param T x - Value to be put at the end of the list
     * 
     * @return void
     */
    void pushRear(MyVector &V2) {
      node<T>* tempPtr = V2.head;

      while(tempPtr) {
        pushRear(tempPtr->data);
        tempPtr = tempPtr->next;
      }      
    }

    /**
     * @brief Member Function: pushAt
     * 
     * Adds the given value to the specified location 
     * of the list, and integrates the new node into the list
     * 
     * @param T x - Value to be put at the specified location of the list
     * @param int point - index to stop at desired location
     * 
     * @return void
     */
    void pushAt(T x, int point) {
      if(head == nullptr){        // Checks to see if list is empty
        head = new node<T>(x, head); // Creates a new node and sets the head
        tail = head;              // Sets tail to head since first node 
        listSize++;
      }else{
        node<T>* traverse1 = head;      // Creates our temporary pointers
        node<T>* traverse2 = traverse1; // in order to insert a node and 
                                        // properly connect it for doubly
        // Checks if at right spot
        while((counter + 1) != point && traverse1->next != nullptr) { 
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
          // Puts second treversing pointer on the next node
          // Creates a new node and
          // attaches it to the surrounding nodes
          // Attaches the node to the right of the
          // new node to the new node
          traverse2 = traverse1->next;                         
          traverse1->next = new node<T>(x, traverse2, traverse1);                            
          traverse2->prev = traverse1->next;                                        
          listSize++;
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
     * @param T x - Value to be put at the ordered location of the list
     * 
     * @return void
     */
    void inOrderPush(T x) {
       if(head == nullptr){       // Checks to see if list is empty
        head = new node<T>(x, head); // Creates a new node and sets the head
        tail = head;              // Sets tail to head since first node 
        listSize++;
      }else{
        node<T>* traverse1 = head;      // Creates our temporary pointer
        node<T>* traverse2 = traverse1; // In order to insert a node and 
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
            traverse1->next = new node<T>(x, traverse2, traverse1); // Creates a new node and
                                                                 // attaches it to the surrounding nodes
            traverse2->prev = traverse1->next;                   // Attaches the node to the right of the 
                                                                 // new node to the new node
            listSize++;
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
     * @return T
     */
    T popFront() {
      node<T> *temPtr; // Creates temporary pointer to delete removed node
      if(!head){    // Checks if the list is empty
        std::cout << "The list is empty...\n";
        return 0;
      }
      temPtr = head;          // Sets the temporary pointer
      T val = temPtr->data; // Stores the value we are returning
      head = head->next;      // Sets the new head of the list
      head->prev = nullptr;   // Resets the front of the list
      delete temPtr;          // Deletes the popped node
      listSize--;
      return val;
    }

    T popRear() {
      node<T> *temPtr; // Creates temporary pointer to delete removed node
      T val;      // Creates a variable to store the value of the popped data

      if (tail->prev == nullptr) { // Checks if the list is empty
        cout << "The list is empty...\n";
      }else{
        temPtr = tail;          // Sets the temporary pointer
        val = temPtr->data;     // Stores the value we are returning
        tail = tail->prev;      // Sets the new tail of the list
        tail->next = nullptr;   // Resets the end of the list
        delete temPtr;          // Deletes the popped node
        listSize--;
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
     * @return T
     */
    T popAt(int loc) {
      node<T> *traverse = head; // Creates temporary pointer to delete removed node
      T val;               // Creates a variable to store the value of the popped data
      loc = loc + 1;
      if (!head) { // Checks if the list is empty
        // std::cout << "The list is empty...\n";
        return -1;
      }

      if (loc == 1) {
        popFront();
      }else{
        // Traverses list for value
        while (traverse->next != nullptr && counter != loc){ 
          traverse = traverse->next;
          counter++;
        }
        if (traverse == tail) {
          popRear();
        }else{
          traverse = traverse->prev;
          // Stores the value we are returning
          val = traverse->data;                  
          // Sets the previous nodes next pointer to the next node
          traverse->prev->next = traverse->next; 
          // Sets the next nodes previous pointer to the previous node
          traverse->next->prev = traverse->prev; 
          // Deletes the popped node
          delete traverse;                       
          listSize--;
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
     * @param T x - Given data value to look for in list
     * 
     * @return int
     */
    int find(T x) {
      if (!head) { // Checks if the list is empty before traversing
        cout << "The list is empty. \nGo add something.\n";
        return -1;
      }
      node<T>* traverse = head; // Creates a pointer to traverse the list
      // Traverses the list to find the specified value
      while(traverse->next != nullptr && traverse->data != x){ 
        traverse = traverse->next;
        counter++;
      }
      if (traverse == tail) { // Handles non-existent values
        return -1;
      }

      int loc = counter; // Stores the location of the specified 
                         // value into a returnable variable
      counter = 0;       // Resets the counter used in tracking location
      return loc;
    }

    /**
     * @brief Member Function: print
     * 
     * Traverses through the list and outputs the data 
     * value in every node to the output stream 
     * and the output file from left to right
     * 
     * @param N/A
     * 
     * @return void
     */
    void print() const {
      if (!head) { // Checks if the list is empty
        cout << "The list is empty. Go put something in it.\n";
      }else{ // If list is not empty
        node<T>* traverse = head; // Creates a pointer to traverse the list
        cout << '[';
        // Traversers the list and prints out the values
        while(traverse != nullptr){ 
          if (traverse->next == nullptr) {
            std::cout << traverse->data;
            traverse = traverse->next;
          }else{
            std::cout << traverse->data << ',' << " ";
            traverse = traverse->next;
          }
        }
        cout << ']';
        cout << "\n";
        // outFile << ']';
        // outFile << "\n";
      }
    }

    /**
     * @brief Member Function: print
     * 
     * Traverses through the list and outputs the data 
     * value in every node to the output stream
     * and the output file from right to left
     * 
     * @param N/A
     * 
     * @return void
     */
    void printBackwards(ofstream &outFile) const {
      node<T>* traverse = tail; // Creates a pointer to traverse the list
      while(traverse != nullptr) { // Traverses the list
        std::cout << traverse->data << " ";
        outFile << traverse->data << " ";
        traverse = traverse->prev;
      }
      cout << "\n";
      outFile.close();
    }

    int GetSize(){
      return listSize;
    }

    /**
     * @brief Overloaded Operator: []
     * 
     * Allows the doubly linked list vector to be treated as
     * an array.
     * 
     * @param int loc - Index of the element we are looking for
     * 
     * @return T
     */
    T &operator[](int loc){
      if (loc >= listSize) { // Checks if the index exists in the list
        exit(0);
      }

      node<T>* traverse = head; // Creates a pointer to traverse the list
      // Traverses the list to find the specified value
      while(counter != loc && traverse->next != nullptr){ 
        traverse = traverse->next;
        counter++;
      }

      counter = 0; // Resets the counter used in tracking location
      return traverse->data;
    }

     /**
     * @brief Overloaded Operator: <<
     * 
     * Allows the doubly linked list vector to be printed out
     * to the output stream using the stream insertion operator.
     * 
     * @param ostream& cout - The ostream object we are returning to output
     * @param const MyVector& V - The linked list we want to output
     * 
     * @return ostream&
     */
    friend ostream& operator<<(ostream& cout, const MyVector& V){
      cout << fixed << setprecision(2);
      node<T>* traverse = V.head; // Creates a pointer to traverse the list
        cout << '[';
        while(traverse != nullptr){ // Traversers the list and prints out the values
          if (traverse->next == nullptr) {
            std::cout << traverse->data;
            traverse = traverse->next;
          }else{
            std::cout << traverse->data << ',' << " ";
            traverse = traverse->next;
          }
        }
        cout << ']';
        cout << "\n";
      return cout;
    }    
    
     /**
     * @brief Overloaded Operator: <<
     * 
     * Allows the doubly linked list vector to be printed out
     * to the output file using the stream insertion operator.
     * 
     * @param ostream& cout - The ostream object we are returning to output
     * @param const MyVector& V - The linked list we want to output
     * 
     * @return ostream&
     */
    friend ofstream& operator<<(ofstream& cout, const MyVector& V){
      cout << fixed << setprecision(2);
      node<T>* traverse = V.head; // Creates a pointer to traverse the list
        cout << '[';
        // Traversers the list and prints out the values
        while(traverse != nullptr){ 
          if (traverse->next == nullptr) {
            cout << traverse->data;
            traverse = traverse->next;
          }else{
            cout << traverse->data << ',' << " ";
            traverse = traverse->next;
          }
        }
        cout << ']';
        cout << "\n";
      return cout;
    }

     /**
     * @brief Overloaded Operator: =
     * 
     * Allows the doubly linked list vector to have values assigned to it
     * by using the assignment operator instead of our member functions.
     * 
     * @param const MyVector &V - The linked list we  
     *                            want to copy values from
     * 
     * @return MyVector &
     */
    MyVector &operator=(const MyVector &V){
      // Cleans up the list to make a new one
      node<T>* temp = head;
      node<T>* deleteMe;
      while(temp != nullptr){
        deleteMe = temp;
        temp = temp->next;
        delete deleteMe;
      }

      head = tail = NULL; // NULL = zeros
                   // and zeros imply empty
      
      node<T>* tempPtr = V.head;

      // Copies the old list to the newly created list
      for (int i = 0; i < V.listSize; i++) {
        pushRear(tempPtr->data);
        tempPtr = tempPtr->next;
      }
      this->listSize = V.listSize;

      return *this;
    }

     /**
     * @brief Overloaded Operator: +
     * 
     * Allows the doubly linked list vector to have values 
     * assigned to it by using the addition operator to add 
     * two other linked lists together.
     * 
     * @param const MyVector &V - The linked list we want 
     *                            to use for adding values
     * 
     * @return MyVector &
     */
    MyVector operator+(MyVector& other){
      MyVector newVector;
      node<T> *thisTemp = this->head;
      node<T> *otherTemp = other.head;

      // Adds the lists together while
      // compensating for the other list being bigger
      if (this->listSize <= other.listSize){
        while (thisTemp){
          newVector.pushRear(thisTemp->data + otherTemp->data);
          thisTemp = thisTemp->next;
          otherTemp = otherTemp->next;
        }
        while (otherTemp){
          newVector.pushRear(otherTemp->data);
          otherTemp = otherTemp->next;
        }
      }
      // Adds the lists together while compensating for this list being bigger
      else{ 
        while (otherTemp){
          newVector.pushRear(thisTemp->data + otherTemp->data);
          thisTemp = thisTemp->next;
          otherTemp = otherTemp->next;
        }
        while (thisTemp){
          newVector.pushRear(thisTemp->data);
          thisTemp = thisTemp->next;
        }
      }
      
      return newVector;
    }

     /**
     * @brief Overloaded Operator: -
     * 
     * Allows the doubly linked list vector to have values assigned to it
     * by using the subtraction operator to subtract two 
     * other linked lists together.
     * 
     * @param const MyVector &V - The linked list we want 
     *                            to use for subtracting values
     * 
     * @return MyVector &
     */
    MyVector operator-(MyVector& other){
      MyVector newVector;
      node<T> *thisTemp = this->head;
      node<T> *otherTemp = other.head;

      // Subtracts the lists together while
      // compensating for the other list being bigger
      if (this->listSize <= other.listSize){
        while (thisTemp){
          newVector.pushRear(thisTemp->data - otherTemp->data);
          thisTemp = thisTemp->next;
          otherTemp = otherTemp->next;
        }
        while (otherTemp){
          newVector.pushRear(otherTemp->data);
          otherTemp = otherTemp->next;
        }
      }
      // Subtracts the lists together while 
      // compensating for this list being bigger
      else{
        while (otherTemp){
          newVector.pushRear(thisTemp->data - otherTemp->data);
          thisTemp = thisTemp->next;
          otherTemp = otherTemp->next;
        }
        while (thisTemp){
          newVector.pushRear(thisTemp->data);
          thisTemp = thisTemp->next;
        }
      }
      
      return newVector;
    }

     /**
     * @brief Overloaded Operator: /
     * 
     * Allows the doubly linked list vector to have values assigned to it
     * by using the division operator to divided two 
     * other linked lists together.
     * 
     * @param const MyVector &V - The linked list we want 
     *                            to use for dividing values
     * 
     * @return MyVector &
     */
    MyVector operator/(MyVector& other){
      MyVector newVector;
      node<T> *thisTemp = this->head;
      node<T> *otherTemp = other.head;

      // Divides the lists together while
      // compensating for the other list being bigger
      if (this->listSize <= other.listSize){
        while (thisTemp){
          if (otherTemp->data == 0){
            cout << "Error, can't divide by zero...\n";
          }else{
            newVector.pushRear(thisTemp->data / otherTemp->data);
            thisTemp = thisTemp->next;
            otherTemp = otherTemp->next;
          }
        }
        while (otherTemp){
          newVector.pushRear(otherTemp->data);
          otherTemp = otherTemp->next;
        }
      }
      // Divides the lists together while 
      // compensating for this list being bigger
      else{
        while (otherTemp){
          if (otherTemp->data == 0){
            cout << "Error, can't divide by zero...\n";
          }else{
            newVector.pushRear(thisTemp->data / otherTemp->data);
            thisTemp = thisTemp->next;
            otherTemp = otherTemp->next;
          }
        }
        while (thisTemp){
          newVector.pushRear(thisTemp->data);
          thisTemp = thisTemp->next;
        }
      }
      
      return newVector;
    }

     /**
     * @brief Overloaded Operator: *
     * 
     * Allows the doubly linked list vector to have values assigned to it
     * by using the multiplication operator to multiply two 
     * other linked lists together.
     * 
     * @param const MyVector &V - The linked list we want 
     *                            to use for multiplying values
     * 
     * @return MyVector &
     */
    MyVector operator*(MyVector& other){
      MyVector newVector;
      node<T> *thisTemp = this->head;
      node<T> *otherTemp = other.head;

      // Mulitplies the lists together while
      // compensating for the other list being bigger
      if (this->listSize <= other.listSize){
        while (thisTemp){
          newVector.pushRear(thisTemp->data * otherTemp->data);
          thisTemp = thisTemp->next;
          otherTemp = otherTemp->next;
        }
        while (otherTemp){
          newVector.pushRear(otherTemp->data);
          otherTemp = otherTemp->next;
        }
      }
      // Multiplies the lists together while 
      // compensating for this list being bigger
      else{
        while (otherTemp){
          newVector.pushRear(thisTemp->data * otherTemp->data);
          thisTemp = thisTemp->next;
          otherTemp = otherTemp->next;
        }
        while (thisTemp){
          newVector.pushRear(thisTemp->data);
          thisTemp = thisTemp->next;
        }
      }
      
      return newVector;
    }

     /**
     * @brief Overloaded Operator: ==
     * 
     * Allows the equal to operator to check if two linked list vectors 
     * are equal to each other
     * 
     * @param const MyVector &V - The linked list we want 
     *                            to use for checking values
     * 
     * @return MyVector &
     */
    bool operator==(const MyVector& other){
      node<T> *thisTemp = this->head;
      node<T> *otherTemp = other.head;
      // Checks if the lists are even the same size first
      if (this->listSize != other.listSize){
        return false;
      }else{
        // Checks if all of the values match each other
        while (thisTemp){
          if (thisTemp->data != otherTemp->data){
            return false;
          }
          thisTemp = thisTemp->next;
          otherTemp = otherTemp->next;
        }
      }
      return true;      
    }
};

int main() {

  ofstream outFile("test.out");
  outFile << "2143\n"
          << "P02\n"
          << "Kolten Pulliam\n\n";

  int a1[] = { 1, 2, 3, 4, 5 };
  int a2[] = { 10, 20, 30 };
  int arrSize1 = (sizeof(a1)/sizeof(0)); // Finds the size of the array
  MyVector<int> v1(a1, arrSize1);
  int arrSize2 = (sizeof(a2)/sizeof(0)); // Finds the size of the array
  MyVector<int> v2(a2, arrSize2);

  // ofstream fout;
  // fout.open("output.txt");

  cout << v1[2] << endl;
  outFile << v1[2] << endl;
  // writes out 3

  v1[4] = 9;
  // v1 now = [1,2,3,4,9]

  cout << v1 << endl;
  // writes out [1,2,3,4,9]` to console.
  outFile << v1 << endl;
  // writes out [1,2,3,4,9]` to your output file.

  MyVector<int> v3 = v1 - v2;
  cout << v3 << endl;
  // writes out [11,22,33,4,9]` to console.
  outFile << v3 << endl;  
  // writes out [11,22,33,4,9]` to outfile.

  v3 = v1 - v2;
  cout << v3 << endl;
  // writes out [-9,-18,-27,4,9]` to console.
  outFile << v3 << endl;
  // writes out [-9,-18,-27,4,9]` to outfile.  

  v3 = v2 - v1;
  cout << v3 << endl;
  // writes out [9,18,27,4,9]` to console.
  outFile << v3 << endl;
  // writes out [9,18,27,4,9]` to outfile.

  v3 = v2 * v1;
  cout << v3 << endl;
  // writes out [10,40,90,4,9]` to console.
  outFile << v3 << endl;
  // writes out [10,40,90,4,9]` to outfile.

  v3 = v1 * v2;
  cout << v3 << endl;
  // writes out [10,40,90,4,9]` to console.
  outFile << v3 << endl;
  // writes out [10,40,90,4,9]` to outfile.

  v3 = v1 / v2;
  cout << v3 << endl;
  // writes out [0,0,0,4,9]` to console.
  outFile << v3 << endl;
  // writes out [0,0,0,4,9]` to outfile.

  v3 = v2 / v1;
  cout << v3 << endl;
  // writes out [10,10,10,4,9]` to console.
  outFile << v3 << endl;
  // writes out [10,10,10,4,9]` to outfile.  

  cout << (v2 == v1) << endl;
  // writes 0 to console (false).
  outFile << (v2 == v1) << endl;
  // writes 0 to outfile (false).

  MyVector v4 = v1;
  cout << (v4 == v1);
  // writes 1 to console (true).
  outFile << (v4 == v1);
  // writes 1 to outfile (true).

  outFile.close();
  return 0;
}