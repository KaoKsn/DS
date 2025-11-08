#include "objects.h"

object_t *get_array()
{
  object_t *obj = malloc(sizeof(object_t));
  if (obj == NULL) {
    fprintf(stderr, "Memory Allocation for the object FAILED!\n");
    return NULL;
  }
// Ensure to initialize with calloc
  return obj;
}

object_t *get_bool()
{
  object_t *obj = malloc(sizeof(object_t));
  if (obj == NULL) {
    fprintf(stderr, "Memory Allocation for the object FAILED!\n");
    return NULL;
  }
  return obj;
}

object_t *get_char()
{
  object_t *obj = malloc(sizeof(object_t));
  if (obj == NULL) {
    fprintf(stderr, "Memory Allocation for the object FAILED!\n");
    return NULL;
  }
  return obj;
}

object_t *get_array()
{
  object_t *obj = malloc(sizeof(object_t));
  if (obj == NULL) {
    fprintf(stderr, "Memory Allocation for the object FAILED!\n");
    return NULL;
  }
  return obj;
}

object_t *get_array()
{
  object_t *obj = malloc(sizeof(object_t));
  if (obj == NULL) {
    fprintf(stderr, "Memory Allocation for the object FAILED!\n");
    return NULL;
  }
  return obj;
}

object_t *get_string()
{
  object_t *obj = malloc(sizeof(object_t));
  if (obj == NULL) {
    fprintf(stderr, "Memory Allocation for the object FAILED!\n");
    return NULL;
  }
  return obj;
}

// Print the object as a string.
void print_obj(object_t *obj)
{
  if (obj == NULL) {
    fprintf(stderr, "NULL object!\n");
    return;
  }

  switch (obj->datatype) {
    case BOOLEAN:
      printf("[BOOLEAN]\n");
      switch (obj->value.v_bool) {
        case 0:
          printf("false\n");
          break;
        case 1:
          printf("true\n");
          break;
      }
      break;
    case CHAR:
      printf("[CHARACTER]\n");
      printf("%c\n", obj->value.v_char);
      break;
    case INT:
      printf("[INTEGER]\n");
      printf("%d\n", obj->value.v_int);
      break;
    case REAL:
      printf("[FLOAT]\n");
      printf("%.4f\n", obj->value.v_float);
      break;
    case STRING:
      printf("[STRING]\n");
      // NOTE: Ensure, NULL can't be passed during creation of the object.
      printf("%s\n", obj->value.v_string);
      printf("len: %d\n", strlen(obj->value.v_string));
      break;
    case ARRAY:
      printf("[ARRAY]\n");
      printf("len: %d\n", obj->value.array.len);
      for (int i = 0; i < obj->value.array.len; i++) {
        printf("\nIndex: %d\n", i);
        print_obj(obj->value.array.arr[i]);
      }
      break;
  }
}

// Free an object.
void free_obj(object_t *obj)
{
  if (obj == NULL) {
    return;
  }
  switch (obj->datatype) {
    case BOOLEAN:
    case CHAR:
    case INT:
    case REAL:
      free(obj);
      break;
    case STRING:
      free(obj->value.v_string);
      free(obj);
      break;
    case ARRAY:
      for (int i = 0; i < obj->value.array.len; i++) {
        free_obj(obj->value.array.arr[i]);
      }
      free(obj->value.array.arr);
      free(obj);
  }
}
