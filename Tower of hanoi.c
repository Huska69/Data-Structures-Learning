//Tower of hanoi in c

//Tower of Hanoi is a mathematical puzzle where we have three rods and n disks. The objective of the puzzle is to move the entire stack to another rod, obeying the following simple rules:
//1. Only one disk can be moved at a time.
//2. Each move consists of taking the upper disk from one of the stacks and placing it on top of another stack i.e. a disk can only be moved if it is the uppermost disk on a stack.
//3. No disk may be placed on top of a smaller disk.

//There are only 3 rods "A", "B" and "C", you need to move all the disks from rod "A" to rod "C" and print out the minimum moved step counts
//Note: You must use your own "Stack" class, no recursive function can be used and no formula like 2^N-1 can be used, or you will get up to 0 points.
//Please do two version for this assignment, one in C++ another in C.

//Input
//The number of the disks on the rod "A", ends up with line-break or end-of-file.
//2
//3
//4
//5
//6

//Output
//The minimum number of moves required, ending with a "\n" of each line
//3
//7
//15
//31
//63

#include <stdio.h>
#include <stdlib.h>

struct Node
{
  int data;
  struct Node *prev, *next;
};

void initLinkList(struct Node **head)
{
  *head = NULL;
}

void addToHead(struct Node **head, int data)
{
  struct Node *newnode = (struct Node *) malloc(sizeof(struct Node));
  newnode -> prev = NULL;
  newnode -> next = *head;
  newnode -> data = data;

  if(*head != NULL)
    (*head) -> prev = newnode;
  *head = newnode;
}

void addToTail(struct Node **head, int data)
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

void deleteData(struct Node **head, int data)
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

void deleteDatas(struct Node **head, int data, int n)
{
  while(n--)
    deleteData(head, data);
}

void display(struct Node *head)
{
  if(head == NULL)
  {
    printf("\n");
    return;
  }

  printf("(");
  while(head -> next != NULL)
  {
    printf("%d, ", head -> data);
    head = head -> next;
  }
  printf("%d)\n", head -> data);
}

void push(struct Node **stack, int data)
{
   addToHead(stack, data);
}

int pop(struct Node **stack)
{
  int data = top(*stack);
  deleteData(stack, data);
  return data;
}

int top(struct Node *stack)
{
  return stack -> data;
}

int isEmpty(struct Node *stack)
{
  return (stack == NULL) ? 1 : 0;
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

void AtoB(struct Node **rodA, struct Node **rodB, struct Node **rodC) {push(rodB, pop(rodA));}
void BtoC(struct Node **rodA, struct Node **rodB, struct Node **rodC) {push(rodC, pop(rodB));}
void CtoA(struct Node **rodA, struct Node **rodB, struct Node **rodC) {push(rodA, pop(rodC));}
void AtoC(struct Node **rodA, struct Node **rodB, struct Node **rodC) {push(rodC, pop(rodA));}
void CtoB(struct Node **rodA, struct Node **rodB, struct Node **rodC) {push(rodB, pop(rodC));}
void BtoA(struct Node **rodA, struct Node **rodB, struct Node **rodC) {push(rodA, pop(rodB));}

void clockwise(struct Node **rodA, struct Node **rodB, struct Node **rodC, struct Node **disk)
{
  if(disk == rodA)
    return AtoB(rodA, rodB, rodC);
  if(disk == rodB)
    return BtoC(rodA, rodB, rodC);
  if(disk == rodC)
    return CtoA(rodA, rodB, rodC);
}

void counterclockwise(struct Node **rodA, struct Node **rodB, struct Node **rodC, struct Node **disk)
{
  if(disk == rodA)
    return AtoC(rodA, rodB, rodC);
  if(disk == rodB)
    return BtoA(rodA, rodB, rodC);
  if(disk == rodC)
    return CtoB(rodA, rodB, rodC);
}

struct Node **find(struct Node **rodA, struct Node **rodB, struct Node **rodC, int data)
{
  if(!isEmpty(*rodA))
    if(top(*rodA) == data)
      return rodA;

  if(!isEmpty(*rodB))
    if(top(*rodB) == data)
      return rodB;

  if(!isEmpty(*rodC))
    if(top(*rodC) == data)
      return rodC;

  return NULL;
}

int evendisk(struct Node **rodA, struct Node **rodB, struct Node **rodC, int num)
{
  int step = 0, count, disk;
  while(size(*rodC) != num)
  {
    step++;
    if(step % 2 == 1)
      clockwise(rodA, rodB, rodC, find(rodA, rodB, rodC, 1));
    else
    {
      count = step;
      disk = 0;
      while(1)
      {
        count/=2;
        disk++;
        if(count % 2 == 1)
          break;
      }
      disk++;
       if(disk % 2 == 1)
        clockwise(rodA, rodB, rodC, find(rodA, rodB, rodC, disk));
      else
        counterclockwise(rodA, rodB, rodC, find(rodA, rodB, rodC, disk));
    }
  }
  return step;
}

int odddisk(struct Node **rodA, struct Node **rodB, struct Node **rodC, int num)
{
  int step = 0, count, disk;
  while(size(*rodC) != num)
  {
    step++;
    if(step % 2 == 1)
      clockwise(rodA, rodB, rodC, find(rodA, rodB, rodC, 1));
    else
    {
      count = step;
      disk = 0;
      while(1)
      {
        count/=2;
        disk++;
        if(count % 2 == 1)
          break;
      }
      disk++;
       if(disk % 2 == 1)
        counterclockwise(rodA, rodB, rodC, find(rodA, rodB, rodC, disk));
      else
        clockwise(rodA, rodB, rodC, find(rodA, rodB, rodC, disk));
    }
  }
  return step;
}

void show(struct Node *rodA, struct Node *rodB, struct Node *rodC)
{
  printf("rodA: ");
  display(rodA);
  printf("rodB: ");
  display(rodB);
  printf("rodC: ");
  display(rodC);
}

int main()
{
  struct Node *rodA, *rodB, *rodC;
  int num;
  while(scanf("%d", &num) != EOF)
  {
    initLinkList(&rodA);
    initLinkList(&rodB);
    initLinkList(&rodC);

    for(int i = num; i > 0; i--)
      push(&rodA, i);
    //show(rodA, rodB, rodC);

    if(num % 2 == 0)
      printf("%d\n", evendisk(&rodA, &rodB, &rodC, num));
    else
      printf("%d\n", odddisk(&rodA, &rodB, &rodC, num));
  }
}
