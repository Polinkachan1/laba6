#ifndef OOP2_POLYNOM_H
#define OOP2_POLYNOM_H

#include "array.h"
#include "number.h"
#include <iostream>

template <class number>
class Polynom {
private:
    int degree;
    number an;
    Array<number>* roots;
    Array<number>* coefficients;
    void calculateCoefficients();

public:
    Polynom();
    ~Polynom();
    Polynom(int n, number an_value);
    Polynom(int n, number an_value, Array<number>& roots_array);

    // Геттеры
    int getDegree();
    number getCoefficient(int index);
    number getRoot(int index);

    void input(std::istream& in);
    void outputForm1(std::ostream& out);
    void outputForm2(std::ostream& out);
    number findNumberInPoint(number x) const;
    void resize(int new_degree);
    void setAn(number new_an);
    void setRoot(int index, number new_root);
    void setRootsFromArray(Array<number>& sourceArray, int startIndex = 0);
    std::string getForm1();
    std::string getForm2();

    // Методы для работы с сервером
    void addLeadCoefficient(const number& coeff);
    void addRoot(const number& root);
    void changeRoot(int index, const number& newRoot);
    number valueAtPoint(const number& x) const;
};

#endif //OOP2_POLYNOM_H