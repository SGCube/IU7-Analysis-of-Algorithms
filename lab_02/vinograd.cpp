#include "vinograd.hpp"

Matrix multiply_vinograd(Matrix A, Matrix B)
{
    size_t M = A.get_rows(), N = A.get_columns(), Q = B.get_columns();

    int *MulH = new int[M];
    for (size_t i = 0; i < M; i++)
    {
        MulH[i] = 0;
        for (size_t k = 0; k < N / 2; k++)
            MulH[i] = MulH[i] + A[i][2 * k] * A[i][2 * k + 1];
    }

    int *MulV = new int[Q];
    for (size_t i = 0; i < Q; i++)
    {
        MulV[i] = 0;
        for (size_t k = 0; k < N / 2; k++)
            MulV[i] = MulV[i] + B[2 * k][i] * B[2 * k + 1][i];
    }

    Matrix C(M, Q);
    for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < Q; j++)
        {
            C[i][j] = -MulH[i] - MulV[j];
            for (size_t k = 0; k < N / 2; k++)
                C[i][j] = C[i][j] + (A[i][2 * k] + B[2 * k + 1][j]) *
                    (A[i][2 * k + 1] + B[2 * k][j]);

        }

    if (N % 2 == 1)
        for (size_t i = 0; i < M; i++)
            for (size_t j = 0; j < Q; j++)
                C[i][j] = C[i][j] + A[i][N - 1] * B[N - 1][j];

    delete [] MulH;
    delete [] MulV;

    return C;
}

Matrix multiply_vinograd_opt(Matrix A, Matrix B)
{
    size_t M = A.get_rows(), N = A.get_columns(), Q = B.get_columns();

    size_t N_minus_1 = N - 1;
    bool is_odd = (N % 2 == 1);

    int *MulH = new int[M];
    for (size_t i = 0; i < M; i++)
    {
        MulH[i] = 0;
        for (size_t k = 0; k < N; k += 2)
            MulH[i] += A[i][k] * A[i][k + 1];
    }

    int *MulV = new int[Q];
    for (size_t i = 0; i < Q; i++)
    {
        MulV[i] = 0;
        for (size_t k = 0; k < N; k += 2)
            MulV[i] += B[k][i] * B[k + 1][i];
    }

    Matrix C(M, Q);
    for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < Q; j++)
        {
            C[i][j] = -MulH[i] - MulV[j];
            for (size_t k = 0; k < N; k += 2)
                C[i][j] += (A[i][k] + B[k + 1][j]) * (A[i][k + 1] + B[k][j]);
        }

    if (is_odd)
        for (size_t i = 0; i < M; i++)
            for (size_t j = 0; j < Q; j++)
                C[i][j] += A[i][N_minus_1] * B[N_minus_1][j];

    delete [] MulH;
    delete [] MulV;

    return C;
}