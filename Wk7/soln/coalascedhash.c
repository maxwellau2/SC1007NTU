#include <stdio.h>
#include <stdlib.h>

#define TABLESIZE 37
#define PRIME     13

enum Marker {EMPTY,USED};

typedef struct _slot{
    int key;
    enum Marker indicator;
    int next;
} HashSlot;

int HashInsert(int key, HashSlot hashTable[]);
int HashFind(int key, HashSlot hashTable[]);

int hash(int key)
{
    return (key % TABLESIZE);
}

int main()
{
    int opt;
    int i;
    int key;
    int index;
    HashSlot hashTable[TABLESIZE];

    for(i=0;i<TABLESIZE;i++){
        hashTable[i].next = -1;
        hashTable[i].key = 0;
        hashTable[i].indicator = EMPTY;
    }

    printf("============= Hash Table ============\n");
    printf("|1. Insert a key to the hash table  |\n");
    printf("|2. Search a key in the hash table  |\n");
    printf("|3. Print the hash table            |\n");
    printf("|4. Quit                            |\n");
    printf("=====================================\n");

    printf("Enter selection: ");
    scanf("%d",&opt);
    while(opt>=1 && opt <=3){
        switch(opt){
        case 1:
            printf("Enter a key to be inserted:\n");
            scanf("%d",&key);
            index = HashInsert(key,hashTable);
            if(index <0)
                printf("Duplicate key\n");
            else if(index < TABLESIZE)
                printf("Insert %d at index %d\n",key, index);
            else
                printf("Table is full.\n");
            break;
        case 2:
            printf("Enter a key for searching in the HashTable:\n");
            scanf("%d",&key);
            index = HashFind(key, hashTable);

            if(index!=-1)
                printf("%d is found at index %d.\n",key,index);
            else
                printf("%d is not found.\n",key);
            break;

        case 3:
            printf("index:\t key \t next\n");
            for(i=0;i<TABLESIZE;i++) printf("%d\t%d\t%d\n",i, hashTable[i].key,hashTable[i].next);
            break;
        }
        printf("Enter selection: ");
        scanf("%d",&opt);
    }
    return 0;
}
int HashInsert(int key, HashSlot hashTable[])
{
 // Write your code here
    int idx = hash(key);
    if (hashTable[idx].indicator == EMPTY)
    {
        hashTable[idx].key = key;
        hashTable[idx].indicator = USED;
        hashTable[idx].next = -1;
        return idx;
    }
    // else it is taken, we do back probing
    // find the index to insert the pointer into
    if(hashTable[idx].key == key) 
    {
        return -1; // duplicate key found
    }
    while(hashTable[idx].next != -1)
    {        
        idx = hashTable[idx].next;
        if(hashTable[idx].key == key)
            return -1; // duplicate key found
    }
    // look at the back of the HT to find vaccancy
    int collisionidx = idx;
    while(hashTable[collisionidx].indicator == USED)
    {
        collisionidx++;
        if (collisionidx == TABLESIZE) collisionidx = 0;
        if (collisionidx == idx) return TABLESIZE + 1;
    }
    hashTable[idx].next = collisionidx;
    hashTable[collisionidx].key = key;
    hashTable[collisionidx].indicator = USED;
    hashTable[collisionidx].next = -1;
    return collisionidx;
}

int HashFind(int key, HashSlot hashTable[])
{
    // Write your code here
    // get the hash code
    int idx = hash(key);
    // probe the first element
    if (hashTable[idx].key == key) 
    {
        return idx;
    }
    // else, traverse the LL
    HashSlot temp;
    temp = hashTable[idx];
    while(temp.next != -1)
    {
        idx = temp.next;
        temp = hashTable[temp.next];
        if (temp.key == key)
        {
            return idx;
        }
    }
    return -1;
}