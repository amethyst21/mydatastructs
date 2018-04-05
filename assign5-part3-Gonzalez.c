#include <stdio.h>

//Always use meaningful names for types
typedef unsigned char boolean;
#define True 't'
#define FALSE (!True)

//this is a really neat trick for swapping values efficiently
void swap(long* a,long *b) { *a=*a^*b;*b=*b^*a;*a=*a^*b; }

//Here's a readability improvement
#define until(condition) while(!(condition))

int main(int n, char*args[]){
  double *d;
  int i;
  char input[5];  //should be long enough for most doubles.
  boolean sorted = FALSE;

  //In C, you need to specify the array size beforehand, so ask
  printf("Please enter the length of the array\n");
  gets(input);
  //scan the input string and convert to a value
  sscanf(input,"%s",&input[0]);
  n=(long)atol(input);

  //allocate space, make sure you get the order of arguments right.
  d = calloc(sizeof(double),n); 

  //Get and sort the array
  until (sorted) {

     for (i=0;i<n;i++) {
        //It's important to always ask nicely
        printf("Please enter the %d%s array item\n",i,i==1?"st":"th");
        scanf("%lf",d+i);
     }
     //do a compare and exchange sort:
     sorted = !sorted;  //not sorted
     //check all the items
     printf("%d %d\n",i,n);
     for (i=1;i<n;i++) {
        //compare
        if (d[i]<d[i-1]) {
          //exchange 
          swap(d+i,d+i-1);
          sorted = FALSE;
        }
     }
     //show results
     printf("The array is%ssorted\n",sorted?" ":" not "); }
  //use the --> "downto operator" for counting downto 0. 
  for (;n-->0;) printf("%lf\n",*d++);
  }
