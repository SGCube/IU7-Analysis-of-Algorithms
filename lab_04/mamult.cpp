#include <vector>
#include <thread>

#include "mamult.hpp"

typedef struct
{
    Matrix &A;
    Matrix &B;
    Matrix &C;
    int *MulH;
    int *MulV;
    unsigned half_N;
    unsigned N_minus_1;
} MultArgs;

typedef struct
{
    unsigned i;
    unsigned start_i;
    unsigned end_i;
    unsigned step;
    unsigned left;
    unsigned amount;
} ThreadArgs;

void init_MultH(int **MVector, Matrix A, unsigned half_N)
{
    const unsigned M = A.get_rows();
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

void init_MultV(int **MVector, Matrix B, unsigned half_N)
{
    const unsigned Q = B.get_cols();
    *MVector = new int[Q];
    for (unsigned j = 0; j < Q; j++)
    {
        (*MVector)[j] = 0;
        for (unsigned k = 0; k < half_N; k++)
        {
            k <<= 1;
            (*MVector)[j] += B[k][j] * B[k + 1][j];
        }
    }
}

void multiply_even(void *_args, void *_thread_args)
{
    MultArgs *args = (MultArgs*) _args;
    ThreadArgs *thread_args = (ThreadArgs*) _thread_args;

    const unsigned Q = args->B.get_cols();

    for (unsigned i = thread_args->start_i; i < thread_args->end_i; i++)
        for (unsigned j = 0; j < Q; j++)
        {
            args->C[i][j] = args->A[i][args->N_minus_1] *
                            args->B[args->N_minus_1][j]
                            - args->MulH[i] - args->MulV[j];
            for (unsigned k = 0; k < args->half_N; k++)
            {
                k <<= 1;
                args->C[i][j] += (args->A[i][k] + args->B[k + 1][j]) *
                                (args->A[i][k + 1] + args->B[k][j]);
            }
        }

    thread_args->i += 1;
	thread_args->start_i = thread_args->end_i;
	if (thread_args->i + 1 != thread_args->amount)
		thread_args->end_i += thread_args->step;
	else
		thread_args->end_i += thread_args->step + thread_args->left;
}

void multiply_odd(void *_args, void *_thread_args)
{
    MultArgs *args = (MultArgs*) _args;
    ThreadArgs *thread_args = (ThreadArgs*) _thread_args;

    const unsigned Q = args->B.get_cols();

    for (unsigned i = thread_args->start_i; i < thread_args->end_i; i++)
        for (unsigned j = 0; j < Q; j++)
        {
            args->C[i][j] = -args->MulH[i] - args->MulV[j];
            for (unsigned k = 0; k < args->half_N; k++)
            {
                k <<= 1;
                args->C[i][j] += (args->A[i][k] + args->B[k + 1][j]) *
                                    (args->A[i][k + 1] + args->B[k][j]);
            }
        }

    thread_args->i += 1;
	thread_args->start_i = thread_args->end_i;
	if (thread_args->i + 1 != thread_args->amount)
		thread_args->end_i += thread_args->step;
	else
		thread_args->end_i += thread_args->step + thread_args->left;
}

Matrix multiply_vinograd_thread(Matrix &A, Matrix &B, unsigned thread_amount)
{
    const unsigned M = A.get_rows();
    const unsigned N = A.get_cols();
    const unsigned Q = B.get_cols();

    Matrix C(M, Q);

    unsigned half_N = N >> 1;

    int *MulH = nullptr, *MulV = nullptr;

    std::thread thr_MulH(init_MultH, &MulH, A, half_N);
    std::thread thr_MulV(init_MultV, &MulV, B, half_N);

    thr_MulH.join();
    thr_MulV.join();

    std::vector<std::thread> threads;

    MultArgs args = { A, B, C, MulH, MulV, half_N, N - 1 };
    ThreadArgs targs;
    targs.amount = thread_amount;
    targs.step = M / thread_amount;
	targs.left = M % thread_amount;
    targs.i = 0;
	targs.start_i = 0;
	targs.end_i = targs.step;
    
    void (*f)(void*, void*) = multiply_odd;
    if (N % 2)
        f = multiply_even;

    for (unsigned i = 0; i < thread_amount; i++)
        threads.push_back(std::thread(f, (void *)&args, (void *)&targs));

    for (auto& th : threads)
        th.join();

    delete [] MulH;
    delete [] MulV;

    return C;
}

Matrix multiply_vinograd_nothread(Matrix &A, Matrix &B)
{
    const unsigned M = A.get_rows();
    const unsigned N = A.get_cols();
    const unsigned Q = B.get_cols();

    Matrix C(M, Q);

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
                C[i][j] = A[i][N_minus_1] * B[N_minus_1][j] -
                                MulH[i] - MulV[j];
                for (unsigned k = 0; k < half_N; k++)
                {
                    k <<= 1;
                    C[i][j] += (A[i][k] + B[k + 1][j]) * 
                                (A[i][k + 1] + B[k][j]);
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
                    C[i][j] += (A[i][k] + B[k + 1][j]) * 
                                (A[i][k + 1] + B[k][j]);
                }
            }
    }

    delete [] MulH;
    delete [] MulV;

    return C;
}
