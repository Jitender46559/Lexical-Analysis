#include <iostream>
#include <string>
#include <fstream>
//Raymond Jones
using namespace std;
// Node Class for Linked List
//Class for Stack
class Stack
{
private:
  struct Item
  {
  string name;
  Item* prev;
    };
  Item* stackPtr;
  string name;

  Stack* prev;
//Creating Stack Pointer stackPtr
public:
    void Push(string name);
    void Pop();
    void getWord();
    string top();
    void readItem(Item* r);
    void Print();
    int size();
    Stack();
    ~Stack();

};
