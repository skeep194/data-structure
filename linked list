//반복자 순회 방식의 양방향 linked list 구현체, [head,tail) 까지의 원소가 있는 것으로 가정함.
#include <stdio.h>
#include <stdlib.h>

typedef struct list
{
   struct list* next;
   struct list* prev;
   int value;
}list;

void push_back(list** head, list** tail, int value);
void pop_back(list** head, list** tail);
void push_front(list** head, list** tail, int value);
void pop_front(list** head, list** tail);
void print_list(list* head, list* tail);
void insert(list** pos,int value);//pos 앞에 원소 삽입
void erase(list** pos);//pos가 가리키는 원소 삭제
unsigned int size(list* head, list* tail);//O(n) 방식의 사이즈 구하는 함수
void make_list(list** head, list** tail);//head,tail이 null이라 가정하고 그 두개를 리스트의 헤드, 테일로 하는 새 리스트를 생성함

void make_list(list** head, list** tail)
{
   *head = *tail = (list*) malloc(sizeof(list));
   (*head)->next = *tail;
   (*head)->prev = *tail;
   (*head)->value = 0;
}

void push_back(list** head, list** tail, int value)
{
   list* newnode = (list*)malloc(sizeof(list));
   newnode->next = *head;
   newnode->prev = *tail;
   newnode->value = 0;

   (*head)->prev = newnode;

   (*tail)->next = newnode;
   (*tail)->value = value;

   (*tail) = newnode;
}

void pop_back(list** head, list** tail)
{
   if((*head)->next == *tail) return;

   list* deltail = *tail;
   (*tail) = (*tail)->prev;
   free(deltail);

   (*tail)->value = 0;
   (*tail)->next = *head;

   (*head)->prev = *tail;
}

void push_front(list** head, list** tail,int value)
{
   list* newnode = (list*) malloc(sizeof(list));
   newnode->next = *head;
   newnode->prev = *tail;
   newnode->value = value;

   (*head)->prev = newnode;
   *head = newnode;

   (*tail)->next = *head;
}

void pop_front(list** head, list** tail)
{
   if((*head)->next == *tail) return;

   list* delhead = *head;
   *head = (*head)->next;
   free(delhead);

   (*head)->prev = *tail;

   (*tail)->next = *head;
}

void insert(list** pos, int value)
{
   list* newnode = (list*)malloc(sizeof(list));
   newnode->next = *pos;
   newnode->prev = (*pos)->prev;
   newnode->value = value;

   (*pos)->prev->next = newnode;
   (*pos)->prev = newnode;
}

void erase(list** pos)
{
   (*pos)->prev->next = (*pos)->next;
   (*pos)->next->prev = (*pos)->prev;
   free(*pos);
}

unsigned int size(list* head, list* tail)
{
   unsigned int ret = 0;
   for(list* iter = head; iter != tail; iter = iter->next)
   {
      ++ret;
   }
   return ret;
}

void print_list(list* head, list* tail)
{
   for(list* iter = head; iter != tail; iter = iter->next)
   {
      printf("%d ",iter->value);
   }
}



int main()
{
   list* head,*tail;
   make_list(&head,&tail);
   push_back(&head,&tail,1);
   push_back(&head,&tail,2);
   push_back(&head,&tail,3);
   push_front(&head,&tail,4);
   pop_back(&head,&tail);
   push_front(&head,&tail,5);
   pop_front(&head,&tail);
   push_back(&head,&tail,6);
   pop_front(&head,&tail);
   
   list* iter = head->next;
   insert(&iter,35);
   erase(&iter);
   print_list(head,tail);
   printf("\n%d",size(head,tail));
}



