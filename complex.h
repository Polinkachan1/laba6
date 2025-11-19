#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <cmath>
#include <string>
#include <QString>
#include <QByteArray>

class TComplex{

private:
    double re;
    double im;
public:
    static QChar SEPARATOR;
    TComplex();
    TComplex(double re, double im);
    TComplex(double re);
    double getRe() const;
    double getIm() const;
    void setRe(double newRe) { re = newRe; }
    void setIm(double newIm) { im = newIm; }

    TComplex operator-(const TComplex &second) const;
    TComplex operator+(const TComplex &second) const;
    TComplex operator*(const TComplex &second) const;

    TComplex operator-() const;

    TComplex& operator+=(const TComplex &second);
    TComplex& operator-=(const TComplex &second);
    TComplex& operator*=(const TComplex &second);
    TComplex& operator/=(const TComplex &second);

    TComplex& operator=(const TComplex &other);
    operator QString () const;
    bool operator>(const TComplex &second) const;
    bool operator<(const TComplex &second) const;
    bool operator==(const TComplex &second) const;

    double modulus() const;
    std::string to_str() const;

    static QChar getSeparator() { return SEPARATOR; }

    friend std::istream& operator >> (std::istream & in, TComplex & c);
    friend std::ostream& operator << (std::ostream & os, const TComplex & c);
    friend TComplex pow(const TComplex &complex, double n);
};
QByteArray& operator>>(QByteArray& arr, TComplex& c);

#endif