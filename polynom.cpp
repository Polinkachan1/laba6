#include "polynom.h"
#include "array.h"
#include "number.h"
#include <cmath>
#include <iostream>
#include <sstream>

using namespace std;

template <class number>
Polynom<number>::Polynom() {
    degree = 0;
    an = number(1, 0);
    roots = new Array<number>(degree);
    coefficients = new Array<number>(degree + 1);
    coefficients->changeElem(0, an);
}

template <class number>
Polynom<number>::Polynom(int n, number an_value) {
    degree = n;
    an = an_value;
    roots = new Array<number>(degree);
    coefficients = new Array<number>(degree + 1);

    for (int i = 0; i < degree; i++) {
        roots->changeElem(i, number(0, 0));
    }
    for (int i = 0; i <= degree; i++) {
        if (i == degree) {
            coefficients->changeElem(i, an);
        } else {
            coefficients->changeElem(i, number(0, 0));
        }
    }

    calculateCoefficients();
}

template <class number>
Polynom<number>::Polynom(int n, number an_value, Array<number>& roots_array) {
    degree = n;
    an = an_value;
    roots = new Array<number>(roots_array);
    coefficients = new Array<number>(degree + 1);
    calculateCoefficients();
}

template <class number>
Polynom<number>::~Polynom() {
    delete roots;
    delete coefficients;
}

template <class number>
void Polynom<number>::calculateCoefficients() {
    if (degree == 0) {
        coefficients->changeElem(0, an);
        return;
    }

    for (int i = 0; i <= degree; i++) {
        coefficients->changeElem(i, number(0, 0));
    }
    number* currentPoly = new number[degree + 1];
    for (int i = 0; i <= degree; i++) {
        currentPoly[i] = number(0, 0);
    }
    currentPoly[0] = number(1, 0);

    int currentDegree = 0;

    for (int rootIndex = 0; rootIndex < degree; rootIndex++) {
        number root = roots->findElem(rootIndex);

        number* newPoly = new number[degree + 1];
        for (int i = 0; i <= degree; i++) {
            newPoly[i] = number(0, 0);
        }
        for (int i = 0; i <= currentDegree; i++) {
            newPoly[i + 1] = newPoly[i + 1] + currentPoly[i];
        }

        for (int i = 0; i <= currentDegree; i++) {
            newPoly[i] = newPoly[i] - (currentPoly[i] * root);
        }
        for (int i = 0; i <= currentDegree + 1; i++) {
            currentPoly[i] = newPoly[i];
        }

        currentDegree++;
        delete[] newPoly;
    }
    for (int i = 0; i <= degree; i++) {
        coefficients->changeElem(i, currentPoly[i] * an);
    }

    delete[] currentPoly;
}

template <class number>
int Polynom<number>::getDegree() {
    return degree;
}

template <class number>
number Polynom<number>::getCoefficient(int index) {
    if (index >= 0 && index <= degree) {
        return coefficients->findElem(index);
    }
    return number(0, 0);
}

template <class number>
number Polynom<number>::getRoot(int index) {
    if (index >= 0 && index < degree) {
        return roots->findElem(index);
    }
    return number(0, 0);
}

template <class number>
void Polynom<number>::setAn(number new_an) {
    an = new_an;
    if (degree >= 0) {
        coefficients->changeElem(degree, an);
    }
    calculateCoefficients();
}

template <class number>
void Polynom<number>::setRoot(int index, number new_root) {
    if (index >= 0 && index < degree) {
        roots->changeElem(index, new_root);
        calculateCoefficients();
    }
}

template <class number>
void Polynom<number>::resize(int new_degree) {
    if (new_degree < 0) return;

    Array<number>* new_roots = new Array<number>(new_degree);
    Array<number>* new_coefficients = new Array<number>(new_degree + 1);

    int min_degree = (degree < new_degree) ? degree : new_degree;

    for (int i = 0; i < min_degree; i++) {
        new_roots->changeElem(i, roots->findElem(i));
    }

    for (int i = min_degree; i < new_degree; i++) {
        new_roots->changeElem(i, number(0, 0));
    }
    for (int i = 0; i <= min_degree; i++) {
        new_coefficients->changeElem(i, coefficients->findElem(i));
    }

    if (new_degree > degree) {
        new_coefficients->changeElem(new_degree, an);
    }
    for (int i = min_degree + 1; i < new_degree; i++) {
        new_coefficients->changeElem(i, number(0, 0));
    }

    delete roots;
    delete coefficients;
    roots = new_roots;
    coefficients = new_coefficients;
    degree = new_degree;

    calculateCoefficients();
}

template <class number>
number Polynom<number>::findNumberInPoint(number x) const {
    number result(0, 0);

    for (int i = degree; i >= 0; i--) {
        result = result * x + coefficients->findElem(i);
    }

    return result;
}

template <class number>
void Polynom<number>::input(std::istream& in) {
    cout << "Введите степень полинома: ";
    in >> degree;

    cout << "Введите коэффициент an: ";
    in >> an;

    delete roots;
    delete coefficients;

    roots = new Array<number>(degree);
    coefficients = new Array<number>(degree + 1);

    if (degree > 0) {
        cout << "Введите " << degree << " корней полинома: " << endl;
        for (int i = 0; i < degree; i++) {
            cout << "Корень номер "<< i+1 << ": ";
            number root;
            in >> root;
            roots->changeElem(i, root);
        }
    }
    calculateCoefficients();
    cout << "Полином успешно создан!!" << endl;
}

template <class number>
void Polynom<number>::setRootsFromArray(Array<number>& sourceArray, int startIndex) {
    if (startIndex < 0 || startIndex >= sourceArray.getLength()) {
        cout << "Неверный начальный индекс" << endl;
        return;
    }

    int availableRoots = sourceArray.getLength() - startIndex;
    if (availableRoots < degree) {
        cout << "В массиве недостаточно элементов для всех корней. Нужно: " << degree
             << ", доступно: " << availableRoots << endl;
        return;
    }

    for (int i = 0; i < degree; i++) {
        number root = sourceArray.findElem(startIndex + i);
        roots->changeElem(i, root);
    }

    calculateCoefficients();
    cout << "Корни полинома успешно установлены из массива!" << endl;
}

template <class number>
void Polynom<number>::outputForm1(std::ostream& out) {
    bool firstItem = true;

    for (int i = degree; i >= 0; i--) {
        number coeff = coefficients->findElem(i);

        if (coeff.getRe() == 0 && coeff.getIm() == 0) {
            continue;
        }

        if (!firstItem) {
            out << " + ";
        }

        out << "(" << coeff << ")";

        if (i > 0) {
            out << "*x";
            if (i > 1) {
                out << "^" << i;
            }
        }
        firstItem = false;
    }

    if (firstItem) {
        out << "0";
    }
}

template <class number>
void Polynom<number>::outputForm2(std::ostream& out) {
    out << "(" << an << ")";
    for (int i = 0; i < degree; i++) {
        number root = roots->findElem(i);
        out << "*(x - (" << root << "))";
    }
}

template <class number>
std::string Polynom<number>::getForm1() {
    std::string result;
    bool firstItem = true;

    for (int i = degree; i >= 0; i--) {
        number coeff = coefficients->findElem(i);

        if (coeff.getRe() == 0 && coeff.getIm() == 0) {
            continue;
        }

        if (!firstItem) {
            result += " + ";
        }

        result += "(" + coeff.to_str() + ")";

        if (i > 0) {
            result += "*x";
            if (i > 1) {
                result += "^" + std::to_string(i);
            }
        }
        firstItem = false;
    }

    if (firstItem) {
        result = "0";
    }

    return result;
}

template <class number>
std::string Polynom<number>::getForm2() {
    std::string result = "(" + an.to_str() + ")";
    for (int i = 0; i < degree; i++) {
        number root = roots->findElem(i);
        result += "*(x - (" + root.to_str() + "))";
    }
    return result;
}

template <class number>
void Polynom<number>::addLeadCoefficient(const number& coeff) {
    resize(degree + 1);
    setAn(coeff);
}

template <class number>
void Polynom<number>::addRoot(const number& root) {
    for (int i = 0; i < degree; i++) {
        number currentRoot = roots->findElem(i);
        if (currentRoot.getRe() == 0 && currentRoot.getIm() == 0) {
            roots->changeElem(i, root);
            calculateCoefficients();
            return;
        }
    }
}

template <class number>
void Polynom<number>::changeRoot(int index, const number& newRoot) {
    if (index >= 0 && index < degree) {
        roots->changeElem(index, newRoot);
        calculateCoefficients();
    }
}

template <class number>
number Polynom<number>::valueAtPoint(const number& x) const {
    return findNumberInPoint(x);
}

// Явное инстанцирование шаблона для типа number
template class Polynom<number>;