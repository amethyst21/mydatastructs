#include <stdio.h>

#include <stdlib.h>

#include <string.h>

typedef struct{

int iPriority; /* Priority of the student to be enrolled */

int iStudentID; /* ID of the student */

} WaitlistEntry;

typedef struct PQNode {

WaitlistEntry info; /* WaitlistEntry stored in the node (sorted with largest priority first) */

struct PQNode* pNext; /* Pointer to next node in the LL */

struct PQNode* pPrev; /* Pointer to previous node in the LL */

} PQNode;

typedef struct{

int iCourseNumber; /* Course number of the course */

int* iStudentIDs; /* Array of IDs of students enrolled in the course */

int iNumEnrolled; /* Number of Students currently enrolled in course */

int iMaxEnrolled; /* Max number of Students that can enroll in the course */

PQNode* pFront; /* Priority queue representing the waitlist for the course */

} Course;

typedef enum { FALSE, TRUE } bool;

/* PQ function prototypes */

void printQueue( PQNode* pFront );

/* To be completed by you */

WaitlistEntry dequeue( PQNode** ppFront );

void enqueue( PQNode** ppFront, WaitlistEntry info );

/* function prototypes for course management */

void enrollStudent( Course* pCourse, int iStudentID );

void waitlistStudent( Course* pCourse, WaitlistEntry wl );

int searchCourses( Course* pCourses, int iNumCourses, int iCourseID );

int findStudent( Course* pCourse, int iStudentID );

/* To be completed by you */

void addSeats( Course* pCourse, int NumAdded );

void attemptEnrollment( Course* pCourse, int iStudentID, int iPriority );

void dropStudent( Course* pCourse, int iStudentID );

/* provided code - DO NOT CHANGE

* main simulates the waitlist for a number of courses by calling your functions

*/

int main( )

{

char courseFileName[] = "a3_CourseData.txt";

char enrollFileName[] = "a3_EnrollData.txt";

char szCommand[256];

FILE *in_file = fopen(courseFileName, "r");

Course *pCourses;

int i;

int iNumCourses;

int iCourseNumber;

int iCourse;

int iStudent;

int iPriority;

int iNumAdd;

  

printf("CS 2123 Assignment 3 written by Grecia Gonzalez\n");

  

if (in_file == NULL)

{

printf("File %s not found.\n", courseFileName);

return -1;

}

  

/* read the number of courses from file and allocate space to store them */

fscanf( in_file, "%d", &iNumCourses );

pCourses = (Course*) malloc( iNumCourses*sizeof(Course) );

  

/* initialize course data */

for( i=0 ; i<iNumCourses; i++){

if( fscanf( in_file, "%d %d", &pCourses[i].iCourseNumber, &pCourses[i].iMaxEnrolled )!=2 )

break;

pCourses[i].iStudentIDs = (int*) malloc( pCourses[i].iMaxEnrolled*sizeof(int) );

pCourses[i].iNumEnrolled = 0;

pCourses[i].pFront = NULL;

}

fclose(in_file);

  

/* open enrollment data file */

in_file = fopen(enrollFileName, "r");

if (in_file == NULL)

{

printf("File %s not found.\n", enrollFileName);

return -1;

}

  

/* reads enrollment data and calls your functions to handle the commands */

while( !feof(in_file) ){

if(fscanf( in_file, "%s", szCommand)!=1 )

break;

if( strcmp(szCommand, "enroll")==0 ){

fscanf( in_file, "%d %d %d", &iCourse, &iStudent, &iPriority );

iCourseNumber = searchCourses( pCourses, iNumCourses, iCourse );

attemptEnrollment( &pCourses[iCourseNumber], iStudent, iPriority );

}

else if( strcmp(szCommand, "addSeats")==0 ){

fscanf( in_file, "%d %d", &iCourse, &iNumAdd);

iCourseNumber = searchCourses( pCourses, iNumCourses, iCourse );

addSeats( &pCourses[iCourseNumber], iNumAdd );

}

else if( strcmp(szCommand, "drop")==0 ){

fscanf( in_file, "%d %d", &iCourse, &iStudent);

iCourseNumber = searchCourses( pCourses, iNumCourses, iCourse );

dropStudent( &pCourses[iCourseNumber], iStudent );

}

printf("\n" );

}

fclose(in_file);

  

/* Free course data */

for( i=0 ; i<iNumCourses; i++){

free( pCourses[i].iStudentIDs );

}

free( pCourses );

  

return 0;

  

}

/* provided code - DO NOT CHANGE

* search courses for one with iCourseNumber equal to iCourseID and return its index in the pCourses array

* returns -1 if the course is not found

*/

int searchCourses( Course* pCourses, int iNumCourses, int iCourseID ){

int i;

for( i=0; i<iNumCourses; i++ ){

if( pCourses[i].iCourseNumber==iCourseID )

return i;

}

return -1;

}

/* provided code - DO NOT CHANGE

* search the given course's iStudentIDs for an enrolled student.

* If the student is found it returns their index in the iStudentIDs array

* returns -1 if the iStudentID is not found

*/

int findStudent( Course* pCourse, int iStudentID ){

int i;

for( i=0; i<pCourse->iNumEnrolled; i++ ){

if( pCourse->iStudentIDs[i]==iStudentID )

return i;

}

return -1;

}

/*

* addSeats increases the maximum enrollment of the course by NumAdded.

* Use realloc to increase the number of student IDs which can be storexd in pCourse.

* dequeue students from the waitlist call enrollStudent on them to add them to the

* course until the course is full or the waitlist is empty.

*

* precondition: NumAdded > 0

*/

void addSeats( Course* pCourse, int NumAdded ){

WaitlistEntry wl;

/* increase the maximum enrollment of pCourse */

pCourse->iMaxEnrolled += NumAdded;

  

/* Print that seats have been added to the course (no changes needed to this line) */

printf("Added Seats:\t\t%d seats added to the course %d\n", NumAdded, pCourse->iCourseNumber );

  

/* add students to the course until it is full or the waitlist is empty */

pCourse->iStudentIDs = realloc(pCourse->iStudentIDs, pCourse->iMaxEnrolled *sizeof(int) );

while(pCourse->pFront != NULL && pCourse->iNumEnrolled < pCourse->iMaxEnrolled)

{

wl = dequeue(&pCourse->pFront);

enrollStudent(pCourse, wl.iStudentID);

}

  

}

/*

* attemptEnrollment attempts to enroll the given student in the course pCourse.

* If there is room left in the course call enrollStudent to add the student.

* Otherwise call waitlistStudent to add the student to the course's waitlist.

*/

void attemptEnrollment( Course* pCourse, int iStudentID, int iPriority ){

printf("attempt:\t\t%d in %d\n", iStudentID, pCourse->iCourseNumber );

if(pCourse->iNumEnrolled < pCourse->iMaxEnrolled)

{

enrollStudent(pCourse, iStudentID);

}

else

{

WaitlistEntry wl;

wl.iStudentID = iStudentID;

wl.iPriority = iPriority;

waitlistStudent(pCourse, wl);

}

}

/* provided code - DO NOT CHANGE

* enrolls the given student in the given course

*

* precondition: the course has room left in it to enroll the student

*/

void enrollStudent( Course* pCourse, int iStudentID ){

if( pCourse->iMaxEnrolled <= pCourse->iNumEnrolled ){

printf("ERROR - enrollStudent called with a full course %d\n", pCourse->iCourseNumber );

return;

}

pCourse->iStudentIDs[pCourse->iNumEnrolled] = iStudentID;

pCourse->iNumEnrolled++;

printf("Enrolled:\t\t%d in %d\n", iStudentID, pCourse->iCourseNumber );

}

/* provided code - DO NOT CHANGE

* adds the given student to the courses waitlist

*

* precondition: the course is full

*/

void waitlistStudent( Course* pCourse, WaitlistEntry wl ){

if( pCourse->iMaxEnrolled > pCourse->iNumEnrolled ){

printf("ERROR - waitlistStudent called with a non-full course %d\n", pCourse->iCourseNumber );

return;

}

enqueue( &pCourse->pFront, wl );

printf("Waitlisted:\t\t%d in %d\n", wl.iStudentID, pCourse->iCourseNumber );

printf("Current waitlist:\t" );

printQueue( pCourse->pFront );

}

/*

* dropStudent drops the given student from the course.

* If the waitlist is not empty you should dequeue the first student and enroll them in the now non-full course.

* It should print an error if the student to be dropped is not enrolled in the course.

*/

void dropStudent( Course* pCourse, int iStudentID ){

/* Use findStudent to determine where student is in iStudentIDs array */

WaitlistEntry wl;

int index = findStudent(pCourse, iStudentID);

int i;

if(index == -1 ){

printf("ERROR - dropStudent called to drop non-enrolled student %d from %d\n", iStudentID, pCourse->iCourseNumber );

return;

}

  

/* Use a loop to shift down students in iStudentIDs array and fill gap from the dropped student */

for(i = index; i < pCourse->iNumEnrolled - 1; i++)

{

pCourse->iStudentIDs[i] = pCourse->iStudentIDs[i+1];

}

  

pCourse->iNumEnrolled--;

  

/* Print that student has been dropped from the course (no changes needed to this line) */

printf("Dropped:\t\t%d from %d\n", iStudentID, pCourse->iCourseNumber );

  

/* Add student if the waitlist is not empty */

if(pCourse->pFront != NULL)

{

wl = dequeue(&pCourse->pFront);

enrollStudent(pCourse, wl.iStudentID);

}

}

/*

* insert a new node which contains info into the priority queue contained in the linked list pointed to by ppFront

*/

void enqueue( PQNode** ppFront, WaitlistEntry info ){

  

/* create a new node to store the info */

PQNode* node = (PQNode*)malloc(sizeof(PQNode));

PQNode *curr;

  

node->info = info;

node->pNext = NULL;

node->pPrev = NULL;

/* check if the LL is empty and add the new node to the front if it is */

if(*ppFront == NULL)

{

*ppFront = node;

return;

}

/* check if the new node should come before the first node in the LL */

if(node->info.iPriority > (*ppFront)->info.iPriority)

{

(*ppFront)->pNext = node;

node->pPrev = *ppFront;

*ppFront = node;

}

else

{

/* walk back through the previous nodes in the LL until the correct insertion point is found */

/* remember to also check whether the previous node is NULL */

curr = *ppFront;

while(curr->info.iPriority >= node->info.iPriority)

{

if(curr->pPrev == NULL) //should insert node in end

{

node->pNext = curr;

curr->pPrev = node;

  

return;

}

curr = curr->pPrev;

}

  

  

/* insert the new node into the place you found with your loop */

/* note you may need a special case for when the previous node is NULL */

node->pNext = curr->pNext;

curr->pNext = node;

node->pPrev = curr;

node->pNext->pPrev = node;

  

}

}

/*

* remove the node at the front of the priority queue and return its info

*

* precondition: the queue is not empty

*/

WaitlistEntry dequeue( PQNode** ppFront ){

WaitlistEntry ret;

if(*ppFront != NULL)

{

   ret = (*ppFront)->info;

*ppFront = (*ppFront)->pPrev;

}

  

return ret;

}

/* provided code - DO NOT CHANGE

* print the contents of the priority queue contained in the linked list pointed to by ppFront

*/

void printQueue( PQNode* pFront ){

while( pFront!=NULL ){

printf("%d ", pFront->info.iStudentID);

pFront = pFront->pPrev;

}

printf("\n");

}
