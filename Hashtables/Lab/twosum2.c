#include <stdio.h>
#include <stdlib.h>

void quickSort(int A[], int low, int high);
int partition (int A[], int low, int high);

void dualSortedSearch (int[],int, int, int[]);

int main()
{
    int testArrays[][10] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},        // Ascending order
        {10, 9, 8, 7, 6, 5, 4, 3, 2, 1},        // Descending order
        {-5, -3, -1, 0, 2, 4, 6, 8, 10, 12},     // Alternating positive and negative
        {-10, -8, -6, -4, -2, 0, 2, 4, 6, 8},    // All negative
        {2, 4, 6, 8, 10, 12, 14, 16, 18, 20}     // All positive
    };

    // Sample keys to search
    int testKeys[] = {5, 11, 3, -6, 16};

    int size = 10;  // Size of each sample array

    // Iterate over test cases
    for (int i = 0; i < sizeof(testKeys) / sizeof(testKeys[0]); i++)
    {
        int* A = testArrays[i];
        int K = testKeys[i];
        int index[2] = {-1, -1};

        printf("Test Case %d:\n", i + 1);
        printf("Array: ");
        for (int j = 0; j < size; j++)
        {
            printf("%d ", A[j]);
        }
        printf("\nKey: %d\n", K);

        dualSortedSearch(A, size, K, index);

        if (index[0] != -1)
            printf("Indices: %d %d\n", index[0], index[1]);
        else
            printf("Not found\n");

        printf("\n");
    }
    return 0;
}

void dualSortedSearch(int A[], int size, int K, int dualIndex[])
{
    // Write your code here
    quickSort(A,0,size-1);
    int left = 0;
    int right = size-1;
    while(right > left)
    {
        int sum = A[left] + A[right];
        if (sum < K)
            left ++; // sum is less, move left ptr right
        else if (sum > K)
            right --;
        else
        {
            dualIndex[0] = left;
            dualIndex[1] = right;
            return;
        }
    }
    return; // not found
}

int partition (int A[], int low, int high)
{
    int pivot = A[high];
    int i = (low - 1);

    int temp;
    for (int j = low; j <= high- 1; j++)
    {
        if (A[j] < pivot)
        {
            i++;

            temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }

    temp = A[i+1];
    A[i+1]= A[high];
    A[high] = temp;
    return (i + 1);
}

void quickSort(int A[], int low, int high)
{
    if (low < high)
    {
        int pivot = partition(A, low, high);

        quickSort(A, low, pivot - 1);
        quickSort(A, pivot + 1, high);
    }
}
