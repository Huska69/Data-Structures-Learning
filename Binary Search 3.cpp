#include<iostream>
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
public:
    LinkedList():head(NULL),tail(NULL) {}
    Node<T>* gethead()
    {
        return head;
    }
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
    bool is_order(){
        Node<T>* current=head;
        while(current){
            if(current->next){
                if(bigger(current->next->data,current->data)==false) return false;
            }
            current=current->next;
        }
        return true;
    }
    bool bigger(string first,string second){
        if(isdigit(first[0])){
            return stoi(first)>stoi(second);
        }else{
            return first>second;
        }
    }
private:
    Node<T> *head;
    Node<T> *tail;
};
template<class T>
class Queue
{
    template<class U>  friend class BinarySearchTree;
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
template<class H>
class TreeNode
{
    template<class U> friend class BinarySearchTree;
public:
    TreeNode():left(nullptr),right(nullptr) {}
    TreeNode(H data):left(nullptr),right(nullptr),data(data) {}
    template<class T>
    friend void bstpreorder(TreeNode<T>* node,TreeNode<T>* End);
    template<class T>
    friend void bstinorder(TreeNode<T>* node,TreeNode<T>* End);
    template<class T>
    friend void bstpostorder(TreeNode<T>* node,TreeNode<T>* End);
    template<class T>
    friend bool bstinsert(TreeNode<T>** node,T data);
private:
    H data;
    TreeNode<H> *left;
    TreeNode<H> *right;
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
    virtual void deSerialize(string tree) = 0;
    virtual string serialize() = 0;
protected:
    TreeNode<T> *root;
};
template<class T>
void bstpreorder(TreeNode<T>* node,TreeNode<T>* End)
{
    if(node==nullptr) return;
    if(node!=End) cout<<node->data<<",";
    else cout<<node->data<<endl;
    bstpreorder(node->left,End);
    bstpreorder(node->right,End);
}
template<class T>
void bstinorder(TreeNode<T>* node,TreeNode<T>* End)
{
    if(node==nullptr) return;
    bstinorder(node->left,End);
    if(node!=End) cout<<node->data<<",";
    else cout<<node->data<<endl;
    bstinorder(node->right,End);
}
template<class T>
void bstpostorder(TreeNode<T>* node,TreeNode<T>* End)
{
    if(node==nullptr) return;
    bstpostorder(node->left,End);
    bstpostorder(node->right,End);
    if(node!=End) cout<<node->data<<",";
    else cout<<node->data<<endl;
}
template<class T>
bool bstinsert(TreeNode<T>** node,T data)
{
    if(*node==nullptr)
    {
        TreeNode<T>* newnode=new TreeNode<T>(data);
        *node=newnode;
        return true;
    }
    else if((*node)->data>data)
    {
        return bstinsert(&(*node)->left,data);
    }
    else return bstinsert(&(*node)->right,data);

}
template<class T>
class BinarySearchTree : public binarySearchTree<T>
{
public:
    BinarySearchTree()
    {
        root=nullptr;
    }
    void preorder()
    {
        TreeNode<T>* current=root;
        while(current->right!=NULL)
        {
            current=current->right;
        }
        bstpreorder(root,current);
    }
    void inorder()
    {
        TreeNode<T>* current=root;
        while(current->right!=NULL)
        {
            current=current->right;
        }
        bstinorder(root,current);
    }
    void postorder()
    {
        bstpostorder(root,root);
    }
    void levelorder()
    {
        Queue<TreeNode<T>*> my_queue;
        my_queue.enqueue(root);
        while (!my_queue.isEmpty())
        {
            Node<TreeNode<T>*>* current=my_queue.list->gethead();
            bool flag=false;
            while(current)
            {
                if(current->getdata()) flag=true;
                current=current->getnext();
            }
            if(flag==false) break;
            TreeNode<T> *node=my_queue.dequeue();
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
    bool insert(T data)
    {
        if(serach(data)) return false;
        else return bstinsert(&root,data);
    }
    void setRoot(T data)
    {
        if(root) return;
        root=new TreeNode<T>(data);
    }
    bool serach(T target)
    {
        TreeNode<T>* current=root;
        while(current)
        {
            if(current->data==target) return true;
            if(current->data>target) current=current->left;
            else current=current->right;
        }
        return false;

    }
    bool levelinsert(T data)
    {
        if(!this->root)
        {
            this->root=new TreeNode<T>(data);
            return true;
        }
        Queue<TreeNode<T>*> my_queue;
        my_queue.enqueue(this->root);
        while (!my_queue.isEmpty())
        {
            TreeNode<T> *node=my_queue.dequeue();
            if(node->data=="NULL") continue;
            if(node->left)my_queue.enqueue(node->left);
            else
            {
                node->left=new TreeNode<T>(data);
                return true;
            }
            if(node->right)my_queue.enqueue(node->right);
            else
            {
                node->right=new TreeNode<T>(data);
                return true;
            }
        }
        return false; 
    }
    void deSerialize(string tree)
    {
        string tmp;
        for(int i=0; i<tree.length(); i++)
        {
            if(tree[i]!=',')
            {
                tmp+=tree[i];
            }
            else
            {
                this->levelinsert(tmp);
                tmp="";
            }
        }
        this->levelinsert(tmp);
    }
    string serialize() {}

    bool isValidSerialization(string str)
    {
        string tmp;
        for(int i=0; i<str.length(); i++)
        {
            if(str[i]==' ') return false;
            if(str[i]!=',')
            {
                tmp+=str[i];
            }
            else
            {
                if(this->levelinsert(tmp)==false||tmp==""||tmp=="NULLL") return false; 
                tmp="";
            }
        }
        if(this->levelinsert(tmp)==false||tmp=="") return false; //if levelinsert=F or temp=empty; if one of this T it return F. 
        return true;  //if both are false it returns T
    }
    bool isValidBinarySearchTree()
    {
        LinkedList<string>* list=new LinkedList<string>;
        to_list(root,list);
        return list->is_order();
    }
    void to_list(TreeNode<T> *node ,LinkedList<string>* list) //traverse bst by in-order
    {
        if (!node)   return;
        if(node->data=="NULL") return;
        to_list(node->left, list);
        list->addToTail(node->data); //add each element of the tree at the end of the list, which is the same order as in-order traversal.
        to_list(node->right, list);
    }
private:
    TreeNode<T> *root;
};
int main()
{
    string str;
    while(getline(cin,str))
    {
        BinarySearchTree<string>* tree=new BinarySearchTree<string>;
        if(!tree->isValidSerialization(str)) cout<<"Serialization invalid"<<endl;
        else if(!tree->isValidBinarySearchTree()) cout<<"Binary Search Tree invalid"<<endl;
        else cout<<"OK"<<endl;
    }
}
