#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printArray(int arr[], int len) {
    for (int j = 0; j < len; j++)
        printf("%d ", arr[j]);

    printf("\n");
}

int main() {
    FILE *in;
    int size_arr = 0;
    int ch;

    if ((in = fopen("data_a5.txt", "r")) == NULL) {
        printf("Error!");
        exit(1);
    }
    do {
        ch = fgetc(in);
        if (ch == '\n')
            size_arr++;
    } while (ch != EOF);
    rewind(in);

    int arr[size_arr];
    int sort_arr[2 * size_arr + 1];

    int n = 0;
    while (!feof(in)) {
        fscanf(in, "%d", &arr[n]);
        n++;
    }
    fclose(in);

    for (n = 0; n < 2 * size_arr; n++) {
        sort_arr[n] = 0;
    }

    sort_arr[size_arr] = arr[0];

    for (n = 1; n < size_arr; n++) {
        int index = size_arr;
        if (arr[n] <= sort_arr[size_arr]) {
            while (!(arr[n] <= sort_arr[index]) && sort_arr[index] != 0 && index >= 0) {
                index--;
            }
        }
        if (arr[n] > sort_arr[size_arr]) {
            while (!(arr[n] <= sort_arr[index]) && sort_arr[index] != 0 && index < 2 * size_arr) {
                index++;
            }
        }

        if (sort_arr[index] == 0) {
            sort_arr[index] = arr[n];
        } else {
            int next_R, next_L = index;
            while (sort_arr[next_R] != 0 && next_R <= 2 * size_arr) {
                next_R++;
            }
            while (sort_arr[next_L] != 0 && next_L >= 0) {
                next_L--;
            }
            int R_move = next_R - index;
            int L_move = index - next_L;
            if (R_move > L_move) {
                while (L_move <= index) {
                    sort_arr[L_move] = sort_arr[L_move + 1];
                    L_move++;
                }
                sort_arr[index] = arr[n];
            } else {
                while (R_move >= index) {
                    sort_arr[R_move] = sort_arr[R_move - 1];
                    R_move--;
                }
                sort_arr[index] = arr[n];
            }
        }
    }
    printArray(arr, size_arr);
    return 0;
}
