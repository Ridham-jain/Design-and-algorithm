#include <iostream>
using namespace std;

int **square_matrix_multiplication(int **arr1, int **arr2, int n, int row1, int col1, int row2, int col2)
{
    int **c = new int *[n];
    for (int i = 0; i < n; i++)
    {
        c[i] = new int[n];
    }
    if (n == 1)
    {
        c[0][0] = arr1[row1][col1] * arr2[row2][col2];
    }
    else
    {
        int mid = (n) / 2;
        int **c1 = square_matrix_multiplication(arr1, arr2, n / 2, row1, col1, row2, col2);
        int **c2=square_matrix_multiplication(arr1, arr2, n / 2, row1, col1 + mid, row2 + mid, col2);

        int **c3 = square_matrix_multiplication(arr1, arr2, n / 2, row1, col1, row2, col2 + mid);
        int **c4=square_matrix_multiplication(arr1, arr2, n / 2, row1, col1 + mid, row2 + mid, col2 + mid);

        int **c5 = square_matrix_multiplication(arr1, arr2, n / 2, row1 + mid, col1, row2, col2);
        int **c6=square_matrix_multiplication(arr1, arr2, n / 2, row1 + mid, col1 + mid, row2 + mid, col2);

        int **c7 = square_matrix_multiplication(arr1, arr2, n / 2, row1 + mid, col1, row2, col2 + mid);
        int **c8=square_matrix_multiplication(arr1, arr2, n / 2, row1 + mid, col1 + mid, row2 + mid, col2 + mid);

        for (int i = 0; i < mid; i++)
        {
            for (int j=0; j < mid; j++)
            {
                c[i][j] = c1[i][j]+c2[i][j];
                c[i][j + mid] = c3[i][j]+c4[i][j];
                c[i + mid][j] = c5[i][j]+c6[i][j];
                c[i + mid][j + mid] = c7[i][j]+c8[i][j];
            }
        }
        for (int i = 0; i < mid; i++)
        {
            delete[] c1[i];
            delete[] c2[i];
            delete[] c3[i];
            delete[] c4[i];
            delete[] c5[i];
            delete[] c6[i];
            delete[] c7[i];
            delete[] c8[i];
        }
        delete[] c1;
        delete[] c2;
        delete[] c3;
        delete[] c4;
        delete[] c5;
        delete[] c6;
        delete[] c7;
        delete[] c8;
    }

    return c;
}

int main()
{
    int n;
    cout << "Enter the size of the square nmatrices : ";
    cin >> n;
    int **arr1 = new int *[n];
    for (int i = 0; i < n; i++)
    {
        arr1[i] = new int[n];
    }
    int **arr2 = new int *[n];
    for (int i = 0; i < n; i++)
    {
        arr2[i] = new int[n];
    }
    cout << "Enter the elements of the matrix arr1 : "<<endl;
    for (int i=0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << "Enter arr[i][j] : ";
            cin >> arr1[i][j];
        }
    }
    cout << endl
         << "Enter the elements of the matrix arr2 : " << endl;
    for (int i=0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << "Enter arr2[i][j] : ";
            cin >> arr2[i][j];
        }
    }
    int **c = square_matrix_multiplication(arr1, arr2, n, 0, 0, 0, 0);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << c[i][j] << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < n; i++)
    {
        delete[] arr1[i];
        delete[] arr2[i];
        delete[] c[i];
    }
    delete[] arr1;
    delete[] arr2;
    delete[] c;
    return 0;
}