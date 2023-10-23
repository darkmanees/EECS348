#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

// Prototypes//
void print_matrix(int matrix[], int size);
int *matrix_add(int matrix_a[], int matrix_b[], int size);
int *matrix_multiply(int matrix_A[], int matrix_B[], int size);
int *matrix_subtract(int matrix_A[], int matrix_B[], int size);

int main()
{
    int SIZE = 100;
    int size = 0;
    int matrix_A[SIZE];
    int matrix_B[SIZE];

    string file_name = "";
    cout << "\nManish Singh\nLab #6: Matrix manipulation\n\n";
    cin >> file_name;

    // Open file
    ifstream file;
    file.open(file_name);

    // Add integers from file to two 1D arrays containing matrices A and B
    try
    {
        if (file.is_open())
        {
            file >> size;
            if (size > SIZE)
            {

                file.close();
                throw(runtime_error("Size must be less than or equal to 100"));
            }
            for (int i = 0; i < (size * size * 2); i++)
            {
                if (i < (size * size))
                {
                    file >> matrix_A[i];
                }
                else
                {
                    file >> matrix_B[i - (size * size)];
                }
            }
        }
        else
        {

            throw(runtime_error("Invalid file name"));
        }

        // Close file
        file.close();

        cout << "\nMatrix A:\n";
        print_matrix(matrix_A, size);

        cout << "\nMatrix B:\n";
        print_matrix(matrix_B, size);

        // sum of matrices A and B and print the sum
        cout << "\nMatrix Sum (A + B):\n";
        int *sum_matrix = matrix_add(matrix_A, matrix_B, size);
        print_matrix(sum_matrix, size);

        // Store product of matrices A and B and print the product
        cout << "\nMatrix Product (A * B):\n";
        int *product_matrix = matrix_multiply(matrix_A, matrix_B, size);
        print_matrix(product_matrix, size);

        // Store difference of matrices A and B and print the difference
        cout << "\nMatrix Difference (A - B):\n";
        int *difference_matrix = matrix_subtract(matrix_A, matrix_B, size);
        print_matrix(difference_matrix, size);
        cout << "\n";

        return 0; // End the function
    }

    // Print error message
    catch (runtime_error &rte)
    {
        cout << "Error: " << rte.what() << "\n";
    }
}

void print_matrix(int matrix[], int size) // Print matrix
{
    int width = 0;

    // Set width of matrix columns
    for (int i = 0; i < (size * size); i++)
    {
        if (int(log10(matrix[i]) + 1) > width)
        {
            width = int(log10(matrix[i]) + 1);
        }
    }

    // Print 1D array as a matrix
    for (int i = 0; i < (size * size); i++)
    {
        cout << right << setw(width) << matrix[i] << " ";
        if ((i + 1) % size == 0)
        {
            cout << "\n";
        }
    }
}

int *matrix_add(int matrix_A[], int matrix_B[], int size) // Return sum of two matrices
{
    static int output_matrix[sizeof(size * size)]; // Create 1D array for sum of matrices

    // Sum each element in the matrices and add result to corresponding element in output array
    for (int i = 0; i < (size * size); i++)
    {
        output_matrix[i] = matrix_A[i] + matrix_B[i];
    }
    return output_matrix; // Return 1D array containing the sum of two matrices
}

int *matrix_multiply(int matrix_A[], int matrix_B[], int size) // Return product of two matrices
{
    int A[size][size];
    int B[size][size];
    int C[size][size];

    // Convert 1D input arrays into 2D arrays
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            A[i][j] = matrix_A[i * size + j];
            B[i][j] = matrix_B[i * size + j];
        }
    }

    static int output_matrix[sizeof(size * size)]; // Create 1D array for product of matrices
    int element_sum;

    // Calculate product of two matrices and add result to each element of a 2D array
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            element_sum = 0;
            for (int k = 0; k < size; k++)
            {
                element_sum += (A[i][k] * B[k][j]);
                C[i][j] = element_sum;
            }
        }
    }

    // Convert 2D array to 1D array
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            output_matrix[(3 * i) + j] = C[i][j];
        }
    }
    return output_matrix;
}

int *matrix_subtract(int matrix_A[], int matrix_B[], int size) // Return difference of two matrices
{
    static int output_matrix[sizeof(size * size)]; // Create 1D array for difference of matrices

    for (int i = 0; i < (size * size); i++)
    {
        output_matrix[i] = matrix_A[i] - matrix_B[i];
    }
    return output_matrix;
}