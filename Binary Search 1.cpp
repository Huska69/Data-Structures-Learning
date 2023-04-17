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
      return out;
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
class Queue
{
public:
  Queue():list(new LinkedList<T>()) {}

  void enqueue(T data) {list -> addToTail(data);}

  T dequeue() 
  {     
    if(!isEmpty())
    {
      T temp = front();
      list -> deleteData(temp);
      return temp;
    }  
  }

  T front() {return list -> head -> data;}

  bool isEmpty() {return (list -> head == NULL) ? true : false;}

  void  show() {cout << list;}

private:
    LinkedList<T> *list;
};

template<class T>
class TreeNode 
{
  public: 
    TreeNode():left(NULL), right(NULL) {}
    TreeNode(T data):left(NULL), right(NULL), data(data) {}
    T D() {return data;}
    TreeNode<T> *L() {return left;}
    TreeNode<T> *R() {return right;}
    void setD(T D) {data = D;}
    void setL(TreeNode<T> *node) {left = node;}
    void setR(TreeNode<T> *node) {right = node;}
  private:
    T data;
    TreeNode<T> *left;
    TreeNode<T> *right;
};

template<class T>
class binarySearchTree 
{
  public:
    virtual void preorder() = 0;
    virtual void inorder() = 0;
    virtual void postorder() = 0;
    virtual void levelorder() = 0;
    virtual bool insert(T data) = 0;
    virtual void setRoot(T data) = 0;
    virtual bool serach(T target) = 0;
  protected:
    TreeNode<T> *root;
};

template<class T>
class BinarySearchTree:public binarySearchTree<T> 
{
  public:
    BinarySearchTree() {this -> root = NULL;}
    TreeNode <T> *Root() {return this -> root;}

    void preorder() 
    {
      Preorder(this -> root);
      cout << endl; 
    }
    void Preorder(TreeNode<T> *parent) 
    {
      if(parent != NULL)
      {
        if(parent != this -> root)
          cout << ",";
        cout << parent -> D();
        Preorder(parent -> L());
        Preorder(parent -> R());
      }
    }

    void inorder() 
    {
      Inorder(this -> root);
      cout << endl; 
    }
    void Inorder(TreeNode<T> *parent) 
    {
      static int size = 0;
      if(parent != NULL)
      {        
        Inorder(parent -> L());
        /*
        if(!size++)
          cout << parent -> D(); 
        else
          cout << "," << parent -> D();
        */
        (!size++) ? cout << parent -> D() : cout << "," << parent -> D();
        Inorder(parent -> R());
      }
    }

    void postorder() 
    {
      Postorder(this -> root);
      cout << endl; 
    }
    void Postorder(TreeNode<T> *parent) 
    {
      if(parent != NULL)
      {
        Postorder(parent -> L());
        Postorder(parent -> R());
        cout << parent -> D();
        if(parent != this -> root)
          cout << ",";  
      }
    }

    void levelorder() 
    {
      Levelorder(this -> root); 
      cout << endl;
    }
    void Levelorder(TreeNode<T> *parent) 
    {
      Queue<TreeNode<T>*> q;  //creating empty queue
      q.enqueue(parent);   //enqueue the parent to be analyzed. //also comes with all children
      while(!q.isEmpty())  //iterates through every node in the queue until there is no nodes left. 
      {
        TreeNode<T> *cur = q.dequeue();
        if(cur != this -> root) //If the current node is not equal to this->root, then it prints out ","
          cout << ",";      
        cout << cur -> D(); //and it will prints out the current value to D()
        if(cur -> L())   
          q.enqueue(cur -> L());  
        if(cur -> R())
          q.enqueue(cur -> R());  
      }
    }

    bool insert(T data) 
    {
      TreeNode<T> *cur = this -> root;
      TreeNode<T> *parent = NULL;
      while(cur != NULL)
      {
        parent = cur;
        if(data == cur -> D())
          return false;
        if(data < cur -> D())
          cur = cur -> L();
        else
          cur = cur -> R();
      }
      if(data < parent -> D())
        parent -> setL(new TreeNode<T>(data));
      if(data > parent -> D())
        parent -> setR(new TreeNode<T>(data));
      return true;
    }

    void setRoot(T data) 
    {
      if(!this -> root)
        this -> root = new TreeNode<T> (data);
    }

    bool serach(T target) 
    {
      TreeNode<T> *cur = this -> root;
      while(cur)
      {
        if(target == cur -> D())
          return true;
        if(target < cur -> D())
          cur = cur -> L();
        if(target > cur -> D())
          cur = cur -> R();
      }
      return false;
    }
};
