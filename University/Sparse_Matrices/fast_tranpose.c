#include<stdio.h>
#define INVALID_INPUTS -1

typedef struct {
	int rows, columns, values;
}sparse_element;


// int (*b)[c] - pointer that points to array with c elements.
int get_matrix(int r, int c, int (*mat)[c]);

void get_sparse(int t_rows, int t_columns, int mat[][t_columns],int t_values, sparse_element sparse_a[]);

void fast_transpose_sparse(sparse_element sparse_a[], sparse_element transpose_sparse_a[]);

void print_sparse(sparse_element sparse_mat[]);


int main(void)
{
	int r, c;
	printf("Enter the numbers of rows in the matrix: \n");
	scanf("%d", &r);
	printf("Enter the numbers of columns in the matrix: \n");
	scanf("%d", &c);


	// Get matrix a
	int a[r][c];
	int t_values = get_matrix(r, c, a);


	// Print matrix a on reading valid inputs.
	if (t_values != -1)
	{
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
		printf("\nInvalid input.Exiting...\n");
		return INVALID_INPUTS;
	}

	// Convert the matrix to the sparse form.
	sparse_element sparse_a[t_values + 1];
	get_sparse(r, c, a,t_values, sparse_a);
	

	/*
	 * Transpose the sparse matrix using fast transpose.
	 * Time Complexity - O(rows + columns)
	 */

	sparse_element transpose_sparse_a[t_values + 1];
	fast_transpose_sparse(sparse_a, transpose_sparse_a);


	// Print both the sparse and the tranpose of the sparse.
	printf("\nMatrix A: \n");
	print_sparse(sparse_a);

	printf("\nSparse of tranpose of matrix A: \n");
	print_sparse(transpose_sparse_a);
	
	return 0;
}

int get_matrix(int r, int c, int mat[][c])
{
	int t_values = -1;
	
	if(r != 0 && c != 0)
	{
		// Initialize to 0 so that you don't miss the last non-zero value.
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

void fast_transpose_sparse(sparse_element sparse_a[], sparse_element transpose_sparse_a[])
{
	int t_values = sparse_a[0].values, t_columns = sparse_a[0].columns, t_rows = sparse_a[0].rows;
	
	// During transpose of a matrix , the columns turn into rows.
	int r_values[t_columns];

	/* The starting position tracks the starting position of every column of the sparse matrix
	 * in ascending order of column values.
	 */

	int starting_pos[t_values + 1];

	// Initialize all total number of non-zero values in the column.
	for(int i = 0; i < t_columns; i++)
		r_values[i] = 0;

	// Update the store total number of non-zero values in each columns.
	for(int i = 1; i < t_values + 1; i++)
		r_values[sparse_a[i].columns]++;

	// Populate the starting_pos matrix.
	starting_pos[0] = 1;
	for(int i = 1; i < t_values + 1; i++)
	{
		starting_pos[i] = starting_pos[i-1] + r_values[i-1];
	}

	// Populate the first row of the sparse of transpose of matrix.
	transpose_sparse_a[0].rows = t_columns;
	transpose_sparse_a[0].columns = t_rows;
	transpose_sparse_a[0].values = t_values;

	// Look for the column value in the ascending order in the column section of the sparse matrix.
	for(int i = 1; i < t_values + 1; i++)
	{
		transpose_sparse_a[starting_pos[sparse_a[i].columns]].rows = sparse_a[i].columns;
		transpose_sparse_a[starting_pos[sparse_a[i].columns]].columns = sparse_a[i].rows;
		transpose_sparse_a[starting_pos[sparse_a[i].columns]].values = sparse_a[i].values;
		starting_pos[sparse_a[i].columns]++;
	}
}

void print_sparse(sparse_element sparse_mat[])
{
	// Print sparse matrices.
	for(int i = 0; i< sparse_mat[0].values + 1; i++)
		printf("%d\t%d\t%d\n", sparse_mat[i].rows, sparse_mat[i].columns, sparse_mat[i].values);
}
