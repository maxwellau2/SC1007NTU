def isOperator(p):
    return p in ['+', '-', '*', '/', '(',')']

def precedence(p):
    if p in ['*', '/']:
        return 1
    return 0

p = str(input("Enter an expression\t"))
builder = ""
stack = []
for i in p:
    if not isOperator(i):
        builder += i
    elif i == '(':
        stack.append(i)
    elif i == ')':
        if len(stack) != 0:
            while stack[-1] != '(':
                builder += stack.pop()
            stack.pop()
    elif isOperator(i):
        if len(stack) != 0:
            while precedence(stack[-1]) > precedence(i):
                builder += stack.pop()
        stack.append(i)
    else:
        stack.append(i)
    print(stack)
    print(builder)
while len(stack) != 0:
    builder += stack.pop()
print(builder)


def isOperator(p):
    return p in ['+', '-', '*', '/', '(',')']

def precedence(p):
    if p in ['*', '/']:
        return 2
    elif p in ['+', '-']:
        return 1
    return 0

p = str(input("Enter an expression\t"))
builder = ""
stack = []
for i in p:
    if not isOperator(i):
        builder += i
    elif i == '(':
        stack.append(i)
    elif i == ')':
        while stack and stack[-1] != '(':
            builder += stack.pop()
        stack.pop()  # Pop '('
    elif isOperator(i):
        while stack and precedence(stack[-1]) >= precedence(i):
            builder += stack.pop()
        stack.append(i)

# Pop remaining operators from the stack
while stack:
    builder += stack.pop()

print(builder)
