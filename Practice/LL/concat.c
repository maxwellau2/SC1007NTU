
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

int concatenate(ListNode **ptrHead1, ListNode *head2);
ListNode * createNode(int value);
void printList(ListNode *head);

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
    printf("List 1: ");
    printList(head1);
    printf("List 2: ");
    printList(head2);
    concatenate(&head1, head2);
    printf("After concatenating: ");
    printList(head1);

    printf("List 1: ");
    printList(head3);
    printf("List 2: ");
    printList(head4);
    concatenate(&head3, head4);
    printf("After concatenating: ");
    printList(head3);

    printf("List 1: ");
    printList(head5);
    printf("List 2: ");
    printList(head6);
    concatenate(&head5, head6);
    printf("After concatenating: ");
    printList(head5);

    printf("List 1: ");
    printList(head7);
    printf("List 2: ");
    printList(head1); // Reusing head1 from the first test
    concatenate(&head7, head1);
    printf("After concatenating: ");
    printList(head7);

    return 0;
}

int concatenate(ListNode **ptrHead1, ListNode *head2)
{
    if (!*ptrHead1) return -1;

    ListNode *temp;
    temp = *ptrHead1;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    // now concat
    if (!head2) return -1;

    temp->next = head2;
    return 0;
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