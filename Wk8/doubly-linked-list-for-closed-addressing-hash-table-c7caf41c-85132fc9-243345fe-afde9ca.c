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

int main()
{
    int opt;
    int size;

    int i;
    int key;

    //Create a HashTable
    HashTable Q1;

    printf("============= Hash Table ============\n");
    printf("|1. Create a hash table             |\n");
    printf("|2. Insert a key to the hash table  |\n");
    printf("|3. Search a key in the hash table  |\n");
    printf("|4. Delete a key from the hash table|\n");
    printf("|5. Print the hash table            |\n");
    printf("|6. Quit                            |\n");
    printf("=====================================\n");

    printf("Enter selection: ");
    scanf("%d",&opt);
    while(opt>=1 && opt <=5){
        switch(opt){
            case 1:
                printf("Enter number of data to be inserted:\n");
                scanf("%d",&size);

                Q1.hSize = (int)size/ LOAD_FACTOR;
                Q1.nSize = 0;

                Q1.Table = (HashTableNode *) malloc(sizeof(HashTableNode)*(Q1.hSize));

                for(i=0;i<Q1.hSize;i++){
                    Q1.Table[i].head = NULL;
                    Q1.Table[i].size = 0;
                }
                printf("HashTable is created.\n");
                break;
            case 2: //Insertion
                printf("Enter a key to be inserted:\n");
                scanf("%d",&key);
                if(HashInsert(&Q1,key))
                    printf("%d is inserted.\n",key);
                else
                    printf("%d is a duplicate. No key is inserted.\n",key);
                break;
            case 3: //Search
                printf("Enter a key for searching in the HashTable:\n");
                scanf("%d",&key);
                ListNode* node = HashSearch(Q1, key);

                if(node!=NULL)
                    printf("%d is found.\n",key);
                else
                    printf("%d is not found.\n",key);
                break;
            case 4: //Deletion
                printf("Enter a key to be deleted:\n");
                scanf("%d",&key);
                if(HashDelete(&Q1,key))
                    printf("%d is deleted.\n",key);
                else
                    printf("%d is not existing.\n",key);
                break;
            case 5:
                HashPrint(Q1);
                break;
        }

        printf("Enter selection: ");
        scanf("%d",&opt);
    }

    for(i=0;i<Q1.hSize;i++)
    {
        while(Q1.Table[i].head)
        {
            ListNode *temp;
            temp = Q1.Table[i].head;
            Q1.Table[i].head = Q1.Table[i].head->next;
            free(temp);
        }
    }
    free(Q1.Table);

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