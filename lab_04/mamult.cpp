#include <vector>
#include <thread>

#include "mamult.hpp"

void init_MVector(int **MVector, int **A, unsigned M, unsigned half_N)
{
    *MVector = new int[M];
    for (unsigned i = 0; i < M; i++)
    {
        (*MVector)[i] = 0;
        for (unsigned k = 0; k < half_N; k++)
        {
            k <<= 1;
            (*MVector)[i] += A[i][k] * A[i][k + 1];
        }
    }
}

void node_calc_odd(int **A, int **B, int **C, int *MulH, int *MulV,
    unsigned i, unsigned j, unsigned half_N, unsigned N_minus_1)
{
    C[i][j] = A[i][N_minus_1] * B[N_minus_1][j] - MulH[i] - MulV[j];
    for (unsigned k = 0; k < half_N; k++)
    {
        k <<= 1;
        C[i][j] += (A[i][k] + B[k + 1][j]) * (A[i][k + 1] + B[k][j]);
    }
}

void node_calc_even(int **A, int **B, int **C, int *MulH, int *MulV,
    unsigned i, unsigned j, unsigned half_N)
{
    C[i][j] = -MulH[i] - MulV[j];
    for (unsigned k = 0; k < half_N; k++)
    {
        k <<= 1;
        C[i][j] += (A[i][k] + B[k + 1][j]) * (A[i][k + 1] + B[k][j]);
    }
}

Matrix& multiply_vinograd_opt(const Matrix &A, const Matrix &B)
{
    const unsigned M = A.get_rows();
    const unsigned N = A.get_cols();
    const unsigned Q = B.get_cols();

    int **A_matr = A.matr();
    int **B_matr = B.matr();

    Matrix C(M, Q);
    int **C_matr = C.matr();


    unsigned half_N = N >> 1;

    int *MulH = nullptr, *MulV = nullptr;

    std::thread thr_MulH(init_MVector, &MulH, A, M, half_N);
    std::thread thr_MulV(init_MVector, &MulV, B, Q, half_N);

    thr_MulH.join();
    thr_MulV.join();

    std::vector<std::thread> threads;

    if (N % 2)
    {
        unsigned N_minus_1 = N - 1;
        for (unsigned i = 0; i < M; i++)
            for (unsigned j = 0; j < Q; j++)
                threads.push_back(std::thread(node_calc_odd, A, B, C,
                                            MulH, MulV, i, j, half_N,
                                            N_minus_1));
    }
    else
    {
        for (unsigned i = 0; i < M; i++)
            for (unsigned j = 0; j < Q; j++)
                threads.push_back(std::thread(node_calc_even, A, B, C,
                                            MulH, MulV, i, j, half_N));
    }

    for (auto& th : threads)
        th.join();

    delete [] MulH;
    delete [] MulV;

    return C;
}

Matrix& multiply_vinograd_nothread(const Matrix &A, const Matrix &B)
{
    const unsigned M = A.get_rows();
    const unsigned N = A.get_cols();
    const unsigned Q = B.get_cols();

    int **A_matr = A.matr();
    int **B_matr = B.matr();

    Matrix C(M, Q);
    int **C_matr = C.matr();

    unsigned half_N = N >> 1;

    int *MulH = new int[M];
    for (unsigned i = 0; i < M; i++)
    {
        MulH[i] = 0;
        for (unsigned k = 0; k < half_N; k++)
        {
            k <<= 1;
            MulH[i] += A_matr[i][k] * A_matr[i][k + 1];
        }
    }

    int *MulV = new int[Q];
    for (unsigned i = 0; i < Q; i++)
    {
        MulV[i] = 0;
        for (unsigned k = 0; k < half_N; k++)
        {
            k <<= 1;
            MulV[i] += B_matr[k][i] * B_matr[k + 1][i];
        }
    }

    if (N % 2)
    {
        unsigned N_minus_1 = N - 1;
        for (unsigned i = 0; i < M; i++)
            for (unsigned j = 0; j < Q; j++)
            {
                C_matr[i][j] = A_matr[i][N_minus_1] * B_matr[N_minus_1][j] -
                                MulH[i] - MulV[j];
                for (unsigned k = 0; k < half_N; k++)
                {
                    k <<= 1;
                    C_matr[i][j] += (A_matr[i][k] + B_matr[k + 1][j]) * 
                                    (A_matr[i][k + 1] + B_matr[k][j]);
                }
            }
    }
    else
    {
        for (unsigned i = 0; i < M; i++)
            for (unsigned j = 0; j < Q; j++)
            {
                C_matr[i][j] = -MulH[i] - MulV[j];
                for (unsigned k = 0; k < half_N; k++)
                {
                    k <<= 1;
                    C_matr[i][j] += (A_matr[i][k] + B_matr[k + 1][j]) * 
                                    (A_matr[i][k + 1] + B_matr[k][j]);
                }
            }
    }

    delete [] MulH;
    delete [] MulV;

    return C;
}
