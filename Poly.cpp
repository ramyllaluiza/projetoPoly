#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include "Poly.h"

using namespace std;

Poly::Poly()
{
    grau = -1;
    a = nullptr;
}

// Construtor específico
Poly::Poly(int n) : grau(n), a(nullptr) {
    if (n >= 0) {
        a = new double[grau + 1];
        for (int i = 0; i <= grau; ++i) {
            a[i] = (i == grau) ? 1.0 : 0.0;
        }
        if (grau == 0) {
            a[0] = 0.0;
        }
    }
}

// Construtor de cópia
Poly :: Poly(const Poly &P) : grau(P.grau) {
    if (grau >= 0) {
      a = new double[grau + 1];
      for (int i = 0; i <= grau; ++i) {
        a[i] = P.a[i];
      }
    } else {
      a = nullptr;
    }
  }

// Operador de atribuição por cópia
Poly& Poly::operator=(const Poly& P) {
    if (this != &P) {
      delete[] a;
      grau = P.grau;
      if (grau >= 0) {
        a = new double[grau + 1];
        for (int i = 0; i <= grau; ++i) {
          a[i] = P.a[i];
        }
      } else {
        a = nullptr;
      }
    }
    return *this;
  }

// Construtor por movimento
Poly :: Poly (Poly &&P) : grau(P.grau), a(P.a) {
    P.grau = -1;
    P.a = nullptr;
  }

// Operador de atribuição por movimento
Poly& Poly :: operator=(Poly&& P) {
    if (this != &P) {
      delete[] a;
      grau = P.grau;
      a = P.a;
      P.grau = -1;
      P.a = nullptr;
    }
    return *this;
  }

//Destrutor
Poly::~Poly(){
    delete[] a;
    grau = -1;
    a = nullptr;
}

// Método de consulta getGrau
  int Poly :: getGrau() const{
   return grau;
  }

// Método de consulta getCoef
double Poly::getCoef(int i) const{
    if(grau>=i && i>=0){
        return(a[i]);
    }
    return(0.0);
}

// Método de consulta getValor
double Poly::getValor(double x) const{
    if (empty()) {
        return 0.0;
    }

    double valor = 0.0;

    for (int i = 0; i <= grau; ++i) {
        double coeficiente = getCoef(i);
        double termo = pow(x, i);
        valor += coeficiente * termo;
    }

    return valor;
}

// Método para definir o valor do i-ésimo coeficiente
void Poly::setCoef(int i, double newValue) {
    if (i < 0 || i > grau) {
        cerr << "Índice inválido.\n";
        return;
    }

    if (i == grau && grau != 0 && newValue == 0.0) {
        cerr << "Coeficiente inválido.\n";
    }
    a[i] = newValue;
}

// Método Recriar
void Poly::recriar(int newDegree) {
    *this = Poly(newDegree);
}
// Sobrecarga do operador [] para obter o i-ésimo coeficiente do polinômio
double Poly::operator[](int i) const{
    return getCoef(i);
    }

// Sobrecarga do operador ()
double Poly::operator()(double x) const{
    return getValor(x);
}

// Sobrecarga do operador ==
bool Poly::operator==(const Poly& P) const{
    if (grau != P.grau) {
        return false;
    }
    for (int i = 0; i <= grau; ++i) {
        if (a[i] != P.a[i]) {
            return false;
        }
    }
    return true;
    }

// Sobrecarga do operador !=
bool Poly::operator!=(const Poly& P) const{
    return !(*this == P);
}

// Método de consulta empty
bool Poly::empty() const{
    return (grau < 0);
}

// Método de consulta isZero
bool Poly::isZero() const{
    return(grau == 0 && a[0] == 0.0);
}

// Sobrecarga do operador >>
istream& operator>>(istream& X, Poly& P) {
    if (P.empty()) {
        cerr << "Polinomio vazio.\n";
        return X;
    }

    for (int i = P.grau; i >= 0; i--) {
        cout << "Coeficiente de x^" << i << ":\n ";
        X >> P.a[i];
    }

    while (P.a[P.grau] == 0 && !P.isZero()) {
        cout << "O coeficiente de maior grau não pode ser zero. Digite novamente x^" << P.grau << ":\n ";
        X >> P.a[P.grau];
    }

    return X;
}

// Sobrecarga do operador <<
ostream& operator<<(ostream& X, const Poly& P) {
    if(P.grau >= 0){
        for(int i = P.grau; i >= 0; --i){
            if(P.a[i] == 0.0){
                if(i == 0 && P.grau == 0){
                    X << P.a[i];
                }
            }else{
                if(P.a[i] < 0.0){
                    X << "-";
                }else{
                    if(i != P.grau){
                        X << "+";
                    }
                }
                if(abs(P.a[i]) != 1.0 || i == 0){
                    X << abs(P.a[i]);
                }
                if(i != 0){
                    if(abs(P.a[i]) != 1.0){
                        X << "*";
                    }
                    X << "x";

                    if(i > 1){
                        X << "^" << i;
                    }
                }
            }
        }
    }
    return(X);
}

// Sobrecarga do operador +
Poly Poly::operator+(const Poly& P) const{
    if (empty()) {
        return P;
    } else if (P.empty()) {
        return *this;
    }
    int prov = max(grau, P.grau);
    Poly result(prov);

    for(int i = 0; i <= result.getGrau(); ++i)
    {
        result.a[i] = getCoef(i) + P.getCoef(i);
    }

    result.reduceDegree();
    return result;
}

//Sobrecarga do operador - (binario)
Poly Poly::operator-(const Poly& P) const{
    if (empty()) {
        return -P;
    } else if (P.empty()) {
        return *this;
    }

    int prov = max(grau, P.grau);
    Poly result(prov);

    for(int i = 0; i <= result.getGrau(); ++i)
    {
        result.a[i] = getCoef(i) - P.getCoef(i);
    }

    result.reduceDegree();
    return result;
}

//Sobrecarga do operador *
Poly Poly::operator*(const Poly& P) const{

    if(empty() || isZero() && (!P.empty())) return *this;
    if(P.empty() || P.isZero()) return P;

    Poly prov(grau + P.grau);
    prov.a[prov.grau] = 0.0;

    for(int i = 0; i <= grau; ++i){
        for(int j = 0; j <= P.grau; ++j){
            prov.a[i+j] = prov.a[i+j] + a[i] * P.a[j];
        }
    }
    prov.reduceDegree();
    return prov;
}

void Poly::reduceDegree(){
    int newDegree = grau;
    while(newDegree > 0 && a[newDegree] == 0.0){
        newDegree--;
    }
    if(newDegree == grau){
        return;
    }
    Poly prov(newDegree);

    for(int i = 0; i <= newDegree; ++i){
        prov.a[i] = a[i];
    }
    *this = prov;
}

//Sobrecarga do operador - (unario)
Poly Poly::operator-() const{
    if (empty() || isZero()) {
        return *this;
    }
    Poly prov(grau);
    for(int i = 0; i <= grau; ++i){
        prov.a[i] = (-1)*a[i];
    }
    return prov;
}

//Salvar em arquivo
bool Poly::salvar(const string& nome_arq) const{
    ofstream arq(nome_arq);
    if (arq.is_open()) {
        arq << "POLY " << grau << endl;

        for (int i = 0; i <= grau; ++i) {
            arq << a[i] << " ";
        }

        arq << endl;
        arq.close();
        return true;

    } else {
        return false;
    }
}

// Ler arquivo
bool Poly::ler(const string& nome_arq) {

    ifstream arq(nome_arq);
    if (!arq.is_open()) {
        return false;
    }

    string cabecalho;
    arq >> cabecalho;

    if (!arq.good() || cabecalho != "POLY") {
        arq.close();
        return false;
    }

    int value;
    arq >> value;

    if (!arq.good() || value < 0) {
        arq.close();
        grau = value;
        if (a) {
            delete[] a;
            a = nullptr;
        }
        return true;
    }

    Poly prov(value);

    for (int i = 0; i <= value; ++i) {
        arq >> prov.a[i];

        if (!arq.good()) {
            arq.close();
            return false;
        }
    }

    if (prov.a[prov.grau] == 0.0 && prov.grau > 0) {
        arq.close();
        return false;
    }

    arq.close();
    *this = prov;
    return true;
}
