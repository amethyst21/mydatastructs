#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Student{
int id;
int age;
float gpa;
char name[255];
}Student;

Student *list;

Student *make_student(int id, char name[255]);
Student *set_Age(int age);
Student *set_GPA(float gpa);
void printList(int listCount);

int main(int nargs, char *argv[])
{
   FILE *infp;
   int listCount=0;
   int i=0;
   int id;
   int age;
   float gpa;
   char name[255];

/*check you have a file on command line*/
   if(nargs != 2)
   {
       printf("No datafile was inputted on command line!\n");
       return(EXIT_FAILURE);
   }

   /*open file*/

   infp = fopen(argv[1],"r");
/*check if data is in data file*/

   if(infp == NULL)
   {
       printf("Error opening file please try again\n");
           return(EXIT_FAILURE);
   }


/*read data file into pointer that points to the structs that are being filled*/

       while(!feof(infp)) {
       fscanf(infp, "%d\n", &id);
       fscanf(infp, "%[^\n]", name);
       fscanf(infp, "%d\n", &age);
       fscanf(infp, "%f\n", &gpa);
       listCount++;
   }

       printf("# of students: %d\n", listCount);

       /*malloc for number of structs*/
       fclose(infp);
       list = (Student *) malloc(sizeof(Student) * listCount);

       infp = fopen(argv[1],"r");  
  
   while(!feof(infp))
   {
           fscanf(infp, "%d\n", &id);
           fscanf(infp, "%[^\n]", name);
           fscanf(infp, "%d\n", &age);
           fscanf(infp, "%f\n", &gpa);
           Student *temp = NULL;
           Student *temp1 = NULL;
           Student *temp2 = NULL;
       /*check id and name*/
               if(id>0)
               {
                       temp=make_student(id,name);
               }
   /* check age*/
               if(age > 0)
               {
                       temp1=set_Age(age);
               }
   /*check gpa*/
               if(gpa >=0 && gpa<= 4.0)
               {
                       temp2=set_GPA(gpa);
               }
/*put temp into listp[i]*/
           (list + i)->id = (temp)->id;
          
           strcpy((list + i)->name,temp->name);
          
           (list + i)->gpa = (temp2)->gpa;
           (list + i)->age = (temp1)->age;
          
           free(temp);
           free(temp2);
           free(temp1);
          
           i++;
   }
      
       printList(listCount);
        printf("The total amount of students is:%d\n",listCount);
   return (0);
}
/*passed the check so fill name and id*/
Student *make_student(int id, char name[255])
{
          
       Student *ret=(Student *)malloc(sizeof(Student));
       ret->id=id;
       strcpy(ret->name,name);
      
       return(ret);
}
/*passed the check so fill name and id*/
Student *set_Age(int age)
{
          
       Student *ret=(Student *)malloc(sizeof(Student));
       ret->age=age;
      
       return(ret);
}
/*passed the check so fill name and id*/
Student *set_GPA(float gpa)
{
          
       Student *ret=(Student *)malloc(sizeof(Student));
       ret->gpa=gpa;
       return(ret);
}
/*print stuff for me*/
void printList(int listCount)
{
  
       int i;
   printf("list:\n");
   for(i = 0; i < listCount; i++) {
       Student *p = list + i;
       printf("student: %d\n id: %d\n name:%s\n age:%d\n gpa:%f\n", (i + 1), p->id, p->name,p->age,p->gpa);
   }
}

