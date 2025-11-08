#include<stdio.h>
#define INVALID_INPUTS -1

typedef struct {
	int rows, columns, values;
}sparse_element;

int get_int();

// int (*b)[c] - pointer that points to array with c elements.
int get_matrix(int r, int c, int (*mat)[c]);

void get_sparse(int t_rows, int t_columns, int mat[][t_columns],int t_values, sparse_element sparse_a[]);

void transpose_sparse(sparse_element sparse_a[], sparse_element transpose_sparse_a[]);

void print_sparse(sparse_element sparse_mat[]);


int main(void)
{
	int r, c;
	printf("Enter the numbers of rows in the matrix: \n");
	r = get_int();
	printf("Enter the numbers of columns in the matrix: \n");
	c = get_int();


	// Get matrix a
	int a[r][c];
	int t_values = get_matrix(r, c, a);

	if (t_values != -1)
	{
		// Print matrix a.
		printf("\nMatrix a: \n");
		for(int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
				printf("%d\t", a[i][j]);
			printf("\n");
		}
	}
	else
	{
		printf("\nInvalid Input. Exiting...\n");
		return INVALID_INPUTS;
	}

	// Convert the matrix to the sparse form.
	sparse_element sparse_a[t_values + 1];
	get_sparse(r, c, a,t_values, sparse_a);
	

	/*
	 * Transpose the sparse matrix using simple transpose.
	 * Time complexity of O(columns * total_non_zero_values).
	 */

	sparse_element transpose_sparse_a[t_values + 1];
	transpose_sparse(sparse_a, transpose_sparse_a);


	// Print both the sparse and the tranpose of the sparse.
	printf("\nMatrix A: \n");
	print_sparse(sparse_a);

	printf("\nSparse of tranpose of matrix A: \n");
	print_sparse(transpose_sparse_a);
	
	return 0;
}

// Basic error handled, integer input.
int get_int()
{
  int value;

  while (true) {
      if (scanf("%d", &value) != 1 || value <= 0) {
          printf("Enter a positive integer!\n");
          int buffer;
          while (buffer = getchar() != '\n');
      } else {
          break;
      }
  }
  return value;
}

int get_matrix(int r, int c, int mat[][c])
{
	int t_values = -1;

	if (r != 0 && c != 0)
	{
		t_values = 0;
		printf("\nEnter the matrix a: \n");
		for(int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				scanf("%d", &mat[i][j]);
				if (mat[i][j])
					t_values ++;
			}
		}
	}
	return t_values;
}

void get_sparse(int r, int c, int (*mat)[c],int t_values, sparse_element sparse_a[])
{
	// Initialize the first row of the sparse matrix.
	sparse_a[0].rows = r; 
	sparse_a[0].columns = c; 
	sparse_a[0].values = t_values; 

	for(int i = 0, k = 1; i < r; i++)
	{
		for(int j = 0; j < c; j++)
		{
			// Populate non-zero values in the sparse matrix.
			if (mat[i][j])
			{
				sparse_a[k].rows = i;
				sparse_a[k].columns = j;
				sparse_a[k].values = mat[i][j];
				k++;
			}
		}
	}
	printf("\n");
}

void transpose_sparse(sparse_element sparse_a[], sparse_element transpose_sparse_a[])
{
	// Populate the first row of the sparse matrix.
	transpose_sparse_a[0].rows = sparse_a[0].columns;
	transpose_sparse_a[0].columns = sparse_a[0].rows;
	transpose_sparse_a[0].values = sparse_a[0].values;

	// Look for the column value in the ascending order in the column section of the sparse matrix.
	for(int i = 0, k = 1; i < sparse_a[0].columns; i++)
	{
		for(int j = 1; j < sparse_a[0].values + 1; j++)
		{
			if (sparse_a[j].columns == i)
			{
				// Change row to column and vice versa.
				transpose_sparse_a[k].rows = i;
				transpose_sparse_a[k].columns = sparse_a[j].rows;
				transpose_sparse_a[k].values = sparse_a[j].values;
				k++;
			}
		}
	}
}

void print_sparse(sparse_element sparse_mat[])
{
	// Print sparse matrices.
	for(int i = 0; i< sparse_mat[0].values + 1; i++)
		printf("%d\t%d\t%d\n", sparse_mat[i].rows, sparse_mat[i].columns, sparse_mat[i].values);
}
