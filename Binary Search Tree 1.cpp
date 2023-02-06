//Binary Search Tree 1.
//Please finish the class "BinarySearchTree"


#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

class Tree
{
public:
	Tree()
	{
	    recursive_index =0;
	    first_done = false;
		int j;
		for(j = 0;j < 2000;j ++)
			root[j] = -1;
	}
	int insert(int node)
	{
		int index = 0;
		while(index < 2000 && root[index] != -1)
		{ 
			if(root[index] < node)
				index = index * 2 + 2;
			else
				index = index * 2 + 1;
		}
		root[index] = node;
	}
	void inorder()
	{
	    int temp = recursive_index;
	    if(root[recursive_index] == -1)
            return;
        //left
        recursive_index = 2*temp + 1;
        inorder();
        //mid
        if(first_done)
            cout<<",";
        else first_done = true;
        cout<<root[temp];
        //right
        recursive_index = 2*temp + 2;
        inorder();
        //back to
        recursive_index = temp;
        if(recursive_index == 0)
            first_done = false;

	}
	void preorder()
	{

	    int temp = recursive_index;

	    if(root[recursive_index] == -1)
            return;
//        mid
        if(first_done)
            cout<<",";
        else first_done = true;
        cout<<root[temp];
        //right
        recursive_index = 2*temp + 2;
        inorder();
        //left
        recursive_index = 2*temp + 1;
        inorder();


        //back to
        recursive_index = temp;
        if(recursive_index == 0)
            first_done = false;
	}
	void postorder()
	{
	    int temp = recursive_index;
	    if(root[recursive_index] == -1)
            return;
        //left
        recursive_index = 2*temp + 1;
        inorder();
        //right
        recursive_index = 2*temp + 2;
        inorder();
        //mid
        if(first_done)
            cout<<",";
        else first_done = true;
        cout<<root[temp];

        //back to
        recursive_index = temp;
        if(recursive_index == 0)
            first_done = false;
	}
	void levelorder()
	{
	    while(recursive_index<2000)
        {

	    if(root[recursive_index] != -1)
        {
            if(first_done) cout<<",";
            else first_done = true;
            cout<<root[recursive_index];
        }
	    recursive_index++;
        }


	}int root[2000];
private:
    int recursive_index;
    bool first_done;

};


int main()
{
	Tree *tree = new Tree();
	int j, node;
	srand(time(NULL));
	for(j = 0;j < 10;j ++)
	{
		node = rand() % 10;
		tree->insert(node);
	}
	for(int i=0; i<50; i++)
        printf("%d ",tree->root[i]);
	tree->inorder();
	printf("\n");
	tree->preorder();
	printf("\n");
	tree->postorder();
	printf("\n");
	tree->levelorder();
	printf("\n");
}
