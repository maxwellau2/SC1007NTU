## Linked List Notes
### Q1. Insert into sorted LL
``` C
int insertSortedLL(LinkedList *ll, int item)
{
	// add your code here
    ListNode * newnode = NULL;
    newnode = (ListNode*)malloc(sizeof(ListNode));
    newnode->item = item;
    newnode->next = NULL;
    // if the length of LL is 0, make it the head
    if (ll->size == 0)
    {
        ll->head = newnode;
        ll->size ++;
        return 0;
    }
    else
    {
        // find the node
        ListNode * temp = ll->head;
        int idx = 0;
        while (temp->next!=NULL)
        {
            if (temp->item < item && temp->next->item > item)
            {
                ListNode * nextnode = temp->next;
                temp->next = newnode;
                newnode->next = nextnode;
                ll->size ++;
                return ++idx;
            }
            else if (temp->item == newnode->item)
            {
                free(newnode);
                return -1;
            }
            temp = temp->next;
            ++idx;
        }
        temp->next = newnode;
        ll->size ++;
        ++idx;
        return idx;
        
    }
}
```
### Simplified answer
``` c
int insertSortedLL(LinkedList *ll, int item) {
    // Find the index where the item should be inserted
    int index = 0;
    ListNode *cur = ll->head;
    while (cur != NULL && cur->item < item) {
        cur = cur->next;
        index++;
    }
    
    // Check if the item already exists in the list
    if (cur != NULL && cur->item == item) {
        return -1; // Item already exists, return -1
    }
    
    // Insert the item at the found index
    if (insertNode(ll, index, item) == 0) {
        return index; // Successfully inserted, return the index
    } else {
        return -1; // Failed to insert, return -1
    }
}
```

### Q2. Alternating Merge LL
```c
void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2) {
    int idx1 = 1;  // Start index for inserting elements from ll2 into ll1
    int idx2 = 0;  // Index for removing elements from ll2

    ListNode *temp1 = ll1->head;  // Pointer to traverse ll1
    ListNode *temp2 = ll2->head;  // Pointer to traverse ll2

    // Traverse both lists until either one reaches the end
    while (temp1 != NULL && temp2 != NULL) {
        // Insert the item from ll2 into ll1 at index idx1
        insertNode(ll1, idx1, temp2->item);
        
        // Increment idx1 to the next position for inserting from ll2
        idx1 += 2;

        // Move to the next node in ll2
        temp2 = temp2->next;

        // Remove the node from ll2 that was already inserted into ll1
        removeNode(ll2, idx2);

        // Move temp1 to the next position for traversal (skipping the inserted node)
        if (temp1->next != NULL) {
            temp1 = temp1->next->next;
        } else {
            // If temp1 reaches the end of ll1, break the loop
            break;
        }
    }
}
```
### Alternative soln
``` c
void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2) {
    ListNode *temp1 = ll1->head;  // Pointer to traverse ll1
    ListNode *temp2 = ll2->head;  // Pointer to traverse ll2

    // Traverse both lists until either one reaches the end
    while (temp1 != NULL && temp2 != NULL) {
        // Store the next pointers to preserve the reference
        ListNode *next1 = temp1->next;
        ListNode *next2 = temp2->next;

        // Insert the node from ll2 into ll1 after temp1
        temp1->next = temp2;
        temp2->next = next1;

        // Move temp1 and temp2 to their next positions
        temp1 = next1;
        temp2 = next2;
    }

    // If ll2 still has remaining nodes, append them to ll1
    if (temp2 != NULL) {
        // Find the last node in ll1
        while (temp1->next != NULL) {
            temp1 = temp1->next;
        }

        // Append the remaining nodes from ll2 to ll1
        temp1->next = temp2;
    }

    // Clear ll2
    ll2->head = NULL;
    ll2->size = 0;
}
```

### Q3. Move odd items to back
```c
void moveOddItemsToBack(LinkedList *ll) {
    ListNode *temp = ll->head;  // Pointer to traverse ll
    LinkedList odds;            // Linked list to store odd items temporarily
    odds.head = NULL;           // Initialize odds list
    odds.size = 0;              // Initialize size of odds list

    // Traverse the original list ll
    while (temp != NULL) {
        if (temp->item % 2 == 1) {  // If the current node's item is odd
            // Move the odd item to the back of the odds list
            insertNode(&odds, odds.size, temp->item);
            // Remove the odd item from the original list
            removeNode(ll, 0);
        } else {
            // Move to the next node in the original list
            temp = temp->next;
        }
    }

    // If the original list is empty, set its head to the head of the odds list
    if (ll->head == NULL) {
        ll->head = odds.head;
    }

    // If the odds list is not empty, append it to the end of the original list
    if (odds.head != NULL) {
        // Find the last node in the original list
        temp = ll->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        // Append the odds list to the end of the original list
        temp->next = odds.head;
    }
}

```

### Q4. Front back split
```c
void frontBackSplitLinkedList(LinkedList *ll, LinkedList *resultFrontList, LinkedList *resultBackList) {
    int size = ll->size;  // Get the size of the original linked list
    int frontSize = (size + 1) / 2;  // Calculate the size of the front half
    int idx = 0;  // Initialize index counter
    ListNode *temp = ll->head;  // Pointer to traverse the original list

    // Traverse the original list and split it into front and back halves
    while (temp != NULL) {
        // Insert the current node's item into the front half if it belongs to the front half
        if (idx < frontSize) {
            insertNode(resultFrontList, idx, temp->item);
        }
        // Otherwise, insert it into the back half
        else {
            insertNode(resultBackList, idx - frontSize, temp->item);
        }
        // Move to the next node in the original list
        temp = temp->next;
        // Increment the index counter
        idx++;
    }
}

```