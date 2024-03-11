#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode
{
    int value;
    struct _listnode* next;
} ListNode;

void AppendNode(ListNode* node1, ListNode* node2);
void InsertNode(ListNode* head, ListNode* newnode, int position);
void PrintList(ListNode* head);

int main()
{
    printf("GoodAM, creating head Node\n");
    ListNode* head = NULL;
    head = (ListNode*) malloc(sizeof(ListNode));
    head->value = 13;
    head->next = NULL;
    printf("Node 1 val : %d\n", head->value);

    printf("Creating 2nd Node\n");
    ListNode* newnode = NULL;
    newnode = (ListNode*) malloc(sizeof(ListNode));
    newnode->value = 14;
    newnode->next = NULL;
    printf("Node 2 val : %d\n", newnode->value);
    AppendNode(head, newnode);

    printf("Creating 3rd Node\n");
    ListNode* newnode2 = NULL;
    newnode2 = (ListNode*) malloc(sizeof(ListNode));
    newnode2->value = 15;
    newnode2->next = NULL;
    printf("Node 3 val : %d\n", newnode2->value);
    InsertNode(head, newnode2, 1);
    PrintList(head);
}

void PrintList(ListNode* head)
{
    ListNode* temp = NULL;
    temp = head;
    int count = 0;
    while(temp != NULL)
    {
        printf("Node Number: %d\t Value : %d\n",count, temp->value);
        temp = temp->next;
        count ++;
    }
}

void AppendNode(ListNode* node1, ListNode* node2)
{
    node1->next = node2;
    return;
}

void InsertNode(ListNode* head, ListNode* newnode, int position)
{
    ListNode* temp1 = NULL;
    ListNode* temp2 = NULL;
    temp1 = head;
    temp2 = head;
    for(int i=0; i < position-1; i ++)
    {
        temp1 = temp1->next;
        temp2 = temp2->next; 
    }
    temp2 = temp2->next; // walk one more
    // now start insertion
    newnode->next = temp2;
    temp1->next = newnode;
    return;
}