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

void multiply_vinograd_opt(int **A, int **B, int **C,
    unsigned M, unsigned N, unsigned Q)
{
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
}

void multiply_vinograd_nothread(int **A, int **B, int **C,
    unsigned M, unsigned N, unsigned Q)
{
    unsigned half_N = N >> 1;

    int *MulH = new int[M];
    for (unsigned i = 0; i < M; i++)
    {
        MulH[i] = 0;
        for (unsigned k = 0; k < half_N; k++)
        {
            k <<= 1;
            MulH[i] += A[i][k] * A[i][k + 1];
        }
    }

    int *MulV = new int[Q];
    for (unsigned i = 0; i < Q; i++)
    {
        MulV[i] = 0;
        for (unsigned k = 0; k < half_N; k++)
        {
            k <<= 1;
            MulV[i] += B[k][i] * B[k + 1][i];
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
                    k <<= 1;
                    C[i][j] += (A[i][k] + B[k + 1][j]) * (A[i][k + 1] + B[k][j]);
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
                    k <<= 1;
                    C[i][j] += (A[i][k] + B[k + 1][j]) * (A[i][k + 1] + B[k][j]);
                }
            }
    }

    delete [] MulH;
    delete [] MulV;
}
