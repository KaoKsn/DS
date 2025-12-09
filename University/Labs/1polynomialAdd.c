// 1. Simple polynomial addition using a single array of structure.
typedef struct Term {
    float coef;
    int expo;
} term_t;

#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#define FAILURE 1

term_t terms[MAX];
int avail = 0;

void attach(float coef, int expo);
int compare(int a, int b);
void padd(int starta, int enda, int startb, int endb);

int main(void)
{
    int n1, n2;
    float ac, bc;
    int ae, be;
    int starta = 0, enda = 0, startb = 0, endb = 0;

    printf("First Polynomial: \n");
    printf("Terms: ");
    scanf("%d", &n1);
    for (int i = 0; i < n1; i++) {
          scanf("%f %d", &ac, &ae);
          attach(ac, ae);
    }
    enda = avail;

    // The second polynomial starts after from end of first polynomial.
    startb = avail;
    printf("Second Polynomial: \n");
    printf("Terms: ");
    scanf("%d", &n2);
    for (int i = 0; i < n2; i++) {
        scanf("%f %d", &bc, &be);
        attach(bc, be);
    }
    endb = avail;

    if (n1 == 0 && n2 == 0)
          return 0;

    int startc = avail;
    padd(starta, enda, startb, endb);
    
    printf("== First ==\n");
    for (int i = starta; i < enda; i++) {
        printf("(%.3f)x^%d + ", terms[i].coef, terms[i].expo);
    }
    printf("\n== Second ==\n");
    for (int i = startb; i < endb; i++) {
        printf("(%.3f)x^%d + ", terms[i].coef, terms[i].expo);
    }
    printf("\n== Added ==\n");
    for (int i = startc; i < avail; i++) {
        printf("(%.3f)x^%d + ", terms[i].coef, terms[i].expo);
    }
    printf("\n");
    return 0;
}

int compare(int a, int b)
{
    if (a > b)
        return 1;
    else if (b > a)
        return -1;
    else
        return 0;
}

void attach(float c, int e)
{
    if (avail >= MAX)
        exit(FAILURE);
    if (c != 0) {
        terms[avail].coef = c;
        terms[avail++].expo = e;
    }
}

void padd(int starta, int enda, int startb, int endb)
{
    while (starta < enda && startb < endb) {
        switch(compare(terms[starta].expo, terms[startb].expo)) {
              case -1:
                  attach(terms[startb].coef, terms[startb].expo);
                  startb++;
                  break;
              case 0:
                  attach(terms[starta].coef + terms[startb].coef, terms[starta].expo);
                  starta++;
                  startb++;
                  break;
              case 1:
                  attach(terms[starta].coef, terms[starta].expo);
                  starta++;
                  break;
        }
    }
    // Add any remaining elements in the polynomials.
    while(starta < enda) {
        attach(terms[starta].coef, terms[starta].expo);
        starta++;
    }
    while(startb < endb) {
        attach(terms[startb].coef, terms[startb].expo);
        startb++;
    }
}
