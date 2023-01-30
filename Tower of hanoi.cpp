//Tower of hanoi in c++

//Tower of Hanoi is a mathematical puzzle where we have three rods and n disks. The objective of the puzzle is to move the entire stack to another rod, obeying the following simple rules:
//1. Only one disk can be moved at a time.
//2. Each move consists of taking the upper disk from one of the stacks and placing it on top of another stack i.e. a disk can only be moved if it is the uppermost disk on a stack.
//3. No disk may be placed on top of a smaller disk.

//There are only 3 rods "A", "B" and "C", you need to move all the disks from rod "A" to rod "C" and print out the minimum moved step counts
//Note: You must use your own "Stack" class, no recursive function can be used and no formula like 2^N-1 can be used, or you will get up to 0 points.
//Please do two version for this assignment, one in C++ another in C.

//Input
//The number of the disks on the rod "A", ends up with line-break or end-of-file.
//2
//3
//4
//5
//6

//Output
//The minimum number of moves required, ending with a "\n" of each line
//3
//7
//15
//31
//63

#include <iostream>
#include <cstdlib>
using namespace std;

template<class T>
class Node
{
public:
  Node():prev(NULL),next(NULL),data(NULL) {}
  Node(T data):prev(NULL),next(NULL),data(data) {}
  Node(T data, Node<T> *prev, Node<T> *next):prev(prev),next(next),data(data) {}
  Node<T> *prev;
  Node<T> *next;
  T data;
};

template<class T>
class LinkedList
{
public:
  LinkedList():head(NULL),tail(NULL) {}

  void addToHead(T data)
  {
    Node<T> *newNode = new Node<T>(data);

    if(head == NULL)
    {
      head = newNode;
      tail = newNode;
    }
    else
    {
      newNode -> next = head;
      head -> prev = newNode;
      head = newNode;
    }
  }

  void addToTail(T data)
  {
    Node<T> *newNode = new Node<T>(data);

    if(tail == NULL)
    {
      tail = newNode;
      head = newNode;
    }
    else
    {
      newNode -> prev = tail;
      tail -> next = newNode;
      tail = newNode;
    }
  }

  Node<T> *exist(T data)
  {
    Node<T> *cur = head;
    while(cur != NULL)
    {
      if(cur -> data == data)
        return cur;
      cur = cur -> next;
    }
    return NULL;
  }

  void deleteHead()
  {
    head = head -> next;
    head -> prev = NULL;
  }

  void deleteTail()
  {
    tail = tail -> prev;
    tail -> next = NULL;
  }

  void deleteData(T data)
  {
    Node<T> *node = exist(data);
    if(node == head && node == tail)
    {
      head = NULL;
      tail = NULL;
      return;
    }
    if(node == head)
      return deleteHead();
    if(node == tail)
      return deleteTail();
    if(node != NULL)
    {
      node -> prev -> next = node -> next;
      node -> next -> prev = node -> prev;
    }
    delete(node);
  }

  void deleteData(T data, int n)
  {
    for(int i = 0; i < n; i++)
      deleteData(data);
  }

  Node<T> *operator[](int n)
  {
    Node<T> *cur = head;
    for(int i = 0; i < n; i++)
      cur = cur -> next;
    return cur;
  }

  friend ostream &operator<<(ostream &out, LinkedList *n)
  {
    if(n -> head == NULL)
      return out << "\n";
    out << "(";
    int index = 0;
    while((*n)[index] -> next != NULL)
    {
      out << (*n)[index] -> data << ", ";
      index++;
    }
    out << (*n)[index] -> data << ")" << "\n";
    return out;
  }

  Node<T> *head;
  Node<T> *tail;
};

template<class T>
class Stack
{
public:
  Stack():list(new LinkedList<T>()) {}

  void push(T data) {list -> addToHead(data);}

  T pop()
  {
    if(!isEmpty())
    {
      T temp = top();
      list -> deleteData(temp);
      return temp;
    }
  }

  T top() {return list -> head -> data;}

  bool isEmpty() {return (list -> head == NULL) ? true : false;}

  int size()
  {
    int size = 0;
    while((*list)[size] != NULL)
      size++;
    return size;
  }

  void show() {cout << list;}

private:
    LinkedList<T> *list;
};

template<class T>
class Hanoi
{
public:
  Hanoi():rodA(new Stack<T>()),rodB(new Stack<T>()),rodC(new Stack<T>()),num(0) {}

  Hanoi(int num):rodA(new Stack<T>()),rodB(new Stack<T>()),rodC(new Stack<T>()),num(num)
  {
    for(int i = num; i > 0; i--)
      rodA -> push(i);
  }

  void AtoB() {rodB -> push(rodA -> pop());}
  void BtoC() {rodC -> push(rodB -> pop());}
  void CtoA() {rodA -> push(rodC -> pop());}
  void AtoC() {rodC -> push(rodA -> pop());}
  void CtoB() {rodB -> push(rodC -> pop());}
  void BtoA() {rodA -> push(rodB -> pop());}

  Stack<T> *find(T data)
  {
    if(!rodA -> isEmpty())
      if(rodA -> top() == data)
        return rodA;
    if(!rodB -> isEmpty())
      if(rodB -> top() == data)
        return rodB;
    if(!rodC -> isEmpty())
        if(rodC -> top() == data)
            return rodC;
    return NULL;
  }

  void clockwise(Stack<T> *disk)
  {
    if(disk == rodA)
      return AtoB();
    if(disk == rodB)
      return BtoC();
    if(disk == rodC)
      return CtoA();
  }

  void counterclockwise(Stack<T> *disk)
  {
    if(disk == rodA)
      return AtoC();
    if(disk == rodB)
      return BtoA();
    if(disk == rodC)
      return CtoB();
  }

  int evendisk()
  {
    int step = 0, count, disk;
    while(rodC -> size() != num)  //continue untill all discs on rodC
    {
      step++;
      if(step % 2 == 1)  //checking the step is even or odd.
        clockwise(find(1)); //if odd call find function on clockwise
      else //if its even 
      {
        count = step;  
        disk = 0;
        while(1) //then this loop continues until the step becomes odd 
        {
          count/=2;
          disk++;
          if(count % 2 == 1)
            break;
        }
        disk++; //after break increment the disc by 1 
        if(disk % 2 == 1)  //checks if disc is odd. if then do clockwise
          clockwise(find(disk));
        else
          counterclockwise(find(disk)); //if even do the counterclockwise 
      }
    }
    return step;
  }

  int odddisk()
  {
    int step = 0, count, disk;
    while(rodC -> size() != num)
    {
      step++;
      if(step % 2 == 1)
        clockwise(find(1));
      else
      {
        count = step;
        disk = 0;
        while(1)
        {
          count/=2;
          disk++;
          if(count % 2 == 1)
            break;
        }
        disk++;
        if(disk % 2 == 1)
          counterclockwise(find(disk));
        else
          clockwise(find(disk));
      }
    }
    return step;
  }

  void show()
  {
    printf("rodA: ");
    rodA -> show();
    printf("rodB: ");
    rodB -> show();
    printf("rodC: ");
    rodC -> show();
  }

private:
  Stack<T> *rodA;
  Stack<T> *rodB;
  Stack<T> *rodC;
  int num;
};

int main()
{
  int input;
  while(cin >> input)
  {
    Hanoi<int> *hanoi = new Hanoi<int>(input);
    //hanoi -> show();

    if(input % 2 == 0)
      cout << hanoi -> evendisk() << endl;
    else
      cout << hanoi -> odddisk() << endl;
  }
}
