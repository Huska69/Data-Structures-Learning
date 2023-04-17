#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <ctime>
#include <queue>
#define PRINTS(VAR) std::cout << (VAR) << " ";
#define PRINT(VAR) std::cout << (VAR) << std::endl;

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
		return *data;//return address
	}
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
    	this->child = NULL;
	}
	TreeNode(T d) : Node<T>(d)
	{
    	this->child = NULL;
        *(this->data) = d;
	}
	/*
		Add a child to this node.
	*/
	void addChild(TreeNode *n)
	{
        if (this->child == NULL)
        	this->child = new LinkList<TreeNode<T> *>;
        this->child->addFromTail(n);
	}
	/*
		Add a child to this node.
	*/
	void addChild(T d)
	{
        TreeNode<T> *temp = new TreeNode<T>(d);
        this->addChild(temp);
	}
	/*
		Return the nth child of the node.
	*/
	TreeNode<T> *operator[](int n)
	{
        TreeNode<T> *cur = this->child->head;
        for (int i = 0; i < n; i++)
        {
            cur = cur->next;
        }
        return cur;
	}
	
	
	LinkList<TreeNode<T> *> *child;
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
	}
	/*
		return the nth node on this tree with level order.
	*/
	TreeNode<T> *operator[](int n)
	{
      	std::queue<TreeNode<T> *> q;
        if (n == 0)
            return this->root;
        q.push(this->root);
        while (q.size() && n)
        {
            if (q.front()->child)//q.front 
            {
                ListNode<TreeNode<T> *> *cur = q.front()->child->head;
                while (cur!=NULL)
                {
                    q.push(*cur->data);
                    cur = cur->next;
                }
            }
            q.pop();
            n--;
            if (n == 0)
                return q.front();
        }
        return NULL;
	}
	/*
		return the number of nodes on this tree.
	*/
	int count()
	{
      if (this->root == NULL)
            return 0;
        int cnt = 0;
        std::queue<TreeNode<T> *> q;
        q.push(this->root);
        cnt++;
        while (q.size())
        {
            ListNode<TreeNode<T> *> *cur = NULL;
            if (q.front()->child)
                cur = q.front()->child->head;
            q.pop();
            while (cur)
            {
                q.push(*cur->data);
                cnt++;
                cur = cur->next;
            }
        }
        return cnt;
	}
	/*
		print all the node on this tree with level order.
	*/
	void levelOrder()
	{
        std::queue<TreeNode<T> *> q;
        q.push(this->root);
        while (q.size())
        {
            int sz = q.size();
            for (int i = 0; i < sz; i++)
            {
                PRINTS(*q.front()->data); // 30 15
                ListNode<TreeNode<T> *> *cur = NULL;
                if (q.front() && q.front()->child)
                    cur = q.front()->child->head;
                q.pop();
                while (cur)
                {
                    if (cur->data != NULL)
                        q.push(*cur->data);
                    cur = cur->next;
                }
            }
            // std::cout << std::endl;\n
        }
        std::cout << std::endl;
	}
	/*
		print all the node on this tree with preorder.
	*/
	void preorder()
	{
        preorder_hp(this->root);
        std::cout << std::endl;
	}
      void preorder_hp(TreeNode<T> *root)
    {
        if (root == NULL)
            return;
        PRINTS(*root->data);
        if (root->child)
        {
            ListNode<TreeNode<T> *> *cur = root->child->head;
            while (cur)
            {
                preorder_hp(*cur->data);
                cur = cur->next;
            }
        }
    }
	/*
		print all the node on this tree with postorder.
	*/
	void postorder()
	{
        postorder_hp(this->root);
        std::cout << std::endl;
	}
  	void postorder_hp(TreeNode<T> *root)
    {
        if (root == NULL)
            return;
        if (root->child)
        {
            ListNode<TreeNode<T> *> *cur = root->child->head;
            while (cur)
            {
                preorder_hp(*cur->data);
                cur = cur->next;
            }
        }
        PRINTS(*root->data);
    }
	/*
		set the root of this tree.
	*/
	void setRoot(T d)
	{
        if (this->root == NULL)
        {
            this->root = new TreeNode<T>(d);
            return;
        }
        *(root->data) = d;
	}
  	
	TreeNode<T> *root;
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
}
