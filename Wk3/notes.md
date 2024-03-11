## Stacks and Qs
### Q1. Infix to Postfix
```c
void infixtoPostfix(char *infix, char *postfix)
{
    // Initialize a stack to hold operators
    Stack stack;
    stack.ll.size = 0;
    stack.ll.head = NULL;
    
    int j = 0; // Index for the postfix expression
    
    // Loop through each character in the infix expression
    for (int i = 0; i < strlen(infix); i++)
    {
        // If the character is not an operator, it's an operand
        if (!isOperator(infix[i]))
        {
            // Append operand to the postfix expression
            postfix[j++] = infix[i];
        }
        // If the character is an opening parenthesis '('
        else if (infix[i] == '(')
        {
            // Push it onto the stack
            push(&stack, infix[i]);
        }
        // If the character is a closing parenthesis ')'
        else if (infix[i] == ')')
        {
            // Pop operators from the stack and append them to postfix until '(' is encountered
            while (!isEmptyStack(&stack) && peek(&stack) != '(')
            {
                postfix[j++] = pop(&stack);
            }
            pop(&stack); // Pop the remaining '('
        }
        // If the character is an operator
        else if (isOperator(infix[i]))
        {
            // Pop operators from the stack and append them to postfix if they have higher or equal precedence
            while (!isEmptyStack(&stack) && precedence(peek(&stack)) >= precedence(infix[i]))
            {
                postfix[j++] = pop(&stack);
            }
            // Push the current operator onto the stack
            push(&stack, infix[i]);
        }
    }
    
    // Append remaining operators in the stack to the postfix expression
    while (!isEmptyStack(&stack))
    {
        postfix[j++] = pop(&stack);
    }
    
    // Terminate the postfix expression with a null character
    postfix[j] = '\0';
}

int isOperator(char p)
{
	// printf("%d", p);
	return (p >= 37) && (p <= 47);
}

int precedence(char op)
{
    if(op == '*' || op == '/')
        return 2;
    else if(op == '+' || op == '-')
		return 1;
	else return 0;
}

```
1. Create an empty stack.
2. Initialize index j to 0 for the postfix expression.
3. Iterate through each character in the infix expression from left to right:
    a. If the current character is an operand (not an operator), append it to the postfix expression.

    b. If the current character is '(', push it onto the stack.

    c. If the current character is ')', pop operators from the stack and append them to the postfix expression until '(' is encountered. Pop '(' from the stack.

    d. If the current character is an operator:

        i. Pop operators from the stack and append them to the postfix expression if they have higher or equal precedence to the current operator.

        ii. Push the current operator onto the stack.
4. After processing all characters in the infix expression:
    a. Pop and append remaining operators from the stack to the postfix expression.
5. Terminate the postfix expression with a null character.

### Q2. Infix to Prefix
```c
void infixtoPrefix(char* infix, char* prefix) 
{
    // Initialize a stack to hold operators
    Stack stack;
    stack.ll.size = 0;
    stack.ll.head = NULL;
    
    // Create a reversed copy of the infix expression
    char reversed[strlen(infix)];
    int j = 0;
    for (int i = strlen(infix) - 1; i >= 0; i--)
    {
        reversed[j++] = infix[i];
    }
    reversed[j] = '\0';
    
    // Reset j to 0
    j = 0;
    
    // Loop through the reversed infix expression
    for (int i = 0; i < strlen(reversed); i++)
    {
        // If the character is an operand, add it to the prefix expression
        if (!isOperator(reversed[i])) 
        {
            prefix[j++] = reversed[i];
        }
        // If the character is a closing parenthesis ')', push it onto the stack
        else if (reversed[i] == ')') 
        {
            push(&stack, reversed[i]);
        }
        // If the character is an opening parenthesis '('
        else if (reversed[i] == '(')
        {
            // Pop operators from the stack and add them to prefix until '(' is encountered
            while (!isEmptyStack(&stack) && peek(&stack) != ')')
            {
                prefix[j++] = pop(&stack);
            }
            pop(&stack); // Pop the remaining ')'
        }
        // If the character is an operator
        else if (isOperator(reversed[i]))
        {
            // Pop operators from the stack and add them to prefix if they have higher precedence
            while (!isEmptyStack(&stack) && precedence(peek(&stack)) > precedence(reversed[i]))
            {
                prefix[j++] = pop(&stack);
            }
            // Push the current operator onto the stack
            push(&stack, reversed[i]);
        }
    }
    
    // Append any remaining operators in the stack to the prefix expression
    while (!isEmptyStack(&stack))
    {
        prefix[j++] = pop(&stack);
    }
    
    // Terminate the prefix expression with a null character
    prefix[j] = '\0';
    
    // Reverse the prefix expression to get the final result
    stringReverse(prefix);
}
void stringReverse(char* str) 
{ 
    int len = strlen(str); 
    // pointers to start and end 
    char* start = str; 
    char* end = str + len - 1; 
  
    while (start < end) { 
        char temp = *start; 
        *start = *end; 
        *end = temp; 
        start++; 
        end--; 
    } 
} 

int isOperator(char p)
{
	// printf("%d", p);
	return (p >= 37) && (p <= 47);
}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}
```

### Q3. Postfix Evaluation

```c
double postfixEvaluation(char* postfix) 
{
    //add your code here
    Stack s;
    s.ll.head = NULL;
    s.ll.size = 0;
    int length = strlen(postfix);
    char temp;
    double a, b, res;
    for (int i=0; i<length; i++)
    {
        temp = postfix[i];
        if (!isOperator(temp))
        {
            push(&s, temp-'0');
        }
        else
        {
            b = pop(&s);
            a = pop(&s);
            if (temp == '/')
            {
                res = a/b;
            }
            else if (temp == '*')
            {
                res = a*b;
            }
            else if (temp == '+')
            {
                res = a+b;
            }
            else if (temp == '-')
            {
                res = a-b;
            }
            push(&s, res);
        }
    }
    return peek(&s);
}

int isOperator(char k)
{
    if (k>=48 && k<=57) return 0;
    return 1;
}
```
### Q4. Interleave Q
```c
void interleaveQueue(Queue *q)
{
    Stack stack;
    stack.ll.head=NULL;
    stack.ll.size=0;
    int halfsize = q->ll.size / 2;
    // push first half elements onto the stack
    for (int i = 0; i < halfsize; i++)
    {
        push(&stack, dequeue(q));
    }
    // enqueue back the stack elements
    while (!isEmptyStack(&stack))
    {
        enqueue(q, pop(&stack));
    }
    // dequeue the first half elements of q, then enqueue them back
    for (int i = 0; i < halfsize; i++)
    {
        enqueue(q, dequeue(q));
    }
    // push the first half elements into the stack
    for (int i = 0; i < halfsize; i++)
    {
        push(&stack, dequeue(q));
    }
    while (!isEmptyStack(&stack))
    {
        enqueue(q, pop(&stack));
        enqueue(q, dequeue(q));
    }
}
```