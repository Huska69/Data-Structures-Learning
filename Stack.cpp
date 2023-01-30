//Stack C++
//a class "Stack" by the class "LinkedList" 


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
      list -> head = list -> head -> next;
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
  
private: 
    LinkedList<T> *list;
};
