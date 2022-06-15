#include<stdio.h>
#include<stdlib.h>

typedef struct studstruct
{
    int age;
    struct studstruct *nextPtr;
}Student;

typedef struct linkedlist
{
    Student *head;
    Student *tail;

}StudentList;

/*StudentList* initStack();
int pushStack(StudentList*,int);
Student* popStack(StudentList*);
StudentList* initQueue();
int enQueue(StudentList*,int);
Student* deQueue(StudentList*);
void printList(StudentList*);
void freeList(StudentList*);*/


StudentList* initStack()/*This function initializes an empty stack using “StudentList” struct. Note: head and tail members should be NULL after initialization.*/
{
    StudentList * p;
    p = malloc(sizeof(StudentList));//allocates new stack
    if(p==NULL)//malloc error checking 
    {
        printf("malloc faild :/");
        return NULL;
    }
    p->head = p->tail = NULL;
    return p;
}

StudentList* initQueue()/*This function initializes an empty queue using “StudentList” struct. Note: head and tail members should be NULL after initialization.*/
{
    StudentList * p;
    p = malloc(sizeof(StudentList)); //allocates new queue
    if(p==NULL)//malloc error checking
    {
        printf("malloc faild :/");
        return NULL;
    }
    p->head = p->tail = NULL; 
    return p;
}
int insertAtHead(StudentList *h, int age)
{
    Student *p = malloc(sizeof(Student));
    if (p==NULL)
    {
        printf("malloc failed");
        return 1;
    }
    p->age = age;

    if(h->head == NULL)
    {
        p->nextPtr = NULL;
        h->head = h->tail = p;
    }
    else
    {
        p->nextPtr = h->head;
        h->head = p;
    }

    return 0;
}

int insertAtTail(StudentList * h, int age)
{
    Student* p; 
    p = malloc(sizeof(Student));
    if(p==NULL)
    {
        printf("malloc failed");
        return 1;
    }
    p->age = age;
    p->nextPtr = NULL;

    if (h->tail == NULL)
    {
        h->head = h->tail = p;
    }
    else
    {
        h->tail->nextPtr= p;
        h->tail=p;
    }

    return 0;
    
}
void printList(StudentList *head) /*This function prints out all the “age” values from the head of the list to the tail of the list.*/
{ 
    
    
    Student* temp = head->head;
    while (temp != NULL)
    {
    printf(" %d ", temp->age);
    temp = temp->nextPtr;
    
    }
    
} 





int getLength(StudentList* head)
{
    int i=0;
    Student* temp = head->head;
    while (temp != NULL)
    {
        i++;
        temp = temp->nextPtr;
    
    }

    return i;
}

int pushStack(StudentList*h,int age)/*This function receives the current linked-list and an integer value. It creates a “Student” struct with the member “age” equals to the input integervalue, and pushesthis struct into the current linked-list at the headof the current linked-list. This function returns 1 if the insertion succeeds, or -1if the insertion fails*/
{
    int test = insertAtHead(h,age); //uses insert head to push a node at the head of a stack
    if(test==1)//malloc error checking 
    {
        printf("malloc failed, aborted\n");
        
        return -1;
    }
    return 1;
}

int enQueue(StudentList* h, int age)/*This function receives the current linked-list and an integer value. It creates a “Student” struct with the member “age” equals to the input integervalue, and enqueuesthis struct into the current linked-list at the front(head)of the current linked-list. This function returns 1 if the insertion succeeds, or -1if the insertion fails.*/ 
{
    int test = insertAtHead(h,age);//uses insert head function to enqueue at head of the list
    if(test==1)//malloc error checking 
    {
        printf("malloc failed, aborted\n");
        return -1;
    }
    return 1; //error codes
}

Student * deQueue(StudentList*h)/*This function receives the current linked-list, and dequeues the earliest “Student” struct out of the current linked-list (which is at the tailcurrently), and returns the pointer to the dequeued struct, it returns NULL if no struct can be dequeued.*/
{
    Student* second_last = h->head;
    Student* last = h->head;
    if(getLength(h)==0)
    {
        printf("list is empty");
        return NULL;
    }
    while(last->nextPtr != NULL)
    {
        second_last=last;
        last = last->nextPtr;
    }
    if(last==h->head)
    {
        h->head = NULL;
    }
    second_last->nextPtr=NULL;
    printf("node value returned: %d\n", last->age);
    return last;
}
Student* popStack(StudentList*h)/*This function receives the current linked-list, and pops out the latest “Student” struct out of the current linked-list (which is at the headcurrently), and returns the pointer to the popped struct, it returns NULL if no struct can be popped.*/
{
    if(getLength(h)==0)
    {
        printf("list is empty");
        return NULL;
    }
    Student *p = h->head;//temp variable
    h->head = p->nextPtr;//changes the head to the new head 
    printf("node value being removed = %d\n", p->age); //for me to make sure the right thing is popped
    return p;
}
void freeList(StudentList *head)/*This function frees all the previously allocated memories*/
{
   Student *temp = head->head; //the following frees all memories and prints the addresses for debugging purposes
    while(temp != NULL)
    {
        Student *new_head = temp->nextPtr;
        //printf("\ntmp = %p ---- head = %p ----- head->nextPtr = %p",temp,head,temp->nextPtr);
        free(temp);
        temp = new_head;
    }
    free(head);

}

/*int main(void)
{
    StudentList *llist;
    llist = initStack();
    
    pushStack(llist, 3);
    pushStack(llist, 23);
    pushStack(llist, 11);
    pushStack(llist, 6);
    pushStack(llist, 7);
    popStack(llist);
    popStack(llist);
    
    
    printf("List contents:");
    printList(llist);
    int length = getLength(llist);
    printf("\nLength of StudentList: %d\n", length);
    
    
   
    freeList(llist);
 

    

    
    return 0;
}*/