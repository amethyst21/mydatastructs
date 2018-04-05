#include <stdio.h>
#include <stdlib.h>

void print_array(const int arr[], int len) {
    for (int j = 0; j < len; j++)
        printf("%d%c", arr[j], " \n"[j == len - 1]);
}

int main(void) {
    FILE *in;
    int size_arr, n, start;
    int value;

    if ((in = fopen("data_a5.txt", "r")) == NULL) {
        printf("Cannot open input file %s\n", "data_a5.txt");
        exit(1);
    }
    for (size_arr = 0; fscanf(in, "%d", &value) == 1; size_arr++)
        continue;

    rewind(in);

    int *arr = calloc(2 * size_arr + 1, sizeof(*arr));
    if (arr == NULL) {
        printf("Cannot allocate memory for %d entries\n", size_arr);
        exit(1);
    }

    start = size_arr;
    for (n = 0; n < size_arr && fscanf(in, "%d", &value) == 1; n++) {
        /* insert value into the sorted array */
        int a, b;
        for (a = start, b = start + n; a < b;) {
            int mid = a + (b - a) / 2;
            if (arr[mid] < value) {
                a = mid + 1;
            } else {
                b = mid;
            }
        }
        /* insert value at offset b */
        if (b - start < start + n - b) {
            /* shift left portion to the left */
            for (int i = start--; i < b; i++) {
                arr[i - 1] = arr[i];
            }
            b--;
        } else {
            /* shift right portion to the right */
            for (int i = start + n + 1; --i > b;) {
                arr[i] = arr[i - 1];
            }
        }
        arr[b] = value;
    }
    fclose(in);

    print_array(arr + start, n);
    free(arr);
    return 0;
}
