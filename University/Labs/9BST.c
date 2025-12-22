// 9 - Binary Search Tree.
typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
} node_t;

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool insert(int value);
void inorder(node_t *);
void preorder(node_t *);
void postorder(node_t *);
void free_tree(node_t *);

node_t *tree = NULL;

int main() {
    int n = 0;
    printf("Number of nodes: ");
    scanf("%d", &n);

    printf("Enter values: \n");
    for (int i = 0, val = 0; i < n; i++) {
        scanf("%d", &val);
        insert(val);
    }

    int choice, value;
    while (1) {
        printf("\n--- BST MENU ---\n");
        printf("1. InOrder\n");
        printf("2. PreOrder\n");
        printf("3. PostOrder\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                inorder(tree);
                break;
            case 2:
                preorder(tree);
                break;
            case 3:
                postorder(tree);
                break;
            case 4:
                printf("Exiting...\n");
                free_tree(tree);
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

bool insert(int val)
{
    node_t *node = malloc(sizeof(node_t));
    if (node == NULL)
        return false;
    node->value = val;
    node->left = node->right = NULL;
    // If its the root.
    if (tree == NULL)
        tree = node;
    else {
        node_t *ptr = tree;
        while (1) {
            // If val > the node value then move to the right subtree.
            if (ptr->value > val) {
                // If the left child is empty, insert.
                if (ptr->left == NULL) {
                    ptr->left = node;
                    break;
                }
                // Move on.
                else
                    ptr = ptr->left;
            }
            else if (ptr->value < val) {
                if (ptr->right == NULL) {
                    ptr->right = node;
                    break;
                }
                else
                    ptr = ptr->right;
            }
            else {
                printf("Unqiue Keys only allowed!");
                return false;
            }
        }
    }
    return true;
}

void inorder(node_t *tree)
{
    if (tree == NULL)
        return;
    inorder(tree->left);
    printf("%d\t", tree->value);
    inorder(tree->right);
}
void preorder(node_t *tree)
{
    if (tree == NULL)
        return;
    printf("%d\t", tree->value);
    preorder(tree->left);
    preorder(tree->right);
}
void postorder(node_t *tree)
{
    if (tree == NULL)
        return;
    postorder(tree->left);
    postorder(tree->right);
    printf("%d\t", tree->value);
}
void free_tree(node_t *tree)
{
    if (tree == NULL)
        return;
    // Iterative postorder.
    free_tree(tree->left);
    free_tree(tree->right);
    free(tree);
    return;
}
