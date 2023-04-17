#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <ctime>
using namespace std;

template<class T>
class Node_Q {
  public:

  Node_Q()
  {
  	this -> prev = NULL;
    this -> next = NULL;
  }

  Node_Q(T data)
  {
    this -> data = data;
    this -> prev = NULL;
    this -> next = NULL;
  }

  Node_Q(T data, Node_Q<T> *prev, Node_Q<T> *next)
  {
  	this -> data = data;
    this -> prev = prev;
    this -> next = next;
  }
  Node_Q<T> *getPrev(){return this -> prev;}
  Node_Q<T> *getNext(){return this -> next;}
  T getData(){return this -> data;}
  void setPrev(Node_Q<T> *prev){this -> prev = prev;}
  void setNext(Node_Q<T> *next){this -> next = next;}
  void setData(T data){this -> data = data;}
  private:
    Node_Q<T> *prev;
    Node_Q<T> *next;
    T data;
};

template<class T>
class LinkedList_Q {
  public:

  LinkedList_Q()
  {
  	this -> head = NULL;
    this -> tail = NULL;
  }

  void newlink(T data)
  {
    Node_Q<T> *add = new Node_Q<T>(data, NULL, NULL);
    head = add;
    tail = add;
  }

  void addToTail(T data)
  {
  	if(tail == NULL)	//linkedlistis empty
  	{
  	    newlink(data);
  	}
    else
    {
      Node_Q<T> *add = new Node_Q<T>(data, tail, NULL);
      tail -> setNext(add);
      tail = tail -> getNext();
    }
    //this -> print();
  }

  void addToHead(T data)
  {
    if(head == NULL)	//linkedlistis empty
    {
        newlink(data);
    }
    else
    {
      Node_Q<T> *add = new Node_Q<T>(data, NULL, head);
      head -> setPrev(add);
      head = add;
    }
  }

  void deleteData(T data)
  {
  	Node_Q<T> *j = head;
    while(j)
    {
      if(j -> getData() == data)
      {
        if(j == head && j == tail)
        {
            head = NULL;
            tail = NULL;
        }
        else if(j == head)	//remove head
        {
          head = j -> getNext();
          if(j -> getNext())
            j -> getNext() -> setPrev(NULL);
          j -> setNext(NULL);
        }
        else if(j == tail)	//remove tail
        {
          tail = j -> getPrev();
          if(j -> getPrev())
            j -> getPrev() -> setNext(NULL);
          j -> setPrev(NULL);
        }
        else	//remove middle node
        {
          j -> getPrev() -> setNext(j -> getNext());
          j -> getNext() -> setPrev(j -> getPrev());
          j -> setPrev(NULL);
          j -> setNext(NULL);
        }
        break;
      }
      j = j -> getNext();
    }
  }

  void deleteData(T data, int n)
  {
    for(int i = 0;i < n;i ++)
    {
        deleteData(data);
    }
  }

  T removeFromHead()
  {
      T re = head -> getData();
      deleteData(re);
      return re;
  }

  Node_Q<T> *getHead() {return this -> head;}
  Node_Q<T> *getTail() {return this -> tail;}
  void setHead(Node_Q<T> *head) {this -> head = head;}
  void setTail(Node_Q<T> *tail) {this -> tail = tail;}

  private:
    Node_Q<T> *head;
    Node_Q<T> *tail;
};

template<class T>
class Queue
{
  public:

  Queue()
  {
    list = new LinkedList_Q<T>();
  }

  void enqueue(T data)
  {
    list -> addToTail(data);
  }

  T dequeue()
  {
    if(isEmpty())
        return NULL;
    return list -> removeFromHead();
  }

  T front()
  {
    return list -> getHead() -> getData();
  }

  bool isEmpty()
  {
    return list -> getHead() == NULL;
  }
  LinkedList_Q<T> *getLinkedList() {return list;}
  private:
    LinkedList_Q<T> *list;
};

template<class T>
class Node
{
public:
	Node()
	{
		data = new T;
	}
	Node(T d)
	{
		data = new T;
		(*data) = d;
	}
	Node &operator=(T d)
	{
		(*data) = d;
		return *this;
	}
	friend std::ostream &operator<<(std::ostream &out, Node n)
	{
		out<<*(n.data);
		return out;
	}
	friend std::ostream &operator<<(std::ostream &out, Node *n)
	{
		out<<*(n->data);
		return out;
	}
	void setData(T d)
	{
		*data = d;
	}
	T &getData() const
	{
		return *data;
	}
protected:
	T *data;
};

template<class T>
class ListNode : public Node<T>
{
public:
	ListNode() : Node<T>()
	{
		prev = NULL;
		next = NULL;
	}
	ListNode(T d) : Node<T>(d)
	{
		prev = NULL;
		next = NULL;
	}
	ListNode(ListNode *p, ListNode *n) : Node<T>()
	{
		prev = p;
		next = n;
	}
	ListNode(T d, ListNode *p, ListNode *n) : Node<T>(d)
	{
		prev = p;
		next = n;
	}
	ListNode *getNext() const
	{
		return next;
	}
	ListNode *getPrev() const
	{
		return prev;
	}
	void setNext(ListNode *n)
	{
		next = n;
	}
	void setPrev(ListNode *p)
	{
		prev = p;
	}
	ListNode &operator=(T d)
	{
		this->setData(d);
		return *this;
	}
private:
	ListNode *prev, *next;
};

template<class T>
class LinkList
{
public:
	LinkList()
	{
		head = NULL;
		tail = NULL;
	}
	void addFromHead(T d)
	{
		ListNode<T> *node = new ListNode<T>(d);
		if(head != NULL)
		{
			head->setPrev(node);
		}
		node->setNext(head);
		head = node;
		if(tail == NULL)
			tail = node;
	}
	void addFromTail(T d)
	{
		ListNode<T> *node = new ListNode<T>(d);
		if(tail != NULL)
		{
			tail->setNext(node);
		}
		node->setPrev(tail);
		tail = node;
		if(head == NULL)
			head = node;
	}
	void addAfter(ListNode<T> *at, T d)
	{
		if(!exist(at))
			return;
		ListNode<T> *node = new ListNode<T>(d);
		if(at->getNext() != NULL)
			at->getNext()->setPrev(node);
		node->setNext(at->getNext());
		at->setNext(node);
		node->setPrev(at);
		if(node->getNext() == NULL)
			tail = node;
	}
	ListNode<T> *removeFromHead()
	{
		ListNode<T> *n = head;
		if(head != NULL)
		{
			head = head->getNext();
			if(head != NULL)
				head->setPrev(NULL);
			else
				tail = NULL;
			n->setNext(NULL);
		}
		return n;
	}
	ListNode<T> *removeFromTail()
	{
		ListNode<T> *n = tail;
		if(tail != NULL)
		{
			tail = tail->getPrev();
			if(tail != NULL)
				tail->setNext(NULL);
			else
				head = NULL;
			n->setPrev(NULL);
		}
		return n;
	}
	ListNode<T> *remove(ListNode<T> *n)
	{
		if(!exist(n))
			return NULL;
		if(n == head)
			return removeFromHead();
		if(n == tail)
			return removeFromTail();
		n->getPrev()->setNext(n->getNext());
		n->getNext()->setPrev(n->getPrev());
		n->setNext(NULL);
		n->setPrev(NULL);
		return n;
	}
	ListNode<T> *exist(T d)
	{
		ListNode<T> *j = head;
		while(j != NULL)
		{
			if(j->getData() == d)
				return j;
			j = j->getNext();
		}
		return NULL;
	}
	bool exist(ListNode<T> *n)
	{
		ListNode<T> *j = head;
		while(j != NULL)
		{
			if(j == n)
				return true;
			j = j->getNext();
		}
		return false;
	}
	ListNode<T> &operator[](int i)
	{
		ListNode<T> *j = head;
		int k;
		for(k = 0;k < i && j != NULL;k ++)
			j = j->getNext();
		if(j == NULL)
			throw std::invalid_argument("index does not exist.");
		return *j;
	}
	void print() const
	{
		ListNode<T> *j;
		j = head;
		while(j != NULL)
		{
			std::cout<<(*j)<<" ";
			j = j->getNext();
		}
		std::cout<<std::endl;
	}
	ListNode<T>* getHead() {return this->head;}
protected:
	ListNode<T> *head, *tail;
};

/*
	Please finish the TreeNode class, TreeNode class respresent a node in a general tree.
	A general tree is different from binary tree, every node in binary tree have at most two child node, but a node in general tree may have more than two child node.
*/
template<class T>
class TreeNode : public Node<T>
{
public:
	TreeNode() : Node<T>()
	{
        this -> child = new LinkList<TreeNode<T>*>;
        size = 0;
	}
	TreeNode(T d) : Node<T>(d)
	{
	    this -> child = new LinkList<TreeNode<T>*>;
	    size = 0;
	}
	/*
		Add a child to this node.
	*/
	void addChild(TreeNode *n)
	{
        this -> child -> addFromTail(n);
        size ++;
	}
	/*
		Add a child to this node.
	*/
	void addChild(T d)
	{
	    TreeNode<T> *newNode = new TreeNode<T>(d);
	    this -> child -> addFromTail(newNode);
	    size ++;
	}
	/*
		Return the nth child of the node.
	*/
	TreeNode<T> *operator[](int n)
	{

        return (*(this -> child))[n].getData();
	}

	int getSize()
	{
	    return this -> size;
	}

	LinkList<TreeNode<T>*> *getChild() { return this -> child; }


private:
	LinkList<TreeNode<T> *> *child;
	int size;
};

/*
	Please finish the Tree class. Tree class respresent a general tree, that means node on this tree may have more than two child node.

*/
template<class T>
class Tree
{
public:
	Tree()
	{
        this->root = NULL;

	}
	/*
		return the nth node on this tree with level order.
	*/
	TreeNode<T> *operator[](int n)
	{
        if(this -> root == NULL)
            return NULL;
	    Queue<TreeNode<T>*> tmp;
        tmp.enqueue(this -> root);
        int index = 0;
        while(index != n && !tmp.isEmpty())
        {
            TreeNode<T> *j = tmp.dequeue();
            for(int i = 0;i < j -> getSize();i ++)
                tmp.enqueue((*j)[i]);
            index ++;
        }
        if(tmp.isEmpty())
            return NULL;
        else
            return tmp.dequeue();
	}
	/*
		return the number of nodes on this tree.
	*/
	int count()
	{
        if(this -> root == NULL)
            return 0;
        return treeSize(this -> root);
	}
	/*
		print all the node on this tree with level order.
	*/
	void levelOrder()
	{
	    Queue<TreeNode<T>*> tmp;
        tmp.enqueue(this -> root);
        while(!tmp.isEmpty())
        {
            TreeNode<T> *j = tmp.dequeue();
            cout << j -> getData() << " ";
            for(int i = 0;i < j ->getSize();i ++)
                tmp.enqueue((*j)[i]);
        }
        cout << endl;
	}
	/*
		print all the node on this tree with preorder.
	*/
	void preorder()
	{
	    pre(this -> root);
        cout << endl;
	}
	/*
		print all the node on this tree with postorder.
	*/
	void postorder()
	{
	    post(this -> root);
        cout << endl;
	}
	/*
		set the root of this tree.
	*/
	void setRoot(T d)
	{
	    TreeNode<T> *newNode = new TreeNode<T>(d);
	    root = newNode;
	}

	TreeNode<T> *getRoot() {return this->root;}
private:
	TreeNode<T> *root;

	int treeSize(TreeNode<T>* head)
	{
        int cou = 0;
        for(int i = 0;i < head ->getSize();i ++)
            cou += treeSize((*head)[i]);
        return cou + 1;
	}

	void pre(TreeNode<T> *root)
	{
	    if(root == NULL)
            return;
        cout << root -> getData() << " ";
        for(int i = 0;i < root ->getSize();i ++)
            pre((*root)[i]);
	}

	void post(TreeNode<T> *root)
	{
	    if(root == NULL)
            return;
        for(int i = 0;i < root ->getSize();i ++)
            post((*root)[i]);
        cout << root -> getData() << " ";
	}
};

template<class T>
class BinaryTreeNode : public Node<T>
{
public:
	BinaryTreeNode() : Node<T>()
	{
		left = NULL;
		right = NULL;
	}
	BinaryTreeNode(T d) : Node<T>(d)
	{
		left = NULL;
		right = NULL;
	}
	BinaryTreeNode(TreeNode<T> d) : Node<T>(d.getData())
	{
		left = NULL;
		right = NULL;
	}
	BinaryTreeNode(BinaryTreeNode<T> *l, BinaryTreeNode<T> *r) : Node<T>()
	{
		left = l;
		right = r;
	}
	BinaryTreeNode(T d, BinaryTreeNode<T> *l, BinaryTreeNode<T> *r) : Node<T>(d)
	{
		left = l;
		right = r;
	}
	void setLeft(BinaryTreeNode<T> *l)
	{
		left = l;
	}
	void setRight(BinaryTreeNode<T> *r)
	{
		right = r;
	}
	BinaryTreeNode<T> *&getLeft()
	{
		return left;
	}
	BinaryTreeNode<T> *&getRight()
	{
		return right;
	}
	bool operator>(BinaryTreeNode<T> n)
	{
		if(*(this->data) > *(n.data))
			return true;
		return false;
	}
	bool operator==(BinaryTreeNode<T> n)
	{
		if(*(this->data) == *(n.data))
			return true;
		return false;
	}
private:
	BinaryTreeNode<T> *left, *right;
};

template<class T>
class BinaryTree
{
public:
	BinaryTree()
	{
		root = NULL;
		count = 0;
	}

	BinaryTree(T d)
	{
		root = new BinaryTreeNode<T>(d);
		count = 1;
	}

	/*
		Convert a general tree to sibling tree
	*/

	static BinaryTreeNode<T>* convert(TreeNode<T> *node)
	{
	    if(node == NULL)
            return NULL;
        BinaryTreeNode<T>* re = new BinaryTreeNode<T>(node->getData());
        if(node->getChild()->getHead() != NULL)
            re->setLeft(convert(node->getChild()->getHead()->getData()));
        else
            re->setLeft(NULL);
        BinaryTreeNode<T>* j = re->getLeft();
        ListNode<TreeNode<T>*>* tmp = node->getChild()->getHead();
        while(tmp && tmp->getNext())
        {
            tmp = tmp->getNext();
            j->setRight(convert(tmp->getData()));
            j = j->getRight();
        }
	    if(j != NULL)
            j->setRight(NULL);
        return re;
	}

	static BinaryTree<T> *convertFromGeneralTree(Tree<T> *tree)
	{
	    BinaryTree<T>* re = new BinaryTree<T>(tree->getRoot()->getData());
	    re->root = convert(&tree->getRoot()[0]);
	    return re;
	}
	virtual BinaryTreeNode<T> *insert(T d)
	{
		BinaryTreeNode<T> *node = new BinaryTreeNode<T>(d);
		if(root == NULL)
		{
			root = node;
		}
		else //starts searching correct position.
		{
			int j = count + 1;
			int k = 1;
			BinaryTreeNode<T> *cur = root;
			while(k <= j)
				k = k << 1;
			k = k >> 2;
			while(k > 1)
			{
				if(k & j)
					cur = cur->getRight();
				else
					cur = cur->getLeft();
				k = k >> 1;
			}
			if(k & j)
				cur->setRight(node);
			else
				cur->setLeft(node);
		}
		count ++;
		return NULL;
	}
	BinaryTreeNode<T> *remove(BinaryTreeNode<T> *n)
	{
		if(!exist(n))
			return NULL;
		BinaryTreeNode<T> *last = getLast();
		if(last == root)
		{
			count --;
			root = NULL;
			return n;
		}
		BinaryTreeNode<T> *lastsFather = getFather(last);
		if(lastsFather->getLeft() == last)
			lastsFather->setLeft(NULL);
		else
			lastsFather->setRight(NULL);
		if(last == n)
		{
			count --;
			return n;
		}
		if(n != root)
		{
			BinaryTreeNode<T> *father = getFather(n);
			if(father->getLeft() == n)
				father->setLeft(last);
			else
				father->setRight(last);
		}
		else
		{
			root = last;
		}
		last->setLeft(n->getLeft());
		last->setRight(n->getRight());
		n->setLeft(NULL);
		n->setRight(NULL);
		count --;
		return n;
	}
	BinaryTreeNode<T> *getFather(BinaryTreeNode<T> *n)
	{
		if(n == root || !exist(n))
			return NULL;
		return _getFather(root, n);
	}
	bool exist(BinaryTreeNode<T> *n)
	{
		return _exist(root, n);
	}
	BinaryTreeNode<T> *getRoot()
	{
		return root;
	}
	void print()
	{
		_print(root, 0);
	}
	void swapNode(BinaryTreeNode<T> *node1, BinaryTreeNode<T> *node2)
	{
	    if(!exist(node1) || !exist(node2))
            return;
        BinaryTreeNode<T> *father1 = getFather(node1);
        BinaryTreeNode<T> *father2 = getFather(node2);
        if(father1 != NULL)
            if(father1->getLeft() == node1)
                father1->setLeft(node2);
            else
                father1->setRight(node2);
        else
            root = node2;
        if(father2 != NULL)
            if(father2->getLeft() == node2)
                father2->setLeft(node1);
            else
                father2->setRight(node1);
        else
            root = node1;
        BinaryTreeNode<T> *node1L = node1->getLeft();
        BinaryTreeNode<T> *node1R = node1->getRight();
        BinaryTreeNode<T> *node2L = node2->getLeft();
        BinaryTreeNode<T> *node2R = node2->getRight();
        node1->setLeft(node2L);
        node1->setRight(node2R);
        node2->setLeft(node1L);
        node2->setRight(node1R);
	}
protected:
	BinaryTreeNode<T> *root;
	int count;
private:
	BinaryTreeNode<T> *getLast()
	{
		int j = count, k = 1;
		BinaryTreeNode<T> *cur = root;
		while(k <= j)
			k = k << 1;
		k = k >> 2;
		while(k > 0)
		{
			if(k & j)
				cur = cur->getRight();
			else
				cur = cur->getLeft();
			k = k >> 1;
		}
		return cur;
	}
	bool _exist(BinaryTreeNode<T> *r, BinaryTreeNode<T> *n)
	{
		if(n == r)
			return true;
		if(r->getLeft() && _exist(r->getLeft(), n))
			return true;
		if(r->getRight() && _exist(r->getRight(), n))
			return true;
		return false;
	}
	BinaryTreeNode<T> *_getFather(BinaryTreeNode<T> *r, BinaryTreeNode<T> *n)
	{
		if(r == NULL)
			return NULL;
		if(r->getLeft() == n || r->getRight() == n)
			return r;
		BinaryTreeNode<T> *temp;
		temp = _getFather(r->getLeft(), n);
		if(temp != NULL)
			return temp;
		temp = _getFather(r->getRight(), n);
		return temp;
	}
	void _print(BinaryTreeNode<T> *r, int n)
	{
		if(r == NULL)
			return;
		int j;
		_print(r->getRight(), n + 1);
		for(j = 0;j < n;j ++)
			std::cout<<"    ";
		std::cout<<r<<std::endl;
		_print(r->getLeft(), n + 1);
	}
};

int main()
{
	Tree<int> *tree = new Tree<int>();
	srand(0);
	int j, k, i;
	for(j = 0;j < 20;j ++)
	{
		if(tree->count() == 0)
			tree->setRoot(rand() % 100);
        else
		{
			k = rand() % tree->count();
			(*tree)[k]->addChild(rand() % 100);
		}
	}
	tree->levelOrder();
	tree->preorder();
	tree->postorder();

	BinaryTree<int> *binaryTree = BinaryTree<int>::convertFromGeneralTree(tree);
	binaryTree->print();
}
