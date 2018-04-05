#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* function prototypes */
int iterGCD(int x, int y);
int recGCD(int x, int y);

int main(int argc, char *argv[])
{
    int num_vals = 6;
    int x_vals[] = {3, 9, 12, 36, 1, 105};
    int y_vals[] = {3, 21, 18, 27, 12, 91};
    int i = 0;

    printf("Assignment 2 Problem 2 by Grecia Gonzalez.\n\n");

    while (i<num_vals)
    {
        printf("Iterative GCD: x = %d, y = %d, result = %d\n", x_vals[i], y_vals[i], iterGCD(x_vals[i],y_vals[i]));
        printf("Recursive GCD: x = %d, y = %d, result = %d\n\n", x_vals[i], y_vals[i], recGCD(x_vals[i],y_vals[i]));

        i++;
    }

    return 0;
}

int iterGCD(int x, int y)

    {
	int i,gcd;
	for(i=1; i <= x && i <= y; ++i)
	{
	// Checks if i is factor of both integers
	if(x%i==0 && y%i==0)
	gcd = i;
	}
	return gcd;
     }


int recGCD(int x, int y)
{
    if (y!=0)
     return recGCD(y, x%y);
    else
     return x;
}
