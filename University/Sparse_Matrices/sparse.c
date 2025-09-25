#include<stdio.h>

typedef struct {
	int rows, columns, values;
}sparse_element;


// int (*b)[c] - pointer that points to array with c elements.
int get_matrix(int r, int c, int (*mat)[c]);

void get_sparse(int t_rows, int t_columns, int mat[][t_columns],int t_values, sparse_element sparse_a[]);

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

	// Print matrix a.
	printf("\nMatrix a: \n");
	for(int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
			printf("%d\t", a[i][j]);
		printf("\n");
	}

	// Convert the matrix to the sparse form.
	sparse_element sparse_a[t_values + 1];
	get_sparse(r, c, a,t_values, sparse_a);
	

	// Print the sparse.
	printf("\nMatrix A: \n");
	print_sparse(sparse_a);

	return 0;
}

int get_matrix(int r, int c, int mat[][c])
{
	int t_values = 0;
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

void print_sparse(sparse_element sparse_mat[])
{
	// Print sparse matrices.
	for(int i = 0; i< sparse_mat[0].values + 1; i++)
		printf("%d\t%d\t%d\n", sparse_mat[i].rows, sparse_mat[i].columns, sparse_mat[i].values);
}
