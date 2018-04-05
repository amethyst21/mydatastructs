#include <stdio.h>

int main(int argc,char** argv) {
int a[10], i, j, k;
FILE *fp;
fp = fopen("f://data_a5.txt", "r");
//assuming file contains 10 numbers;
for (i = 0; i < 10; i++) {
fscanf(fp, "%d", &a[i]);
}
fclose(fp);
printf("unsorted elements are: ");
for (i = 0; i < 10; i++) {
printf("%d\t", a[i]);
}

//sorting
for (j = 1; j < 10; j++) {
k = a[j];
i = j - 1;
//shifting
while (i >= 0 && k < a[i]) {
a[i+1]=a[i];
i = i - 1;
}

//insertion
a[i + 1] = k;
  
}

printf("\nsorted elements are: ");
for (i = 0; i < 10; i++) {
printf("%d\t", a[i]);
}

return 0;
}
