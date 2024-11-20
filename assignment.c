#include <stdio.h> // for input and output operations
#include <fcntl.h> // file control operations (not used)
#include <string.h> // string manipulation functions
#include <unistd.h> // POSIX operating system API (not used)
#include <time.h> // for seeding the random number generator with current time
#include <stdlib.h> // for memory allocation


// function to check if a string is a positive integer
int is_positive_integer(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) return 0; 
    }
    return atoi(str) > 0; // convert the str to int and if its more than 0
}

int main(int argc, char *argv[]) {
    // seed random number generator witht the current time to generate random numbers
    srand(time(NULL));
    int minrand = 1; // the min number we can get
    int maxrand = 100; // the max num we can get

    // check if the number of arguments is correct
    if (argc != 3) {
        printf("Incorrect usage. You provided %d arguments. The correct number of arguments is 2\n", argc - 1);
        return 1; // exit with an error
    }

    // check if both arguments are positive integers
    if (!is_positive_integer(argv[1]) || !is_positive_integer(argv[2])) {
        printf("Incorrect usage. The parameters you provided are not positive integers\n");
        return 1; // exit with an error
    }

    // convert arguments to integers
    int rows = atoi(argv[1]); 
    int cols = atoi(argv[2]);

    // dynamically allocate memory for the matrix
    int **matrix = malloc(rows * sizeof(int *)); 
    if (!matrix) { // check if memory allocation failed
        fprintf(stderr, "Memory allocation failed\n");
        return 1; // exit with an error code
    }

    // allocate memory for each row of the metrix
    for (int i = 0; i < rows; i++) { 
        matrix[i] = malloc(cols * sizeof(int)); // allocate memory for the columns in each row
        if (!matrix[i]) { // check if allocation failed
            fprintf(stderr, "Memory allocation failed\n");

            // VERY IMPORTNAT TO CLEAN UP!!!!!
            for (int j = 0; j < i; j++) free(matrix[j]); // free previously allocated rows
            free(matrix); // free the row pointer array
            return 1; // exit with an error code
        }
    }

    // fill the matrix with random integers between 1 and 100
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = minrand + rand() % (maxrand - minrand + 1); // random number generation
        }
    }

    // write the matrix to "matrix.txt"
    FILE *file = fopen("matrix.txt", "w");
    if (!file) { // check if the file could not be created
        fprintf(stderr, "Failed to create file\n");
        
        // Free all allocated memory
        for (int i = 0; i < rows; i++) free(matrix[i]);
        free(matrix);
        return 1;// exit wiht an error
    }

    // write the matrix to the file, row by row
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(file, "%d", matrix[i][j]); // write the current value
            if (j < cols - 1) fprintf(file, " "); // add space between numbers, but not after the last column
        }
        fprintf(file, "\n");// move to the next line after each row
    }

    fclose(file); // close the file after writing

    // free dynamically allocated memory!!!!!!
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix); // free the row pointer array

    return 0; // exit successfully
}
