#include <stdio.h>   // Standard Input/Output header for printf, scanf, etc.
#include <stdbool.h> // To use boolean logic
#include <stdlib.h>  // Standard library header for exit() and other utility functions

#define SIZE 24       // Define SIZE for length of the array
#define nCols 3       // Define the number of columns for 2D arrays
#define nRows 8       // Define the number of rows for 2D arrays

// Function prototypes
void print_array(int array[], int length);                                                         // Prints a 1D array
void print_matrix(int mat[][nCols], int rows);                                                     // Prints a 2D matrix
bool is_valid_index(int length, int pos);                                                         // Checks if a position is valid in the array
void remove_element(int arr[], int length, int pos);                                              // Removes an element at a given position from the array
void insert_element(int arr[], int length, int pos, int value);                                   // Inserts a value at a specific position in the array
void reshape(const int arr[], int length, int nrows, int ncols, int arr2d[nRows][nCols]);         // Reshapes a 1D array into a 2D array
void transpose_matrix(int nrows, int ncols, const int mat[nrows][ncols], int mat_transp[nCols][nRows]); // Transposes a 2D matrix
bool has_duplicates(int arr[], int length);                                                       // Checks if the array contains duplicates
void print_transposed_matrix(int arr[][8], int rows);                                             // Prints a transposed 2D matrix

int main() {
    int arr[SIZE];                  // Declare a 1D array of size SIZE
    int arr2d[nRows][nCols];        // Declare a 2D array with nRows and nCols

    // Initialize the array with values from 1 to SIZE
    printf("Initializing the array arr with values: 1, 2, 3, ... 24\n");
    for (int i = 0; i < SIZE; i++) {
        arr[i] = i + 1;  // Assign sequential values to the array elements
    }
    print_array(arr, SIZE);
    printf("\n");

    // Remove the element at position 7
    printf("Removing the element at position 7 from the array arr\n");
    remove_element(arr, SIZE, 7);
    print_array(arr, SIZE);
    printf("\n");

    // Insert the value 25 at position 7
    printf("Inserting the value 25 at position 7 in the array arr\n");
    insert_element(arr, SIZE, 7, 25);
    print_array(arr, SIZE);
    printf("\n");

    // Reshape the array into a 2D array
    printf("Reshaping the array arr into a 2D array arr2d with 8 rows and 3 columns\n");
    reshape(arr, SIZE, nRows, nCols, arr2d);
    print_matrix(arr2d, nRows);
    printf("\n");

    // Transpose the 2D array into another array
    printf("Transposing the 2D array arr2d into a new 2D array arr2d_transp with 3 rows and 8 columns\n");
    int arr2d_transp[nCols][nRows];  // Declare a transposed array
    transpose_matrix(nRows, nCols, arr2d, arr2d_transp);
    print_transposed_matrix(arr2d_transp, nCols);
    printf("\n");

    // Check for duplicates in the array
    printf("Checking if the array arr has any duplicate elements\n");
    if (has_duplicates(arr, SIZE)) {
        printf("The array has duplicate elements\n\n");
    } else {
        printf("The array does not have duplicate elements\n\n");
    }

    // Test with a new array containing duplicates
    printf("Test 2\n");
    int arr2[SIZE] = {1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 14, 15, 16, 17, 18, 19, 20, 21, 22};
    if (has_duplicates(arr2, SIZE)) {
        printf("The array has duplicate elements\n\n");
    } else {
        printf("The array does not have duplicate elements\n\n");
    }

    return 0;
}

// Function to print a 1D array
void print_array(int array[], int length) {
    for (int i = 0; i < length; i++) {
        printf("array[%d] = %d\n", i, array[i]);
    }
}

// Function to print a 2D matrix
void print_matrix(int mat[][nCols], int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < nCols; j++) {
            printf("mat[%d][%d] = %d\n", i, j, mat[i][j]);
        }
        printf("\n");
    }
}

// Function to check if an index is valid in the array
bool is_valid_index(int length, int pos) {
    return (pos >= 0 && pos < length);
}

// Function to remove an element from the array at a given index
void remove_element(int arr[], int length, int pos) {
    if (is_valid_index(length, pos)) {
        for (int i = pos; i < length - 1; i++) {
            arr[i] = arr[i + 1];
        }
    } else {
        printf("Invalid index\n");
        exit(1);
    }
}

// Function to insert a value at a given index in the array
void insert_element(int arr[], int length, int pos, int value) {
    if (is_valid_index(length, pos)) {
        for (int i = length - 1; i > pos; i--) {
            arr[i] = arr[i - 1];
        }
        arr[pos] = value;
    } else {
        printf("Invalid index\n");
        exit(1);
    }
}

// Function to reshape a 1D array into a 2D array
void reshape(const int arr[], int length, int nrows, int ncols, int arr2d[nRows][nCols]) {
    if (length != nrows * ncols) {
        printf("Error: The length of arr is not equal to rows * cols\n");
        exit(1);
    }
    int k = 0;
    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {
            arr2d[i][j] = arr[k++];
        }
    }
}

// Function to transpose a 2D matrix
void transpose_matrix(int nrows, int ncols, const int mat[nrows][ncols], int mat_transp[nCols][nRows]) {
    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {
            mat_transp[j][i] = mat[i][j];
        }
    }
}

// Function to check for duplicates in the array
bool has_duplicates(int arr[], int length) {
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            if (arr[i] == arr[j]) {
                return true;
            }
        }
    }
    return false;
}

// Function to print a transposed 2D matrix
void print_transposed_matrix(int arr[][8], int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < 8; j++) {
            printf("mat[%d][%d] = %d\n", i, j, arr[i][j]);
        }
        printf("\n");
    }
}
