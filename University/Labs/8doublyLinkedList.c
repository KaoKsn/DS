typedef struct Node {
    int val;
    struct Node *next;
    struct Node *prev;
} node_t;

#include <stdio.h>
#include <stdlib.h>

void insert(int);
node_t *delete(int);
void printList();
void freeList();

node_t *list = NULL, *latest = NULL;

int main(void) {
    int choice, value;

    while (1) {
        printf("\n--- LIST MENU ---\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Print\n");
        printf("4. Delete\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insert(value);
                break;
            case 2:
                printf("Key: ");
                scanf("%d", &value);
                list = delete(value);
                if (list == NULL)
                    latest = NULL;
                break;
            case 3:
                printList();
                break;
            case 4:
                printf("Exiting...\n");
                freeList();
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
    if (list == NULL) {
        list = node;
        node->prev = NULL;
    } else {
        latest->next = node;
        node->prev = latest;
    }
    latest = node;
    node->next = NULL;
}

node_t *delete(int key)
{
    if (list == NULL) {
        printf("Empty!\n");
        return NULL;
    }

    node_t dummy;
    dummy.prev = NULL;
    dummy.next = list;

    node_t *ptr = &dummy;
    while (ptr->next != NULL) {
        if (ptr->next->val == key) {
            printf("Element found!\n");
            node_t *tmp = ptr->next;
            ptr->next = ptr->next->next;
            // Need not change prev if it's the first or the last node.
            if (tmp->next)
                 tmp->next->prev = ptr;
            free(tmp);
            return dummy.next;
        }
        ptr = ptr->next;
    }
    printf("Element not found!\n");
    return dummy.next;
}

void printList()
{
    if (list == NULL)
      return;
    printf("== LIST ==\n");
    node_t *ptr = list;
    while(ptr != NULL) {
      printf("%d\t", ptr->val);
      ptr = ptr->next;
    }
    printf("\n");
}

void freeList()
{
    if (list == NULL)
        return;
    node_t *ptr = list;
    while(ptr != NULL) {
      node_t *tmp = ptr;
      ptr = ptr->next;
      free(tmp);
    }
    return;
}
