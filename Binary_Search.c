#include <stdio.h>
#include<stdlib.h>
typedef struct studstruct
{
	int age;
	int ID;
}Student;
Student** readRecord(FILE*); /*This function receives a FILE pointer pointingto the provided csv file. It creates an array of “Student” struct pointers, and populates the array with the provided information. It returns the array or NULL back to the calling program.*/
int comparison(void*,void*);/*This function receives two struct pointers, and comparesthe “ID” values in them. It returns 1 if the first one is larger, -1 if the second one is larger, or 0 if the two are equal.*/
int binarySearch(void**,int,int,void*); /*This generic function receives a sorted struct pointer array (sorted based on “ID” in descendingorder), two integers indicating the array boundaries, and a query “Student” struct pointer. This function recursively searches this query “Student” struct based on its “ID” member, and returns the index if this “ID” value exists in this array. This function returns -1 if the query “ID” valuedoesn’t exist in this array.*/
void freeArr(Student**,int); /*This function receives the current pointer array, and its size (it’s safe to assume that the main program has the size value), thenfrees all the previously allocatedmemories.*/


Student** readRecord(FILE* fp)
{
    if(fp==NULL)
    {
        printf("file DNE\n");
        return NULL;
    }
    Student** array;
	int size;
	int i;
    int j;
	fscanf(fp,"%d", &size);
	array = malloc(size * sizeof(Student*));
	if(array == NULL)
	{
		printf("malloc failed");
		return NULL;
	}
	for(i=0;i<size;i++)
	{
		array[i]=malloc(sizeof(Student));
        if (array[i] == NULL) // if this malloc fails it frees all previously allocated memories
		{
			printf("malloc 2 failed\n");

			
			for (j = 0; j < i; j++){
				free(array[j]);
			}

			
			free((Student*)array);

			return NULL;

		}
	}

	while(!feof(fp))
	{
		for(i=0;i<size;i++)
		{
			fscanf(fp, "%d,%d\n", &array[i]->age,&array[i]->ID);
		}
	}

	fclose(fp);
	return array;
    
}



int comparison(void* a, void* b)
{
	int query = ((Student*)(a))->ID;   //im assuming the query value is of type Student like this in main: Student target; target.ID = 5; If target value is declared as int target = 5; then just change "query" in the comparison statements to "*x"
    //int* x = a; this is commented out for compiler purposes but it is very much there if needed for scenario 2 mentioned above ^^^
	int mid = ((Student*)(b))->ID;
	printf("comparing %d to %d\n", query, mid);
	if(query > mid)
	{
		return 1;
	}
	if(query < mid)
	{
		return -1;
	}
	if(query == mid)
	{
		return 0;
	}
    return 0;
}




int binarySearch(void** array, int low, int high, void * target)
{
    if(low > high)
        return -1;
    
    int mid = (low + high)/2;
	/*Student* a;
	a = target;
	printf("target is %d\n",a->ID);*/
    int result = comparison(target, array[mid]);
    
    if(result > 0)
        return binarySearch(array, low, mid-1, target);
    
    else if(result < 0)
        return binarySearch(array, mid+1, high, target);
    
    else
        return mid;
}

void freeArr(Student** array, int size)
{
	int i;
	if (array == NULL)
	{
		printf("array is empty");
		return NULL;
	}
	 
	for (i = 0; i < size; i++)
		{
			Student* temp = (Student*)(array[i]);
			free(temp);
			temp = NULL;
		}
		free((Student*)array);
	
}
/*int main(void)
{
	Student target;
    target.ID = 99971339;
	FILE* fp = fopen("students.csv","r");
    if(fp==NULL) 
    {
        printf("file DNE\n");
        return NULL;
    }
	Student ** array = readRecord(fp);

	int size = 10000;

	int low = 0, high = size;
	int result = binarySearch((void**)array, low, high, &target);

	if (result != -1)
		printf("Element found at index %d", result);
	else
		printf("Element not found in the array");
	
	freeArr(array, size);
	return 0;
}*/