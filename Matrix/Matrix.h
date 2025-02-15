#pragma once
#include <iostream>
#include <cmath>
using namespace std;


class Massive {
    int N;
    int** m_S;
    void Copy(Massive const& B);
    void Clean();
public:
    Massive(int N, int b, int** A);
    Massive(Massive const& B);
    int operator[](int a);
    Massive& operator= (Massive const& B);
    ~Massive();

};



class Matrix {
    int N;
    int** m_M = nullptr;
    /*Massive m_M_col;*/
    void Clean();
    void Copy(Matrix const& B);

public:
    /* Конструкторы и Деструктор */
    Matrix();
    Matrix(int N);
    Matrix(int N, int* M);
    Matrix(Matrix const& B);
    ~Matrix();

    /* Публичные Методы */
    int size();
    void input(int N);
    void print();

    /* Перегруженные операторы */
    Matrix operator+(Matrix const& B) const;
    Matrix operator-(Matrix const& B) const;
    Matrix operator*(Matrix const& B) const;
    Matrix operator() (int a, int b) const;
    Massive operator() (int a);
    Matrix operator!();
    int* operator[] (int a);
    Matrix& operator= (Matrix const& B);

    bool operator==(Matrix const& B) const;
    bool operator!=(Matrix const& B) const;


};