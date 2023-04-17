#include <iostream>
#include <string.h>
using namespace std;
#define BLACK 0
#define RED 1

template <class T>
class Node
{
public:
    T data;
    int color;
    Node<T> *left;
    Node<T> *right;
    Node<T> *parent;

    Node() : color(1), left(NULL), right(NULL), parent(NULL) {}
    Node(T data) : data(data), color(1), left(NULL), right(NULL), parent(NULL) {}
    Node(T data, Node<T> *left, Node<T> *right, Node<T> *parent) : data(data), color(1), left(left), right(right), parent(parent) {}
};

// Queue
template <class T>
class Queue
{
private:
    Node<T> *front;
    Node<T> *rear;

public:
    Queue() : front(NULL), rear(NULL) {}

    void Enqueue(T data);
    T Dequeue();
    bool IsEmpty();
};

// Red Black Tree
template <class T>
class Red_Black_Tree
{
private:
    Node<T> *root;
    Node<T> *NIL;

    bool IsNumber(string str);
    int Compare(T a, T b);

    Node<T> *Search(T data);
    Node<T> *Maximum(Node<T> *p);
    void Transplant(Node<T> *u, Node<T> *v);

    void LeftRotate(Node<T> *p);
    void RightRotate(Node<T> *p);

    void InsertFix(Node<T> *p);
    void DeleteFix(Node<T> *p);

public:
    Red_Black_Tree();

    void Insert(T data);
    void Delete(T data);

    string Serialize();
};

// Driver
int main()
{
    string op, data;
    Red_Black_Tree<string> *tree = new Red_Black_Tree<string>();
    while (cin >> op >> data)
    {
        if (op == "insert")
        {
            tree->Insert(data);
        }
        else if (op == "delete")
        {
            tree->Delete(data);
        }
        else
        {
            break;
        }
    }
    cout << tree->Serialize() << endl;
    return 0;
}

// Queue
template <class T>
void Queue<T>::Enqueue(T data)
{
    Node<T> *t = new Node<T>(data);
    if (front == NULL)
    {
        front = t;
        rear = t;
    }
    else
    {
        rear->right = t;
        rear = t;
    }
}

template <class T>
T Queue<T>::Dequeue()
{
    Node<T> *p = front;
    T x = NULL;
    if (front)
    {
        front = front->right;
        x = p->data;
        delete p;
    }
    return x;
}

template <class T>
bool Queue<T>::IsEmpty()
{
    return front == NULL;
}

// Red Black Tree : Public
template <class T>
Red_Black_Tree<T>::Red_Black_Tree()
{
    NIL = new Node<T>();
    NIL->color = BLACK;
    root = NIL;
}

template <class T>

void Red_Black_Tree<T>::Insert(T data)  //insert
{
    Node<T> *p = root, *q = NULL, *new_node;
    while (p != NIL)
    {
        q = p;
        if (Compare(data, p->data) < 0)
        {
            p = p->left;
        }
        else if (Compare(data, p->data) > 0)
        {
            p = p->right;
        }
        else
            return;
    }
    new_node = new Node<T>(data, NIL, NIL, q);
    if (q == NULL)
    {
        root = new_node;
        return;
    }
    else if (Compare(new_node->data, q->data) < 0)
    {
        q->left = new_node;
    }
    else
    {
        q->right = new_node;
    }
    if (new_node->parent->color == RED)
        InsertFix(new_node);
}

template <class T>
void Red_Black_Tree<T>::Delete(T data)  //delete
{
    Node<T> *target = Search(data);
    if (target == NIL || target == NULL)
        return;
    Node<T> *x, *replaced = target;
    int replaced_original_color = replaced->color;
    if (target->left == NIL)
    {
        x = target->right;
        Transplant(target, target->right);
    }
    else if (target->right == NIL)
    {x
        x = target->left;
        Transplant(target, target->left);
    }
    else
    {
        replaced = Maximum(target->left);
        replaced_original_color = replaced->color;
        x = replaced->left;
            if (replaced->parent == target)
            {
                x->parent = replaced;
            }
            else
            {
                Transplant(replaced, replaced->left); //replace the replaced node with its left child, 
                replaced->left = target->left;
                replaced->left->parent = replaced; //parent of this left child to be replaced.
            }
            Transplant(target, replaced); //replace target node 
            replaced->right = target->right;
            replaced->right->parent = replaced;
            replaced->color = target->color;
    }
    if (replaced_original_color == BLACK)
    {
        DeleteFix(x);
    }
}

template <class T>
string Red_Black_Tree<T>::Serialize()
{
    string tree = "";
    Queue<Node<T> *> q;
    q.Enqueue(root);
    while (!q.IsEmpty())
    {
        Node<T> *p = q.Dequeue();
        if (p != NIL)
        {
            tree += p->data + ",";
            q.Enqueue(p->left);
            q.Enqueue(p->right);
        }
        else
        {
            tree += "NULL,";
        }
    }
    for (int i = tree.length() - 1; i >= 0; i--)
    {
        if (tree[i] == ',')
        {
            tree.erase(i, 1);
        }
        else if (tree[i] == 'L' && tree[i - 1] == 'L' && tree[i - 2] == 'U' && tree[i - 3] == 'N')
        {
            tree.erase(i - 3, 4);
            i -= 3;
        }
        else
        {
            break;
        }
    }
    return tree;
}

// Red Black Tree : Private
template <class T>
bool Red_Black_Tree<T>::IsNumber(string str)
{   
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] < '0' || str[i] > '9')
        {
            return false;
        }
    }
    return true;
}

template <class T>
int Red_Black_Tree<T>::Compare(T a, T b)
{
    if (IsNumber(a) || IsNumber(b))
    {
        if (IsNumber(a) && IsNumber(b))
        {
            int num1 = stoi(a);
            int num2 = stoi(b);
            if (num1 < num2)
            {
                return -1;
            }
            else if (num1 > num2)
            {
                return 1;
            }
        }
        return 0;
    }
    else
    {
        return strcmp(a.c_str(), b.c_str());
    }
}

template <class T>
Node<T> *Red_Black_Tree<T>::Search(T data)
{
    Node<T> *p = root;
    while (p != NIL && Compare(data, p->data))
    {
        if (Compare(data, p->data) < 0)
        {
            p = p->left;
        }
        else
        {
            p = p->right;
        }
    }
    return p;
}

template <class T>
Node<T> *Red_Black_Tree<T>::Maximum(Node<T> *p)
{
    while (p->right != NIL)
    {
        p = p->right;
    }
    return p;
}

template <class T>
void Red_Black_Tree<T>::Transplant(Node<T> *u, Node<T> *v)
{
    if (u->parent == NULL)
    {
        root = v;
    }
    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

template <class T>
void Red_Black_Tree<T>::LeftRotate(Node<T> *p)
{
    Node<T> *pr = p->right;
    p->right = pr->left;
    if (p->right != NIL)
    {
        p->right->parent = p;
    }
    pr->parent = p->parent;
    if (pr->parent == NULL)
    {
        root = pr;
    }
    else if (p == p->parent->left)
    {
        p->parent->left = pr;
    }
    else
    {
        p->parent->right = pr;
    }
    pr->left = p;
    p->parent = pr;
}

template <class T>
void Red_Black_Tree<T>::RightRotate(Node<T> *p)
{
    Node<T> *pl = p->left;
    p->left = pl->right;
    if (p->left != NIL)
    {
        p->left->parent = p;
    }
    pl->parent = p->parent;
    if (pl->parent == NULL)
    {
        root = pl;
    }
    else if (p == p->parent->left)
    {
        p->parent->left = pl;
    }
    else
    {
        p->parent->right = pl;
    }
    pl->right = p;
    p->parent = pl;
}

template <class T>
void Red_Black_Tree<T>::InsertFix(Node<T> *p)
{
    Node<T> *grandparent = NULL, *parent = NULL, *uncle = NULL;
    while (p != root && p->color == RED && p->parent->color == RED)
    {
        parent = p->parent;
        grandparent = p->parent->parent;
        if (grandparent == NULL)
            break;
        if (parent == grandparent->left)
        {
            uncle = grandparent->right;
            if (uncle != NIL && uncle->color == RED)
            {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                p = grandparent;
            }
            else
            {
                if (p == parent->right)
                {
                    LeftRotate(parent);
                    p = parent;
                    parent = p->parent;
                }
                RightRotate(grandparent);
                parent->color = BLACK;
                grandparent->color = RED;
                p = parent;
            }
        }
        else // parent == grandparent -> right
        {
            uncle = grandparent->left;
            if (uncle != NIL && uncle->color == RED)
            {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                p = grandparent;
            }
            else
            {
                if (p == parent->left)
                {
                    RightRotate(parent);
                    p = parent;
                    parent = p->parent;
                }
                LeftRotate(grandparent);
                parent->color = BLACK;
                grandparent->color = RED;
                p = parent;
            }
        }
    }
    root->color = BLACK;
}

template <class T>
void Red_Black_Tree<T>::DeleteFix(Node<T> *p)
{
    Node<T> *sibling = NULL;
    while (p != root && p->color == BLACK)
    {
        if (p == p->parent->left)
        {
            sibling = p->parent->right;
            if (sibling->color == RED)
            {
                sibling->color = BLACK;
                p->parent->color = RED;
                LeftRotate(p->parent);
                sibling = p->parent->right;
            }
            if (sibling->left->color == BLACK && sibling->right->color == BLACK)
            {
                sibling->color = RED;
                p = p->parent;
            }
            else
            {
                if (sibling->right->color == BLACK)
                {
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    RightRotate(sibling);
                    sibling = p->parent->right;
                }
                sibling->color = p->parent->color;
                p->parent->color = BLACK;
                sibling->right->color = BLACK;
                LeftRotate(p->parent);
                p = root;
            }
        }
        else
        {
            sibling = p->parent->left;
            if (sibling->color == RED)
            {
                sibling->color = BLACK;
                p->parent->color = RED;
                RightRotate(p->parent);
                sibling = p->parent->left;
            }
            if (sibling->right->color == BLACK && sibling->left->color == BLACK)
            {
                sibling->color = RED;
                p = p->parent;
            }
            else
            {
                if (sibling->left->color == BLACK)
                {
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    LeftRotate(sibling);
                    sibling = p->parent->left;
                }
                sibling->color = p->parent->color;
                p->parent->color = BLACK;
                sibling->left->color = BLACK;
                RightRotate(p->parent);
                p = root;
            }
        }
    }
    p->color = BLACK;
}
