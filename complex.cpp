#include "complex.h"
#include <cmath>
#include <iostream>
#include <sstream>

using namespace std;
#include "..\common\common.h"
QChar TComplex::SEPARATOR = separator;
TComplex::TComplex(){
    im = re = 0;
}

TComplex::TComplex(double re){
    this->re = re;
    im = 0;
}

TComplex::TComplex(double re, double im){
    this->re = re;
    this->im = im;
}

std::istream &operator>>(istream & in, TComplex &num){
    in >> num.re >> num.im;
    return in;
}

double TComplex::getRe() const {
    return this->re;
}

double TComplex::getIm() const {
    return this->im;
}

TComplex TComplex::operator-(const TComplex &num) const {
    return TComplex(re - num.re, im - num.im);
}

TComplex TComplex::operator+(const TComplex &num) const {
    return TComplex(re + num.re, im + num.im);
}

TComplex TComplex::operator*(const TComplex &num) const {
    double resRe = re * num.re - im * num.im;
    double resIm = re * num.im + im * num.re;
    return TComplex(resRe, resIm);
}

TComplex TComplex::operator-() const {
    return TComplex(-re, -im);
}

TComplex& TComplex::operator+=(const TComplex &num) {
    re += num.re;
    im += num.im;
    return *this;
}

TComplex& TComplex::operator-=(const TComplex &num) {
    re -= num.re;
    im -= num.im;
    return *this;
}

TComplex& TComplex::operator*=(const TComplex &num) {
    double new_re = re * num.re - im * num.im;
    double new_im = re * num.im + im * num.re;
    re = new_re;
    im = new_im;
    return *this;
}

TComplex& TComplex::operator/=(const TComplex &num){
    double denominator = num.re * num.re + num.im * num.im;
    double new_re = (re * num.re + im * num.im) / denominator;
    double new_im = (im * num.re - re * num.im) / denominator;
    re = new_re;
    im = new_im;
    return *this;
}

TComplex& TComplex::operator=(const TComplex &other) {
    if (this != &other) {
        re = other.re;
        im = other.im;
    }
    return *this;
}

double TComplex::modulus() const {
    return sqrt(re * re + im * im);
}

bool TComplex::operator<(const TComplex &num) const {
    double mod1 = this->modulus();
    double mod2 = num.modulus();

    if(mod1 == mod2){
        double arg1 = atan2(this->im, this->re);
        double arg2 = atan2(num.im, num.re);
        return arg1 < arg2;
    }
    return mod1 < mod2;
}

bool TComplex::operator>(const TComplex &num) const {
    double mod1 = this->modulus();
    double mod2 = num.modulus();

    if(mod1 == mod2){
        double arg1 = atan2(this->im, this->re);
        double arg2 = atan2(num.im, num.re);
        return arg1 > arg2;
    }
    return mod1 > mod2;
}

bool TComplex::operator==(const TComplex &num) const {
    return (re == num.re) && (im == num.im);
}

std::ostream &operator<<(std::ostream &os, const TComplex &complex){
    if (complex.im < 0 && complex.re != 0){
        os << complex.re << complex.im << "i";
    } else if (complex.im != 0 && complex.re == 0){
        os << complex.im << "i";
    } else if (complex.im > 0 && complex.re != 0){
        os << complex.re << "+" << complex.im << "i";
    } else if (complex.im == 0 && complex.re != 0){
        os << complex.re;
    } else {
        os << "0";
    }
    return os;
}

TComplex pow(const TComplex &complex, double num) {
    double r = complex.modulus();
    double theta = atan2(complex.im, complex.re);

    double new_r = pow(r, num);
    double new_theta = theta * num;

    return TComplex(new_r * cos(new_theta), new_r * sin(new_theta));
}

std::string TComplex::to_str() const {
    std::stringstream ss;
    if (im < 0 && re != 0) {
        ss << re << im << "i";
    } else if (im != 0 && re == 0) {
        ss << im << "i";
    } else if (im > 0 && re != 0) {
        ss << re << "+" << im << "i";
    } else if (im == 0 && re != 0) {
        ss << re;
    } else {
        ss << "0";
    }
    return ss.str();
}
QByteArray& operator>>(QByteArray& arr, TComplex& c)
{
    QString str = QString(arr);
    int p = str.indexOf(TComplex::getSeparator());
    if (p > 0)
    {
        QString reStr = str.left(p);
        c.setRe(reStr.toDouble());
        str = str.mid(p + 1);

        p = str.indexOf(TComplex::getSeparator());
        if (p > 0)
        {
            QString imStr = str.left(p);
            c.setIm(imStr.toDouble());
            arr = str.mid(p + 1).toUtf8();
        }
        else
        {
            c.setIm(str.toDouble());
            arr.clear();
        }
    }
    return arr;
}
TComplex::operator QString () const {
    QString s;
    if (im < 0 && re != 0){
        s = QString::number(re) + QString::number(im) + "i";
    } else if (im != 0 && re == 0){
        s = QString::number(im) + "i";
    } else if (im > 0 && re != 0){
        s = QString::number(re) + "+" + QString::number(im) + "i";
    } else if (im == 0 && re != 0){
        s = QString::number(re);
    } else {
        s = "0";
    }
    return s;
}