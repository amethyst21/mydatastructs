#include <stdio.h>
#include <stdlib.h>

int main()
{
   FILE *fp=fopen("data_a5.txt","r");
   int array[100];
   int n=0,i,d,t;
   int assigns=0;
   while(!feof(fp))
   {
       fscanf(fp,"%d",&array[n]);
       n++;
   }
   for (i = 0 ; i < n ; i++) {
d = i;

while ( d > 0 && array[d] < array[d-1]) {
   assigns++;
t = array[d];
array[d] = array[d-1];
array[d-1] = t;
d--;
}
}
printf("Data after insertion sort: \n");
for(i=0;i<n;i++)
{
   printf("%d ",array[i]);
}
printf("\n\n # of assignments: %d",assigns);
   return 0;
}
