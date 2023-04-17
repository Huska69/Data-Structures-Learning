#include <iostream>
#include <string>
#include <cctype>
using namespace std;
template <class T>
class Node
{
public:
    Node()
    {
        this->prev = NULL;
        this->next = NULL;
    }

    Node(T data)
    {
        this->data = data;
        this->prev = NULL;
        this->next = NULL;
    }

    Node(T data, Node<T> *prev, Node<T> *next)
    {
        this->data = data;
        this->prev = prev;
        this->next = next;
    }

    Node<T> *getprev()
    {
        return prev;
    }

    Node<T> *getnext()
    {
        return next;
    }

    void setprev(Node<T> *input)
    {
        this->prev = input;
        return;
    }

    void setnext(Node<T> *input)
    {
        this->next = input;
        return;
    }
    
    T getdata()
    {
        return data;
    }

private:
    Node<T> *prev;
    Node<T> *next;
    T data;
};
template <class T>
class LinkedList
{
public:
    LinkedList()
    {
        this->head = NULL;
        this->tail = NULL;
    }
    void addToTail(T data)
    {
        Node<T> *node = new Node<T>(data);
        if (this->head == NULL)
        {
            head = node;
            tail = node;
            return;
        }
        this->tail->setnext(node);
        node->setprev(this->tail);
        this->tail = node;
        return;
    }
    void addToHead(T data)
    {
        Node<T> *node = new Node<T>(data);
        if (this->head == NULL)
        {
            head = node;
            tail = node;
            return;
        }
        this->head->setprev(node);
        node->setnext(this->head);
        this->head = node;
        return;
    }

    void deleteData(T data)
    {
        Node<T> *current = this->head;
        while (current != NULL)
        {
            if (current->getdata() == data)
            {
                if (current->getprev() == NULL && current->getnext() == NULL)
                {
                    this->head = NULL;
                    this->tail = NULL;
                }
                else if (current->getprev() == NULL)
                {
                    this->head = current->getnext();
                    current->getnext()->setprev(NULL);
                }
                else if (current->getnext() == NULL)
                {
                    current->getprev()->setnext(NULL);
                    this->tail = current->getprev();
                }
                else
                {
                    current->getprev()->setnext(current->getnext());
                    current->getnext()->setprev(current->getprev());
                }
                delete current;
                return;
            }
            current = current->getnext();
        }
        return;
    }

void rdeleteData(T data)
    {
        Node<T> *current = this->tail;
        while (current != NULL)
        {
            if (current->getdata() == data)
            {
                if (current->getprev() == NULL && current->getnext() == NULL)
                {
                    this->head = NULL;
                    this->tail = NULL;
                }
                else if (current->getprev() == NULL)
                {
                    this->head = current->getnext();
                    current->getnext()->setprev(NULL);
                }
                else if (current->getnext() == NULL)
                {
                    current->getprev()->setnext(NULL);
                    this->tail = current->getprev();
                }
                else
                {
                    current->getprev()->setnext(current->getnext());
                    current->getnext()->setprev(current->getprev());
                }
                delete current;
                return;
            }
            current = current->getprev();
        }
        return;
    }
    void deleteData(T data, int n)
    {
        for (int i = 0; i < n; i++)
        {
            this->deleteData(data);
        }
        return;
    }

    Node<T> *gethead()
    {
        return head;
    }

    Node<T> *gettail()
    {
        return tail;
    }

    void sethead(Node<T> *input)
    {
        this->head = input;
        return;
    }

    void settail(Node<T> *input)
    {
        this->tail = input;
        return;
    }

    friend std::ostream &operator<<(std::ostream &out, LinkedList *n)
    {
        Node<T> *current = n->head;
        out << "(";
        while (current->getnext() != NULL)
        {
            out << current->getdata() << ", ";
            current = current->getnext();
        }
        out << current->getdata() << ")" << endl;
        return out;
    }

private:
    Node<T> *head;
    Node<T> *tail;
};
template<class T>
class Queue{
public:
  Queue(){
    this->list = new LinkedList<T>;
    this->count = 0;
  }
  void enqueue(T data){
    list->addToTail(data);
    this->count++;
    return;
  }

  T dequeue(){
        Node<T> *current = list->gethead();
        if (current == NULL) return NULL;
        T result = current->getdata();
        list->deleteData(result);
        this->count--;
        return result;
  }

  T front(){
    return list->gethead()->getdata();
  }

  bool isEmpty(){
    if (list->gethead() == NULL) return true;
    return false;
  }
  int size()
  {
    return this->count;
  }
  LinkedList<T> *getlist()
  {
    return list;
  }
  private: 
    LinkedList<T> *list;
    int count;
};
template <class T>
class Stack
{
public:
    Stack()
    {
        this->list = new LinkedList<T>;
        count = 0;
    }

    void push(T data)
    {
        list->addToTail(data);
        count++;
        return;
    }

    T pop()
    {
        Node<T> *current = list->gettail();
        if (current == NULL) return NULL;
        T result = current->getdata();
        list->rdeleteData(result);
        count--;
        return result;
    }

    T top()
    {
        return list->gettail()->getdata();
    }

    bool isEmpty()
    {
        if (count == 0)
            return true;
        return false;
    }

    int size()
    {
        return count;
    }

    LinkedList<T> *getlist()
    {
        return list;
    }

private:
    LinkedList<T> *list;
    int count;
};
template <class T>
class TreeNode{
public:
    TreeNode()
    {
        this->left = NULL;
        this->right = NULL;
    }
    TreeNode(T data)
    {
        this->left = NULL;
        this->right = NULL;
        this->data = data;
    }

    T getdata()
    {
        return this->data;
    }
    TreeNode<T> *getleft()
    {
        return this->left;
    }
    TreeNode<T> *getright()
    {
        return this->right;
    }
    void setdata(T input)
    {
        this->data = input;
    }
    void setleft(TreeNode<T> *input)
    {
        this->left = input;
    }
    void setright(TreeNode<T> *input)
    {
        this->right = input;
    }
private:
    T data;
    TreeNode<T> *left;
    TreeNode<T> *right;
};
template <class T>
class binarySearchTree{
public:
    binarySearchTree()
    {
        this->root = new TreeNode<T>;
        count = 0;
    }
    virtual void preorder() = 0;
    virtual void inorder() = 0;
    virtual void postorder() = 0;
    virtual void levelorder() = 0;
    virtual bool insert(T data) = 0;
    virtual void setRoot(T data) = 0;
    virtual bool serach(T target) = 0;
    virtual void deSerialize(string tree) = 0;
    virtual string serialize() = 0;
protected:
    TreeNode<T> *root;
    int count;
};
template <class T>
class BinarySearchTree : public binarySearchTree<T>{
public:
    BinarySearchTree()
    {
        this->root = new TreeNode<T>;
        this->count = 0;
    }
    void preorder()
    {
        TreeNode<T> *node = this->root;
        Stack<TreeNode<T>*> stack;
        if (node == NULL) return;
        stack.push(node);
        int node_count = this->count;
        while (true)
        {
            node = stack.pop();
            cout << node->getdata() << ",";
            node_count--;
            if (node->getright() != NULL) stack.push(node->getright());
            if (node->getleft() != NULL) stack.push(node->getleft());
            if (node_count == 0)
            {
                cout << stack.pop()->getdata() << endl;
                break;
            }
        }
    }

    void inorder()
    {
        TreeNode<T> *node = this->root;
        Stack<TreeNode<T>*> stack;
        int node_count = this->count;
        if (node == NULL) return;
        while (true)
        {
            while(node != NULL)
            {
                stack.push(node);
                node = node->getleft();
            }
            if (node_count == 0)
            {
                cout << stack.pop()->getdata() << endl;
                break; 
            } 
            node = stack.pop();
            cout << node->getdata() << ",";
            node_count--;
            node = node->getright();
        }
    }

    void postorder()
    {
        TreeNode<T> *node = this->root;
        Stack<TreeNode<T>*> stack;
        Stack<TreeNode<T>*> tmp;
        int node_count = this->count;
        if (node == NULL) return;
        stack.push(node);
        while (stack.size() > 0)
        {
            node = stack.pop();
            tmp.push(node);
            if (node->getleft() != NULL) stack.push(node->getleft());
            if (node->getright() != NULL) stack.push(node->getright());
        }
        while (true)
        {
            cout << tmp.pop()->getdata() << ",";
            node_count--;
            if (node_count == 0)
            {
                cout << tmp.pop()->getdata() << endl;
                break;
            }
        }
    }

    void levelorder()
    {
        TreeNode<T> *node = this->root;
        Queue<TreeNode<T>*> queue;
        int node_count = this->count;
        if (node == NULL) return;
        queue.enqueue(node);
        while (true)
        {
            node = queue.dequeue();
            cout << node->getdata() << ",";
            node_count--;
            
            if (node->getleft() != NULL) queue.enqueue(node->getleft());
            if (node->getright() != NULL) queue.enqueue(node->getright());
            if (node_count == 0)
            {
                cout << queue.dequeue()->getdata() << endl;
                break;
            }
        }
    }

    bool insert(T data)
    {
        if (this->serach(data)) return 0;
        bool is_R = 0;
        TreeNode<T> *node = this->root;
        TreeNode<T> *tmp = node;
        while (true)
        {
            if (node == NULL)
            {
                TreeNode<T> *Node = new TreeNode<T>(data);
                if (is_R) tmp->setright(Node);
                else tmp->setleft(Node);
                this->count++;
                return 1;
            }
            else if(data > node->getdata())
            {
                is_R = 1;
                tmp = node;
                node = node->getright();
            } 
            else
            {
                is_R = 0;
                tmp = node;
                node = node->getleft();
            } 
        }   
    }

    void setRoot(T data)
    {
        if (this->root == NULL)
        {
            this->root = new TreeNode<T>(data);
            return;
        }
        this->root->setdata(data);
    }

    bool serach(T target)
    {
        TreeNode<T> *node = this->root;
        while (true)
        {
            if (node == NULL) return 0;
            if (node->getdata() == target) return 1;
            else if(target > node->getdata()) node = node->getright();
            else node = node->getleft();
        }
    }

    bool AllNULL(Node<TreeNode<T>*> *head)
    {
        Node<TreeNode<T>*> *current = head;
        while (current != NULL)
        {
            if (current->getdata() != NULL)
            return 1;
            current = current->getnext();
        }
        return 0;
    }
    void deSerialize(string tree)
    {
        string tmp = tree.substr(0,tree.find(","));
        tree.erase(0,tree.find(",") + 1);
        this->setRoot(stoi(tmp));
        while (true)
        {
            if ((int)tree.find(",") == -1) break;
            tmp = tree.substr(0,tree.find(","));
            tree.erase(0,tree.find(",") + 1);
            if (tmp != "NULL") this->insert(stoi(tmp));
        }
        int len = (int)tree.size();
        for (int i=0;i<len;i++)
        {
            tmp = "";
            while (isdigit(tree[i])){
                tmp += tree[i];
                i++;
            } 
            this->insert(stoi(tmp));
        }  
    }

    string serialize()
    {
        string result = "";
        TreeNode<T> *node = this->root;
        Queue<TreeNode<T>*> queue;
        if (node == NULL) return "NULL";
        queue.enqueue(node);
        while (true)
        {
            node = queue.dequeue();
            if (node == NULL) result += "NULL,";
            else
            {
                result += (to_string(node->getdata()) + ",");
                queue.enqueue(node->getleft());
                queue.enqueue(node->getright());
            } 
            if (!AllNULL(queue.getlist()->gethead()))
            {
                node = queue.dequeue();
                if (node == NULL) result.erase(result.size()-1,1);
                else result += to_string(node->getdata());
                break;
            }
        }
        return result;
    }
};

int main()
{
    
    string input;
    while (getline(cin,input)){
        BinarySearchTree<int> *bst = new BinarySearchTree<int>();
        bst->deSerialize(input);
        cout << bst->serialize() << endl;
        delete bst;
    }
    return 0;
}
