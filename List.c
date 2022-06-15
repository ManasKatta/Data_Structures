#include<stdio.h>
#include<stdlib.h>
#include"lab8.h"

/*typedef struct studstruct
{
    int age;
    struct studstruct *nextPtr;
}Student;*/



Student* initList() /*This function initializes an empty List without dummy nodes.*/
{
    /*Student* emptyList; //idk if all this is neccesary but you never know with y'all, i couldve simply put return NULL but i decided to stay on the safe side
    emptyList = (Student*)malloc(sizeof(Student));
    if (emptyList==NULL)
    {
        printf("Malloc failed, returning NULL");//its supposed to return NULL anyway?
        return NULL;
    }
    emptyList = NULL;*/ //i was told by the TA no mallocing is involved but i kept it there just in case
    Student* emptyList = NULL;
    return emptyList; //returns NULL because it is empty and dummy nodes are not allowed 
}

Student* createNode(int age)/*This function receives an integer number, then creates a “Student” struct with the member
“age” equals to the input integer value. It returns the pointer to this struct.*/
{
    Student* node;
    node = (Student*)malloc(sizeof(Student)); //allocates node
    if (node==NULL) //malloc error checking 
    {
        printf("Malloc failed, returning NULL");
        return NULL;
    }
    node->age= age; //sets the age member of the node to the user defined value 

    return node;
}

Student* addToTail(Student* head, int new_data) /*This function receives the current linked-list and an integer value. It creates a “Student” struct
with the member “age” equals to the input integer value, and adds this struct at the tail of the
current linked-list. This function returns the pointer to the current linked-list.*/

{ 
    Student * temp = head; //temp variable for safety purposes
    Student *new_node = malloc(sizeof(Student));
    if (new_node==NULL) //malloc error checking 
    {
        printf("Malloc failed, returning NULL");
        return NULL;
    }
    new_node->age=new_data; //sets the age member of the struct to the user defined value 
    new_node->nextPtr=NULL; //sets the nextPtr node of the new node to NULL since it is the nextPtr 

    while(temp->nextPtr != NULL) // this little code segment traverses through the list until it finds the tail 
    {
        temp = temp->nextPtr;
    }
   
   temp->nextPtr = new_node;

    return head; 
} 

Student* addToHead(Student* head, int new_data) /*This function receives the current linked-list and an integer value. It creates a “Student” struct
with the member “age” equals to the input integer value, and adds this struct at the head of
the current linked-list. This function returns the pointer to the current linked-list.*/

{ 
    
    Student* new_node = (Student*) malloc(sizeof(Student)); //allocates new node 
    if (new_node==NULL) //malloc error checking 
    {
        printf("Malloc failed, returning NULL");
        return NULL;
    }
  
    
    new_node->age  = new_data; //sets the age member of the struct to the user defined value
    new_node->nextPtr = head;// puts the new head in front of the old head
   
    
    

    
    

    return new_node;
} 
Student* freeList(Student * head)/*This function receives the current linked-list, and frees all the previously allocated memories. It
sets the list back to NULL and returns it back to calling function.*/
{
  Student * temp = head;

  while(temp != NULL)
  {
    head = temp;
    //printf("\ntmp = %p ---- head = %p ----- head->nextPtr = %p",temp,head,head->nextPtr);
    temp = temp->nextPtr; //iterates the list to move to the nextPtr node
    free(head); //frees teh node
  }
  head = NULL; //sets the node to NULL

  return head; //returns the NULL node

  
}
void printList(Student *head) /*This function receives the current linked-list, and prints out all the “age” values from head of
the list to tail of the list.*/

{ 
    
    int i=0;
    while (head != NULL) //the following prints all of the elements in the linked list from head to tail. as a bonus it also prints the number of nodes 
    {
        printf(" %d ", head->age);
        head = head->nextPtr;
        i++;
    }
    printf("\nNumber of nodes: %d\n", i);
    
     
  
} 

int searchAge(Student* head, int x) /*This function receives the current linked-list and an integer, which is an age query. It searches
this age query in the list, and returns the location (0-based) of the first struct whose “age”
member equals to the age query. The function returns -1 if no struct has “age” member equals
to the age query.*/

{
    int location=0; //initializes the location to 0
    Student* temp = head;  //creating temp variable for safety purposes
    while (temp != NULL) //scans through the end of the list
    { 
        if (temp->age == x) 
            return location; //if the condition is satisfied it returns the location
        temp = temp->nextPtr; //iterates the list
        location++; //iterates the location 
    } 
    return -1; //if the age does not exist then the function will return -1 as stated in the lab assignment
}

