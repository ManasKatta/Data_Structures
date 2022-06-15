#include<stdio.h>
#include<stdlib.h>
typedef struct studstruct
{
    int age;
    struct studstruct *nextPtr;
}Student;

Student* initListWithDummyNode()/*This function initializes an empty List withtwo dummy nodes: one dummy node at the head of the linked-list, and one dummy node at the tail of the linked-list. */
{
    Student* dummyNodeHead; //the following lines allocate the head and tail dummy nodes
    dummyNodeHead = malloc(sizeof(Student));
    if(dummyNodeHead==NULL)//malloc error checking
    {
        printf("head did not allocate");
        return NULL;
    }
    Student* dummyNodeTail;
    dummyNodeTail = malloc(sizeof(Student));
    if(dummyNodeTail==NULL)//malloc error checking
    {
        printf("tail did not allocate");
        return NULL;
    }
    dummyNodeHead->nextPtr = dummyNodeTail;//empty list so head->next is tail
    dummyNodeHead->age = '\0';
    
    dummyNodeTail->nextPtr = NULL;//its the tail so next is null
    dummyNodeTail->age = '\0'; //setting values of the dummy node to 0;
    
    

    
    return dummyNodeHead;
}
int insertToHead(Student* head, int new_data)/*This function receives the current linked-list and a float value. It creates a “Student” struct with the member “age” equals to the input integervalue, and adds this struct at the head of the current linked-list (hint: this struct should be right after the head dummy node). This function returns 1 if the insertion succeeds, or 0 if the insertion fails. */ 
{ 
    
    Student* new_node = (Student*) malloc(sizeof(Student)); 
    if(new_node==NULL)//malloc error checking
    {
        printf("malloc failed");
        return 0;
    }
  
    
    new_node->age  = new_data;
    new_node->nextPtr = head->nextPtr;
    head->nextPtr = new_node;

    
    
    

    
    

    return 1;
} 
int insertToTail(Student* head, int new_data)/* This function receives the current linked-list and a float value. It creates a “Student” struct with the member “age” equals to the input integervalue, and adds this struct at the tail of the current linked-list (hint: this struct should be right before the tail dummy node). This function returns 1 if the insertion succeeds, or 0 if the insertion fails.*/
{
    
    Student *new_node = malloc(sizeof(Student));
    if(new_node==NULL)//malloc error checking
    {
        printf("malloc failed");
        return 0;
    }
    new_node->age=new_data; //inserts the data 
    new_node->nextPtr=NULL; //since this is the tail, the next pointer is NULL

    while(head->nextPtr->nextPtr != NULL) //the following increments the list until it finds the tail dumy node
    {
        head = head->nextPtr;
    }
   new_node->nextPtr = head->nextPtr;
   head->nextPtr = new_node;

   

    
   return 1;
}

void freeList(Student* head)/*This function receives the current linked-list, and frees all the previously allocated memories.*/
{
   Student* tmp; //tmp variable for safety purposes
   int i=0;//keeps track of number of nodes freed

   while (head != NULL) //the following frees ALL nodes including the 2 dummy nodes
    {
       tmp = head;
       head = head->nextPtr;
       
       free(tmp);
       i++;
    }
    free(head);
    printf("\nFreed %d nodes",i); //this print statement should print the number of real nodes + the 2 dummy nodes

}
void printList(Student* list)/*This function receives the current linked-list, and prints out all the “age” values from head of the list to tail of the list (note: only print out the values in real nodes).*/ 
{ 

      
    list = list->nextPtr; //this statement increments the list so that it starts at the first real node instead of dummy node
    while(list->nextPtr != NULL)//the statement inside the while loop prevents the loop from printing the tail dummy node and the following prints all REAL nodes
    {
        printf(" %d ", list->age);
        list = list->nextPtr;
    }
    
     
  
} 

void emptyList(Student* head)/*This function receives the current linked-list, and frees the memories for all REAL nodes. After calling this function, the linked-list should contain nothing but the head and tail dummy nodes. Note: the addresses of the head and tail dummy nodes should not be changed.*/
{
   Student* tmp;//temp variable for safety purposes
   int i=0; //count variable to keep track of number of nodes freed

head = head->nextPtr;//increments the list so that it points to the real node instead of the dummy head
   while (head->nextPtr != NULL) //the statment inside this while loop prevents the function from freeing the tail dummy node and the following loop frees all the real nodes
    {
       tmp = head;
       head = head->nextPtr;
       
       free(tmp);
       i++;
    }
    printf("\nemptyList Freed %d nodes",i); //this print statement should print the number of real nodes in the list 

}


/*int main(void)
{
    Student* head;
    head = initListWithDummyNode();
    insertToHead(head,3);
    insertToHead(head,23);
    insertToHead(head, 6);
    insertToTail(head,35);
    insertToHead(head, 7);
    printf("Linked list contents: "); 
    printList(head); 

    
    freeList(head);
    

}*/