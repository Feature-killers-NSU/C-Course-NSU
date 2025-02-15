#include "Matrix.h"




/*Класс Massive*/

Massive::Massive(int N, int b, int** A) {
    m_S = new int* [N];
    for (int i = 0;i < N;i++) {
        m_S[i] = &(A[i][b]);

    }

}

void Massive::Copy(Massive const& B) {
    this->N = B.N;
    this->m_S = new int* [N];
    for (int i = 0;i < N;i++) {
        m_S[i] = B.m_S[i];

    }

}

Massive::Massive(Massive const& B) {
    this->Copy(B);
}


int Massive::operator[](int a) {
    return *(m_S[a]);
}


Massive& Massive::operator=(Massive const& B) {
    if(this!=&B){
    this->Clean();
    this->Copy(B);
      }
    return *this;
      
}



void Massive::Clean() {
    delete[] m_S;
}
Massive::~Massive() {
    this->Clean();
}








/*закрытые методы*/
void Matrix::Copy(Matrix const& B) {
    this->N = B.N;

    this->m_M = new int* [N];
    for (int i = 0;i < N;i++) {
        m_M[i] = new int[N];
        for (int j = 0;j < N;j++) {
            m_M[i][j] = B.m_M[i][j];
        }
    }

}
void  Matrix::Clean() {
    if (m_M != nullptr) {
        for (int i = 0;i < N;i++) {
            delete[] m_M[i];
        }
        delete[] m_M;
    }


}





/* Конструкторы  и Деструктор*/
Matrix::Matrix() {
    this->N = 0;

    this->m_M = nullptr;


};

Matrix::Matrix(int N) {
    this->N = N;
    if (N == 0) {
        this->m_M = nullptr;
    }
    this->m_M = new int* [N];
    for (int i = 0;i < N;i++) {
        m_M[i] = new int[N];
        for (int j = 0;j < N;j++) {
            m_M[i][j] = 1 * (j == i);
        }
    }
}

Matrix::Matrix(int N, int* M) {
    this->N = N;
    this->m_M = new int* [N];
    for (int i = 0;i < N;i++) {
        m_M[i] = new int[N];
        for (int j = 0;j < N;j++) {
            m_M[i][j] = M[j] * (j == i);
        }
    }
};
Matrix::Matrix(Matrix const& B) {
    this->Copy(B);
}
Matrix::~Matrix() {
    this->Clean();
}
/*Методы */
int Matrix::size() {
  return N;
}
void Matrix::input(int N) {
    this->Clean();
    this->N = N;
    this->m_M = new int* [N];
    for (int i = 0;i < N;i++) {
        m_M[i] = new int[N];
        for (int j = 0;j < N;j++) {
            cin >> m_M[i][j];
        }
    }
}






void Matrix::print() {
    for (int i = 0;i < this->N;i++) {
        for (int j = 0;j < N;j++) {
            cout << m_M[i][j] << " ";
        }
        cout << "\n";
    }
};

/* Перегрузка операторов*/
Matrix Matrix::operator+(Matrix const& B) const
{
    if (N != B.N) throw (abs(N - B.N));

    Matrix C(this->N);
    for (int i = 0;i < this->N;i++) {
        for (int j = 0;j < N;j++) {
            C.m_M[i][j] = this->m_M[i][j] + B.m_M[i][j];
        }
    }
    return C;


}
Matrix Matrix::operator-(Matrix const& B) const
{
    Matrix C(this->N);
    for (int i = 0;i < this->N;i++) {
        for (int j = 0;j < N;j++) {
            C.m_M[i][j] = this->m_M[i][j] - B.m_M[i][j];
        }
    }
    return C;
}
Matrix Matrix::operator*(const Matrix& B)const
{
    if (N != B.N) throw (abs(N - B.N));
    Matrix C(this->N);
    for (int i = 0;i < N;i++) {
        C.m_M[i][i] = 0;
    }
    for (int i = 0;i < this->N;i++) {
        for (int k = 0;k < N;k++) {
            for (int j = 0;j < N;j++) {
                C.m_M[i][k] += this->m_M[i][j] * B.m_M[j][k];
            }
        }
    }
    return C;
}

bool Matrix::operator==(Matrix const& B)const {
    if (this->N != B.N) return 0;
    for (int i = 0;i < N;i++) {
        for (int j = 0;j < N;j++) {
            if (this->m_M[i][j] != B.m_M[i][j]) return 0;
        }
    }
    return 1;
};
bool Matrix:: operator!=(Matrix const& B)const
{
    if (this->N != B.N) return 1;
    for (int i = 0;i < N;i++) {
        for (int j = 0;j < N;j++) {
            if (this->m_M[i][j] != B.m_M[i][j]) return 1;
        }
    }
    return 0;
};
Matrix Matrix:: operator()(int a, int b) const {
    Matrix C = Matrix(this->N - 1);
    int k = 0;
    int l = 0;
    for (int i = 0;i < N;i++) {
        if (i == a - 1) continue;
        for (int j = 0;j < N;j++) {
            if (j == b - 1) continue;
            C.m_M[k][l] = m_M[i][j];
            l = (l + 1) % (N - 1);
        }
        k = (k + 1) % (N - 1);
    }
    return C;
}
Massive Matrix:: operator()(int a) {
    return Massive(N, a, m_M);
}
int* Matrix:: operator[](int a) {
    return m_M[a];
}
Matrix& Matrix::operator=(Matrix const& B) {
    this->Clean();
    this->Copy(B);
    return *this;
}
Matrix Matrix:: operator!() {
    Matrix C(this->N);
    for (int i = 0;i < N;i++)
        for (int j = i;j < N;j++) {
            C.m_M[j][i] = m_M[i][j];
            C.m_M[i][j] = m_M[j][i];
        }
    return C;
}