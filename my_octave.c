//Copyright Tudor Brandibur 313CAa 2023-2024
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int **alloc_mat(int n, int m)
{
	int **a = (int **)malloc(n * sizeof(int *));
	if (!a) {
		printf("malloc() failed 1\n");
		return NULL;
	}
	for (int i = 0; i < n; ++i) {
		a[i] = (int *)malloc(m * sizeof(int));
		if (!a[i]) {
			printf("malloc() failed 2\n");
			for (int j = i - 1; j >= 0; --j)
				free(a[j]);
			free(a);
			return NULL;
		}
	}
	return a;
}

void read_matrix(int m, int n, int **a)
{
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			scanf("%d", &a[i][j]);
	}
}

void print_matrix(int m, int n, int **a)
{
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; ++j)
			printf("%d ", a[i][j]);
		printf("\n");
	}
}

void matrix_swap(int ***a, int ***b)
{
	int **aux = *a;
	*a = *b;
	*b = aux;
}

//reallocs the matrix that stores the lines and columns
//of the other matrices
void reall_dim_mat(int nr_mat, int ***dim_mat)
{
	(*dim_mat) = (int **)realloc((*dim_mat), nr_mat * sizeof(int *));
	if (!(*dim_mat)) {
		printf("malloc() failed in reall_dim_mat  1\n");
		return;
	}
	(*dim_mat)[nr_mat - 1] = (int *)malloc(2 * sizeof(int));
	if (!(*dim_mat)[nr_mat - 1]) {
		printf("realloc() failed in reall_dim_mat 2\n");
		return;
	}
	// Initialize the new elements with 0
	(*dim_mat)[nr_mat - 1][0] = 0;
	(*dim_mat)[nr_mat - 1][1] = 0;
}

void resize_mat(int ***a, int ***dim_mat, int id)
{
	int n, m;
	scanf("%d", &n);
	int *lines = (int *)malloc(n * sizeof(int));
	for (int i = 0; i < n; ++i)
		scanf("%d", &lines[i]);
	scanf("%d", &m);
	int *col = (int *)malloc(m * sizeof(int));
	for (int i = 0; i < m; ++i)
		scanf("%d", &col[i]);
	int **tmp = (int **)alloc_mat(n, m);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			tmp[i][j] = (*a)[lines[i]][col[j]];
	matrix_swap(&tmp, &(*a));
	for (int i = 0; i < (*dim_mat)[id][0]; ++i)
		free(tmp[i]);
	free(tmp);
	(*dim_mat)[id][0] = n;
	(*dim_mat)[id][1] = m;
	free(lines);
	free(col);
}

//this function will sort all matrices in increasing order
//based on the sum of the elements
void sort_matrix(int ****mat_arr, int nr_mat, int ***dim_mat)
{
	int *sum = (int *)calloc(nr_mat, sizeof(int));
	for (int i = 0; i < nr_mat; ++i) {
		for (int j = 0; j < (*dim_mat)[i][0]; j++) {
			for (int k = 0; k < (*dim_mat)[i][1]; k++)
				sum[i] += (*mat_arr)[i][j][k] % 10007;
			sum[i] %= 10007;
			if (sum[i] < 0)
				sum[i] += 10007;
		}
	}
	for (int i =  0; i < nr_mat - 1; ++i) {
		for (int j = i + 1; j < nr_mat; ++j) {
			if (sum[i] > sum[j]) {
				int f = sum[i];
				sum[i] = sum[j];
				sum[j] = f;
				matrix_swap(&(*mat_arr)[i], &(*mat_arr)[j]);
				int aux = (*dim_mat)[i][0];
				(*dim_mat)[i][0] = (*dim_mat)[j][0];
				(*dim_mat)[j][0] = aux;
				aux = (*dim_mat)[i][1];
				(*dim_mat)[i][1] = (*dim_mat)[j][1];
				(*dim_mat)[j][1] = aux;
			}
		}
	}
	free(sum);
}

void transpose_matrix(int ****mat_arr, int ***dim_mat, int nr_mat)
{
	int id;
	scanf("%d", &id);
	if (id > nr_mat - 1 || id < 0) {
		printf("No matrix with the given index\n");
		return;
	}
	//allocate space for matrix tmp, the transposed matrix
	int **tmp = alloc_mat((*dim_mat)[id][1], (*dim_mat)[id][0]);
	//transpose matrix id in matrix tmp
	for (int i = 0; i < (*dim_mat)[id][0]; ++i) {
		for (int j = 0; j < (*dim_mat)[id][1]; ++j)
			tmp[j][i] = (*mat_arr)[id][i][j];
	}
	//deallocate id matrix
	for (int i = 0; i < (*dim_mat)[id][0]; ++i)
		free((*mat_arr)[id][i]);
	free((*mat_arr)[id]);
	//swap matrices id and tmp
	matrix_swap(&tmp, &(*mat_arr)[id]);
	int aux = (*dim_mat)[id][0];
	(*dim_mat)[id][0] = (*dim_mat)[id][1];
	(*dim_mat)[id][1] = aux;
}

//multiplies two matrices and stores the result in matrix c
void mp_mat(int n, int m, int p, int **a, int **b, int ***c)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < p; j++) {
			(*c)[i][j] = 0;
			for (int k = 0; k < m; k++)
				(*c)[i][j] += (a[i][k] * b[k][j]) % 10007;
			(*c)[i][j] %= 10007;
			if ((*c)[i][j] < 0)
				(*c)[i][j] += 10007;
		}
	}
}

//checks if two given matrices exist in the matrix vector
int is_valid(int nr_mat, int i1, int i2, int **dim_mat)
{
	if (i1 > nr_mat - 1 || i2 > nr_mat - 1 || i1 < 0 || i2 < 0) {
		printf("No matrix with the given index\n");
		return 0;
	} else if (dim_mat[i1][1] != dim_mat[i2][0]) {
		printf("Cannot perform matrix multiplication\n");
		return 0;
	} else {
		return 1;
	}
}

//allocates space for a new matrix and the result is the
//multiplication of two given matrices
void case_M(int ****mat_arr, int ***dim_mat, int *d, int *nr_mat)
{
	int i1, i2;
	scanf("%d%d", &i1, &i2);
	if (is_valid((*nr_mat), i1, i2, (*dim_mat))) {
		(*nr_mat)++;
		if ((*nr_mat) > (*d)) {
			(*d) *= 2;
			(*mat_arr) = (int ***)realloc((*mat_arr),
			(*d) * sizeof(int **));
			if (!(*mat_arr)) {
				printf("realloc() failed\n");
				return;
			}
		}
		int x = (*nr_mat) - 1;
		reall_dim_mat((*nr_mat), &(*dim_mat));
		(*dim_mat)[x][0] = (*dim_mat)[i1][0];
		(*dim_mat)[x][1] = (*dim_mat)[i2][1];
		(*mat_arr)[x] = alloc_mat((*dim_mat)[i1][0], (*dim_mat)[i2][1]);
		int n = (*dim_mat)[i1][0];
		int m = (*dim_mat)[i1][1];
		int p = (*dim_mat)[i2][1];
		mp_mat(n, m, p, (*mat_arr)[i1], (*mat_arr)[i2], &(*mat_arr)[x]);
	}
}

//multiplies two matrices; result stored in a
void multiply(int ***a, int **b, int n)
{
	int **c = alloc_mat(n, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			c[i][j] = 0;
			for (int k = 0; k < n; k++)
				c[i][j] += ((*a)[i][k] * b[k][j]) % 10007;
			c[i][j] = c[i][j] % 10007;
			if (c[i][j] < 0)
				c[i][j] += 10007;
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j)
			(*a)[i][j] = c[i][j];
	}
	for (int i = 0; i < n; ++i)
		free(c[i]);
	free(c);
}

//raises a matrix to the power p, in logarithmic time complexity
void power(int ***a, int p, int n)
{
	int **pow = alloc_mat(n, n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (i == j)
				pow[i][j] = 1;
			else
				pow[i][j] = 0;
		}
	}
	if (p == 0) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (i == j)
					(*a)[i][j] = 1;
				else
					(*a)[i][j] = 0;
			}
		}
	} else {
		while (p > 0) {
			if (p % 2)
				multiply(&pow, (*a), n);
			multiply(&(*a), (*a), n);
			p /= 2;
		}
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j)
				(*a)[i][j] = pow[i][j];
		}
	}
	for (int i = 0; i < n; ++i)
		free(pow[i]);
	free(pow);
}

//calls power function if the given matrix exists
void case_R(int ****mat_arr, int nr_mat, int ***dim_mat)
{
	int index, p;
	scanf("%d%d", &index, &p);
	if (index > nr_mat - 1 || index < 0) {
		printf("No matrix with the given index\n");
		return;
	} else if (p < 0) {
		printf("Power should be positive\n");
		return;
	}
	if ((*dim_mat)[index][0] != (*dim_mat)[index][1])
		printf("Cannot perform matrix multiplication\n");
	else
		power(&(*mat_arr)[index], p, (*dim_mat)[index][0]);
}

//deallocates a given matrix and reallox the matrix array
//if the number of matrices is lower than dimension / 2
void case_F(int ****mat_arr, int *nr_mat, int *dim, int ***dim_mat)
{
	int id;
	scanf("%d", &id);
	if (id > (*nr_mat) - 1 || id < 0) {
		printf("No matrix with the given index\n");
	} else {
		for (int i = 0; i < (*dim_mat)[id][0]; ++i)
			free((*mat_arr)[id][i]);
		free((*mat_arr)[id]);
		for (int i = id; i < (*nr_mat) - 1; i++) {
			matrix_swap(&(*mat_arr)[i], &(*mat_arr)[i + 1]);
			int aux1 = (*dim_mat)[i][0];
			(*dim_mat)[i][0] = (*dim_mat)[i + 1][0];
			(*dim_mat)[i + 1][0] = aux1;
			int aux2 = (*dim_mat)[i][1];
			(*dim_mat)[i][1] = (*dim_mat)[i + 1][1];
			(*dim_mat)[i + 1][1] = aux2;
		}
		(*nr_mat)--;
		if ((*nr_mat) == (*dim) / 2 && (*nr_mat) > 0) {
			(*dim) /= 2;
			(*mat_arr) = (int ***)realloc((*mat_arr), (*dim) * sizeof(int **));
		}
		free((*dim_mat)[(*nr_mat)]);
	}
}

//allocate nwe space for a matrix, increase the matrix array if needed
// and read the new matrix
void case_L(int *nr_mat, int *dim, int ****mat_arr, int ***dim_mat)
{
	int ok = 0;
	if ((*nr_mat) == 0)
		reall_dim_mat(1, &(*dim_mat));
	(*nr_mat)++;
	if ((*nr_mat) > (*dim)) {
		(*dim) *= 2;
		(*mat_arr) = (int ***)realloc((*mat_arr), (*dim) * sizeof(int **));
		reall_dim_mat((*nr_mat), &(*dim_mat));
		ok = 1;
		if (!(*mat_arr)) {
			printf("realloc() failed\n");
			return;
		}
		if (!(*dim_mat)) {
			printf("reall_dim_mat() failed\n");
			return;
		}
	}
	int m, n;
	scanf("%d%d", &m, &n);
	if ((*nr_mat) > 1 && !ok)
		reall_dim_mat((*nr_mat), &(*dim_mat));
	(*dim_mat)[(*nr_mat) - 1][0] = m;
	(*dim_mat)[(*nr_mat) - 1][1] = n;
	(*mat_arr)[(*nr_mat) - 1] = alloc_mat(m, n);
	read_matrix(m, n, (*mat_arr)[(*nr_mat) - 1]);
}

//sums up tow matrices
void add_mat(int **A, int **B, int ***C, int n)
{
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j) {
			(*C)[i][j] = A[i][j] + B[i][j];
			(*C)[i][j] %= 10007;
			if ((*C)[i][j] < 0)
				(*C)[i][j] += 10007;
		}
}

//subtracts two matrices
void sub_mat(int **A, int **B, int ***C, int n)
{
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j) {
			(*C)[i][j] = A[i][j] - B[i][j];
			(*C)[i][j] %= 10007;
			if ((*C)[i][j] < 0)
				(*C)[i][j] += 10007;
		}
}

//implementation of the Strassen's algorithm
void strassen(int **A, int **B, int ***C, int n)
{
	if (n == 2) {
		int v1 = (A[0][0] + A[1][1]) * (B[0][0] + B[1][1]);
		int v2 = (A[1][0] + A[1][1]) * B[0][0];
		int v3 = A[0][0] * (B[0][1] - B[1][1]);
		int v4 = A[1][1] * (B[1][0] - B[0][0]);
		int v5 = (A[0][0] + A[0][1]) * B[1][1];
		int v6 = (A[1][0] - A[0][0]) * (B[0][0] + B[0][1]);
		int v7 = (A[0][1] - A[1][1]) * (B[1][0] + B[1][1]);
		(*C)[0][0] = v1 + v4 - v5 + v7;
		(*C)[0][1] = v3 + v5;
		(*C)[1][0] = v2 + v4;
		(*C)[1][1] = v1 - v2 + v3 + v6;
	} else {
		int **a1, **a2, **a3, **a4, **b1, **b2, **b3, **b4, **x, **y;
		int m = n / 2;
		a1 = alloc_mat(m, m); a2 = alloc_mat(m, m);
		a3 = alloc_mat(m, m); a4 = alloc_mat(m, m);
		b1 = alloc_mat(m, m); b2 = alloc_mat(m, m);
		b3 = alloc_mat(m, m); b4 = alloc_mat(m, m);
		x = alloc_mat(m, m); y = alloc_mat(m, m);
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < m; ++j) {
				a1[i][j] = A[i][j];
				a2[i][j] = A[i][j + m];
				a3[i][j] = A[i + m][j];
				a4[i][j] = A[i + m][j + m];
				b1[i][j] = B[i][j];
				b2[i][j] = B[i][j + m];
				b3[i][j] = B[i + m][j];
				b4[i][j] = B[i + m][j + m];
			}
		}
		int **M1 = alloc_mat(m, m);
		add_mat(a1, a4, &x, m); add_mat(b1, b4, &y, m);
		strassen(x, y, &M1, m);
		int **M2 = alloc_mat(m, m);
		add_mat(a3, a4, &x, m); strassen(x, b1, &M2, m);
		int **M3 = alloc_mat(m, m);
		sub_mat(b2, b4, &x, m); strassen(a1, x, &M3, m);
		int **M4 = alloc_mat(m, m);
		sub_mat(b3, b1, &y, m); strassen(a4, y, &M4, m);
		int **M5 = alloc_mat(m, m);
		add_mat(a1, a2, &x, m); strassen(x, b4, &M5, m);
		int **M6 = alloc_mat(m, m);
		sub_mat(a3, a1, &x, m); add_mat(b1, b2, &y, m);
		strassen(x, y, &M6, m);
		int **M7 = alloc_mat(m, m);
		sub_mat(a2, a4, &x, m); add_mat(b3, b4, &y, m);
		strassen(x, y, &M7, m);
		int **C1 = alloc_mat(m, m); int **C2 = alloc_mat(m, m);
		int **C3 = alloc_mat(m, m); int **C4 = alloc_mat(m, m);
		sub_mat(M7, M5, &x, m); add_mat(M1, x, &y, m);
		add_mat(M4, y, &C1, m);// C1 = M1 + M4 - M5 + M7
		add_mat(M3, M5, &C2, m);// C2 = M3 + M5
		add_mat(M2, M4, &C3, m);// C3 = M2 + M4
		sub_mat(M1, M2, &x, m); add_mat(M3, M6, &y, m);
		add_mat(x, y, &C4, m);// C4 = M1 - M2 + M3 + M6
		for (int i = 0 ; i < m; ++i)
			for (int j = 0; j < m; ++j) {
				(*C)[i][j] = C1[i][j];
				(*C)[i][j + m] = C2[i][j];
				(*C)[i + m][j] = C3[i][j];
				(*C)[i + m][j + m] = C4[i][j];
			}
		for (int i = 0; i < m; ++i) {
			free(a1[i]); free(a2[i]); free(a3[i]); free(a4[i]); free(b1[i]);
			free(b2[i]); free(b3[i]); free(b4[i]); free(x[i]); free(y[i]);
			free(M1[i]); free(M2[i]); free(M3[i]); free(M4[i]); free(M5[i]);
			free(M6[i]); free(M7[i]); free(C1[i]); free(C2[i]); free(C3[i]);
			free(C4[i]);
		}
		free(a1); free(a2); free(a3); free(a4); free(b1); free(b2);
		free(b3); free(b4); free(x); free(y); free(M1); free(M2);
		free(M3); free(M4); free(M5); free(M6); free(M7); free(C1);
		free(C2); free(C3); free(C4);
	}
}

//calls strassen function if the two matrices i1, i2 are compatible
void case_S(int ****mat_arr, int *nr_mat, int *dim, int ***dim_mat)
{
	int i1, i2;
	scanf("%d%d", &i1, &i2);
	if (is_valid((*nr_mat), i1, i2, (*dim_mat))) {
		(*nr_mat)++;
		if ((*nr_mat) > (*dim)) {
			(*dim) *= 2;
			(*mat_arr) = (int ***)realloc((*mat_arr),
			(*dim) * sizeof(int **));
			if (!(*mat_arr)) {
				printf("realloc() failed\n");
				return;
			}
		}
		reall_dim_mat((*nr_mat), dim_mat);
		(*dim_mat)[(*nr_mat) - 1][0] = (*dim_mat)[i1][0];
		(*dim_mat)[(*nr_mat) - 1][1] = (*dim_mat)[i2][1];
		int n = (*dim_mat)[i1][1];
		int x = (*nr_mat) - 1;
		(*mat_arr)[x] = alloc_mat((*dim_mat)[i1][0], (*dim_mat)[i2][1]);
		strassen((*mat_arr)[i1], (*mat_arr)[i2], &(*mat_arr)[x], n);
	}
}

int main(void)
{
	int nr_mat = 0, dimension = 1;
	int ***mat_arr = (int ***)malloc(1 * sizeof(int **));
	int **dim_mat = NULL;
	char c;
	scanf("%c", &c);
	while (c != 'Q') {
		if (c == 'L') {
			case_L(&nr_mat, &dimension, &mat_arr, &dim_mat);
		} else if (c == 'D') {
			int index;
			scanf("%d", &index);
			if (index > nr_mat - 1 || index < 0)
				printf("No matrix with the given index\n");
			else
				printf("%d %d\n", dim_mat[index][0], dim_mat[index][1]);
		} else if (c == 'P') {
			int i;
			scanf("%d", &i);
			if (i > nr_mat - 1 || i < 0)
				printf("No matrix with the given index\n");
			else
				print_matrix(dim_mat[i][0], dim_mat[i][1], mat_arr[i]);
		} else if (c == 'C') {
			int id;
			scanf("%d", &id);
			if (id > nr_mat - 1 || id < 0)
				printf("No matrix with the given index\n");
			else
				resize_mat(&mat_arr[id], &dim_mat, id);
		} else if (c == 'M') {
			case_M(&mat_arr, &dim_mat, &dimension, &nr_mat);
		} else if (c == 'O') {
			sort_matrix(&mat_arr, nr_mat, &dim_mat);
		} else if (c == 'T') {
			transpose_matrix(&mat_arr, &dim_mat, nr_mat);
		} else if (c == 'R') {
			case_R(&mat_arr, nr_mat, &dim_mat);
		} else if (c == 'F') {
			case_F(&mat_arr, &nr_mat, &dimension, &dim_mat);
		} else if (c == 'S') {
			case_S(&mat_arr, &nr_mat, &dimension, &dim_mat);
		} else if (c >= 'A' && c <= 'Z') {
			printf("Unrecognized command\n");
		}
		scanf("%c", &c);
	}
	//free
	for (int i = 0; i < nr_mat; ++i) {
		for (int j = 0; j < dim_mat[i][0]; ++j)
			free(mat_arr[i][j]);
		free(mat_arr[i]);
	}
	free(mat_arr);
	for (int i = 0; i < nr_mat; ++i)
		free(dim_mat[i]);
	free(dim_mat);
	return 0;
}
