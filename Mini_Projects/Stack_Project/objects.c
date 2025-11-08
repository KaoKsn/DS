#include "objects.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

object_t *get_array(int capacity)
{
    object_t *obj = malloc(sizeof(object_t));
    if (obj == NULL) {
        fprintf(stderr, "Memory Allocation for the object FAILED!\n");
        return NULL;
    }
    
    obj->value.array.arr = calloc(capacity, sizeof(object_t *));
    if (obj->value.array.arr == NULL) {
        fprintf(stderr, "Failed Initializing an array of the requested size!\n");
        free(obj);
        return NULL;
    }
    // Initializing the array.
    obj->datatype = ARRAY;
    obj->value.array.capacity = capacity;
    obj->value.array.len = 0;
    return obj;
}

object_t *get_bool(bool value)
{
    object_t *obj = malloc(sizeof(object_t));
    if (obj == NULL) {
        fprintf(stderr, "Memory Allocation for the object FAILED!\n");
        return NULL;
    }
    obj->datatype = BOOLEAN;
    obj->value.v_bool = value;
    return obj;
}

object_t *get_char(char value)
{
    object_t *obj = malloc(sizeof(object_t));
    if (obj == NULL) {
        fprintf(stderr, "Memory Allocation for the object FAILED!\n");
        return NULL;
    }
    obj->datatype = CHARACTER;
    obj->value.v_char = value;
    return obj;
}

object_t *get_float(float value)
{
    object_t *obj = malloc(sizeof(object_t));
    if (obj == NULL) {
        fprintf(stderr, "Memory Allocation for the object FAILED!\n");
        return NULL;
    }
    obj->datatype = REAL;
    obj->value.v_float = value;
    return obj;
}

object_t *get_int(int value)
{
    object_t *obj = malloc(sizeof(object_t));
    if (obj == NULL) {
        fprintf(stderr, "Memory Allocation for the object FAILED!\n");
        return NULL;
    }
    obj->datatype = INTEGER;
    obj->value.v_int = value;
    return obj;
}

object_t *get_string(char *str)
{
    object_t *obj = malloc(sizeof(object_t));
    if (obj == NULL) {
        fprintf(stderr, "Memory Allocation for the object FAILED!\n");
        return NULL;
    } else if (str == NULL) {
          fprintf(stderr, "Pushing NULL as char* dectected!\nAborting object creation...");
          free(obj);
          return NULL;     
    }
    int len_str = strlen(str);
    char *string = calloc(len_str + 1, sizeof(char));
    if (string == NULL) {
        fprintf(stderr, "Mem Allocation for string failed!\n");
        free(obj);
        return NULL;
    }
    strncpy(string, str, len_str);
    obj->datatype = STRING;
    obj->value.v_string = string;
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
        case CHARACTER:
            printf("[CHARACTER]\n");
            printf("%c\n", obj->value.v_char);
            break;
        case INTEGER:
            printf("[INTEGER]\n");
            printf("%d\n", obj->value.v_int);
            break;
        case REAL:
            printf("[FLOAT]\n");
            printf("%.4f\n", obj->value.v_float);
            break;
        case STRING:
            printf("[STRING]\n");
            printf("%s\n", obj->value.v_string);
            printf("len: %d\n", strlen(obj->value.v_string));
            break;
        case ARRAY:
            printf("[ARRAY]\n");
            printf("capacity: %d\n", obj->value.array.capacity);
            printf("len: %d\n", obj->value.array.len);
            for (int i = 0; i < obj->value.array.len; i++) {
                printf("\nIndex: %d\n", i);
                print_obj(obj->value.array.arr[i]);
            }
            break;
        default:
            fprintf(stderr, "Invalid Object!\n");
    }
}

// Free an object.
/** Freeing an array recursively frees all its objects. **/
void free_obj(object_t *obj)
{
    if (obj == NULL) {
        return;
    }
    switch (obj->datatype) {
        case BOOLEAN:
        case CHARACTER:
        case INTEGER:
        case REAL:
            free(obj);
            break;
        case STRING:
            free(obj->value.v_string);
            free(obj);
            break;
        case ARRAY:
            for (int i = 0; i < obj->value.array.capacity; i++) {
                // arr was calloc'd.
                free_obj(obj->value.array.arr[i]);
            }
            free(obj->value.array.arr);
            free(obj);
            break;
        default:
            fprintf(stderr, "Can't free an invalid oject!\n");
    }
    // Essential,
    // Avoid problems dereferencing/freeing dangling pointers in the array. 
    obj == NULL;
}

// Object len, only defined for strings and arrays.
int len(object_t *obj)
{
    if (obj == NULL || obj->datatype != ARRAY || obj->datatype != STRING) {
        return -1;
    }
    if (obj->datatype == STRING) {
        return strlen(obj->value.v_string);
    }
    // If array, returned the current number of elements in the array.
    return obj->value.array.len;
}
