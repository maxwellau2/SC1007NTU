#include <stdio.h>
#include <stdlib.h>

void dualSearch (int[],int, int, int[]);

int main()
{
    int testArrays[][10] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {2, 4, 6, 8, 10, 12, 14, 16, 18, 20},
        {-1, -2, -3, -4, -5, -6, -7, -8, -9, -10}
    };

    // Sample keys to search
    int testKeys[] = {5, 11, -3};

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

        dualSearch(A, size, K, index);

        if (index[0] != -1)
            printf("Indices: %d %d\n", index[0], index[1]);
        else
            printf("Not found\n");

        printf("\n");
    }
    return 0;
}

void dualSearch(int A[], int size, int K, int dualIndex[])
{
   // Write your code here
    // brute force approach, nesting for loop
    for (int i=0; i<K; i++)
    {   
        for (int j=0; j<size; j++)
        {
            if (A[i] + A[j] == K)
            {
                dualIndex[0] = i;
                dualIndex[1] = j;
                return;
            }
        }
    }
}
