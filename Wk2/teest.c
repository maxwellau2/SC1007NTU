#include <stdio.h>
#include <stdlib.h>

// Forward declaration of Human struct
typedef struct _human Human;

// Function prototype
Human* createHuman(int height);
void printall(Human* head);

// Definition of Human struct
struct _human
{
    int height;
    struct _human* bestfriend;
};

int main()
{
    Human *jack, *tom, *jerry, *john;
    jack = createHuman(200);
    tom = createHuman(300);
    jerry = createHuman(400);
    john = createHuman(500);

    // jack is the head node;
    jack->bestfriend = tom;
    tom->bestfriend = jerry;
    printall(jack);
    printf("+++++++++++\n");
    // insert the node
    tom->bestfriend = john;
    john->bestfriend = jerry;
    printall(jack);
    printf("+++++++++++\n");
    // remove node
    tom->bestfriend = jerry;
    free(john);
    printall(jack);

    printf("jack is %d tall\n", jack->height);
    free(jack); // Don't forget to free allocated memory
    return 0;
}

Human* createHuman(int height)
{
    Human* hum;
    hum = (Human*)malloc(sizeof(Human));
    hum->height = height;
    hum->bestfriend = NULL; // Initialize bestfriend pointer to NULL
    return hum;
}

void printall(Human* head)
{
    Human* temp;
    temp = head;
    while(temp != NULL)
    {
        printf("%d\n", temp->height);
        temp = temp->bestfriend;
    }
}