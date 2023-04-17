#include<iostream>
#include <algorithm>
#define pow2(n) (1 << (n))
using namespace std;

template<class T>
class Node
{
    template<class U>  friend class LinkedList;
public:
    Node():prev(NULL),next(NULL) {}
    Node(T data):data(data),prev(NULL),next(NULL) {}
    Node(T data, Node<T> *prev, Node<T> *next):data(data),prev(prev),next(next) {}
    T getdata()const
    {
        return data;
    }
    Node<T>* getprev()const
    {
        return prev;
    }
    Node<T>* getnext()const
    {
        return next;
    }
private:
    Node<T> *prev;
    Node<T> *next;
    T data;
};
template<class T>
class LinkedList
{
    template<class U>  friend class Queue;
    template<class V>  friend class avlTree;
public:
    LinkedList():head(NULL),tail(NULL) {}
    Node<T>* gethead(){return head;}
    void addToTail(T data)
    {
        Node<T> *Newnode=new Node<T>(data);
        if (tail == NULL&&head==NULL)
        {
            tail=Newnode;
            head=Newnode;
        }
        else
        {
            Node<T> *temp=tail;
            tail=Newnode;
            temp->next=tail;
            tail->prev=temp;
        }
    }
    void addToHead(T data)
    {
        Node<T> *Newnode=new Node<T>(data);
        if (tail == NULL&&head==NULL)
        {
            head=Newnode;
            tail=Newnode;
        }
        else
        {
            Node<T> *temp=head;
            head=Newnode;
            temp->prev=Newnode;
            head->next=temp;
        }
    }
    void deleteData(T data)
    {
        Node<T> *current = head;
        while(current!=NULL)
        {
            if(current->data==data)
            {
                if(current==head)
                {
                    if(head==tail)
                    {
                        head=NULL;
                        tail=NULL;
                    }
                    else
                    {
                        head=current->next;
                        head->prev=NULL;
                    }
                }
                else if(current==tail)
                {
                    if(head==tail)
                    {
                        head=NULL;
                        tail=NULL;
                    }
                    else
                    {
                        tail=current->prev;
                        tail->next=NULL;
                    }
                }
                else
                {
                    current->prev->next=current->next;
                    current->next->prev=current->prev;
                }
                delete current;
                break;
            }
            current=current->next;
        }
    }
    void deleteData(T data, int n)
    {
        while(--n)
        {
            deleteData(data);
        }
    }
    friend std::ostream &operator<<(std::ostream &out, LinkedList * n)
    {
        if(n->head==NULL&&n->tail==NULL)
        {
            out<<endl;
        }
        else
        {
            Node<T> *current = n->head;
            out<<"(";
            while(current!=NULL)
            {
                out<<current->getdata();
                if(current->getnext()!=NULL) out<<", ";
                current=current->getnext();
            }
            out<<")"<<endl;
        }
        return out;
    }
private:
    Node<T> *head;
    Node<T> *tail;
};
template<class T>
class Queue
{
    template<class U>  friend class avlTree;
public:
    Queue()
    {
        LinkedList<T> *temp=new LinkedList<T>;
        list=temp;
    }
    void enqueue(T data)
    {
        this->list->addToTail(data);
    }
    T dequeue()
    {
        T delete_element=front();
        list->deleteData(front());
        return delete_element;
    }
    T front()
    {
        return list->head->getdata();
    }
    bool isEmpty()
    {
        if(list->head==NULL&&list->tail==NULL) return true;
        return false;
    }
private:
    LinkedList<T> *list;
};
/*
* Node Declaration
*/
template<class T>
class avl_node
{
    template<class U> friend class avlTree;
	T data;
	avl_node *left;
	avl_node *right;
};
/*
* Class Declaration
*/
template<class T>
class avlTree
{
private:

public:
	int height(avl_node<T> *);
	int diff(avl_node<T> *);
	avl_node<T> *rr_rotation(avl_node<T> *);
	avl_node<T> *ll_rotation(avl_node<T> *);
	avl_node<T> *lr_rotation(avl_node<T> *);
	avl_node<T> *rl_rotation(avl_node<T> *);
	avl_node<T>* balance(avl_node<T> *);
	avl_node<T>* insert(avl_node<T> *, T);
	void display(avl_node<T> *, int);
	void inorder(avl_node<T> *);
	void preorder(avl_node<T> *);
	void postorder(avl_node<T> *);
	void levelorder();
	avl_node<T>* remove(avl_node<T>* t, T x);
	avl_node<T>* findMin(avl_node<T>*);
	avl_node<T>* findMax(avl_node<T>*);
	avlTree<T>()
	{
		root = NULL;
	}
	avl_node<T> *root;
};

template<class T>
void avlTree<T>::levelorder()
{
        Queue<avl_node<T>*> my_queue;
        my_queue.enqueue(root);
        while (!my_queue.isEmpty())
        {
            Node<avl_node<T>*>* current=my_queue.list->gethead();
            bool flag=false;
            while(current){
                if(current->getdata()) flag=true;
                current=current->getnext();
            }
            if(flag==false) break;
            avl_node<T> *node=my_queue.dequeue();
            if(node)
            {
                my_queue.enqueue(node->left);
                my_queue.enqueue(node->right);

            }
            if(node!=root)
                cout<<',';
            if(node)
            {
                cout<<node->data;
            }
            else
            {
                cout<<"NULL";
            }
        }
        cout<<endl;
}


/*
* Height of AVL Tree
*/
template<class T>
int avlTree<T>::height(avl_node<T> *temp)
{
	int h = 0;
	if (temp != NULL)
	{
		int l_height = height(temp->left);
		int r_height = height(temp->right);
		int max_height = max(l_height, r_height);
		h = max_height + 1;
	}
	return h;
}

/*
* Height Difference
*/
template<class T>
int avlTree<T>::diff(avl_node<T> *temp)
{
	int l_height = height(temp->left);
	int r_height = height(temp->right);
	int b_factor = l_height - r_height;
	return b_factor;
}

/*
* Left- Left Rotation
*/
template<class T>
avl_node<T> *avlTree<T>::ll_rotation(avl_node<T> *parent)
{
	avl_node<T> *temp;
	temp = parent->left;
	parent->left = temp->right;
	temp->right = parent;
	return temp;
}

/*
* Left - Right Rotation
*/
template<class T>
avl_node<T> *avlTree<T>::lr_rotation(avl_node<T> *parent)
{
	avl_node<T> *temp;
	temp = parent->left;
	parent->left = rr_rotation(temp);
	return ll_rotation(parent);
}

/*
* Right- Right Rotation
*/
template<class T>
avl_node<T> *avlTree<T>::rr_rotation(avl_node<T> *parent)
{
	avl_node<T> *temp;
	temp = parent->right;
	parent->right = temp->left;
	temp->left = parent;
	return temp;
}

/*
* Right- Left Rotation
*/
template<class T>
avl_node<T> *avlTree<T>::rl_rotation(avl_node<T> *parent)
{
	avl_node<T> *temp;
	temp = parent->right;
	parent->right = ll_rotation(temp);
	return rr_rotation(parent);
}

/*
* Balancing AVL Tree
*/
template<class T>
avl_node<T> *avlTree<T>::balance(avl_node<T> *temp)
{
	int bal_factor = diff(temp);
	if (bal_factor > 1)
	{
		if (diff(temp->left) > 0)
			temp = ll_rotation(temp);
		else
			temp = lr_rotation(temp);
	}
	else if (bal_factor < -1)
	{
		if (diff(temp->right) > 0)
			temp = rl_rotation(temp);
		else
			temp = rr_rotation(temp);
	}
	return temp;
}

/*
* Insert Element into the tree
*/
template<class T>
avl_node<T> *avlTree<T>::insert(avl_node<T> *root, T value)
{
	if (root == NULL)
	{
		root = new avl_node<T>;
		root->data = value;
		root->left = NULL;
		root->right = NULL;
		return root;
	}
	else if (value < root->data)
	{
		root->left = insert(root->left, value);
		root = balance(root);
	}
	else if (value >= root->data)
	{
		root->right = insert(root->right, value);
		root = balance(root);
	}
	return root;
}

/*
* Display AVL Tree
*/
template<class T>
void avlTree<T>::display(avl_node<T> *ptr, int level)
{
	int i;
	if (ptr != NULL)
	{
		display(ptr->right, level + 1);
		printf("\n");
		if (ptr == root)
			cout << "Root -> ";
		for (i = 0; i < level && ptr != root; i++)
			cout << "        ";
		cout << ptr->data;
		display(ptr->left, level + 1);
	}
}

/*
* Inorder Traversal of AVL Tree
*/
template<class T>
void avlTree<T>::inorder(avl_node<T> *tree)
{
	if (tree == NULL)
		return;
	inorder(tree->left);
	cout << tree->data << "  ";
	inorder(tree->right);
}

/*
* Preorder Traversal of AVL Tree
*/
template<class T>
void avlTree<T>::preorder(avl_node<T> *tree)
{
	if (tree == NULL)
		return;
	cout << tree->data << "  ";
	preorder(tree->left);
	preorder(tree->right);

}

/*
* Postorder Traversal of AVL Tree
*/
template<class T>
void avlTree<T>::postorder(avl_node<T> *tree)
{
	if (tree == NULL)
		return;
	postorder(tree->left);
	postorder(tree->right);
	cout << tree->data << "  ";
}

template<class T>
avl_node<T>* avlTree<T>::findMin(avl_node<T>* t) {
	if (t == NULL) return NULL;
	else if (t->left == NULL) return t; // if element traverse on max left then return
	else return findMin(t->left); // or recursively traverse max left
}

template<class T>
avl_node<T>* avlTree<T>:: findMax(avl_node<T>* t) {
	if (t == NULL) return NULL;
	else if (t->right == NULL) return t;
	else return findMax(t->right);
}

template<class T>
avl_node<T>* avlTree<T>:: remove(avl_node<T>* t, T x) {
	avl_node<T>* temp;
	// element not found
	if (t == NULL) return NULL;
	// searching element
	else if (x < t->data) t->left = remove(t->left, x);
	else if (x >t->data) t->right = remove(t->right, x);
	// element found
	// element has 2 children
	else if (t->left && t->right) {
		temp = findMax(t->left);
		t->data = temp->data;
		t->left = remove(t->left, t->data);
	}
	// if element has 1 or 0 child
	else {
		temp = t;
		if (t->left == NULL) t = t->right;
		else if (t->right == NULL) t = t->left;
		delete temp;
	}
	if (t == NULL) return t;
	// check balanced)
	t = balance(t);
}

/*
* Main Contains Menu
*/
int main()
{
	int dat;
	string opr, data;
	static avlTree<int> avl;
	static avlTree<string> avl2;
	int flag = 0;
	while (cin>>opr>>data)
	{
		if(opr=="insert"){
            for(int i=0; i<data.size(); i++){
                if(isalpha(data[i])) flag = 1;
            }
            if(flag==0){
                dat = stoi(data);
                avl.root = avl.insert(avl.root, dat);
            }
            else{
                avl2.root = avl2.insert(avl2.root, data);
            }
		}
		else if(opr=="delete"){
            for(int i=0; i<data.size(); i++){
                if(isalpha(data[i])) flag = 1;
            }
            if(flag==0){
                dat = stoi(data);
                avl.root = avl.remove(avl.root, dat);
            }
            else{
                avl2.root = avl2.remove(avl2.root, data);
            }
		}
	}
	if(flag==0) avl.levelorder();
	//else avl2.display(avl2.root, 1); //avl2.levelorder();
	else avl2.levelorder();
	return 0;
}
