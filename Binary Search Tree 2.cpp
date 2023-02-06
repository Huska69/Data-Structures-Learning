//Binary Search Tree 2
//Please finish the class "BinarySearchTree" and use it in the main function
//You can add any function or variable if you want.
//You must use your own data structure and are not allowed to use any build in STL library or you will get up to 0 points.
//You must finish the funciton serialize and deserialize in the class binarySearchTree oryou will get up to 0 points.

//Input
//Each line will contain the following information till the end-of-file:
//．First part will be a string that needs to be deserialized to the tree, which is separated by "," and the null pointer is indicated by "NULL", there is no space in this string.
//．Second part will be multiple strings which is the value that needs to be added to the tree.
//Example: assume the input is "15,6,23,NULL,7 71 50 5", then 15,6,23,NULL,7 is the string that needs to be deserialized, "71 50 5" is to be added.
//15,6,23,4,7,NULL,71,NULL,5,NULL,NULL,50 3 20
//41,20,65,11,29,50,91,NULL,NULL,NULL,32,NULL,NULL,72,99 1 10 20 30 40 50 60 70

//Output
//Result of the serialized tree after add, no space between and ending with a "\n" of each line.
//15,6,23,4,7,20,71,3,5,NULL,NULL,NULL,NULL,50
//41,20,65,11,29,50,91,1,NULL,NULL,32,NULL,60,72,99,NULL,10,30,40,NULL,NULL,70

#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

class Tree {
public:
  Tree() {
    int j;
    for (j = 0; j < 2000; j++)
      root[j] = -1;
  }

  int insert(int node) {
    int index = 0;
    while (index < 2000 && root[index] != -1) {
      if (root[index] < node)
        index = index * 2 + 2;
      else
        index = index * 2 + 1;
    }
    root[index] = node;
    return root[index];
  }

  void inorder() { Inorder(0); }
  void Inorder(int index) {
    static int size = 0;
    if (root[index] != -1) {
      Inorder(index * 2 + 1);
      if (size++)
        cout << ",";
      cout << root[index];
      Inorder(index * 2 + 2);
    }
  }

  void preorder() { Preorder(0); }
  void Preorder(int index) {
    if (root[index] != -1) {
      if (index != 0)
        cout << ",";
      cout << root[index];
      Preorder(index * 2 + 1);
      Preorder(index * 2 + 2);
    }
  }

  void postorder() { Postorder(0); }
  void Postorder(int index) {
    if (root[index] != -1) {
      Postorder(index * 2 + 1);
      Postorder(index * 2 + 2);
      cout << root[index];
      if (index != 0)
        cout << ",";
    }
  }

  void levelorder() {
    static int size = 0;
    for (int index = 0; index < 2000; index++)
      if (root[index] != -1) {
        if (index)
          cout << ",";
        cout << root[index];
      }
  }

private:
  int root[2000];
};

int main() {
  Tree *tree = new Tree();
  int j, node;
  srand(time(NULL));
  for (j = 0; j < 10; j++) {
    node = rand();
    tree->insert(node);
  }
  tree->inorder();
  printf("\n");
  tree->preorder();
  printf("\n");
  tree->postorder();
  printf("\n");
  tree->levelorder();
  printf("\n");
}
