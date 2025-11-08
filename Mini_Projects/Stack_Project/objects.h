#pragma once

#include <stddef.h>

typedef enum Datatype
{
  ARRAY,
  CHAR,
  FLOAT,
  INT,
  STRING,
} datatype_t;

typedef union Value
{
  float v_float;
  int v_int;
  char v_char;
  char *v_string;
  void *arr;
} value_t;

typedef struct Object
{
  datatype_t datatype;
  value_t value;
} object_t;

object_t *get_array();
object_t *get_char();
object_t *get_float();
object_t *get_int();
object_t *get_string();
void *print_obj(object_t *obj); 
void free_obj(object_t *obj);
