#include<stdio.h>
#include<stdlib.h>
typedef struct studstruct
{
    int age;
    struct studstruct *nextPtr;
}Student;

typedef struct linkedlist
{
    int numOfItems;
    int numOfEven;
    int numOfOdd;
    Student *head;
    Student *tail;

}StudentList;

typedef struct queuelist
{
    StudentList* list;
}Queue;

Queue initQueue();/*This function initializes an empty “Queue”. Note: all members in your empty queue should be properly initialized in this function, including “list”, “head”, “tail”, “numOfItems”, “numOfOdd“, and “numOfEven”.*/
int enQueue(int, Queue);/*This function receives the current “Queue” and an integer value. It creates a “Student” struct with the member “age” equals to the input integervalue, and enqueues this struct into the current “Queue”. It also updates the “numOfItems”, “numOfOdd“ and “numOfEven” members. This function returns 1 if the insertion succeeds, or -1 if the insertion fails. Note: this function should have O(1) computational complexity.*/
Student* deQueue(Queue);/*This function receives the current linked-list, and dequeues the earliest “Student” struct out of the current “Queue”and returns the pointer to the dequeued struct. It also updates the “numOfItems”, “numOfOdd“ and “numOfEven” members.This functionreturns NULL if no struct can be dequeued. Note: this function should have O(1) computational complexity. */
int getQsize(Queue);/*This function returns the total number of “Student”structsin the current “Queue”. Note:this function should have O(1) computational complexity.*/
int getNumOfEven(Queue);/*This function returns the total number of structs whose “age”valuesare even numbersin the current “Queue”. Note:this function should have O(1) computational complexity.*/
void printQueue(Queue);/*This function prints out all the “age” values from the head of the list to the tail of the list.*/
void emptyQueue(Queue);/*This function frees all the previously allocated memories and sets the current “Queue” to empty, meaning the “list” pointer in the “Queue” should be freed as well.*/





Queue initQueue()
{
    Queue q;
    q.list = malloc(sizeof(StudentList)); //allocates a queue pointer
    q.list->numOfItems=0; //queue member initilaizations
    q.list->numOfEven=0;
    q.list->numOfOdd=0;
    q.list->head = q.list->tail=NULL;
    return q;
}

int enQueue(int data, Queue p)
{
     
    Student* h = malloc(sizeof(Student));
    if(h==NULL) //malloc error checking 
    {
        printf("malloc failed");
        return -1;
    }
    h->age = data;
    h->nextPtr = NULL;

    if (p.list->tail == NULL)
    {
        p.list->head = p.list->tail = h;
        p.list->numOfItems++;
        
        if(h->age % 2 == 0) //checks if the given age value is even or odd and acts accordingly
        {
            p.list->numOfEven++;
        }
        else
        {
            p.list->numOfOdd++;
        }
    }
    else
    {
        p.list->tail->nextPtr= h;
        p.list->tail=h;
        p.list->numOfItems++;
        
        if(h->age % 2 == 0)
        {
            p.list->numOfEven++;
        }
        else
        {
            p.list->numOfOdd++;
        }
    }

    
    


    return 1;
    
}

Student* deQueue(Queue h)
{
    int size = getQsize(h); //used to see whether or not the queue is empty
    if(size==0) //checks if the queue is empty and acts accordingly
    {
        printf("\nnothing to dequeue :(\n");
        return NULL;
    }
    Student* p = h.list->head;
    h.list->head = p->nextPtr;
    

    printf("%d was dequeued\n", p->age);// for me to let me know the right value was removed
    h.list->numOfItems--;

        if(p->age % 2 == 0) //checks if the removed age value was even and acts accordingly
        {
            h.list->numOfEven--;
        }
        else
        {
            h.list->numOfOdd--;
        }
    
    
    
    return p;
}
void printQueue(Queue q) 
{ 
    
    
    Student* temp = q.list->head;
    while (temp != NULL)
    {
    printf(" %d ", temp->age);
    temp = temp->nextPtr;
    
    }
    
} 
void emptyQueue(Queue q)
{
   Student*temp = q.list->head; 
   int i=0;
    while(temp != NULL)
    {
        Student *new_head = temp->nextPtr;
        i++;
        free(temp);
        temp = new_head;
    }
    free(q.list);
    printf("\nfreed %d times (plus the queue pointer so really %d times)\n", i,i+1); // for me to let me know it freed the correct amount of times

}

int getQsize(Queue q)
{
    
    return q.list->numOfItems; //returns the size of the  queue 
}

int getNumOfEven(Queue q)
{
    printf("\nsize of Even is: %d", q.list->numOfEven); //for me so to save some time in main 
    return q.list->numOfEven; //returns the number of even ages in the queue
}

/*int main(void)
{
    Queue test;
    test = initQueue();
    enQueue(2,test);
    enQueue(34,test);
    enQueue(6,test);
    deQueue(test);
    
    printf("Queue:");
    printQueue(test);
    int qsize =getQsize(test);
    printf("\nsize of q is %d", qsize);
    getNumOfEven(test);
    emptyQueue(test);


    return 0;
}*/