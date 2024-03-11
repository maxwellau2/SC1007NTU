#include <stdio.h>
#include <stdlib.h>

// Structure definition for Binary Tree Node
typedef struct _btnode {
    int item;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

// Structure definition for Stack Node
typedef struct _stackNode {
    BTNode *btnode;
    struct _stackNode *next;
} StackNode;

// Structure definition for Stack
typedef struct _stack {
    StackNode *top;
} Stack;

// Function prototypes
int maxDepth(BTNode *node);
BTNode *createBTNode(int item);
void push(Stack *stk, BTNode *node);
BTNode *pop(Stack *stk);
void printTree(BTNode *node);
void removeAll(BTNode **node);

int main() {
    // Test Case 1: Empty Tree
    BTNode *emptyTree = NULL;
    printf("Test Case 1: Empty Tree\n");
    printf("Expected Output: 0\n");
    printf("Actual Output: %d\n", maxDepth(emptyTree));
    printf("\n");

    // Test Case 2: Single Node Tree
    BTNode *singleNodeTree = createBTNode(10);
    printf("Test Case 2: Single Node Tree\n");
    printf("Expected Output: 1\n");
    printf("Actual Output: %d\n", maxDepth(singleNodeTree));
    printf("\n");

    // Test Case 3: Complete Binary Tree
    BTNode *completeBinaryTree = createBTNode(10);
    completeBinaryTree->left = createBTNode(5);
    completeBinaryTree->right = createBTNode(15);
    completeBinaryTree->left->left = createBTNode(3);
    completeBinaryTree->left->right = createBTNode(7);
    completeBinaryTree->right->left = createBTNode(12);
    completeBinaryTree->right->right = createBTNode(18);
    printf("Test Case 3: Complete Binary Tree\n");
    printf("Expected Output: 3\n");
    printf("Actual Output: %d\n", maxDepth(completeBinaryTree));
    printf("\n");

    // Test Case 4: Skewed Binary Tree
    BTNode *skewedBinaryTree = createBTNode(10);
    skewedBinaryTree->left = createBTNode(5);
    skewedBinaryTree->left->left = createBTNode(3);
    skewedBinaryTree->left->left->left = createBTNode(2);
    skewedBinaryTree->left->left->left->left = createBTNode(1);
    printf("Test Case 4: Skewed Binary Tree\n");
    printf("Expected Output: 5\n");
    printf("Actual Output: %d\n", maxDepth(skewedBinaryTree));
    printf("\n");

    // Test Case 5: Binary Tree with Mixed Levels
    BTNode *mixedLevelsBinaryTree = createBTNode(10);
    mixedLevelsBinaryTree->left = createBTNode(5);
    mixedLevelsBinaryTree->right = createBTNode(15);
    mixedLevelsBinaryTree->left->left = createBTNode(3);
    mixedLevelsBinaryTree->left->right = createBTNode(7);
    mixedLevelsBinaryTree->right->left = createBTNode(12);
    mixedLevelsBinaryTree->right->right = createBTNode(18);
    mixedLevelsBinaryTree->left->left->left = createBTNode(2);
    mixedLevelsBinaryTree->left->left->right = createBTNode(4);
    printf("Test Case 5: Binary Tree with Mixed Levels\n");
    printf("Expected Output: 4\n");
    printf("Actual Output: %d\n", maxDepth(mixedLevelsBinaryTree));
    printf("\n");

    // Test Case 6: Binary Tree with Duplicates
    BTNode *duplicateBinaryTree = createBTNode(10);
    duplicateBinaryTree->left = createBTNode(5);
    duplicateBinaryTree->left->left = createBTNode(10); // Duplicate
    duplicateBinaryTree->right = createBTNode(15);
    duplicateBinaryTree->left->right = createBTNode(5);  // Duplicate
    duplicateBinaryTree->right->right = createBTNode(15); // Duplicate
    printf("Test Case 6: Binary Tree with Duplicates\n");
    printf("Expected Output: 3\n");
    printf("Actual Output: %d\n", maxDepth(duplicateBinaryTree));
    printf("\n");

    // Clean up memory
    removeAll(&singleNodeTree);
    removeAll(&completeBinaryTree);
    removeAll(&skewedBinaryTree);
    removeAll(&mixedLevelsBinaryTree);
    removeAll(&duplicateBinaryTree);

    return 0;
}

// Function to find the maximum depth of a binary tree
int maxDepth(BTNode *node)
{
    /* add your code here */
    if (node == NULL) return 0;
    int left, right;
    left = maxDepth(node->left);
    right = maxDepth(node->right);
    if (left > right)
        return 1 + left;
    return 1 + right;

}

// Function to create a binary tree node
BTNode *createBTNode(int item) {
    BTNode *newNode = malloc(sizeof(BTNode));
    newNode->item = item;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to remove all nodes from the binary tree
void removeAll(BTNode **node) {
    if (*node != NULL) {
        removeAll(&((*node)->left));
        removeAll(&((*node)->right));
        free(*node);
        *node = NULL;
    }
}
