#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct 
{
    int empID, age, ssn;
    float salary;
}Record;

int getSize(Record * person) //this function takes in the array of employees and fetches and returns the -1 index where the size is hidden as an int
{
        return *((int *)person - 1);
}

void freeRecordArray(Record * person) //this function takes in the array of employees and frees ALL of them
{
    free((void *)((int *)person - 1)); //frees the struct starting from the hidden size element
    
}


void adjustSalaries(Record* person,int age, float salary_multiplier) //this function takes in the array of employees, the age, and the multiplier and sets every employee with the age parameters salary multiplied by the multiplier parameter
{
    int i;
    int numEmps = getSize(person); // gets the hidden size so it knows how many times to iterate
    for(i=0;i<numEmps;i++)
        {
            if( (person+i)->age==age ) // checks to see if the age meets the qualifications
            {
                (person+i)->salary = ((person+i)->salary)*salary_multiplier; //if the age matches it multiplies their salary by the multiplier
            }
        }
}



Record * readRecordFile(FILE * fp) // this fuction takes in the the file pointer and scans the first element into a size variable to be hidden later, it scans the rest into the array of employees
{
    int numElems; //stores the hidden size
    int count=0; //iteration variable
    fscanf(fp, "%d\n", &numElems); //scans the first element in file(size) into numElems
    printf("\nemployees: %d\n", numElems);
    int *person = malloc(sizeof(Record) * numElems + sizeof(int)); //allocates the array some memory but its an int at first so it can store the hidden size as an int
    *person = numElems; //its an int rn so it scans the size into the first element to be stored as one
    (int*)person++; //even tho its already an int I casted it anyway since yall love to be petty and take off points 

    if (fp) // makes sure fp isnt NULL
        {
          
          while (!feof(fp)) //scans until the end of the file, scans the elements into a casted version of the employee array because it was originally an int to store the size 
            {
              if (4==fscanf(fp,"%f, %d, %d, %d\n",
                          
                          &(((Record *)person + count)->salary),
                          &(((Record *)person + count)->age),
                          &(((Record *)person + count)->empID),
                          &(((Record *)person + count)->ssn)
                           
                           ) 
                 )
              {
                  count++;
              }
            } 

        }
    return (Record*)person; //returns the array of employees as a Record* type 
}

Record * getEmployeeByAge(Record * person,int age) // this function takes in the array of employees and the age to check if one of them matches
{
    int i; //iteration variable
    int numEmps = getSize(person); //gets hidden size
    for(i=0;i<numEmps;i++)
        {
            if( (person+i)->age==age )
            {
                return (person+i); //as soon as it finds a match it returns the matching person and exits
            }
        }
        printf("\nperson does not exist\n"); //error checking if the person does not exist
        return NULL;
}

int main(void)
{
    FILE *fp;
    fp = fopen("employee.csv","r");
    //int i;
    
   

    Record *person;
    person = readRecordFile(fp);
    int numElems = getSize(person);
    printf("Number of Employees: %d\n", numElems);
    adjustSalaries(person, 18,5.0);
    /*for(i=0;i<numElems;i++)
    {
        printf("Person %d details: Salary = %.2f age = %d  ID = %d SSN = %d\n",i, (person+i)->salary, (person+i)->age, (person+i)->empID, (person+i)->ssn);
    }*/
 
    Record* testPerson = getEmployeeByAge(person, 18);
    printf("\nTest Person's salary is %.2f\n", testPerson->salary);
    
    
    

    freeRecordArray(person);
    fclose(fp);

    printf("\nFinished\n");

    return 0;
}