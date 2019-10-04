#include "matrix.h"
#include <iostream>
#include <cstdlib>

template <typename T>
Matrix::Matrix(size_t rows, size_t columns)
{
    _rows = rows;
    ptr = new Array[_rows];

    for (size_t i = 0; i < rows; i++)
        ptr[i].setSize(columns);
        for (size_t j = 0; j < ptr->getSize(); j++)
            ptr[i][j] = 0;
}
 
Matrix::Matrix(  Matrix &matrixToCopy ) // конструктор копии
    :size(matrixToCopy.size)              // инициализатор размера массива
{
    ptr = new Array [size]; // выделить место в памяти для матрицы
 
    for (int ix = 0; ix < size; ix++) // перераспределяем выделенную память
        ptr[ix].setSize(size); // количество столбцов
 
    for (int ix = 0; ix < size; ix++)
        for (int jx = 0; jx < ptr->getSize(); jx++)
            ptr[ix][jx] = matrixToCopy[ix][jx];// заполняем матрицу значениями матрицы matrixToCopy
}
 
Matrix::~Matrix() // десструктор класса Matrix
{
   delete  [] ptr; // освободить память, удалив матрицу
}
 
int Matrix::getSize() const // возвратить количество элементов матрицы
{
    return size;
}
 
Array *Matrix::getPtr() const
{
    return ptr;
}
 
// перегруженный оператор вывода для класса Array (вывод элементов массива на экран)
ostream &operator<< (ostream &output, const Matrix &obj)
{
    for (int ix = 0; ix < obj.size; ix++)
    {
        for (int jx = 0; jx < obj.ptr->getSize(); jx++)
        {
            output << setw(5) // под каждое число выделяется 5 позиций
                   << obj.ptr[ix][jx];
        }
        cout << std::endl;
    }
 
    output << std::endl; // перенос маркера на новую строку
 
    return output; // позволяет множественный вывод, типа cout << x << y << z << ...
}
 
// перегруженный оператор ввода, для заполнения матрицы с клавиатуры
istream &operator>> (istream & input, Matrix &obj)
{
    for (int ix = 0; ix < obj.size; ix++)
        for (int jx = 0; jx < obj.ptr->getSize(); jx++)
            input >> obj.ptr[ix][jx]; // заполняем матрицу
 
    return input; // позволяет множественный ввод, типа cin >> x >> y >> z >> ...
}
 
// перегруженный оператор взятия индекса
Array &Matrix::operator[] (int subscript)
{
    if(subscript < 0 || subscript >= size)
    {
        std::cerr << "\n Ошибка индекса: " << subscript << std::endl;
        exit(1); // завершить работу программы, неправильный индекс
    }
    return ptr[subscript]; // возврат ссылки на элемент массива
}
 
void Matrix::setMatrix() // заполнение массива
{
    for (int ix = 0; ix < size; ix++)
        for (int jx = 0; jx < ptr->getSize(); jx++)
            cin >> ptr[ix][jx]; // ввод элементов матрицы с клавиатуры
}
 
void Matrix::getMatrix() // вывод массива
{
    for (int ix = 0; ix < size; ix++)
    {
        for (int jx = 0; jx < ptr->getSize(); jx++)
            cout << setw(5) << ptr[ix][jx]; // вывод элементов матрицы на экран
        cout << std::endl;
    }
 
    cout << std::endl; // новая строка
}
 
int *Matrix::search(const int key) const // поиск по ключу
{
    for (int ix = 0; ix < size; ix++)
        for (int jx = 0; jx < ptr->getSize(); jx++)
            if ( key == ptr[ix][jx] ) // поиск по ключу
                return (&ptr[ix][jx]);             // позиция искомого элемента
 
    return NULL;
}
 
Matrix Matrix::operator+ (const Matrix &right)
{
    if (size != right.size || ptr->getSize() != right.getPtr()->getSize())
    {
        cout << "Массивы разного размера!\n";
        exit(1); // завершить работу программы
    }
 
    Matrix result(size, ptr->getSize());
    for (int ix = 0; ix < size; ix++)
        for (int jx = 0; jx < ptr->getSize(); jx++)
            result.ptr[ix][jx] = ptr[ix][jx] + right.ptr[ix][jx];
 
    return result; // вернуть сумму
}
 
Matrix Matrix::operator+= (const Matrix &right)
{
    if (size != right.size || ptr->getSize() != right.getPtr()->getSize())
    {
        cout << "Массивы разного размера!\n";
        exit(1); // завершить работу программы
    }
 
//    Matrix result(size, ptr->getSize());
    for (int ix = 0; ix < size; ix++)
        for (int jx = 0; jx < ptr->getSize(); jx++)
            ptr[ix][jx] = ptr[ix][jx] + right.ptr[ix][jx];
 
    return *this; // вернуть сумму
}
 
Matrix Matrix::operator- (const Matrix &right)
{
    if (size != right.size || ptr->getSize() != right.getPtr()->getSize())
    {
        cout << "Массивы разного размера!\n";
        exit(1); // завершить работу программы
    }
 
    Matrix result(size, ptr->getSize());
    for (int ix = 0; ix < size; ix++)
        for (int jx = 0; jx < ptr->getSize(); jx++)
            result.ptr[ix][jx] = ptr[ix][jx] - right.ptr[ix][jx];
 
    return result; // вернуть сумму
}
 
const Matrix &Matrix::operator= (const Matrix &right) // оператор присваивания
{
    if (&right != this) // чтобы не выполнялось самоприсваивание
    {
        if (size != right.size || ptr->getSize() != right.getPtr()->getSize())
        {
            delete [] ptr; // освободить пространство
            size = right.size; // установить нужный размер матрицы
            ptr = new Array [size]; // выделить память под копируемый массив
 
            for (int ix = 0; ix < size; ix++) // перераспределяем выделенную память
                ptr[ix].setSize(right.getPtr()->getSize()); // количество столбцов
        }
 
        for (int ix = 0; ix < size; ix++)
            for (int jx = 0; jx < ptr->getSize(); jx++)
                ptr[ix][jx] = right.ptr[ix][jx]; // скопировать массив
    }
 
    return *this; // разрешает множественное присваивание, например x = t = e
}