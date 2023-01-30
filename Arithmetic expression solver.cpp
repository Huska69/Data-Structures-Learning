//Arithmetic expression solver C++

//Please write a program that reads in an expression and gives its result.
//The expression will contain addition, subtraction, multiplication, division, power, and parentheses.
//Please follow PEMDAS rules and round to the second decimal place after every operation.
//You must use the "Stack" you wrote last week and are not allowed to use any build in STL library or you will get up to 0 points.
//You are not allowed using recursive in this assignment.
//Note: You can use pow()

//Rounding rule:
//Banker's rounding
//Reference:https://www.calculatorsoup.com/calculators/math/rounding-methods-calculator.php

//Symbol example:
//addition: "+"
//subtraction: "-"
//multiplication: "*"
//division: "/"
//power: "^"
//parentheses: "()"

//Please do two version for this assignment, one in C++ another in C.

//Input
//Expressions end up with line-break or end-of-file.
//123+456/789-2^(20+1)*2
//1/2^3
//0.1+0.035+8*2
//(((-8)/3)*0.5)^10
//-100--10*10
//(9*8/7)^1.1*1000

//Output
//Result of the expression to the 2nd decimal place, "ERROR" when parentheses count does not match or operation error, ending with a "\n" of each line
//-4194180.42
//0.12
//6.14
//18.67
//0.00
//12990.00

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <iomanip>
using namespace std;

template<class T>
class Node
{
public:
  Node():prev(NULL),next(NULL),data(NULL) {}
  Node(T data):prev(NULL),next(NULL),data(data) {}
  Node(T data, Node<T> *prev, Node<T> *next):prev(prev),next(next),data(data) {}
  Node<T> *prev;
  Node<T> *next;
  T data;
};

template<class T>
class LinkedList
{
public:
  LinkedList():head(NULL),tail(NULL) {}

  void addToHead(T data)
  {
    Node<T> *newNode = new Node<T>(data);

    if(head == NULL)
    {
      head = newNode;
      tail = newNode;
    }
    else
    {
      newNode -> next = head;
      head -> prev = newNode;
      head = newNode;
    }
  }

  void addToTail(T data)
  {
    Node<T> *newNode = new Node<T>(data);

    if(tail == NULL)
    {
      tail = newNode;
      head = newNode;
    }
    else
    {
      newNode -> prev = tail;
      tail -> next = newNode;
      tail = newNode;
    }
  }

  Node<T> *exist(T data)
  {
    Node<T> *cur = head;
    while(cur != NULL)
    {
      if(cur -> data == data)
        return cur;
      cur = cur -> next;
    }
    return NULL;
  }

  void deleteHead()
  {
    head = head -> next;
    head -> prev = NULL;
  }

  void deleteTail()
  {
    tail = tail -> prev;
    tail -> next = NULL;
  }

  void deleteData(T data)
  {
    Node<T> *node = exist(data);
    if(node == head && node == tail)
    {
      head = NULL;
      tail = NULL;
      return;
    }
    if(node == head)
      return deleteHead();
    if(node == tail)
      return deleteTail();
    if(node != NULL)
    {
      node -> prev -> next = node -> next;
      node -> next -> prev = node -> prev;
    }
    delete(node);
  }

  void deleteData(T data, int n)
  {
    for(int i = 0; i < n; i++)
      deleteData(data);
  }

  Node<T> *operator[](int n)
  {
    Node<T> *cur = head;
    for(int i = 0; i < n; i++)
      cur = cur -> next;
    return cur;
  }

  friend ostream &operator<<(ostream &out, LinkedList *n)
  {
    if(n -> head == NULL)
      return out << "\n";
    out << "(";
    int index = 0;
    while((*n)[index] -> next != NULL)
    {
      out << (*n)[index] -> data << ", ";
      index++;
    }
    out << (*n)[index] -> data << ")" << "\n";
    return out;
  }

  Node<T> *head;
  Node<T> *tail;
};

template<class T>
class Stack
{
public:
  Stack():list(new LinkedList<T>()) {}

  void push(T data) {list -> addToHead(data);}

  T pop()
  {
    if(!isEmpty())
    {
      T temp = top();
      list -> deleteData(temp);
      return temp;
    }
  }

  T top() {return isEmpty() ? (T)0 : list -> head -> data;}

  bool isEmpty() {return (list -> head == NULL) ? true : false;}

  int size()
  {
    int size = 0;
    while((*list)[size] != NULL)
      size++;
    return size;
  }

  void show() {cout << list;}

private:
    LinkedList<T> *list;
};

bool IsError(string s)
{
  int count = 0;
  for(int cur = 0; cur < s.size(); cur++)
  {
    switch(s[cur])
    {
      case '(':
        if(!isdigit(s[cur + 1]) && s[cur + 1] != '(' && s[cur + 1] != '-')
          return true;
        count++;
        break;

      case ')':
        if(isdigit(s[cur + 1]) || s[cur + 1] == '.')
          return true;
        count--;
        if(count < 0)
          return true;
        break;

      case '+': case '*': case '/': case '^':
        if(cur == 0 || cur == s.size() - 1)
          return true;
        if(!isdigit(s[cur + 1]) && s[cur + 1] != '(' && s[cur + 1 != '-'])
          return true;
        break;

      case '-':
        if(cur == s.size() - 1)
          return true;
        if(!isdigit(s[cur + 1]) && s[cur + 1] != '(' && s[cur + 1] != '-')
          return true;
        break;

      case '.':
        if(cur == 0 || cur == s.size() - 1)
          return true;
        if(!isdigit(s[cur + 1]) || !isdigit(s[cur - 1]))
          return true;
        break;
    }
  }
  return (count != 0) ? true : false;
}

int Pirority(char c)
{
  switch(c)
  {
    case '^':
      return 3;

    case '*': case '/':
      return 2;

    case '+': case '-':
      return 1;

    default:
      return 0;
  }
}

string ToPostfix(string s)  //The code will create a string postfix that is the concatenation of the string s and any prefix or suffix that follows it, with a space inserted between each component.
{
  string postfix;
  Stack <char> *oper = new Stack<char>;   //creating a new stack of characters.

  for(int cur = 0; cur < s.size(); cur++)  //loops through all of the characters in the input string.size
  {
    if(isdigit(s[cur]) || s[cur] == '.')  //If the character at position cur is an digit or a letter that is not a digit, then the postfix string will be incremented by appending it to s[cur].
    {
      postfix += s[cur];
      if(!isdigit(s[cur + 1]) && s[cur + 1] != '.')  //If the character at position cur + 1 is not a digit and does not equal '. ', then postfix will be incremented by appending ' ', followed by s[cur + 1] 
        postfix += ' ';       
    }
    else if((s[cur] == '-' && cur == 0) || (s[cur] == '-' && !isdigit(s[cur - 1]) && s[cur - 1] != ')')) //otherwise then count-- and we'll loop through each character in count until we find another '(', and increment postfix accordingly.
    {
      int count = cur;

      while(s[count] == '-')
        count++;

      if((count - cur) % 2)
        postfix += '-';

      cur = count - 1;
    }
    else if(s[cur] == '(' || Pirority(s[cur]) > Pirority(oper -> top()))
    {
      oper -> push(s[cur]);
    }
    else if(s[cur] == ')')
    {
      if(oper -> top() != '(')
      {
        postfix += oper -> pop();
        postfix += ' ';
      }
      oper -> pop();
    }
    else
    {
      if(!oper -> isEmpty())
      {
        postfix += oper -> pop();
        postfix += ' ';
      }
      oper -> push(s[cur]);
    }
  }

  while(!oper -> isEmpty())
  {
    postfix += oper -> pop();
    postfix += ' ';
  }

  return postfix;
}

double BankerRounding(double n)
{
    return rint(n * 100) / 100;
}

double Operator(char oper, double x, double y)
{
  switch(oper)
  {
    case '+':
      return BankerRounding(x + y);

    case '-':
      return BankerRounding(x - y);

    case '*':
      return BankerRounding(x * y);

    case '/':
      return BankerRounding(x / y);

    case '^':
      return BankerRounding(pow(x, y));

    default:
      return 0;
  }
}

double Calculate(string s)
{
  Stack<double> *num = new Stack<double>;
  for(int cur = 0; cur < s.size(); cur++)
  {
    if(isdigit(s[cur]) || (s[cur] == '-' && isdigit(s[cur + 1])))
    {
      num -> push(stod(s.substr(cur)));
      while(s[cur] != ' ')
        cur++;
    }
    else if(s[cur] != ' ')
    {
      num -> push(Operator(s[cur], num -> pop(), num -> pop()));
    }
  }
  return BankerRounding(num -> top());
}


int main()
{
  string str;
  while(cin >> str)
  {
    if(IsError(str))
      cout << "ERROR\n";
    else
      cout << fixed << setprecision(2) << Calculate(ToPostfix(str)) << endl;
  }
}
