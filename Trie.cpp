#include <iostream>
#include <string>
#include <queue>
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
        this->prev = NULL;
        this->next = NULL;
        this->data = data;
    }
    Node(T data, Node<T> *prev, Node<T> *next)
    {
        this->prev = prev;
        this->next = next;
        this->data = data;
    }

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
        this->level = 0;
    }
    LinkedList(int level)
    {
        this->head = NULL;
        this->tail = NULL;
        this->level = level;
    }
    void addToTail(T data)
    {
        if (this->head == NULL)
        {
            this->head = new Node<T>(data);
            this->tail = this->head;
            return;
        }
        this->tail->next = new Node<T>(data);
        this->tail->next->prev = this->tail;
        this->tail = this->tail->next;
    }
    void addToHead(T data)
    {
        if (this->head == NULL)
        {
            this->head = new Node<T>(data);
            this->tail = this->head;
            return;
        }
        this->head->prev = new Node<T>(data);
        this->head->prev->next = this->head;
        this->head = this->head->prev;
    }
    void deleteData(T data)
    {
        if (this->head == NULL)
            return;
        if (this->head == this->tail)
        {
            delete (this->head);
            this->head = NULL;
            this->tail = NULL;
            return;
        }
        Node<T> *cur = this->head;
        while (cur)
        {
            if (cur->data == data)
            {
                if (cur == this->head)
                    this->head = this->head->next;
                else if (cur == this->tail)
                    this->tail = this->tail->prev;
                else
                {
                    cur->prev->next = cur->next;
                    cur->next->prev = cur->prev;
                }
                return;
            }
            else
            {
                cur = cur->next;
            }
        }
    }
    void deleteData(T data, int n)
    {
        if (n == 0)
            return;
        deleteData(data);
        deleteData(data, n - 1);
    }
    Node<T> *insert(T data)
    {
        Node<T> *cur = this->head;
        if (cur == NULL)
        {
            this->head = new Node<T>(data);
            this->tail = this->head;
            return this->head;
        }
        if (cur->data->data > data->data)
        {
            this->head->prev = new Node<T>(data);
            this->head->prev->next = this->head;
            this->head = this->head->prev;
            return this->head;
        }
        while (cur)
        {
            if (cur->data->data == data->data)
                return cur;
            if (cur->data->data > data->data)
            {
                cur->prev->next = new Node<T>(data);
                cur->prev->next->next = cur;
                cur->prev->next->prev = cur->prev;
                cur->prev = cur->prev->next;
                return cur->prev;
            }
            else if (cur->next == NULL)
            {
                cur->next = new Node<T>(data);
                cur->next->prev = cur;
                return cur->next;
            }
            else
                cur = cur->next;
        }
    }
    Node<T> *search(T data)
    {
        Node<T> *cur = this->head;
        while (cur)
        {
            if (cur->data->data == data->data)
                return cur;
            cur = cur->next;
        }
        return NULL;
    }
    friend std::ostream &operator<<(std::ostream &out, LinkedList *n)
    {
        if (n->head == NULL)
        {
            out << "()";
            return out;
        }
        out << "(";
        out << n->head->data;
        if (n->head != n->tail)
        {
            Node<T> *cur = n->head->next;
            while (cur)
            {
                out << "," << cur->data;
                cur = cur->next;
            }
        }
        out << ")";
        return out;
    }

    Node<T> *head;
    Node<T> *tail;
    int level;
};

template <class T>
class Queue
{
public:
    Queue()
    {
        list = new LinkedList<T>;
    }

    void enqueue(T data)
    {
        list->addToTail(data);
    }

    T dequeue()
    {
        T n = front();
        list->deleteData(front());
        return n;
    }

    int size()
    {
        int i = 0;
        Node<T> *cur = list->head;
        while (cur)
        {
            cur = cur->next;
            i++;
        }
        return i;
    }

    T front()
    {
        if (list->head == NULL)
            return 0;
        return (list->head->data);
    }

    bool isEmpty()
    {
        if (list->head == NULL)
            return true;
        else
            return false;
    }

    LinkedList<T> *list;
};

template <class D>
class TreeNode
{
public:
    LinkedList<TreeNode<D> *> *children;
    TreeNode()
    {
        this->parent = NULL;
        // this->children = new LinkedList<TreeNode<std::string> *>;
        this->children = NULL;
        this->isWord = false;
    }
    TreeNode(D data)
    {
        this->parent = NULL;
        this->children = NULL;
        // this->children = new LinkedList<TreeNode<std::string> *>;
        this->data = data;
        this->isWord = false;
    }
    D data;
    TreeNode<D> *parent;
    bool isWord;
};

// T: TreeNode<D>, D: string
template <class T, class D>
class Tree
{
public:
    Tree()
    {
        this->temp = new TreeNode<D>("");
    }
    virtual void levelorder() = 0;
    virtual void inorder() = 0;
    virtual void preorder() = 0;
    virtual void postorder() = 0;
    virtual bool insert(D data) = 0;
    virtual bool remove(D data) = 0;
    virtual TreeNode<D> *search(D data) = 0;
    virtual void setRoot(TreeNode<D> *root) = 0;
    virtual void deSerialize(string tree) = 0;
    virtual string serialize() = 0;

    TreeNode<D> *root, *temp;
};

template <class D>
class GeneralTreeNode : public TreeNode<D>
{
public:
    virtual TreeNode<D> *getParent()
    {
        return this->parent;
    }
    virtual void setParent(TreeNode<D> *parent)
    {
        this->parent = parent;
    }
    virtual LinkedList<TreeNode<D> *> *getChildren()
    {
        return this->children;
    }
    virtual void setChildren(LinkedList<TreeNode<D> *> *children)
    {
        this->children = children;
    }
};

/**
 * Rules of Serialize and Deserialize for General Tree:
 * 1. The serialized string should be in the following format which is standard JSON format but without any spaces:
 * {"root":{"children":[{"children":[{"children":[],"data":"d"},{"children":[],"data":"p"}],"data":"a"},{"children":[],"data":"b"}],"data":""}}
 * In each node, there are two data structures.
 *  a. children.
 *  b. data.
 * "children" is an array that always comes first.
 * "data" is a data structure stored in the node, that comes after children, sorted in alphabetical order.
 *
 * 2. All nodes in the same layer should be sorted in alphabetical order if is a character type, and sorted by numerical order if is a number type.
 * 3. LinkedList is treated as Array in serialization and deserialization.
 */

template <class T, class D>
class GeneralTree : public Tree<T, D>
{
public:
    GeneralTree()
    {
        this->root = new TreeNode<D>();
        this->root->data = "";
    }
    virtual void levelorder()
    {
        std::queue<TreeNode<std::string> *> q;
        q.push(this->root);
        while (q.size())
        {
            int sz = q.size();
            for (int i = 0; i < sz; i++)
            {
                if (q.front()->children)
                {
                    std::cout << "[ " << q.front()->data[q.front()->data.length() - 1] << ", " << q.front()->isWord << " ] ";
                    Node<TreeNode<std::string> *> *cur = q.front()->children->head;
                    while (cur)
                    {
                        q.push(cur->data);
                        cur = cur->next;
                    }
                }
                else
                {
                    std::cout << "[ " << q.front()->data[q.front()->data.length() - 1] << ", " << q.front()->isWord << " ] ";
                }
                q.pop();
            }
            std::cout << std::endl;
        }
    }

    virtual void inorder()
    {
    }

    virtual void preorder()
    {
    }

    virtual void postorder()
    {
    }

    /**
     * Insert a node to the tree with the given data if it not exists.
     * @param data data to insert
     * @return true if the node is inserted, false if the node already exists
     */
    virtual bool insert(D data)
    {
        TreeNode<D> *cur = this->root;
        // cur->isWord = true;
        for (int i = 1; i <= data.length(); i++)
        {
            this->temp->data = data.substr(0, i);
            // std::cout << this->temp->data << std::endl;
            if (cur->children == NULL)
                cur->children = new LinkedList<TreeNode<D> *>;
            else if (cur->children->search(this->temp))
            {
                cur = cur->children->search(this->temp)->data;
                if (i == data.length())
                {
                    cur->isWord = true;
                    return false;
                }
                else
                    continue;
            }
            TreeNode<D> *newNode = new TreeNode<D>(data.substr(0, i));
            cur = cur->children->insert(newNode)->data;
            if (i == data.length())
                newNode->isWord = true;
        }
        return true;
    }

    /**
     * Remove a node from the tree with the given data if it exists.
     * @param data data to insert
     * @return true if the node is removed successfully, false if the node is not found
     */
    virtual bool remove(D data)
    {
    }
    /**
     * Find a node with the given data if it exists.
     * @param data data to search
     * @return the node if found, NULL if not found
     */
    virtual TreeNode<D> *search(D data)
    {
        if (data == "")
            return this->root;
        TreeNode<D> *cur = this->root;
        for (int i = 1; i <= data.length(); i++)
        {
            this->temp->data = data.substr(0, i);
            if (cur->children == NULL)
                return NULL;
            Node<TreeNode<std::string> *> *rst = cur->children->search(this->temp); // result
            if (rst)
            {
                if (i == data.length())
                    return ((rst->data->isWord) ? rst->data : NULL);
                cur = rst->data;
            }
            else
                return NULL;
        }
        return NULL;
    }

    void setRoot(TreeNode<D> *root)
    {
        this->root = root;
    }

    /**
     * Deserialize the string to a tree with levelorder traversal
     * @param tree to be deserialized
     */
    virtual void deSerialize(string tree)
    {
    }

    /**
     * Serialize the tree to a string with levelorder traversal
     * @return the serialized string
     */
    virtual string serialize()
    {
        std::string ans = "{\"root\":";
        ans += this->serialize_hp(this->root, 0);
        ans += "}";
        return ans;
    }
    std::string serialize_hp(TreeNode<D> *root, int cnt)
    {
        if (!root)
            return "";
        std::string ans = "";
        if (cnt != 0)
            ans += ",";
        ans += "{\"children\":[";
        if (root->children != NULL)
        {
            Node<TreeNode<D> *> *cur = root->children->head;
            cnt = 0;
            while (cur)
            {
                ans += this->serialize_hp(cur->data, cnt);
                cur = cur->next;
                cnt++;
            }
        }
        ans += "],\"data\":\"";
        if (root)
        {
            if (root->data != "")
                ans += root->data[root->data.length() - 1];
        }
        ans += "\"";
        if (root->isWord)
        {
            ans += ",\"end\":\"true\"";
        }
        ans += "}";
        return ans;
    }
};

int main()
{
    GeneralTree<TreeNode<std::string> *, std::string> gt;
    int n, m;
    cin >> n >> m;
    string str;
    for (int i = 0; i < n; i++)
    {
        cin >> str;
        gt.insert(str);
    }
    for (int i = 0; i < m; i++)
    {
        cin >> str;
        cout << (gt.search(str) != NULL) << endl;
    }
    cout << gt.serialize() << endl;

    return 0;
}
