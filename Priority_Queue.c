#include<stdio.h>
#include<stdlib.h>

typedef struct studstruct
{
    int age;
    float priority;
    struct studstruct *nextPtr;
    struct studstruct *previousPtr;
}Student;

typedef struct StudentList
{
    int numOfItems;
    Student *head;
    Student *tail;

}StudentList;

typedef struct qstruct
{
    StudentList* list;
}PQueue;

PQueue initPQueue();/*This function initializes an empty “PQueue”. Note: all members in your empty queue should be properly initialized in this function, including “list”, “head”, “tail”, and “numOfItems”.*/
Student* createNode(float,int);/**/
int insertPQ(float,int,PQueue);/*This function receives onefloating-point numberand one integer number, and creates a “Student” struct with the member “priority” equals to the first input value, and the member “age” equals to the second input value. It theninsertsthis struct into the current “PQueue”based on its priority value in descending order(the struct with highest priority value should be at head, the struct with lowest priority value should be at tail). This function returns 1 if the insertion succeeds, or -1 if the insertion fails. Note: this function should have O(n) computational complexity.*/
Student* deleteMin(PQueue);/*This function receives the current PQueue, and removesthestruct with the lowest priorityvalueout of the current “PQueue”and returns the pointer to the removedstruct. This functionreturns NULL if no struct can be removed. Note: this function should have O(1) computational complexity.*/
Student* deleteMax(PQueue);/*This function receives the current PQueue, and removes the struct with the highestpriority valueout of the current “PQueue” and returns the pointer to the removed struct. This function returns NULL if no struct can be removed. Note: this function should have O(1) computational complexity. */
Student* returnMin(PQueue); /*This function receives the current PQueue, and returns the pointer to the struct with the lowest priority valuewithout modifying the PQueue. This function returns NULL if no Min struct exists. Note: this function should have O(1) computational complexity. */
Student* returnMax(PQueue); /*This function receives the current PQueue, and returns the pointer to the struct with the highestpriority valuewithout modifying the PQueue. This function returns NULL if no Max struct exists. Note: this function should have O(1) computational complexity. */
void freePQueue(PQueue); /*This function frees allthe previously allocated memories and sets the current “PQueue” to empty, meaning the “list” pointer in the “PQueue” should be freed as well.*/
void printPQueue(PQueue);/*This function prints out all the “priority” and “age” values from the head to the tail of the list. The two membersshould be printed in this format: priority (age)*/

PQueue initQueue()
{
    PQueue q;
    q.list = malloc(sizeof(StudentList));
    if(q.list==NULL) //malloc error checking
    {
        printf("malloc failed\n");
        return q;
    }
    q.list->numOfItems=0;
    q.list->head = q.list->tail=NULL;
    return q;
}


int insertPQ(float priority,int age, PQueue q)
{
    if(q.list==NULL) //null error check
    {
        printf("list is empty\n");
        return -1;
    }
    Student* new = (Student*)malloc(sizeof(Student));
    if(new==NULL) //malloc error check
    {
        printf("malloc failed\n");
        return -1;
    }
    new->age=age;
    new->priority = priority;
    new->nextPtr = NULL;
    Student* temp = q.list->head;
    if(q.list->head==NULL) //first insertion
    {
        q.list->head=q.list->tail=new;
        q.list->numOfItems++;
    }
    else
    {
        if(new->priority > temp->priority) //if its the head
        {
            if(q.list->numOfItems == 1)
            {
                q.list->tail=temp;
                q.list->tail->previousPtr = new;
            }
            new->nextPtr = q.list->head;
            q.list->head=new;
            q.list->numOfItems++;
        }
        else
        {



            while(temp->nextPtr != NULL && new->priority < temp->nextPtr->priority)
            {
                temp = temp->nextPtr;
            }
            if(temp->nextPtr == NULL) //if its the last Student
            {
                q.list->tail->nextPtr=new;
                new->previousPtr=q.list->tail;
                q.list->tail = new;
                q.list->numOfItems++;
            }
            else
            {
                if(temp->nextPtr->nextPtr==NULL) // if its second to last Student cuz we need it for delete min
                {
                    q.list->tail->previousPtr = new;
                }
                new->nextPtr = temp->nextPtr;
                temp->nextPtr=new;
                new->previousPtr=temp;
                q.list->numOfItems++;



            }


        }
    }

    return 1;
}
void printPQueue(PQueue q)
{
    if(q.list==NULL) //null list check
    {
        printf("list is empty\n");
        exit(-1);
    }


    Student* temp = q.list->head;
    printf("Contents:");
    while (temp != NULL)
    {
    printf(" %.2f (%d) --> ", temp->priority,temp->age);
    temp = temp->nextPtr;
    }
    printf("End");

}
Student* returnMax(PQueue q)
{
    if(q.list==NULL || q.list->head==NULL) // null check
    {
        printf("list is empty\n");
        return NULL;
    }
    printf("returning %.2f\n",q.list->head->priority);
    return q.list->head;
}
Student* returnMin(PQueue q)
{
    if(q.list==NULL || q.list->tail==NULL)//null check
    {
        printf("list is empty\n");
        return NULL;
    }
    printf("returning %.2f\n",q.list->tail->priority);
    return q.list->tail;
}
Student* deleteMax(PQueue h)
{
    if(h.list==NULL || h.list->head==NULL)//null check
    {
        printf("list is empty\n");
        return NULL;
    }
    Student* p = h.list->head;
    h.list->head = p->nextPtr;
    h.list->numOfItems--;
    printf("%.2f was dequeued\n", p->priority);

    return p;

}
Student* deleteMin(PQueue h)
{
    if(h.list==NULL || h.list->head == NULL)//null check
    {
        printf("list is empty\n");
        return NULL;
    }
    if(h.list->numOfItems == 1) // if theres only one then tail->prev is null so i need a special case
    {
        deleteMax(h);

    }
    else
    {
        if(h.list->numOfItems == 2) //once the list size is down to 2 then the tails previous node needs to be the head
        {
            h.list->tail->previousPtr = h.list->head;
        }
    
        Student*  p = h.list->tail;
        h.list->tail = p->previousPtr;
        h.list->tail->nextPtr = NULL;
        h.list->numOfItems--;

        printf("%.2f was dequeued\n", p->priority);

        return p;
    }
    
    return NULL; //if none of the conditions above are met then something is wrong so it returns NULL;
}
void freePQueue(PQueue q)
{
    if(q.list==NULL) //null list check
    {
        printf("list is empty\n");
        exit(-1);
    }
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
    q.list = NULL;
    printf("\nfreed %d time(s)\n", i);

}


int getSize(PQueue q)
{
    if(q.list==NULL) // null list check
    {
        printf("list doesn't exist");
        return -1;
    }
    return q.list->numOfItems;
}
Student* createNode(float priority, int age)
{    
    Student* node = malloc(sizeof(Student));    
    if (node == NULL)//malloc error check
    {        
        printf("malloc failed\n");       
        return NULL;    
    } 

    node->age = age;
    node->priority=priority;       
    node->nextPtr = NULL;        
    return node;    

}

/*int main(void)
{
    PQueue test = initQueue();
    insertPQ(3,23,test);
    insertPQ(2,6,test);
    insertPQ(1,2,test);
    
    
    
  
    
    
    int numOfItems = getSize(test);
    printf("numOfItems is %d\n", numOfItems);
   
    




    printPQueue(test);
    freePQueue(test);

    return EXIT_SUCCESS;
}*/
