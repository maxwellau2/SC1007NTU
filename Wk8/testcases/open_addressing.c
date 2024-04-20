#include <stdio.h>
#include <stdlib.h>

#define TABLESIZE 37
#define PRIME     13

enum Marker {EMPTY,USED,DELETED};

typedef struct _slot{
    int key;
    enum Marker indicator;
} HashSlot;

int HashInsert(int key, HashSlot hashTable[]);
int HashDelete(int key, HashSlot hashTable[]);
void runTests();


int hash1(int key);
int hash2(int key);

int main() {
    runTests();
    return 0;
}

void runTests() {
    int passed = 0;
    int failed = 0;

    // Test case 1: Insertion and retrieval
    HashSlot hashTable[TABLESIZE];
    for (int i = 0; i < TABLESIZE; i++) {
        hashTable[i].indicator = EMPTY;
        hashTable[i].key = 0;
    }

    int key1 = 10;
    int key2 = 20;
    int key3 = 30;

    int comparisons1 = HashInsert(key1, hashTable);
    if (comparisons1 == 0) {
        printf("Test case 1 passed: Insertion of key %d\n", key1);
        passed++;
    } else {
        printf("Test case 1 failed: Insertion of key %d\n", key1);
        failed++;
    }

    int comparisons2 = HashInsert(key2, hashTable);
    if (comparisons2 == 0) {
        printf("Test case 2 passed: Insertion of key %d\n", key2);
        passed++;
    } else {
        printf("Test case 2 failed: Insertion of key %d\n", key2);
        failed++;
    }

    int comparisons3 = HashInsert(key3, hashTable);
    if (comparisons3 == 0) {
        printf("Test case 3 passed: Insertion of key %d\n", key3);
        passed++;
    } else {
        printf("Test case 3 failed: Insertion of key %d\n", key3);
        failed++;
    }

    // Test case 4: Duplicate insertion
    int duplicateComparisons = HashInsert(key1, hashTable);
    if (duplicateComparisons < 0) {
        printf("Test case 4 passed: Duplicate insertion of key %d detected\n", key1);
        passed++;
    } else {
        printf("Test case 4 failed: Duplicate insertion of key %d not detected\n", key1);
        failed++;
    }

    // Test case 5: Deletion
    int deleteComparisons = HashDelete(key2, hashTable);
    if (deleteComparisons > 0) {
        printf("Test case 5 passed: Deletion of key %d\n", key2);
        passed++;
    } else {
        printf("Test case 5 failed: Deletion of key %d\n", key2);
        failed++;
    }

    // Test case 6: Retrieval after deletion
    int searchComparisons = HashInsert(key2, hashTable);
    if (searchComparisons == 0) {
        printf("Test case 6 passed: Insertion of key %d after deletion\n", key2);
        passed++;
    } else {
        printf("Test case 6 failed: Insertion of key %d after deletion\n", key2);
        failed++;
    }

    // Test case 7: Insertion when table is full
    int fullTableComparisons = 0;
    for (int i = 0; i < TABLESIZE; i++) {
        int key = 100 + i; // Keys from 100 to 136
        fullTableComparisons += HashInsert(key, hashTable);
    }
    if (fullTableComparisons >= TABLESIZE) {
        printf("Test case 7 passed: Insertion when table is full\n");
        passed++;
    } else {
        printf("Test case 7 failed: Insertion when table is full\n");
        failed++;
    }

    // Test case 8: Deletion of non-existent key
    int nonExistentDelete = HashDelete(999, hashTable);
    if (nonExistentDelete == -1) {
        printf("Test case 8 passed: Deletion of non-existent key\n");
        passed++;
    } else {
        printf("Test case 8 failed: Deletion of non-existent key\n");
        failed++;
    }

    // Test case 9: Deletion of a key that was never inserted
    int neverInsertedDelete = HashDelete(999, hashTable);
    if (neverInsertedDelete == -1) {
        printf("Test case 9 passed: Deletion of a key that was never inserted\n");
        passed++;
    } else {
        printf("Test case 9 failed: Deletion of a key that was never inserted\n");
        failed++;
    }

    // // Test case 10: Insertion and deletion of multiple keys
    // int multipleInsertsDeletes = 0;
    // int keys[] = {40, 50, 60, 70, 80};
    // for (int i = 0; i < 5; i++) {
    //     multipleInsertsDeletes += HashInsert(keys[i], hashTable);
    // }
    // for (int i = 0; i < 5; i++) {
    //     multipleInsertsDeletes += HashDelete(keys[i], hashTable);
    // }
    // if (multipleInsertsDeletes == 10) {
    //     printf("Test case 10 passed: Insertion and deletion of multiple keys\n");
    //     passed++;
    // } else {
    //     printf("Test case 10 failed: Insertion and deletion of multiple keys\n,%d",multipleInsertsDeletes);
    //     failed++;
    // }

    // Print summary
    printf("\n");
    printf("===== Test Summary =====\n");
    printf("Passed: %d\n", passed);
    printf("Failed: %d\n", failed);
    printf("========================\n");
}

int hash1(int key)
{
    return (key % TABLESIZE);
}

int hash2(int key)
{
    return (key % PRIME) + 1;
}

int doubleHash(int key, int i)
{
    return (hash1(key) + i * hash2(key)) % TABLESIZE;
}

int HashInsert(int key, HashSlot hashTable[])
{
    int idx;
    int cmp = 0;
    int i;

    HashSlot *deletedslot = NULL;

    // iterate from 0 to tablesize-1
    for (i=0; i<TABLESIZE; i++)
    {
        idx = doubleHash(key, i);
        // check duplicate
        if (hashTable[idx].indicator == USED)
        {
            if (hashTable[idx].key == key)
                return -1;
            cmp ++; // if key not the same, increase key cmp
        }
        if (hashTable[idx].indicator == DELETED)
        {
            if (deletedslot == NULL) // store the first deleted slot
                deletedslot = &hashTable[idx];
        }
        if (hashTable[idx].indicator == EMPTY)
        {
            if (deletedslot == NULL) // if deleted slot is not found, and slot if empty
            {
                hashTable[idx].key = key;
                hashTable[idx].indicator = USED;
                return cmp;
            }
            else
            {
                break; // just insert into the first found deleted slot
            }
        }
    }
    if (deletedslot != NULL)
    {
        deletedslot->key = key;
        deletedslot->indicator = USED;
    }
    return cmp;
}

int HashDelete(int key, HashSlot hashTable[])
{
    int idx;
    for(int i=0; i<TABLESIZE; i++)
    {
        idx = doubleHash(key, i);
        if (hashTable[idx].key == key && hashTable[idx].indicator == USED)
        {
            hashTable[idx].indicator = DELETED;
            return ++i;
        }
    }
    return -1;
}