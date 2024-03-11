## BST
### Q1. In Order

```c
void inOrderTraversal(BSTNode *root)
{
    // Initialize a stack for iterative traversal
    Stack s;
    s.top = NULL;

    // Start traversal with the root node
    BSTNode *current = root;

    // Iterate until we reach the end of the tree or the stack is empty
    while (current != NULL || !isEmpty(&s))
    {
        // Traverse to the leftmost node of the current subtree
        while (current != NULL)
        {
            // Push all nodes along the leftmost path onto the stack
            push(&s, current);
            current = current->left;
        }

        // Pop the top node from the stack (leftmost node)
        current = pop(&s);

        // Print the value of the current node
        printf("%d ", current->item);

        // Move to the right subtree to continue traversal
        current = current->right;
    }
}

```
```c
void inOrderTraversal(BSTNode *root)
{
    // Base case: If the current node is NULL, return
    if (root == NULL) {
        return;
    }

    // Recursive call to traverse the left subtree
    inOrderTraversal(root->left);

    // Print the value of the current node
    printf("%d ", root->item);

    // Recursive call to traverse the right subtree
    inOrderTraversal(root->right);
}

```

### Q2. PostOrder Traversal
```c
void postOrderIterativeS1(BSTNode *root)
{
    if (root == NULL)
        return;

    Stack s;
    s.top = NULL;
    BSTNode *current = root;
    BSTNode *lastVisited = NULL;

    while (current != NULL || !isEmpty(&s))
    {
        while (current != NULL)
        {
            push(&s, current);
            current = current->left;
        }

        // Peek at the top of the stack
        BSTNode *peekNode = peek(&s);

        // If the right child is not yet visited, visit it first
        if (peekNode->right != NULL && peekNode->right != lastVisited)
        {
            current = peekNode->right;
        }
        else
        {
            // If the right child has been visited or doesn't exist,
            // it's time to visit the current node
            printf("%d ", peekNode->item);
            lastVisited = pop(&s);
        }
    }
}
```

```c
void postOrderRecursive(BSTNode *root) {
    if (root == NULL)
        return;
    
    // Traverse left subtree
    postOrderRecursive(root->left);

    // Traverse right subtree
    postOrderRecursive(root->right);

    // Visit current node
    printf("%d ", root->item);
}

```

### Q3. Identical tree

```c
int identical(BTNode *tree1, BTNode *tree2)

{
   // add your code here
   if (tree1 == NULL && tree2 == NULL)
   {
        return 1;
   }
   if (tree1 == NULL && tree2 != NULL)
   {
        return 0;
   }
   if (tree1 != NULL && tree2 == NULL)
   {
        return 0;
   }
   if (tree1->item == tree2->item)
   {
        return identical(tree1->left, tree2->left) && identical(tree1->right, tree2->right);
   }
   return 0;
}
```