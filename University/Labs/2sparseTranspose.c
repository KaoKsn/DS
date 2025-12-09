#include <stdio.h>
#define FAILURE 1

typedef struct SparseElement {
    int r, c, val;
} sparse_element_t;

void toSparse(int r, int c, int tvalues, int mat[][c], sparse_element_t *sparse);
void simpleTranspose(sparse_element_t *sparse, sparse_element_t *);
void fastTranspose(sparse_element_t *sparse, sparse_element_t *);
void printSparse(sparse_element_t *sparse);

int main(void)
{
    int r,c, tvalues = 0;
    printf("Rows: ");
    scanf("%d", &r);
    printf("Columns: ");
    scanf("%d", &c);

    if (r == 0 && c == 0)
        return FAILURE;

    int mat[r][c];
    printf("Enter the matrix: \n");
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &mat[i][j]);
            if (mat[i][j] != 0)
                tvalues++;
        }
    }
    sparse_element_t sparse[tvalues + 1];
    // Conversion to sparse.
    toSparse(r, c, tvalues, mat, sparse);

    sparse_element_t stranspose[tvalues + 1];
    simpleTranspose(sparse, stranspose);

    sparse_element_t ftranspose[tvalues + 1];
    simpleTranspose(sparse, ftranspose);

    printf("\n== Matrix ==\n");
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            printf("%d\t", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n== Sparse ==\n");
    printSparse(sparse);

    printf("\n== Simple Transpose ==\n");
    printSparse(stranspose);

    printf("\n== Fast Tranpose ==\n");
    printSparse(ftranspose);
    return 0;
}

void toSparse(int r, int c, int tvalues, int mat[][c], sparse_element_t *sparse)
{
    // Initialize the sparse matrix.
    sparse[0].r = r;
    sparse[0].c = c;
    sparse[0].val = tvalues;

    int index = 1;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            int value = mat[i][j];
            if (value) {
                sparse[index].r = i;
                sparse[index].c = j;
                sparse[index++].val = value;
            }
        }
    }
    return;
}

void simpleTranspose(sparse_element_t *sparse, sparse_element_t *stranspose)
{
    int tvalues = sparse[0].val;
    stranspose[0].r = sparse[0].c;
    stranspose[0].c = sparse[0].r;
    stranspose[0].val = tvalues;

    int index = 1;
    // For every col value.
    for (int i = 0; i < sparse[0].c; i++) {
        for (int j = 1; j < tvalues + 1; j++) {
            if (sparse[j].c == i) {
                stranspose[index].r = i;
                stranspose[index].c = sparse[j].r;
                stranspose[index++].val = sparse[j].val;
            } 
        }
    }
    return;
}

void fastTranspose(sparse_element_t *sparse, sparse_element_t *ftranspose)
{
    int tvalues = sparse[0].val, col = sparse[0].c;
    ftranspose[0].r = sparse[0].c;
    ftranspose[0].c = sparse[0].r;
    ftranspose[0].val = sparse[0].val;

    int index = 1;

    int rmat[col];
    for (int i = 0; i < col; i++)
        rmat[i] = 0;
    // Total number of values in the respective columns.
    for (int i = 1; i < tvalues + 1; i++) {
        rmat[sparse[i].c]++;
    }
    // Starting points.
    int start[col];
    start[0] = 1;
    for (int i = 1; i < col; i++)
        start[i] = start[i-1] + rmat[i - 1];

    for (int i = 1; i < tvalues + 1; i++) {
        ftranspose[start[sparse[i].c]].r = sparse[i].c;
        ftranspose[start[sparse[i].c]].c = sparse[i].r;
        ftranspose[start[sparse[i].c]++].val = sparse[i].val;
    }
    return;
}

void printSparse(sparse_element_t *sparse)
{
    // Print sparse matrices.
    for(int i = 0; i< sparse[0].val + 1; i++)
    printf("%d\t%d\t%d\n", sparse[i].r, sparse[i].c, sparse[i].val);
    return;
}
