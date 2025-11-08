// A simple program to add two polynomials.
#include "polynomial_add.h"

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  // Static initialization of two polynomials.
  polynomial_t polynomials[3];

  printf("First polynomial: \n");
  read_polynomial(&polynomials[0]);

  printf("\nSecond polynomial: \n");
  read_polynomial(&polynomials[1]);

  // Add both the polynomials.
  polynomials[2] = add_polynomial(&polynomials[0], &polynomials[1]);

  // Print the polynomials.
  for (int i = 0; i < 3; i++)
  {
    printf("==== Polynomial %i ====\n", i + 1);
    write_polynomial(&polynomials[i]);
  }

  free_polynomials(polynomials);
}

void read_polynomial(polynomial_t *poly)
{
  do
  {
    printf("Enter the number of terms in the polynomial: ");
    poly->size = get_int();
  } while (poly->size > 25 || poly->size < 0);

  poly->terms = malloc((poly->size) * sizeof(term_t));
  if (poly->terms == NULL)
  {
    fprintf(stderr, "Memory Allocation Failed!\n");
    exit(-1);
  }

  printf("Enter the polynomial: \n");
  for (int i = 0; i < poly->size; i++)
  {
    printf("Coefficient: ");
    poly->terms[i].coef = get_float();
    printf("Exponent: ");
    while (true)
    {
      poly->terms[i].expo = get_int();
      if (poly->terms[i].expo < 0) 
      {
        printf("Exponents for polynomials are whole numbers!\n");
        continue;
      }
      break;
    }
  }
}

polynomial_t add_polynomial(polynomial_t *p1, polynomial_t *p2)
{
  polynomial_t added_p;
  added_p.size = 0;
  added_p.terms = malloc(sizeof(term_t) * (p1->size + p2->size));

  int index = 0;

  if (p1->size <= p2->size)
  {
    for (int i = 0, j = 0; i < p1->size; i++, j++)
    {
      if (p1->terms[i].expo == p2->terms[j].expo)
      {
        added_p.terms[index].coef = p1->terms[i].coef + p2->terms[i].coef;
        added_p.terms[index++].expo = p1->terms[i].expo;
        added_p.size++;
      }
      else
      {
        added_p.terms[index].coef = p1->terms[i].coef;
        added_p.terms[index++].expo = p1->terms[i].expo;

        added_p.terms[index].coef = p2->terms[i].coef;
        added_p.terms[index++].expo = p2->terms[i].expo;
        added_p.size += 2;
      }
    }
    // Add the extra terms as is.
    for (int i = p1->size; i < p2->size; i++)
    {
      added_p.terms[index].coef = p2->terms[i].coef;
      added_p.terms[index++].expo = p2->terms[i].expo;
      added_p.size++;
    }
  }
  else
  {
    for (int i = 0, j = 0; i < p2->size; i++, j++)
    {
      if (p1->terms[i].expo == p2->terms[j].expo)
      {
        added_p.terms[index].coef = p1->terms[i].coef + p2->terms[i].coef;
        added_p.terms[index++].expo = p1->terms[i].expo;
        added_p.size++;
      }
      else
      {
        added_p.terms[index].coef = p1->terms[i].coef;
        added_p.terms[index++].expo = p1->terms[i].expo;

        added_p.terms[index].coef = p2->terms[i].coef;
        added_p.terms[index++].expo = p2->terms[i].expo;
        added_p.size += 2;
      }
    }
    // Add the extra terms as is.
    for (int i = p2->size; i < p1->size; i++)
    {
      added_p.terms[index].coef = p1->terms[i].coef;
      added_p.terms[index++].expo = p1->terms[i].expo;
      added_p.size++;
    }
  }
  return added_p;
}

// Print the polynomial.
void write_polynomial(polynomial_t *poly)
{
  for (int i = 0; i < poly->size; i++)
  {
    // Ignore terms with 0 as coefficient.
    if (poly->terms[i].coef == 0)
    {
      continue;
    }
    else if (poly->terms[i].coef < 0)
    {
      printf("- %.3f * x ^ %d  ", -1 * (poly->terms[i].coef), poly->terms[i].expo);
    }
    else
    {
      printf("+ %.3f * x ^ %d  ", poly->terms[i].coef, poly->terms[i].expo);
    }
  }
  printf("\n\n");
}

// Free memory.
void free_polynomials(polynomial_t *poly)
{
  for (int i = 0; i < 3; i++)
  {
    free(poly[i].terms);
  }
}

// Get a valid integer input.
int get_int()
{
  int n;
  while (true)
  {
    if (scanf("%d", &n) == 1)
    {
      break;
    }
    int buffer = 0;
    printf("Enter a valid integer!\n");
    while (buffer = getchar() != '\n' && buffer != EOF);
  }
  return n;
}

// Get a valid floating point value input.
float get_float()
{
  float n;
  while (true)
  {
    if (scanf("%f", &n) == 1)
    {
      break;
    }
    float buffer = 0.0;
    printf("Enter a valid floating point value!\n");
    while (buffer = getchar() != '\n' && buffer != EOF);
  }
  return n;
}


