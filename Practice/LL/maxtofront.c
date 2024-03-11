
////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////


typedef struct _listnode{
	int num;
	struct _listnode *next;
} ListNode;
typedef struct _linkedlist{
	ListNode *head;
	int size;
} LinkedList;
typedef struct _dbllistnode{
	int num;
	struct _dbllistnode *pre;
	struct _dbllistnode *next;
} DblListNode;

////////////////////////////////////////////////////////////////////
////////////
int removeNode(ListNode **ptrHead, int index);
int removeNode2(LinkedList *ll, int index);
int split(ListNode *head, ListNode **ptrEvenList, ListNode **ptrOddList);
int duplicateReverse(ListNode *head, ListNode **ptrNewHead);

void printList(ListNode *head);
ListNode * findNode(ListNode *head, int index);
int insertNode(ListNode **ptrHead, int index, int value);
ListNode * createNode(int value);
void printList(ListNode *head);

// these are for the practice questions
int moveMaxToFront(ListNode **ptrHead);
int concatenate(ListNode **ptrHead1, ListNode *head2);
int combineAlternating(ListNode **ptrHead, ListNode *head1, ListNode *head2);
int insertDbl(DblListNode **ptrHead, int index, int value);
void printDblList(DblListNode *head);

int main() {
    // Test cases
    ListNode *head1 = NULL;
    ListNode *head2 = createNode(5);
    ListNode *head3 = createNode(3);
    head3->next = createNode(7);
    head3->next->next = createNode(1);
    ListNode *head4 = createNode(-2);
    head4->next = createNode(-5);
    head4->next->next = createNode(-1);
    ListNode *head5 = createNode(4);
    head5->next = createNode(4);
    head5->next->next = createNode(4);
    ListNode *head6 = createNode(9);
    head6->next = createNode(3);
    head6->next->next = createNode(5);
    head6->next->next->next = createNode(7);
    ListNode *head7 = createNode(2);
    head7->next = createNode(8);
    head7->next->next = createNode(6);

    // Test cases execution
    printf("Original List: ");
    printList(head1);
    moveMaxToFront(&head1);
    printf("After moving max to front: ");
    printList(head1);

    printf("Original List: ");
    printList(head2);
    moveMaxToFront(&head2);
    printf("After moving max to front: ");
    printList(head2);

    printf("Original List: ");
    printList(head3);
    moveMaxToFront(&head3);
    printf("After moving max to front: ");
    printList(head3);

    printf("Original List: ");
    printList(head4);
    moveMaxToFront(&head4);
    printf("After moving max to front: ");
    printList(head4);

    printf("Original List: ");
    printList(head5);
    moveMaxToFront(&head5);
    printf("After moving max to front: ");
    printList(head5);

    printf("Original List: ");
    printList(head6);
    moveMaxToFront(&head6);
    printf("After moving max to front: ");
    printList(head6);

    printf("Original List: ");
    printList(head7);
    moveMaxToFront(&head7);
    printf("After moving max to front: ");
    printList(head7);

    return 0;
}

int moveMaxToFront(ListNode **ptrHead)
{
    // empty LL
    if (*ptrHead == NULL || (*ptrHead)->next == NULL)  return -1;

    ListNode *maxnode, *curr, *prevmax, *prev;
    maxnode = *ptrHead;
    prevmax = NULL;
    prev = NULL;

    curr = *ptrHead;
    int max = curr->num;
    int idx = 0;
    int maxidx = 0;
    while(curr->next != NULL)
    {
        if (curr->next->num > max)
        {   
            prevmax = curr;
            maxnode = curr->next;
            maxidx = idx;
            max = curr->next->num;
        }
        curr = curr->next;
        idx++;
    }
    if (prevmax == NULL) return -1;

    prevmax->next = maxnode->next;
    maxnode->next = *ptrHead;
    *ptrHead = maxnode;
    return idx;
}

// Function to create a new list node
ListNode * createNode(int value) {
    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    newNode->num = value;
    newNode->next = NULL;
    return newNode;
}

// Function to print the elements of a linked list
void printList(ListNode *head) {
    ListNode *current = head;
    while (current != NULL) {
        printf("%d -> ", current->num);
        current = current->next;
    }
    printf("NULL\n");
}


void printDblList(DblListNode *head){
	if (head == NULL) return;
	while (head != NULL){
		printf("%d ", head->num);
		head = head->next;
	}
	printf("\n");
}

ListNode * findNode(ListNode *head, int index){
	if (head == NULL || index < 0) return NULL;
	while (index > 0){
		head = head->next;
		if (head == NULL)
			return NULL;
		index--;
	}
	return head;
}


int insertNode(ListNode **ptrHead, int index, int value){
	ListNode *pre, *cur;
	// If empty list or inserting first node, need to update head pointer
	if (*ptrHead == NULL || index == 0){
		cur = *ptrHead;
		*ptrHead = malloc(sizeof(ListNode));
		(*ptrHead)->num = value;
		(*ptrHead)->next = cur;
		return 0;
	}
	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(*ptrHead, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->num = value;
		pre->next->next = cur;
		return 0;
	}
	return -1;
}