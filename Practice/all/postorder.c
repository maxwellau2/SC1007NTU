//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // You should not change the definition of BSTNode

typedef struct _stackNode{
	BSTNode *data;
	struct _stackNode *next;
}StackNode; // You should not change the definition of StackNode

typedef struct _stack
{
	StackNode *top;
}Stack; // You should not change the definition of Stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void postOrderIterative(BSTNode *root);

void insertBSTNode(BSTNode **node, int value);

// You may use the following functions or you may write your own
void push(Stack *stack, BSTNode *node);
BSTNode *pop(Stack *s);
BSTNode *peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
    // Test Case 1: Empty Tree
    BSTNode *emptyTree = NULL;
    printf("Test Case 1: Empty Tree\n");
    printf("Expected Output: No output\n");
    printf("Actual Output: ");
    postOrderIterative(emptyTree);
    printf("\n\n");

    // Test Case 2: Single Node Tree
    BSTNode *singleNodeTree = NULL;
    insertBSTNode(&singleNodeTree, 10);
    printf("Test Case 2: Single Node Tree\n");
    printf("Expected Output: 10\n");
    printf("Actual Output: ");
    postOrderIterative(singleNodeTree);
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
    printf("Expected Output: 3 7 5 12 18 15 10\n");
    printf("Actual Output: ");
    postOrderIterative(completeBinaryTree);
    printf("\n\n");

    // Test Case 4: Skewed Binary Tree
    BSTNode *skewedBinaryTree = NULL;
    insertBSTNode(&skewedBinaryTree, 10);
    insertBSTNode(&skewedBinaryTree, 5);
    insertBSTNode(&skewedBinaryTree, 3);
    insertBSTNode(&skewedBinaryTree, 2);
    insertBSTNode(&skewedBinaryTree, 1);
    printf("Test Case 4: Skewed Binary Tree\n");
    printf("Expected Output: 1 2 3 5 10\n");
    printf("Actual Output: ");
    postOrderIterative(skewedBinaryTree);
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
    printf("Expected Output: 2 4 3 7 5 12 18 15 10\n");
    printf("Actual Output: ");
    postOrderIterative(mixedLevelsBinaryTree);
    printf("\n\n");

    // Test Case 6: Binary Tree with Duplicates
    BSTNode *duplicateBinaryTree = NULL;
    insertBSTNode(&duplicateBinaryTree, 10);
    insertBSTNode(&duplicateBinaryTree, 5);
    insertBSTNode(&duplicateBinaryTree, 10); // Duplicate
    insertBSTNode(&duplicateBinaryTree, 15);
    insertBSTNode(&duplicateBinaryTree, 5);  // Duplicate
    insertBSTNode(&duplicateBinaryTree, 15); // Duplicate
    printf("Test Case 6: Binary Tree with Duplicates\n");
    printf("Expected Output: 5 15 5 15 10 10\n");
    printf("Actual Output: ");
    postOrderIterative(duplicateBinaryTree);
    printf("\n\n");

    return 0;
}


//////////////////////////////////////////////////////////////////////////////////

// void postOrderIterative(BSTNode *root)
// {
// 	if(root == NULL) return;
// 	postOrderIterative(root->left);
// 	postOrderIterative(root->right);
    
// 	printf("%d ", root->item);
// }

void postOrderIterative(BSTNode *root)
{
	Stack s;
    s.top = NULL;
    if (root==NULL) return;
    // create 3 nodes;
    BSTNode *current = root;
    BSTNode *lastVisited = NULL;
    BSTNode *peekNode = NULL;
    while (!isEmpty(&s) || current != NULL)
    {
        // go all the way left
        while (current != NULL)
        {
            push(&s, current);
            current = current->left;
        }
        // peke the top node
        peekNode = peek(&s);
        if (peekNode->right != NULL && peekNode->right != lastVisited)
        {
            current = peekNode->right;
        }
        else
        {
            printf("%d ", peekNode->item);
            lastVisited = pop(&s);
        }
    }
}


// make a stack
// make a current(set to root), lastvisited, peeknode
// while current isnt null or stack isnt empty
// go all the way left, push all the left nodes onto stack
// then peek at the node on top of stack,
// if peek's right isnt null and isnt last visited, set current to peek's right
// else, print peeknode and set lastvisited to pop(s);


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

void push(Stack *stack, BSTNode * node)
{
	StackNode *temp;

	temp = malloc(sizeof(StackNode));

	if (temp == NULL)
		return;
	temp->data = node;

	if (stack->top == NULL)
	{
		stack->top = temp;
		temp->next = NULL;
	}
	else
	{
		temp->next = stack->top;
		stack->top = temp;
	}
}


BSTNode * pop(Stack * s)
{
	StackNode *temp, *t;
	BSTNode * ptr;
	ptr = NULL;

	t = s->top;
	if (t != NULL)
	{
		temp = t->next;
		ptr = t->data;

		s->top = temp;
		free(t);
		t = NULL;
	}

	return ptr;
}

BSTNode * peek(Stack * s)
{
	StackNode *temp;
	temp = s->top;
	if (temp != NULL)
		return temp->data;
	else
		return NULL;
}

int isEmpty(Stack *s)
{
	if (s->top == NULL)
		return 1;
	else
		return 0;
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