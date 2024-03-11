//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024
///////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // You should not change the definition of BSTNode

typedef struct _QueueNode {
	BSTNode *data;
	struct _QueueNode *nextPtr;
}QueueNode; // You should not change the definition of QueueNode


typedef struct _queue
{
	QueueNode *head;
	QueueNode *tail;
}Queue; // You should not change the definition of queue

///////////////////////////////////////////////////////////////////////////////////

// You should not change the prototypes of these functions
void levelOrderTraversal(BSTNode *node);

void insertBSTNode(BSTNode **node, int value);

BSTNode* dequeue(QueueNode **head, QueueNode **tail);
void enqueue(QueueNode **head, QueueNode **tail, BSTNode *node);
int isEmpty(QueueNode *head);
void removeAll(BSTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	// Test Case 1: Empty Tree
    BSTNode *emptyTree = NULL;
    printf("Test Case 1: Empty Tree\n");
    printf("Expected Output: No output\n");
    printf("Actual Output: ");
    levelOrderTraversal(emptyTree);
    printf("\n\n");

    // Test Case 2: Single Node Tree
    BSTNode *singleNodeTree = NULL;
    insertBSTNode(&singleNodeTree, 10);
    printf("Test Case 2: Single Node Tree\n");
    printf("Expected Output: 10\n");
    printf("Actual Output: ");
    levelOrderTraversal(singleNodeTree);
    printf("\n\n");

    // Test Case 3: Complete Binary Tree
    BSTNode *completeBinaryTree = NULL;
    insertBSTNode(&completeBinaryTree, 10);
    insertBSTNode(&completeBinaryTree, 5);
    insertBSTNode(&completeBinaryTree, 15);
    insertBSTNode(&completeBinaryTree, 3);
    insertBSTNode(&completeBinaryTree, 7);
    insertBSTNode(&completeBinaryTree, 12);
    insertBSTNode(&completeBinaryTree, 18);
    printf("Test Case 3: Complete Binary Tree\n");
    printf("Expected Output: 10 5 15 3 7 12 18\n");
    printf("Actual Output: ");
    levelOrderTraversal(completeBinaryTree);
    printf("\n\n");

    // Test Case 4: Skewed Binary Tree
    BSTNode *skewedBinaryTree = NULL;
    insertBSTNode(&skewedBinaryTree, 10);
    insertBSTNode(&skewedBinaryTree, 5);
    insertBSTNode(&skewedBinaryTree, 3);
    insertBSTNode(&skewedBinaryTree, 2);
    insertBSTNode(&skewedBinaryTree, 1);
    printf("Test Case 4: Skewed Binary Tree\n");
    printf("Expected Output: 10 5 3 2 1\n");
    printf("Actual Output: ");
    levelOrderTraversal(skewedBinaryTree);
    printf("\n\n");

    // Test Case 5: Binary Tree with Mixed Levels
    BSTNode *mixedLevelsBinaryTree = NULL;
    insertBSTNode(&mixedLevelsBinaryTree, 10);
    insertBSTNode(&mixedLevelsBinaryTree, 5);
    insertBSTNode(&mixedLevelsBinaryTree, 15);
    insertBSTNode(&mixedLevelsBinaryTree, 3);
    insertBSTNode(&mixedLevelsBinaryTree, 7);
    insertBSTNode(&mixedLevelsBinaryTree, 12);
    insertBSTNode(&mixedLevelsBinaryTree, 18);
    insertBSTNode(&mixedLevelsBinaryTree, 2);
    insertBSTNode(&mixedLevelsBinaryTree, 4);
    printf("Test Case 5: Binary Tree with Mixed Levels\n");
    printf("Expected Output: 10 5 15 3 7 12 18 2 4\n");
    printf("Actual Output: ");
    levelOrderTraversal(mixedLevelsBinaryTree);
    printf("\n\n");

    // Test Case 6: Binary Tree with Duplicates
    BSTNode *duplicateBinaryTree = NULL;
    insertBSTNode(&duplicateBinaryTree, 10);
    insertBSTNode(&duplicateBinaryTree, 5);
    insertBSTNode(&duplicateBinaryTree, 10);
    insertBSTNode(&duplicateBinaryTree, 15);
    insertBSTNode(&duplicateBinaryTree, 5);
    insertBSTNode(&duplicateBinaryTree, 15);
    printf("Test Case 6: Binary Tree with Duplicates\n");
    printf("Expected Output: 10 5 15 10 5 15\n");
    printf("Actual Output: ");
    levelOrderTraversal(duplicateBinaryTree);
    printf("\n\n");
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void levelOrderTraversal(BSTNode* root)
{

    /* add your code here */
    if (root == NULL) return;
    Queue q;
    q.head = NULL;
    q.tail = NULL;
    BSTNode *res;
    enqueue(&q.head, &q.tail, root);
    while(!isEmpty(q.head))
    {
        res = dequeue(&q.head, &q.tail);
        printf("%d ", res->item);
        if(res->left != NULL)
            enqueue(&q.head, &q.tail, res->left);
        if(res->right != NULL)
            enqueue(&q.head, &q.tail, res->right);
    }
}

///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value){
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL) {
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value >(*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

// enqueue node
void enqueue(QueueNode **headPtr, QueueNode **tailPtr, BSTNode *node)
{
	// dynamically allocate memory
	QueueNode *newPtr = malloc(sizeof(QueueNode));

	// if newPtr does not equal NULL
	if (newPtr != NULL) {
		newPtr->data = node;
		newPtr->nextPtr = NULL;

		// if queue is empty, insert at head
		if (isEmpty(*headPtr)) {
			*headPtr = newPtr;
		}
		else { // insert at tail
			(*tailPtr)->nextPtr = newPtr;
		}

		*tailPtr = newPtr;
	}
	else {
		printf("Node not inserted");
	}
}

BSTNode* dequeue(QueueNode **headPtr, QueueNode **tailPtr)
{
	BSTNode *node = (*headPtr)->data;
	QueueNode *tempPtr = *headPtr;
	*headPtr = (*headPtr)->nextPtr;

	if (*headPtr == NULL) {
		*tailPtr = NULL;
	}

	free(tempPtr);

	return node;
}

int isEmpty(QueueNode *head)
{
	return head == NULL;
}

void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}