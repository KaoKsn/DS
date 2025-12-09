// 7. A queue implementation using linked lists.
typedef struct Node {
  int val;
  struct Node *next;
} node_t;

#include <stdio.h>
#include <stdlib.h>
#define FAILURE 1

void insert(int value);
int delete();
void printQ();
void freeQ();

node_t *q = NULL, *latest = NULL;

int main() {
    int choice, value;

    while (1) {
        printf("\n--- STACK MENU ---\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Print\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value for insertion: ");
                scanf("%d", &value);
                insert(value);
                break;
            case 2:
                delete();
                break;
            case 3:
                printQ();
                break;
            case 4:
                printf("Exiting...\n");
                freeQ();
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

void insert(int value)
{
    node_t *node = malloc(sizeof(node_t));
    if (node == NULL)
        return;
    node->val = value;
    node->next = NULL;
    if (q == NULL)
        q = node;
    else
        latest->next = node;
    latest = node;
    return;
}

int delete()
{
    if (q == NULL) {
        printf("Queue Empty!\n");
        return FAILURE;
    }
    // Deletion from the front end.
    int returnVal = q->val;
    node_t *tmp = q;
    q = q->next;
    // If the queue empties.
    if (q == NULL)
        latest = NULL;
    free(tmp);
    printf("%d\n", returnVal);
    return returnVal;
}

void printQ()
{
    if (q == NULL)
        return;
    node_t *ptr = q;
    printf("==== Queue ====\n");
    printf("front --->\t");
    while (ptr != NULL) {
        printf("%d\t", ptr->val);
        ptr = ptr->next;
    }
    printf("<--- rear\n");
    return;
}

void freeQ()
{
    if (q == NULL)
        return;
    node_t *ptr = q;
    while (ptr != NULL) {
        node_t *tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }
    return;
}
