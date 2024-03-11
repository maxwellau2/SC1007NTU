////////////////////////////////////////////////////////////


//#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;

int searchList(ListNode *head, int value);

void main()
{
	ListNode *head, *p, *temp;
	int n;
    int count = 0;


	head=NULL;
	p=NULL;		// pointing to the last node in the list
	printf("Enter a list of numbers, terminated by the value -1:\n");
    // getchar();

	/////////////////////////////////////////////////////////////////

	//Question 2
    //Write your program code here
    while(1)
    {
        scanf("%d", &n);
        if (n == -1)
        {
            temp = head;
            while(temp != NULL)
            {
                printf("%d\n", temp->item);
                temp = temp->next;
            }
            break;
        }
        if (count == 0)
        {
            head = (ListNode *) malloc(sizeof(ListNode));
            head->item = n;
            head->next = NULL;
            p = head;
            count ++;  

        }
        else
        {
            p->next = (ListNode *) malloc(sizeof(ListNode));
            p = p->next;
            p->item = n;
            p->next = NULL;
        }
    }

    // freeing memory
    // proposed solution does not work because we are freeing the data in the head's pointer address, hence there will be no next pointer to reference in runtime, causing a crash
    p = head;
    while(p != NULL)
    {
        temp = p->next;
        free(temp);
    }
    printf("%d", head);

    // printf("Enter value to search for:");
	// scanf("%d", &n);
	// searchList(head,n);
   //////////////////////////////////////////////////////////////////
}

int searchList(ListNode *head, int value)
{
    ListNode *temp;
    temp = head;
    int count = 0;
    while (temp != NULL)
    {
        if (temp->item == value)
        {
            printf("%d", count);
            return count;
        }
        temp = temp->next;
        count ++;
    }
}