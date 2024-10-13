<small>Copyright Tudor Brandibur 2023-2024</small>


# Matrix Calculator

## Functionality

The program has multiple functionalities such as: storing, resizing, multiplying,
transposing, power raising and sorting matrices. It also presents a personal 
implementation of Volker Strassen's algorithm for matrix multiplication.

### Case L

If c == 'L', the function case_L is called. In this function,
the program recives a new matrix, which has to be stored in ***mat_arr.
First the counter (nr_mat) increses by 1. Then, if there are more matrices
than the dimension of the matrix array, the array is reallocated with a 
dimension double its previous one. When there is enough space in mat_arr, 
the dimensions of the new matrix are read, the matrix dim_mat is reallocated
with one more line and the dimensions are stored in it and the new matrix is
allocated using the function "alloc_mat" and read "read_matrix".

### Case D

If c == 'D', the index of a matrix is read, and if it coresponds to 
a matrix stored in mat_arr, its dimensions are printed on the screen.

### Case P

If c == 'P', the index of a matrix is read, and if it coresponds to 
a matrix stored in mat_arr, said matrix if printed using the function 
"print_matrix".

### Case D
If c == 'C', the index of a matrix is read, and if it coresponds to a 
matrix stored in mat_arr, the function "resize_mat" is called. This function 
takes a given matrix, then it reads two numbers n, m which are the number of 
lines and columns which the final matrix will have. It then allocates two 
arrays sizes n and m, and reads and stores the lines and columns given in those
arrays. Using a temporary matrix (**tmp), size n x m, the new resized matrix is
build and then copied in the initial matrix using the function "matrix_swap". 
Tmp is then deallocated and the dimensions of the resized matrix memorized in 
dim_mat overwriting the old ones.

### Case M
If c == 'M', the function case_M is called. This function reads the 
indexes of two matrices and checks if they are valid using the function
"is_valid" (the matrices have to exist in mat_arr and their dimensions 
need to match col_mat1 = lines_mat2). Then the program checks if there 
is enough space in mat_arr for a new matrix, as in Case L, and resizes 
the mat_arr if needed. The dimensions of the new matrix are stored in 
dim_mat and the two matrices are multiplied using the function "mp_mat".

### Case O
If c == 'O', the function "sort_matrix" is called. This function allocates
an array (*sum) in which the sum of every matrix in mat_arr is stored. Then,
while sorting the array sum in increasing order, it swaps the matrices, 
using the function "matrix_swap", and their dimensions stored in dim_mat.

### Case T
If c == 'T', the  function "transpose_matrix" is called. This function
reads an index and, if the matrix exists, a temporary matrix is allocated 
(**tmp) and the transpose of the given matrix is stored in tmp. Then the 
two matrices are swapped using "matrix_swap" and the matrix tmp is freed.

### Case R
If c == 'R', the function "case_R" is called. This function checks
if a given matrix exists and if the power given is pozitive, then calls
the function "power". In "power", a matrix pow is initialized as In, 
matching the dimensions of the given matrix. It then raises the given 
matrix at the power provided, using a logarithmic time complexity, 
and the result, memorized in the matrix pow, is copied in the given matrix.

### Case F
If c == 'F', the function "case_F" is called. This function check to 
see if a given matrix is in mat_arr and frees it. After that, it moves all
the matrices, starting from the given matrix, one position to the left, 
using the function "matrix_swap". If the number of matrices is lower then 
half of the dimension of mat_arr, mat_arr is reallocated with a dimension
equal to dimension / 2.

### Case S
If c == 'S', the function "case_S" is called. This function checks 
if two given matrices exist and are compatible, and if they are, it 
allocates space for a new matrix size dim_mat[i1][0] x dim_mat[id1][0],
and calls the function "strassen". The function "strassen" is a recursive
implementation of Volker Strassen's algorithm for matrix multiplication.

### Case Q
If c == 'Q', the program ends and all the memory space is freed.




