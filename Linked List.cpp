//Linked List C++

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
    Node<T> *cur = head, *cur2;
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
    if (head == NULL)
      return;

    if (head->next != NULL)
    {
      Node <T> *cur = head;
      head = head->next;
      delete(cur);  
      head->prev = NULL;
    }
    else
    {
      head = NULL; 
      tail = NULL;
    }
}


  void deleteTail() 
  {
    if (tail == NULL)
      return; 
    if (tail->prev != NULL)
    {
      Node <T> *cur = tail; 
      tail = tail -> prev; 
      delete(cur);
      tail-> next = NULL;
    }
    else 
    {
      head = NULL;
      tail = NULL;
    }
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
    if (cur != NULL) {
    for(int i = 0; i < n; i++)
      cur = cur -> next;
    return cur;}
    else
    {
      return NULL;
    }
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
