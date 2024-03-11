#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode {
    int item;
    struct _listnode *next;
} ListNode;

typedef struct _linkedlist {
    int size;
    ListNode *head;
} LinkedList;

void removeDuplicates(LinkedList *ll);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *l);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

int main() {
    LinkedList ll;
    ll.head = NULL;
    ll.size = 0;

    // Test Case 1: Insert elements into the linked list
    insertNode(&ll, ll.size, 5);
    insertNode(&ll, ll.size, 3);
    insertNode(&ll, ll.size, 7);
    insertNode(&ll, ll.size, 5);
    insertNode(&ll, ll.size, 3);
    insertNode(&ll, ll.size, 8);
    insertNode(&ll, ll.size, 3);
    insertNode(&ll, ll.size, 7);
    insertNode(&ll, ll.size, 9);
    insertNode(&ll, ll.size, 3);

    printf("Test Case 1:\n");
    printf("Original linked list: ");
    printList(&ll);

    // Remove duplicates
    removeDuplicates(&ll);
    printf("Linked list after removing duplicates: ");
    printList(&ll);
    removeAllItems(&ll);

    // Test Case 2: Insert elements into the linked list
    insertNode(&ll, ll.size, 1);
    insertNode(&ll, ll.size, 2);
    insertNode(&ll, ll.size, 3);
    insertNode(&ll, ll.size, 4);
    insertNode(&ll, ll.size, 5);

    printf("\nTest Case 2:\n");
    printf("Original linked list: ");
    printList(&ll);

    // Remove duplicates
    removeDuplicates(&ll);
    printf("Linked list after removing duplicates: ");
    printList(&ll);
    removeAllItems(&ll);

    // Test Case 3: Insert elements into the linked list
    insertNode(&ll, ll.size, 1);
    insertNode(&ll, ll.size, 1);
    insertNode(&ll, ll.size, 1);
    insertNode(&ll, ll.size, 1);
    insertNode(&ll, ll.size, 1);

    printf("\nTest Case 3:\n");
    printf("Original linked list: ");
    printList(&ll);

    // Remove duplicates
    removeDuplicates(&ll);
    printf("Linked list after removing duplicates: ");
    printList(&ll);
    removeAllItems(&ll);

    return 0;
}


void removeDuplicates(LinkedList *ll) {
    if (ll->head == NULL || ll == NULL) return;
    ListNode *slow = ll->head;
    ListNode *fast = ll->head;
    while(slow != NULL)
    {
        fast = slow;
        while(fast->next != NULL)
        {
            if (slow->item == fast->next->item)
            {
                ListNode *dupe = fast->next;
                fast->next = fast->next->next;
                free(dupe);
            }
            else
            {
                fast = fast->next;
            }
        }
        slow = slow->next;
    }
}

void printList(LinkedList *ll) {
    ListNode *cur;
    if (ll == NULL)
        return;
    cur = ll->head;
    if (cur == NULL)
        printf("Empty");
    while (cur != NULL) {
        printf("%d ", cur->item);
        cur = cur->next;
    }
    printf("\n");
}

void removeAllItems(LinkedList *ll) {
    ListNode *cur = ll->head;
    ListNode *tmp;

    while (cur != NULL) {
        tmp = cur->next;
        free(cur);
        cur = tmp;
    }
    ll->head = NULL;
    ll->size = 0;
}

ListNode *findNode(LinkedList *ll, int index) {
    ListNode *temp;

    if (ll == NULL || index < 0 || index >= ll->size)
        return NULL;

    temp = ll->head;

    if (temp == NULL || index < 0)
        return NULL;

    while (index > 0) {
        temp = temp->next;
        if (temp == NULL)
            return NULL;
        index--;
    }

    return temp;
}

int insertNode(LinkedList *ll, int index, int value) {
    ListNode *pre, *cur;

    if (ll == NULL || index < 0 || index > ll->size + 1)
        return -1;

    // If empty list or inserting first node, need to update head pointer
    if (ll->head == NULL || index == 0) {
        cur = ll->head;
        ll->head = malloc(sizeof(ListNode));
        ll->head->item = value;
        ll->head->next = cur;
        ll->size++;
        return 0;
    }

    // Find the nodes before and at the target position
    // Create a new node and reconnect the links
    if ((pre = findNode(ll, index - 1)) != NULL) {
        cur = pre->next;
        pre->next = malloc(sizeof(ListNode));
        pre->next->item = value;
        pre->next->next = cur;
        ll->size++;
        return 0;
    }

    return -1;
}

int removeNode(LinkedList *ll, int index) {
    ListNode *pre, *cur;

    // Highest index we can remove is size-1
    if (ll == NULL || index < 0 || index >= ll->size)
        return -1;

    // If removing first node, need to update head pointer
    if (index == 0) {
        cur = ll->head->next;
        free(ll->head);
        ll->head = cur;
        ll->size--;

        return 0;
    }

    // Find the nodes before and after the target position
    // Free the target node and reconnect the links
    if ((pre = findNode(ll, index - 1)) != NULL) {

        if (pre->next == NULL)
            return -1;

        cur = pre->next;
        pre->next = cur->next;
        free(cur);
        ll->size--;
        return 0;
    }

    return -1;
}
