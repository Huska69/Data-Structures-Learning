//Arithmetic expression solver C

//Please write a program that reads in an expression and gives its result.
//The expression will contain addition, subtraction, multiplication, division, power, and parentheses.
//Please follow PEMDAS rules and round to the second decimal place after every operation.
//You must use the "Stack" you wrote last week and are not allowed to use any build in STL library or you will get up to 0 points.
//You are not allowed using recursive in this assignment.
//Note: You can use pow()

//Rounding rule
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

struct Node
{
    double data;
    struct Node *prev, *next;
};

void initLinkList(struct Node **head)
{
  *head = NULL;
}

void addToHead(struct Node **head, double data)
{
  struct Node *newnode = (struct Node *) malloc(sizeof(struct Node));
  newnode -> prev = NULL;
  newnode -> next = *head;
  newnode -> data = data;

  if(*head != NULL)
    (*head) -> prev = newnode;
  *head = newnode;
}

void addToTail(struct Node **head, double data)
{
  if(*head == NULL)
    addToHead(head, data);
  else
  {
    struct Node *newnode = (struct Node *) malloc(sizeof(struct Node));
    newnode -> data = data;

    struct Node *tail = *head;
    while(tail -> next != NULL)
      tail = tail -> next;

    tail -> next = newnode;
    newnode -> prev = tail;
  }
}

void deleteData(struct Node **head, double data)
{
  struct Node *cur = *head;
  while(cur != NULL)
  {
    if(cur -> data == data)
      break;
    cur = cur -> next;
  }

  if(cur == NULL)
    return;

  if((*head) -> next == NULL)
  {
    initLinkList(head);
    return;
  }

  if(cur -> prev == NULL)
  {
    *head = (*head) -> next;
    (*head) -> prev = NULL;
  }
  else if(cur -> next == NULL)
  {
    cur = cur -> prev;
    cur -> next = NULL;
  }
  else if(cur != NULL)
  {
    cur -> prev -> next = cur -> next;
    cur -> next -> prev = cur -> prev;
  }
}

void deleteDatas(struct Node **head, double data, int n)
{
  while(n--)
    deleteData(head, data);
}

void display(struct Node *head)
{
  if(head == NULL)
    return;

  printf("(");
  while(head -> next != NULL)
  {
    printf("%f, ", head -> data);
    head = head -> next;
  }
  printf("%f)\n", head -> data);
}

int isEmpty(struct Node *stack)
{
  return (stack == NULL) ? 1 : 0;
}

void push(struct Node **stack, double data)
{
   addToHead(stack, data);
}

double top(struct Node *stack)
{
  return isEmpty(stack) ? 0 : stack -> data;
}

double pop(struct Node **stack)
{
  if(!isEmpty(*stack))
  {
    double data = top(*stack);
    deleteData(stack, data);
    return data;
  }
}

int size(struct Node *stack)
{
  int size = 0;
  while(stack != NULL)
  {
    stack = stack -> next;
    size++;
  }
  return size;
}

bool IsError(char *s)
{
  int count = 0;
  for(int i = 0; i < strlen(s); i++)
  {
    switch(s[i])
    {
      case '(':
        if(!isdigit(s[i + 1]) && s[i + 1] != '(' && s[i + 1] != '-')
          return true;
        count++;
        break;

      case ')':
        if(isdigit(s[i + 1]) || s[i + 1] == '.')
          return true;
        count--;
        if(count < 0)
          return true;
        break;

      case '+': case '*': case '/': case '^':
        if(i == 0 || i == strlen(s) - 1)
          return true;
        if(!isdigit(s[i + 1]) && s[i + 1] != '(' && s[i + 1 != '-'])
          return true;
        break;

      case '-':
        if(i == strlen(s) - 1)
          return true;
        if(!isdigit(s[i + 1]) && s[i + 1] != '(' && s[i + 1] != '-')
          return true;
        break;

      case '.':
        if(i == 0 || i == strlen(s) - 1)
          return true;
        if(!isdigit(s[i + 1]) || !isdigit(s[i - 1]))
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

double BankerRounding(double n)
{
  return (double)(lrint(n*100)/100.0);
}

double Operator(char oper, double x, double y)
{
    double d = 0;
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

double ans(char *s)
{
  char postfix[1000] = {'\0'} ;
  struct Node *oper;
  initLinkList(&oper);
  int count = 0, cur = 0;

  for(int i = 0; i < strlen(s); i++)
  {
    if(isdigit(s[i]) || s[i] == '.')
    {
      postfix[cur] = s[i];
      cur++;

      if(!isdigit(s[i + 1]) && s[i + 1] != '.')
      {
        postfix[cur] = ' ';
        cur++;
      }
    }
    else if((s[i] == '-' && i == 0) || (s[i] == '-' && !isdigit(s[i - 1]) && s[i - 1] != ')'))
    {
      int count = i;

      while(s[count] == '-')
        count++;

      if((count - i) % 2)
      {
        postfix[cur] = '-';
        cur++;
      }

      i = count - 1;
    }
    else if(s[i] == '(' || Pirority(s[i]) > Pirority(top(oper)))
    {
      push(&oper, s[i]);
    }
    else if(s[i] == ')')
    {
      if(top(oper) != '(')
      {
        postfix[cur] = pop(&oper);
        cur++;
        postfix[cur] = ' ';
        cur++;
      }
      pop(&oper);
    }
    else
    {
      if(!isEmpty(oper))
      {
        postfix[cur] = pop(&oper);
        cur++;
        postfix[cur] = ' ';
        cur++;
      }
      push(&oper, s[i]);
    }
  }

  while(!isEmpty(oper))
  {
    postfix[cur] = pop(&oper);
    cur++;
    postfix[cur] = ' ';
    cur++;
  }

  struct Node *num;
  initLinkList(&num);

  for(int i = 0; i < strlen(postfix); i++)
  {
    if(isdigit(postfix[i]) || (postfix[i] == '-' && isdigit(postfix[i + 1])))
    {
      push(&num, atof(&postfix[i]));
      while(postfix[i] != ' ')
        i++;
    }
    else if(postfix[i] != ' ')
    {
      push(&num, (Operator(postfix[i], pop(&num), pop(&num))));
    }
  }
  return BankerRounding(top(num));
}

int main()
{
  char str[1000];
  while(scanf("%s", str) != EOF)
  {
    if(IsError(str))
      printf("ERROR\n");
    else
      printf("%.2f\n", ans(str));
  }
}
