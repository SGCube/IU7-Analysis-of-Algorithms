#include "mamult.hpp"

void multiply_classic(int **A, int **B, int **C,
    unsigned M, unsigned N, unsigned Q)
{
    for (unsigned i = 0; i < M; i++)
        for (unsigned j = 0; j < Q; j++)
        {
            C[i][j] = 0;
            for (unsigned k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

void multiply_vinograd(int **A, int **B, int **C,
    unsigned M, unsigned N, unsigned Q)
{
    int *MulH = new int[M];
    for (unsigned i = 0; i < M; i++)
    {
        MulH[i] = 0;
        for (unsigned k = 0; k < N / 2; k++)
            MulH[i] = MulH[i] + A[i][2 * k] * A[i][2 * k + 1];
    }

    int *MulV = new int[Q];
    for (unsigned i = 0; i < Q; i++)
    {
        MulV[i] = 0;
        for (unsigned k = 0; k < N / 2; k++)
            MulV[i] = MulV[i] + B[2 * k][i] * B[2 * k + 1][i];
    }

    for (unsigned i = 0; i < M; i++)
        for (unsigned j = 0; j < Q; j++)
        {
            C[i][j] = -MulH[i] - MulV[j];
            for (unsigned k = 0; k < N / 2; k++)
                C[i][j] = C[i][j] + (A[i][2 * k] + B[2 * k + 1][j]) *
                    (A[i][2 * k + 1] + B[2 * k][j]);

        }

    if (N % 2 == 1)
        for (unsigned i = 0; i < M; i++)
            for (unsigned j = 0; j < Q; j++)
                C[i][j] = C[i][j] + A[i][N - 1] * B[N - 1][j];

    delete [] MulH;
    delete [] MulV;
}

void multiply_vinograd_opt(int **A, int **B, int **C,
    unsigned M, unsigned N, unsigned Q)
{
    unsigned half_N = N >> 1, kk = 0;

    int *MulH = new int[M];
    for (unsigned i = 0; i < M; i++)
    {
        MulH[i] = 0;
        for (unsigned k = 0; k < half_N; k++)
        {
            kk = k << 1;
            MulH[i] += A[i][kk] * A[i][kk + 1];
        }
    }

    int *MulV = new int[Q];
    for (unsigned i = 0; i < Q; i++)
    {
        MulV[i] = 0;
        for (unsigned k = 0; k < half_N; k++)
        {
            kk = k << 1;
            MulV[i] += B[kk][i] * B[kk + 1][i];
        }
    }

    if (N % 2)
    {
        unsigned N_minus_1 = N - 1;
        for (unsigned i = 0; i < M; i++)
            for (unsigned j = 0; j < Q; j++)
            {
                C[i][j] = A[i][N_minus_1] * B[N_minus_1][j] - MulH[i] - MulV[j];
                for (unsigned k = 0; k < half_N; k++)
                {
                    kk = k << 1;
                    C[i][j] += (A[i][kk] + B[kk + 1][j]) * (A[i][kk + 1] + B[kk][j]);
                }
            }
    }
    else
    {
        for (unsigned i = 0; i < M; i++)
            for (unsigned j = 0; j < Q; j++)
            {
                C[i][j] = -MulH[i] - MulV[j];
                for (unsigned k = 0; k < half_N; k++)
                {
                    kk = k << 1;
                    C[i][j] += (A[i][kk] + B[kk + 1][j]) * (A[i][kk + 1] + B[kk][j]);
                }
            }
    }

    delete [] MulH;
    delete [] MulV;
}