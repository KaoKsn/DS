#include <stddef.h>

typedef struct Term
{
  float coef;
  int expo;
} term_t;

typedef struct Polynomial
{
  int size;
  term_t *terms;
} polynomial_t;

int get_int();
float get_float(); 
polynomial_t add_polynomial(polynomial_t *, polynomial_t *); 
void read_polynomial(polynomial_t *);
void write_polynomial(polynomial_t *);
void free_polynomials(polynomial_t *);
