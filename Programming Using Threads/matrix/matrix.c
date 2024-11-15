#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MATRIX_SIZE 20  // Adjust matrix size if needed

int matA[MATRIX_SIZE][MATRIX_SIZE];
int matB[MATRIX_SIZE][MATRIX_SIZE];
int matSumResult[MATRIX_SIZE][MATRIX_SIZE];
int matDiffResult[MATRIX_SIZE][MATRIX_SIZE];
int matProductResult[MATRIX_SIZE][MATRIX_SIZE];

// Structure to hold coordinates of the cell
typedef struct {
    int row;
    int col;
} Cell;

void fillMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            matrix[i][j] = rand() % 10 + 1;  // Random values from 1 to 10
        }
    }
}

void printMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%5d", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Function to compute sum for a cell
void* computeSum(void* args) {
    Cell* cell = (Cell*)args;
    int row = cell->row;
    int col = cell->col;
    matSumResult[row][col] = matA[row][col] + matB[row][col];
    free(cell);
    pthread_exit(NULL);
}

// Function to compute difference for a cell
void* computeDiff(void* args) {
    Cell* cell = (Cell*)args;
    int row = cell->row;
    int col = cell->col;
    matDiffResult[row][col] = matA[row][col] - matB[row][col];
    free(cell);
    pthread_exit(NULL);
}

// Function to compute product for a cell
void* computeProduct(void* args) {
    Cell* cell = (Cell*)args;
    int row = cell->row;
    int col = cell->col;
    matProductResult[row][col] = 0;
    for (int k = 0; k < MATRIX_SIZE; k++) {
        matProductResult[row][col] += matA[row][k] * matB[k][col];
    }
    free(cell);
    pthread_exit(NULL);
}

int main() {
    srand(time(0));  // Initialize random seed

    // Fill matrices A and B with random values
    fillMatrix(matA);
    fillMatrix(matB);

    // Print initial matrices
    printf("Matrix A:\n");
    printMatrix(matA);
    printf("Matrix B:\n");
    printMatrix(matB);

    // Sum operation
    pthread_t threads[MATRIX_SIZE][MATRIX_SIZE];
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            Cell* cell = (Cell*)malloc(sizeof(Cell));
            cell->row = i;
            cell->col = j;
            pthread_create(&threads[i][j], NULL, computeSum, cell);
        }
    }

    // Wait for sum threads to complete
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            pthread_join(threads[i][j], NULL);
        }
    }

    // Difference operation
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            Cell* cell = (Cell*)malloc(sizeof(Cell));
            cell->row = i;
            cell->col = j;
            pthread_create(&threads[i][j], NULL, computeDiff, cell);
        }
    }

    // Wait for difference threads to complete
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            pthread_join(threads[i][j], NULL);
        }
    }

    // Product operation
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            Cell* cell = (Cell*)malloc(sizeof(Cell));
            cell->row = i;
            cell->col = j;
            pthread_create(&threads[i][j], NULL, computeProduct, cell);
        }
    }

    // Wait for product threads to complete
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            pthread_join(threads[i][j], NULL);
        }
    }

    // Print results
    printf("Sum:\n");
    printMatrix(matSumResult);
    printf("Difference:\n");
    printMatrix(matDiffResult);
    printf("Product:\n");
    printMatrix(matProductResult);

    return 0;
}