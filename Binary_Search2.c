#include<stdio.h>
#include<stdlib.h>
typedef struct studstruct
{
    int age;
    int ID;
} Student;
typedef struct studdatabase
{
    int sizeOfDB; //indicates the number of elements in the array
    Student **array;
} StudentDB;

Student** readRecord(FILE*);/*This function receives a FILE pointer pointingto the provided csv file. It creates an array of “Student” struct pointers, and populates the array with the provided information. It returns the array or NULL back to the calling program.*/
StudentDB createDatabase(Student**,int);/*This function receives an array of “Student” pointers and an integer as the array size. It then creates a “StudentDB” struct with the input data, in which,the member “sizeOfDB” equals to the array size, and the “array” member should be a sorted array of “Student” pointers based on their “ID” in descendingorder. Insertionsortshould be used to sort the array. This functionreturns the “StudentDB” struct back tothecalling program.*/
Student* findStudentByID(StudentDB,int);/*This function receives a “StudentDB” struct and an integernumber. Itrecursively searches any “Student” that has “ID” member equal to this integernumber, and returns the pointer to this “Student”if such “Student”exists. This function returns NULLif no “Student” has “ID” member equal to the input integernumber. */
void freeDatabase(StudentDB);/*This function receives the current”StudentDB”, thenfrees all the previously allocatedmemories.*/
/*Custom functions*/
void insertionSortAge(Student**, int);/*this function recieves an array and sorts by the age parameter in DESCENDING order*/
void insertionSortID(Student**, int);/*this function recieves an array and sorts by the ID parameter in DESCENDING order*/
int binarySearchID(Student**,int,int,int);/*this function takes in the array, the lowest and highest index, and the target value and returns the index where the target is located. it returns -1 if it doesnt exist*/


void insertionSortID(Student **array, int size)
{
    int i;
    int query;
    int j;
    for (i = 1; i < size; i++)
    {
        query = array[i]->ID;
        j = i - 1;

        while (j >= 0 && array[j]->ID < query)
        {
            array[j + 1]->ID = array[j]->ID;
            j = j - 1;
        }
        array[j + 1]->ID = query;
    }
}

void insertionSortAge(Student **array, int size)
{
    int i;
    int query;
    int j;
    for (i = 1; i < size; i++)
    {
        query = array[i]->age;
        j = i - 1;

        while (j >= 0 && array[j]->age < query)
        {
            array[j + 1]->age = array[j]->age;
            j = j - 1;
        }
        array[j + 1]->age = query;
    }
}
Student **readRecord(FILE *fp)
{
    if (fp == NULL)
    {
        printf("file DNE\n");
        return NULL;
    }
    Student **array;
    int size;
    int i;
    int j;
    fscanf(fp, "%d", &size);
    array = malloc(size * sizeof(Student *));
    if (array == NULL)
    {
        printf("malloc failed");
        return NULL;
    }
    for (i = 0; i < size; i++)
    {
        array[i] = malloc(sizeof(Student));
        if (array[i] == NULL) // if this malloc fails it frees all previously allocated memories
        {
            printf("malloc 2 failed\n");

            for (j = 0; j < i; j++)
            {
                free(array[j]);
            }

            free((Student *)array);

            return NULL;
        }
    }

    while (!feof(fp))
    {
        for (i = 0; i < size; i++)
        {
            fscanf(fp, "%d,%d\n", &array[i]->age, &array[i]->ID);
        }
    }

    fclose(fp);
    return array;
}

StudentDB createDatabase(Student **array, int size)
{
    StudentDB StuDB;
    int i;
    int j;

    StuDB.sizeOfDB = size;
    StuDB.array = malloc(size * sizeof(Student *));
    if(StuDB.array == NULL) //malloc error checking 
    {
        printf("malloc failed returning useless database\n");
        return StuDB;
    }

    for (i = 0; i < size; i++)
    {
        StuDB.array[i] = malloc(sizeof(Student));
        if (array[i] == NULL) // if this malloc fails it frees all previously allocated memories
        {
            printf("malloc 2 failed returning a useless database\n");

            for (j = 0; j < i; j++)
            {
                free(array[j]);
            }
            free((Student *)array);

            return StuDB;
        }
    }

    for (i = 0; i < size; i++) //copies the contents into the array inside the database
    {
        StuDB.array[i]->ID = array[i]->ID;
        StuDB.array[i]->age = array[i]->age;
    }
    insertionSortID(StuDB.array, size);
    insertionSortAge(StuDB.array, size);
    
    
    return StuDB;
}

int binarySearchID(Student **array, int low, int high, int x)
{
    if(low > high)
        return -1;
    
    int mid = (low + high)/2;
	

    
    if(x > array[mid]->ID)
        return binarySearchID(array, low, mid-1, x);
    
    else if(x < array[mid]->ID)
        return binarySearchID(array, mid+1, high, x);
    
    else
        return mid;
}

Student *findStudentByID(StudentDB StuDB, int target)
{
    int x = binarySearchID(StuDB.array, 0, StuDB.sizeOfDB, target);
    if (x == -1)
    {
        printf("\nSTUDNE\n");
        return NULL;
    }
    return (StuDB.array[x]);
}

void freeDatabase(StudentDB StuDB)
{
    int i;
    int size = StuDB.sizeOfDB;
    if (StuDB.array == NULL)
    {
        printf("DB is empty\n");
        exit(-1);
    }
    for (i = 0; i < size; i++)
    {
        Student *temp = (Student *)(StuDB.array[i]);
        free(temp);
        temp = NULL;
    }
    free((Student *)StuDB.array);
}

/*int main(void)
{
    Student** array;
    int size = 10000;
    int target = 99170080;
    FILE* fp = fopen("students.csv","r");
    if(fp==NULL) 
    {
        printf("file DNE\n");
        return NULL;
    }
	array = readRecord(fp);
    StudentDB stuDB;
    stuDB = createDatabase(array, size);
    findStudentByID(stuDB, target);
    freeDatabase(stuDB);
	printf(":)");
}*/