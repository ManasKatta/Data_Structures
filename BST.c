#include<stdio.h>
#include<stdlib.h>

typedef struct
{    
    int ID;    
    float salary;    
    int ssn;
}Employee;

typedef struct node
{            
    Employee* data;            
    struct node *left, *right;
}Node;

Employee** readRecord(FILE*);/*This function receives a FILE pointer pointingto the provided csv file. It creates an array of “Employee” struct pointers, and populates the array with the provided information. It returns the array or NULL back to the calling program.*/
int comparison(void*,void*);/*This function receives two Employee struct pointers, and comparesthe “ssn” values in them. It returns 1 if the first ssnis larger, -1 if the second ssnis larger, or 0 if the two values are equal.*/
Node* insertBST(Node*, Employee*);/*This function receives the current BST root and an Employee struct pointer. It creates a new Node with the given Employee information andrecursivelyinserts the new node into the */
Employee* searchBST(Node*,int);/*This function receives the current BST root and an integer number. It recursively searches any Employee struct whose “ssn” member is equal to the given integernumber. This function returns the pointer to the struct if such struct exists, or NULL if no such struct can be found.*/
void deleteTree(Node*);/*This function receives the currentBST root,thenfrees the memory for the whole BST.*/
//Custom Functions//
Node* NewNode(Employee*);
//End of Custom Functions//

Node* NewNode(Employee* emp)
{
    Node* new_node = malloc(sizeof(Node));
    if(new_node==NULL)
    {
        printf("malloc failed\n");
        return NULL;
    }
   
    new_node->data = emp;
    new_node->left = new_node->right = NULL;

    return new_node;
}
int comparison(void* a, void* b)
{
    
    if(((Employee*)(a))->ssn > ((Employee*)(b))->ssn)
    {
        return 1;
    }
    else if (((Employee*)(b))->ssn > ((Employee*)(a))->ssn)
    {
        return -1;
    }
    else if (((Employee*)(a))->ssn == ((Employee*)(b))->ssn)
    {
        return 0;
    }

    return 0;
}

Employee **readRecord(FILE *fp)
{
    if (fp == NULL)
    {
        printf("file DNE 2\n");
        return NULL;
    }
    Employee **array;
    int size;
    int i;
    int j;
    fscanf(fp, "%d", &size);
    array = malloc(size * sizeof(Employee *));
    if (array == NULL)
    {
        printf("malloc failed");
        return NULL;
    }
    for (i = 0; i < size; i++)
    {
        array[i] = malloc(sizeof(Employee));
        if (array[i] == NULL) // if this malloc fails it frees all previously allocated memories
        {
            printf("malloc 2 failed\n");

            for (j = 0; j < i; j++)
            {
                free(array[j]);
            }

            free((Employee *)array);

            return NULL;
        }
    }

    while (!feof(fp))
    {
        for (i = 0; i < size; i++)
        {
            fscanf(fp, "%d,%f,%d\n", &array[i]->ID, &array[i]->salary, &array[i]->ssn);
        }
    }

    fclose(fp);
    return array;
}

Node* insertBST(Node* tree, Employee* emp)
{
    if (tree == NULL) 
    {
        return NewNode(emp); 
    }
  
   int result = comparison(emp, tree->data);
   
    if (result > 0) 
        tree->left  = insertBST(tree->left, emp); 
    else if (result < 0) 
        tree->right = insertBST(tree->right, emp);    
  
    
    return tree; 
}

Employee* searchBST(Node* tree, int query)
{
    if(tree == NULL);
    {
        printf("tree DNE");
        return NULL;
    }
    
    if(tree->data->ssn == query)
    {
        return tree->data;
    }
    
    else if (tree->data->ssn > query)
    {
        return searchBST(tree->right, query);
    }
    
    else if(tree->data->ssn < query)
    {
        return searchBST(tree->left,query);
    }
}

void deleteTree(Node* tree)
{
    if(tree==NULL) return;
    deleteTree(tree->left);
    deleteTree(tree->right);
    free(tree);
}

/*int main(void)
{
   int i;
   FILE* fp = fopen("employee.csv","r");
   if (fp == NULL)
   {
       printf("file DNE");
       return NULL;
   }
   Employee** array = readRecord(fp);
   Node* tree = NULL;
   tree = insertBST(tree, array[0]);
   for(i=1;i<3;i++)
   {
       insertBST(tree,array[i]);
   }
   
}*/