#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
 
 
struct Student {
 
  int id;
  char name[255];
  int age;
  float gpa;
 
};
 
 
 
typedef struct Student Student;
 
 
//this operator takes the id and name
Student*  makeStudent(int id, char * name, int line)
 
{
 
  if(id > 0 && strlen(name) >= 1)
 
  {
 
    Student  *x = malloc(sizeof(Student));
    x->id = id;
    strcpy(x->name, name);
    return x;
}
 
    if (id < 0)
 
        printf("Could not create student record from file row %d: ID is invalid.\n", line-3);
 
    if (strlen(name) < 1)
 
        printf("Could not create student record from file row %d: Name is invalid.\n", line-2);
 
    return NULL;
 
}
 
//This operator takes student age and assigns to the student
 
int setAge(Student * s, int age, int line)
 
{
 
  if (age > 0)
 
  {
 
    s->age = age;
 
    return 1;
 
  } else
 
      printf("Could not create student record from file row %d: Age is invalid.\n", line-1);
 
    return 0;
}
 
 
// This operator sets studnent gpa and assigns it
int setGPA(Student * s, float gpa, int line)
 
{
 
  if (gpa >= 0.0 && gpa <= 4.0)
 
  {
 
    s->gpa = gpa;
 
    return 1;
 
  } else
 
      printf("Could not create student record from file row %d: GPA is invalid.\n", line);
 
    return 0;
 
}
 
 
//the main methods opens and reads the file
//the main method calls makestudent(),set age(), set GPA()
int main(int argc, char *argv[])
 
{
 
  printf("CS 2123 Assignment 1 was written by Grecia Gonzalez.\n");
 FILE *wordFile;
 
  wordFile = fopen(argv[1], "r");
 
 
 
  int lineCountr=0, studentCount = 0, i = 1, ageTotal = 0, nextId, nxtAge;
 
  float nxtGPA, gpaTotal=0;
 
  char nextName[100];
 
  Student ** array = malloc(sizeof(Student *));
//Checks if the file is empty
  if(array == NULL)
 
  {
 
      printf("Error: Malloc returned NULL");
 
      exit(EXIT_FAILURE);
 
  }
//Calls info from file and checks that it's not empty
//Allocates memory of students, with corresponding ID,Name,Age,and GPA
  while(!feof(wordFile))
 
  {
 
    fscanf(wordFile, "%d %[^\n]s", &nextId, nextName);
 
    fscanf(wordFile, "%d %f", &nxtAge, &nxtGPA);
 
    lineCountr= lineCountr+4;
 
    array = realloc(array, i * sizeof(Student *));
 
    *(array + studentCount) = makeStudent(nextId, nextName, lineCountr);
 
     if (*(array+studentCount) != NULL)
 
     {
 
       if (setAge(*(array+(studentCount)), nxtAge, lineCountr) && setGPA(*(array+(studentCount)), nxtGPA, lineCountr))
 
       {
 
          ++studentCount;
 
          ++i;
 
          ageTotal += nxtAge;
 
          gpaTotal += nxtGPA;
 
       }
 
     }
 
   }
    //Print number of students, calculates the average age and average gpa
//Frees memory and closes file
 
  printf("Number of students: %d\n", studentCount);
 
  printf("Average age: %d\n", ageTotal/studentCount);
 
  printf("Average GPA: %.2f\n", gpaTotal/studentCount);
 
 
 
  for (i=0; i<studentCount; i++)
 
       free(*(array+i));
 
  free(array);
 
 
 
  fclose(wordFile);
 
  return(0);
 
}
                                                                                  
            
                          
