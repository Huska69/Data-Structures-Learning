#include <iostream>
#include <string>
using namespace std;
template<class T>
class Node
{
public:
    Node()
    {
        prev=NULL;
        next=NULL;
    }
    Node(T _data)
    {
        prev=NULL;
        next=NULL;
        data=_data;
    }
    Node(T _data, Node<T> *prev1, Node<T> *next1)
    {
        data=_data;
        prev=prev1;
        next=next1;
    }
    Node<T> *prev;
    Node<T> *next;
    T data;
};

template<class T>
class LinkedList
{
public:
    LinkedList()
    {
        head=NULL;
        tail=NULL;
    }

    void addToTail(T _data)
    {
        Node<T> *newone=new Node<T>(_data);
        if(tail!=NULL)
        {
            tail->next=newone;
            newone->prev=tail;
            tail=newone;
        }
        else
        {
            tail=newone;
            head=newone;
        }
    }

    void addToHead(T _data)
    {
        Node <T>*newone=new Node<T>( _data);
        if(head!=NULL)
        {
            newone->next=head;
            head->prev=newone;
            head=newone;
        }
        else//One is NULL and both are NULL;
        {
            head=newone;
            tail=newone;
        }
    }

    void deleteData(T _data)
    {
        if(head==NULL)
            return;
        Node <T>*temp=head;
        while(temp!=NULL)
        {
            if(temp->data==_data)
            {
                if(temp->prev==NULL)//the first one is deleted
                {
                    head=temp->next;
                    if(tail==temp)//first and last
                        tail=NULL;
                    break;
                }
                Node <T>*temp1=temp->next;
                temp=temp->prev;
                temp->next=temp1;
                temp1->prev=temp;
                break;
            }
            else
            {
                if(temp->next==tail && tail->data==_data)
                {
                    tail=tail->prev;
                    tail->next=NULL;
                }
                temp=temp->next;
            }
        }
    }

    void deleteData(T _data, int n)
    {
        if(n==0)
            return;
        deleteData(_data);
        deleteData(_data,n-1);
    }

    friend ostream &operator<<(ostream &out, LinkedList * n)
    {
        out<<"(";
        Node <T>*temp=n->head;
        if(n->head==NULL)
        {
            out<<")"<<endl;
            return out;
        }
        while(temp->next!=NULL)
        {
            out<<temp->data<<", ";
            temp=temp->next;
        }
        out<<n->tail->data<<")"<<endl;
        return out;
    }
    Node<T> *head;
    Node<T> *tail;
};

class GeneralTreeNode
{
public:
    GeneralTreeNode()
    {
        children=NULL;
        data="";
        path="";
        type="";
    }
    GeneralTreeNode* find(string target)
    {
        if(children==NULL)
            return NULL;
        Node<GeneralTreeNode *>* temp=children->head;
        while(temp!=NULL)
        {
            if(temp->data->path==target)
                return temp->data;
            temp=temp->next;
        }
        return NULL;
    }
    void deleted(GeneralTreeNode* root)
    {
        Node<GeneralTreeNode*> *tpnode=children->head;
        while(tpnode!=NULL)
        {
            if(tpnode->data==root)
            {
                if(tpnode->prev==NULL && tpnode->next==NULL)
                {
                    children=NULL;
                }
                else if(tpnode->prev==NULL)
                {
                    tpnode->next->prev=NULL;
                    children->head=tpnode->next;
                }
                else if(tpnode->next==NULL)
                {
                    tpnode->prev->next=NULL;
                    children->tail=tpnode->prev;
                }
                else
                {
                    tpnode->next->prev=tpnode->prev;
                    tpnode->prev->next=tpnode->next;
                }
                return;
            }
            tpnode=tpnode->next;
        }
    }
    string data;
    string type;
    string path;
    LinkedList<GeneralTreeNode*>* children;
};


class GeneralTree
{
public:
    GeneralTree()
    {
        this -> root = new GeneralTreeNode();
        root->path="/";
        root->type="dir";
        root->children=NULL;
    }
    void change(GeneralTreeNode* root, GeneralTreeNode* node)
    {
        Node<GeneralTreeNode*>* temp=root->children->head;
        while(temp!=NULL)
        {
            if(temp->data->path==node->path)
            {
                temp->data=node;
                return;
            }
            temp=temp->next;
        }
    }
    bool compare(string a,string b)
    {
        int sizea=a.size();
        int sizeb=b.size();
        int i;
        for(i=0; i<sizea && i<sizeb; i++)
        {
            if(a[i]<b[i])
                return true;
            else if(a[i]>b[i])
                return false;
            else
                continue;
        }
        if(sizeb>sizea)
            return true;
        return false;
    }
    void copy(GeneralTreeNode* to, GeneralTreeNode* from)
    {
        to->data=from->data;
        to->path=from->path;
        to->type=from->type;
        LinkedList<GeneralTreeNode*> * newlist=new LinkedList<GeneralTreeNode*>;
        to->children=newlist;
        if(from->children==NULL)
        {
            to->children=from->children;
            return;
        }
        Node<GeneralTreeNode*> *temp=from->children->head;
        while(temp!=NULL)
        {
            GeneralTreeNode* newone=new GeneralTreeNode;
            to->children->addToTail(newone);
            copy(newone,temp->data);
            temp=temp->next;
        }
        return;
    }
    GeneralTreeNode* insert(GeneralTreeNode* root,GeneralTreeNode* node)//complete;
    {
        if(root->children==NULL)
        {
            LinkedList<GeneralTreeNode*>*newlist=new LinkedList<GeneralTreeNode*>;
            newlist->addToHead(node);
            root->children=newlist;
            return node;
        }
        if(root->find(node->path)!=NULL)
            return root->find(node->data);
        Node<GeneralTreeNode*>* temp=root->children->head;
        Node<GeneralTreeNode*>* newone=new  Node<GeneralTreeNode*>;
        newone->data=node;
        while(temp!=NULL)
        {
            if(compare(node->path,temp->data->path))
            {
                if(temp->prev==NULL)
                {
                    newone->prev=NULL;
                    newone->next=temp;
                    temp->prev=newone;
                    root->children->head=newone;
                }
                else
                {
                    newone->next=temp;
                    newone->prev=temp->prev;
                    temp->prev->next=newone;
                    temp->prev=newone;
                }
                return node;
            }
            else
                temp=temp->next;
        }
        newone->prev=root->children->tail;
        newone->next=NULL;
        newone->prev->next=newone;
        root->children->tail=newone;
        return node;
    }
    GeneralTreeNode* findfather(GeneralTreeNode* root,GeneralTreeNode* node)//complete
    {
        if(root==node)
            return NULL;
        if(root->children==NULL)
            return NULL;
        Node<GeneralTreeNode*>* temp=root->children->head;
        while(temp!=NULL)
        {
            if(temp->data==node)
                return root;
            if(findfather(temp->data,node)!=NULL)
                return findfather(temp->data,node);
            temp=temp->next;
        }
        return NULL;
    }

    void deSerialize(string str)
    {
        GeneralTreeNode* temp=root,* tpp;
        string tempdata,temppath,temptype;
        for(int i=str.size()-1; i>=0; i--)
        {
            if(i+3<str.size() && str.substr(i,5)=="path\"")
            {
                int cur=i+7;
                while(str[cur]!='"')
                {
                    temppath+=str[cur];
                    cur++;
                }
                if(str[i-3]!=']')
                    continue;
                GeneralTreeNode* newone=new GeneralTreeNode;
                newone->path=temppath;
                newone->type=temptype;
                newone->data=tempdata;
                if(newone->path!="/")
                {
                    temp=insert(temp,newone);
                }
                temppath="";
                temptype="";
                tempdata="";
            }
            else if(i+3<str.size() && str.substr(i,5)=="type\"")
            {
                int cur=i+7;
                while(str[cur]!='"')
                {
                    temptype+=str[cur];
                    cur++;
                }
            }
            else if(i+3<str.size() && str.substr(i,5)=="data\"")
            {
                int cur=i+7;
                while(str[cur]!='"')
                {
                    tempdata+=str[cur];
                    cur++;
                }
                GeneralTreeNode* newone=new GeneralTreeNode;
                newone->path=temppath;
                newone->type=temptype;
                newone->data=tempdata;
                if(newone->path!="/")
                {
                    tpp=insert(temp,newone);
                }
                temppath="";
                temptype="";
                tempdata="";
            }
            else if(i+7<str.size() && str.substr(i,9)=="children\"")
            {
                temp=findfather(root,temp);
            }
        }
    }
    string recursive (GeneralTreeNode *root)
    {
        string str;
        if(root==NULL)
            return str;
        if(root->type=="dir")  //tag type dir
        {
            str+="{\"children\":[";
            if(root->children!=NULL)
            {
                Node<GeneralTreeNode*> *tempnode=root->children->head;
                while (tempnode != NULL)
                {
                    str+=recursive(tempnode->data);
                    tempnode=tempnode->next;
                    str+=',';
                }
                if(str[str.size()-1]==',')
                    str=str.substr(0,str.size()-1);
            }
            str+="],\"path\":\"";
            str+=root->path;
            str+="\"";
            str+=",\"type\":\"";
            str+=root->type;
            str+="\"";
            str+="}";

        }
        if(root->type=="file")   //tag type file
        {
            str+="{\"data\":\"";
            str+=root->data;
            str+="\"";
            str+=",\"path\":\"";
            str+=root->path;
            str+="\"";
            str+=",\"type\":\"";
            str+=root->type;
            str+="\"";
            str+="}";
        }
        return str;
    }
    string serialize()
    {
        string ans="{\"root\":";
        ans+=recursive (root);
        ans+="}";
        return ans;
    }
    GeneralTreeNode* root;
};


int main()
{
    GeneralTree GT;
    string str;
    getline(cin,str);
    GT.deSerialize(str);
    while(getline(cin,str))
    {
        if(str[0]=='m')
        {
            if(str[1]=='k')//mkdir
            {
                int cur=7;
                string tempstr;
                for(; cur<str.size() && str[cur]!='/'; cur++)
                    tempstr+=str[cur];
                GeneralTreeNode* dest=GT.root;
                GeneralTreeNode* tppp;
                tppp=dest;
                dest=dest->find(tempstr);
                if(dest==NULL)
                {
                    GeneralTreeNode* newone=new GeneralTreeNode;
                    newone->type="dir";
                    newone->path=tempstr;
                    newone->data="";
                    dest=GT.insert(tppp,newone);
                }
                if(dest->type!="file")
                {
                    tempstr="";
                    for(cur++; cur<str.size(); cur++)
                    {
                        GeneralTreeNode* newone=new GeneralTreeNode;
                        for(; cur<str.size() && str[cur]!='/'; cur++)
                            tempstr+=str[cur];
                        if(dest->find(tempstr)!=NULL)
                        {
                            dest=dest->find(tempstr);
                            if(dest->type=="file")
                                break;
                            tempstr="";
                            continue;
                        }
                        newone->type="dir";
                        newone->path=tempstr;
                        newone->data="";
                        dest=GT.insert(dest,newone);
                        tempstr="";
                    }
                }
            }
            else//mv
            {
                string tempstr;
                bool flag=false;
                int cur=4;
                GeneralTreeNode* dest=GT.root;
                GeneralTreeNode* source=GT.root;
                GeneralTreeNode* tp;
                for(; cur<str.size(); cur++)
                {
                    for(; cur<str.size() && str[cur]!='/' && str[cur]!=' '; cur++)
                        tempstr+=str[cur];
                    if(flag)
                    {
                        tp=dest;
                        dest=dest->find(tempstr);
                    }
                    else
                        source=source->find(tempstr);
                    if(source==NULL)
                        break;
                    if(dest==NULL)
                    {
                        GeneralTreeNode* newone=new GeneralTreeNode;
                        newone->type="dir";
                        newone->path=tempstr;
                        newone->data="";
                        dest=GT.insert(tp,newone);
                    }
                    if(cur==str.size())//not sure
                    {
                        GeneralTreeNode* newone=new GeneralTreeNode;
                        GT.copy(newone,source);
                        if(dest->find(source->path)!=NULL)
                        {
                            tp=dest;
                            dest=dest->find(source->path);
                            dest=newone;
                            GT.change(tp,newone);
                            GT.findfather(GT.root,source)->deleted(source);
                        }
                        else
                        {
                            GT.findfather(GT.root,source)->deleted(source);
                            dest=GT.insert(dest,newone);
                        }
                    }
                    if(str[cur]==' ')
                    {
                        cur++;
                        flag=true;
                    }
                    tempstr="";
                }
            }
        }
        else if(str[0]=='t')//touch
        {
            int cur=7;
            string tempstr;
            GeneralTreeNode* dest=GT.root;
            GeneralTreeNode* tp;
            for(; str[cur]!=' '; cur++)
            {
                for(; cur<str.size() && str[cur]!='/' && str[cur]!=' '; cur++)
                    tempstr+=str[cur];
                tp=dest;
                dest=dest->find(tempstr);
                if(str[cur]!=' '&& dest==NULL)
                {
                    GeneralTreeNode* newone=new GeneralTreeNode;
                    newone->type="dir";
                    newone->path=tempstr;
                    newone->data="";
                    dest=GT.insert(tp,newone);
                }
                else if(str[cur]==' '&& dest==NULL)
                {
                    GeneralTreeNode* newone=new GeneralTreeNode;
                    newone->type="file";
                    newone->path=tempstr;
                    newone->data=str.substr(cur+1,str.size());
                    dest=GT.insert(tp,newone);
                }
                else if(str[cur]==' '&& dest!=NULL && dest->type=="file")
                {
                    dest->data=str.substr(cur+1,str.size());
                }
                tempstr="";
            }
        }
        else if(str[0]=='r')//rm
        {
            GeneralTreeNode* dest=GT.root;
            GeneralTreeNode* source;
            int cur=4;
            string tempstr;
            for(; cur<str.size(); cur++)
            {
                for(; cur<str.size() && str[cur]!='/'; cur++)
                    tempstr+=str[cur];
                dest=dest->find(tempstr);
                if(dest==NULL)
                    break;
                if(cur==str.size())
                {
                    GT.findfather(GT.root,dest)->deleted(dest);
                    break;
                }
                tempstr="";
            }
        }
        else//cpnot
        {
            int cur=4;
            string tempstr;
            GeneralTreeNode* dest=GT.root;
            GeneralTreeNode* source=GT.root;
            bool flag=false;
            for(; cur<str.size(); cur++)
            {
                for(; cur<str.size() && str[cur]!='/' && str[cur]!=' '; cur++)
                    tempstr+=str[cur];
                if(flag)
                    dest=dest->find(tempstr);
                else
                    source=source->find(tempstr);
                if(source==NULL)
                    break;
                if(cur==str.size())
                {
                    GeneralTreeNode* newone=new GeneralTreeNode;
                    GT.copy(newone,source);
                    if(dest->find(source->path)!=NULL)
                    {
                        GeneralTreeNode* tp=dest;
                        dest=dest->find(source->path);
                        GT.change(tp,newone);
                        dest=newone;
                    }
                    else
                    {
                        dest=GT.insert(dest,newone);
                    }
                }
                if(str[cur]==' ')
                {
                    cur++;
                    flag=true;
                }
                tempstr="";
            }
        }
    }
    cout<<GT.serialize()<<endl;
    return 0;
}
