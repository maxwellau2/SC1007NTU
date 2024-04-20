#include <stdio.h>
#include <stdlib.h>

#define LOAD_FACTOR 3

typedef struct _listnode{
    int key;
    struct _listnode *next;
    struct _listnode *pre;
} ListNode;

typedef struct _linkedlist{
    int size;
    ListNode *head;
} HashTableNode;

typedef struct _hashTable{
    int hSize;
    int nSize;
    HashTableNode *Table;
} HashTable;

int Hash(int key,int hSize);

ListNode* HashSearch(HashTable, int);
int HashInsert(HashTable *, int);
int HashDelete(HashTable *, int);

//In Practice, we will not do it
void HashPrint(HashTable);
void runTests() {
    int passed = 0;
    int failed = 0;

    // Test case 1: Create an empty hash table
    HashTable Q1;
    Q1.hSize = 0;
    Q1.nSize = 0;
    Q1.Table = NULL;
    printf("Test case 1: Creating an empty hash table\n");
    // Nothing to assert, just creation

    // Test case 2: Insert a key into an empty hash table
    printf("Test case 2: Inserting a key into an empty hash table\n");
    int key1 = 10;
    int insertResult = HashInsert(&Q1, key1);
    if (insertResult == 1 && Q1.Table != NULL && Q1.Table[0].size == 1 && Q1.Table[0].head->key == key1) {
        printf("Passed\n");
        passed++;
    } else {
        printf("Failed\n");
        failed++;
    }

    // Test case 3: Insert a duplicate key
    printf("Test case 3: Inserting a duplicate key\n");
    int insertDuplicateResult = HashInsert(&Q1, key1);
    if (insertDuplicateResult == 0 && Q1.Table != NULL && Q1.Table[0].size == 1 && Q1.Table[0].head->key == key1) {
        printf("Passed\n");
        passed++;
    } else {
        printf("Failed\n");
        failed++;
    }

    // Test case 4: Search for an existing key
    printf("Test case 4: Searching for an existing key\n");
    ListNode* searchResult = HashSearch(Q1, key1);
    if (searchResult != NULL && searchResult->key == key1) {
        printf("Passed\n");
        passed++;
    } else {
        printf("Failed\n");
        failed++;
    }

    // Test case 5: Search for a non-existent key
    printf("Test case 5: Searching for a non-existent key\n");
    ListNode* searchNonExistentResult = HashSearch(Q1, key1 + 1);
    if (searchNonExistentResult == NULL) {
        printf("Passed\n");
        passed++;
    } else {
        printf("Failed\n");
        failed++;
    }

    // Test case 6: Delete an existing key
    printf("Test case 6: Deleting an existing key\n");
    int deleteResult = HashDelete(&Q1, key1);
    if (deleteResult == 1 && Q1.Table != NULL && Q1.Table[0].size == 0) {
        printf("Passed\n");
        passed++;
    } else {
        printf("Failed\n");
        failed++;
    }

    // Test case 7: Delete a non-existent key
    printf("Test case 7: Deleting a non-existent key\n");
    int deleteNonExistentResult = HashDelete(&Q1, key1);
    if (deleteNonExistentResult == 0 && Q1.Table != NULL && Q1.Table[0].size == 0) {
        printf("Passed\n");
        passed++;
    } else {
        printf("Failed\n");
        failed++;
    }

    // Test case 8: Search after deletion
    printf("Test case 8: Searching for a key after deletion\n");
    ListNode* searchAfterDeletionResult = HashSearch(Q1, key1);
    if (searchAfterDeletionResult == NULL) {
        printf("Passed\n");
        passed++;
    } else {
        printf("Failed\n");
        failed++;
    }

    // Test case 9: Create a hash table with size 1
    printf("Test case 9: Creating a hash table with size 1\n");
    Q1.hSize = 1;
    Q1.nSize = 0;
    Q1.Table = (HashTableNode *) malloc(sizeof(HashTableNode) * Q1.hSize);
    for (int i = 0; i < Q1.hSize; i++) {
        Q1.Table[i].head = NULL;
        Q1.Table[i].size = 0;
    }
    // Nothing to assert, just creation

    // Test case 10: Insert multiple keys and print the hash table
    printf("Test case 10: Inserting multiple keys and printing the hash table\n");
    int keys[] = {10, 20, 30, 40};
    for (int i = 0; i < 4; i++) {
        HashInsert(&Q1, keys[i]);
    }
    HashPrint(Q1);

    // Cleanup
    if (Q1.Table != NULL) {
        for (int i = 0; i < Q1.hSize; i++) {
            while (Q1.Table[i].head != NULL) {
                ListNode *temp = Q1.Table[i].head;
                Q1.Table[i].head = Q1.Table[i].head->next;
                free(temp);
            }
        }
        free(Q1.Table);
    }

    // Print summary
    printf("\n");
    printf("===== Test Summary =====\n");
    printf("Passed: %d\n", passed);
    printf("Failed: %d\n", failed);
    printf("========================\n");
}

int main()
{
    
    runTests();
    return 0;
}



int HashInsert(HashTable* Q1Ptr, int key)
{
    if(Q1Ptr->hSize <= 0)
        return 0;
    // check for dupes
    ListNode *dupe = HashSearch(*Q1Ptr, key);
    if (dupe != NULL) // if dupes found
        return 0;

    int idx = Hash(key, Q1Ptr->hSize); // hash
    ListNode *curr = Q1Ptr->Table[idx].head; // save current head
    Q1Ptr->Table[idx].head = malloc(sizeof(ListNode)); // allocate memory for new node, set to head
    Q1Ptr->Table[idx].head->key = key; // set head's key, next, and pre
    Q1Ptr->Table[idx].head->next = curr;
    Q1Ptr->Table[idx].head->pre = NULL;

    if(curr!=NULL) // if curr not null -> means the LL was empty
        curr->pre = Q1Ptr->Table[idx].head;
    Q1Ptr->Table[idx].size ++;
    return 1;
}

int HashDelete(HashTable* Q1Ptr, int key)
{

    if (Q1Ptr->hSize <= 0)
        return 0;
    // find idx
    int idx = Hash(key, Q1Ptr->hSize);
    ListNode *del = HashSearch(*Q1Ptr, key);
    if (del == NULL) // no node found
        return 0;
    if (del->pre == NULL) // if head ptr
        Q1Ptr->Table[idx].head = del->next;
    else
    {
        ListNode *pre = del->pre;
        ListNode *next = del->next;
        pre->next = next; // ignore middle
        if (next != NULL)
            next->pre = pre; // middle node, set back the pre
    }
    return 1;

}

int Hash(int key,int hSize)
{
    return key%hSize;
}

ListNode* HashSearch(HashTable Q1, int key)
{
    int index;

    ListNode *temp;

    if(Q1.hSize != 0)
        index = Hash(key,Q1.hSize);
    else
        return NULL;

    temp = Q1.Table[index].head;
    while(temp !=NULL){
        if(temp->key == key)
            return temp;
        temp = temp->next;
    }

    return NULL;
}

void HashPrint(HashTable Q1)
{
    int i;
    ListNode *temp;
    for(i=0;i<Q1.hSize;i++)
    {
        temp =Q1.Table[i].head;
        printf("%d:  ",i);
        while(temp !=NULL)
        {
            printf("%d -> ", temp->key);
            temp = temp->next;
        }
        printf("\n");
    }
}