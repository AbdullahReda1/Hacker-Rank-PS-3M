#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);
int parse_int(char*);

/*
 * Complete the 'findMedian' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

void vSwapElements(int* a_element, int* b_element) {
    int temp_element = *a_element;
    *a_element = *b_element;
    *b_element = temp_element;
}

int intPartition(int* arr, int low_element, int high_element) {
    int pivot_element = arr[high_element];
    int index = low_element - 1;

    for (int j = low_element; j < high_element; j++) {
        if (arr[j] < pivot_element) {
            index++;
            vSwapElements(&arr[index], &arr[j]);
        }
    }
    vSwapElements(&arr[index + 1], &arr[high_element]);
    return index + 1;
}

void vQuicksort(int* arr, int low_element, int high_element) {
    if (low_element < high_element) {
        int partitionIndex = intPartition(arr, low_element, high_element);

        vQuicksort(arr, low_element, partitionIndex - 1);
        vQuicksort(arr, partitionIndex + 1, high_element);
    }
}

int findMedian(int arr_count, int* arr) {
    vQuicksort(arr, 0, arr_count - 1);

    if (arr_count % 2 == 0) {
        int median1 = arr[(arr_count / 2) - 1];
        int median2 = arr[arr_count / 2];
        return (median1 + median2) / 2;
    } else {
        return arr[arr_count / 2];
    }
}

int find_Median(int arr_count, int* arr) {
    // Create an auxiliary stack for iterative quicksort
    int* stack = (int*)malloc(arr_count * sizeof(int));
    int top = -1;

    // Push initial values of low and high to stack
    int low = 0;
    int high = arr_count - 1;
    stack[++top] = low;
    stack[++top] = high;

    // Keep popping from stack while it is not empty
    while (top >= 0) {
        // Pop high and low
        high = stack[top--];
        low = stack[top--];

        // Partition process
        int pivot = arr[high];
        int index_of_partition = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                index_of_partition++;
                // Swap arr[index_of_partition] and arr[j]
                int temp = arr[index_of_partition];
                arr[index_of_partition] = arr[j];
                arr[j] = temp;
            }
        }
        // Swap arr[index_of_partition + 1] and arr[high] (or pivot)
        int temp = arr[index_of_partition + 1];
        arr[index_of_partition + 1] = arr[high];
        arr[high] = temp;
		
        int p = index_of_partition + 1;

        // Push left side to stack
        if (p - 1 > low) {
            stack[++top] = low;
            stack[++top] = p - 1;
        }

        // Push right side to stack
        if (p + 1 < high) {
            stack[++top] = p + 1;
            stack[++top] = high;
        }
    }

    // Free the stack memory
    free(stack);

    // Calculate and return the median
    if (arr_count % 2 == 0) {
        int median1 = arr[(arr_count / 2) - 1];
        int median2 = arr[arr_count / 2];
        return (median1 + median2) / 2;
    } else {
        return arr[arr_count / 2];
    }
}

int main()
{
    int n = parse_int(ltrim(rtrim(readline())));

    char** arr_temp_element = split_string(rtrim(readline()));

    int* arr = malloc(n * sizeof(int));

    for (int index = 0; index < n; index++) {
        int arr_item = parse_int(*(arr_temp_element + index));
        *(arr + index) = arr_item;
    }

    //int result = findMedian(n, arr);

    int result = find_Median(n, arr);       /* Best one */

    printf("%d\n", result);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';
            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
        data = realloc(data, data_length);
        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);
        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }
    if (!*str) {
        return str;
    }
    while (*str != '\0' && isspace(*str)) {
        str++;
    }
    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }
    if (!*str) {
        return str;
    }
    char* end = str + strlen(str) - 1;
    while (end >= str && isspace(*end)) {
        end--;
    }
    *(end + 1) = '\0';
    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");
    int spaces = 0;
    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);
        if (!splits) {
            return splits;
        }
        splits[spaces - 1] = token;
        token = strtok(NULL, " ");
    }
    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);
    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }
    return value;
}
