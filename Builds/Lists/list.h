typedef enum
{
  chr,
  integer,
  real,
  int_array,
} datatype_t;

typedef union value
{
  char v_char;
  int v_int;
  float v_float;
  int v_int_arr[];
} value_t;

typedef struct data
{
  datatype_t datatype;
  value_t value;
} data_t;

typedef struct list_node
{
  int data;
  struct list_node *next;
} list_node_t;

typedef struct Linked_list
{
  list_node_t *listptr;
  list_node_t *latest;
  int len;
} list_t;

list_t *new_list();
list_t *insert(list_t *, int);
list_t *remove_node(list_t *);
void print_list(list_t *);
void free_list(list_t *);

