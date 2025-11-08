// A simple cricular singly linked list.

#include "list.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int get_int();

int main(void)
{
  list_t *list = new_list();
  while (true)
  {
    printf("List Operations: \n");
    printf("1. Insert\n");
    printf("2. Remove\n");
    printf("3. Print List\n");
    printf("4. Exit\n\n");

    int op_code = get_int();
    switch (op_code)
    {
      case 1:
        printf("Number: ");
        int data = get_int();
        list = insert(list, data);
        break;
      case 2:
        list = remove_node(list);
        break;
      case 3:
        print_list(list);
        break;
      case 4:
        free_list(list);
        return 0;
      default:
        printf("Select one from the index!\n");
    }
    printf("\n");
  }
}

// Create a new list.
list_t *new_list()
{
  list_t *list = malloc(sizeof(list_t));
  if (list == NULL)
  {
    fprintf(stderr, "Memory Allocation Failed!\n");
    exit(-1);
  }

  list->len = 0;
  list->listptr = NULL;
  list->latest = NULL;
  return list;
}

// Insert an element into the list.
list_t *insert(list_t *list, int data)
{
  if (list == NULL)
  {
    fprintf(stderr, "List Doesn't Exists!\n");
    return NULL;
  }

  list_node_t *node = malloc(sizeof(list_node_t));
  if (node == NULL)
  {
    fprintf(stderr, "Memory Allocation Failed!\n");
    return list;
  }

  node->data = data;
  if (list->listptr == NULL)
  {
    list->listptr = node;
    list->latest = node;
    node->next = node;
  }
  else
  {
    list->latest->next = node;
    list->latest = node;
    node->next = list->listptr;
  }
  list->len++;
  return list;
}

// Remove an element from the list.
list_t *remove_node(list_t *list)
{
  if (list == NULL)
  {
    fprintf(stderr, "List doesn't exists?!\n");
    return NULL;
  }
  if (list->listptr == NULL)
  {
    fprintf(stderr, "List Empty!\n");
    return list;
  }

  printf("NOTE: List Index Starts from 0! Current length: %d\n", list->len);
  printf("Index: ");
  int index = get_int();

  if (index >= list->len || index < 0)
  {
    fprintf(stderr, "Index out of bounds!\n");
    // Return the original list.
    return list;
  }
  
  // Removing the first node.
  if (index == 0)
  { 
    // Removing the first element when only a single element exists in the list.
    if (list->len == 1)
    {
      // Free the node.
      free(list->listptr);
      // Update the starting point of the list.
      list->listptr = NULL;
      list->latest = NULL;
    }
    else
    {
      // Update latest node to point to the second node.
      list->latest->next = list->listptr->next;
      // Free the current starting node.
      free(list->listptr);
      // Update the starting point of the list.
      list->listptr = list->latest->next;
    }
    list->len--;
    return list;
  }
  
  // Removing node at a non-zero index. 
  list_node_t *ptr = list->listptr; 
  int i = 0;
  do
  {
    // Removing the last node.
    if (ptr->next->next == list->listptr && index == list->len - 1)
    {
      // ptr here is the last second node.
      ptr->next = list->listptr;
      free(list->latest);
      list->latest = ptr;
      break;
    }
    
    else if ((i + 1) == index)
    {
      list_node_t *tmp = ptr->next;
      // Remove the middle element link.
      ptr->next = ptr->next->next; 
      // Free the middle element.
      free(tmp);
      break;
    }
    ptr = ptr->next;
    i++;
  } while (ptr != list->listptr);

  list->len--;
  return list;
}

void print_list(list_t *list)
{
  if (list == NULL || list->listptr == NULL)
  {
    printf("Empty!\n");
    return;
  }
  printf("===== List =====\n");
  list_node_t *tmp = list->listptr;
  do
  {
    printf("%d\n", tmp->data);
    tmp = tmp->next;
  } while (tmp != list->listptr);
  return;
}

// Free the list.
void free_list(list_t *list)
{
  if (list == NULL || list->listptr == NULL)
  {
    free(list);
    return;
  }

  list_node_t *tmp = list->listptr;
  // Remove circularity.
  list->latest->next = NULL;

  while (tmp != NULL)
  {
    tmp = list->listptr->next;
    free(list->listptr);
    list->listptr = tmp;
  }
  free(list);
  return;
}

// Get an integer.
int get_int()
{
  int integer;
  while (true)
  {
    if (scanf("%d", &integer) == 1)
    {
      break;
    }
    else
    {
      printf("Enter a valid integer!\n");
      int buff;
      // Consume the input buffer.
      while (buff = getchar() != '\n' && buff != EOF);
    }
  }
  return integer;
}
