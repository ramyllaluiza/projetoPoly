#ifndef POLY_H_
#define POLY_H_
#include <string>

class Poly {

private:
    int grau;
    double* a;

    void reduceDegree();

public:
    // Construtores e destrutores
    Poly();
    Poly(int n);
    Poly(const Poly& P);
    ~Poly();
    Poly(Poly&& P);

    // Funções de acesso e utilitárias
    void imprimir() const;
    void recriar(int newDegree);
    int getGrau() const;
    double getCoef(int i) const;
    double getValor(double x) const;
    bool empty() const;
    bool isZero() const;
    void setCoef(int i, double newValue);

    //Funções de I/O
    friend std::ostream& operator<<(std::ostream& X, const Poly& P);
    friend std::istream& operator>>(std::istream& X, Poly& P);

    // Operadores sobrecarregados
    bool operator!=(const Poly& P) const;
    bool operator==(const Poly& P) const;
    Poly &operator=(const Poly& P);
    Poly &operator=(Poly&& P);
    Poly operator+(const Poly& P) const;
    Poly operator-(const Poly& P) const;
    Poly operator-() const;
    Poly operator*(const Poly& P) const;
    double operator[](int i) const;
    double operator()(double x )const;

    // Funções para salvar e ler de arquivo
    bool salvar(const std::string& nome_aqr) const;
    bool ler(const std::string& nome_arq);

};

#endif
