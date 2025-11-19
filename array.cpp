#include "array.h"
#include <cmath>
#include <iostream>
#include "complex.h"
using namespace std;

template <class number>
Array<number>::Array(int length) {
    if (length < 0) {
        this->length = 0;
        cout << "Введите неотрицательное число, сейчас по-умолчанию длина массива 0";
    }
    else {
        this->length = length;
    }
    array = new number[length];
}

template <class number>
Array<number>::Array(const Array& other) {
    length = other.length;
    array = new number[length];
    for (int i = 0; i < length; i++) {
        array[i] = other.array[i];
    }
}

template <class number>
Array<number>::~Array() {
    delete[] array;
}

template <class number>
void Array<number>::add() {
    for (int i = 0; i < length; i++) {
        cin >> array[i];
    }
}

template <class number>
int Array<number>::changeLength(int new_length) {
    if (new_length <= 0) return length;

    number* new_array = new number[new_length];
    for (int i = 0; i < min(length, new_length); i++) {
        new_array[i] = array[i];
    }
    delete[] array;
    array = new_array;
    for (int i = length; i < new_length; i++) {
        cout << "Введите новый элемент массива";
        cin >> array[i];
    }
    length = new_length;
    return length;
}

template <class number>
void Array<number>::printArray() {
    for (int i = 0; i < length; i++) {
        cout << array[i] <<" ";
    }
    cout << "\n";
}

template <class number>
double Array<number>::average() {
    double summa = 0;
    if (length != 0) {
        for (int i = 0; i < length; i++) {
            summa += array[i].getRe();
        }
        summa /= length;
    }
    return summa;
}

template <class number>
double Array<number>::sko() {
    double result = 0;
    double average = 1;
    if (length != 0) {
        for (int i = 0; i < length; i++) {
            result += pow((array[i].getRe()-average),2);
        }
        result /= (length-1);
        result = pow(result, 0.5);
    }
    return result;
}

template <class number>
void Array<number>::sortIncrease(){
    for (int i = 0; i < length - 1; i++) {
        for (int j=0; j < length - i - 1; j++) {
            if (array[j] > array[j+1]) {
                swap(array[j], array[j+1]);
            }
        }
    }
}

template <class number>
void Array<number>::sortDecrease() {
    for (int i = 0; i < length - 1; i++) {
        for (int j=0; j < length - i - 1; j++) {
            if (array[j] < array[j+1]) {
                swap(array[j], array[j+1]);
            }
        }
    }
}

template <class number>
void Array<number>::changeElem(int index) {
    if (index <= length && index >= 0) {
        cout << "Введите новое значение: ";
        cin >> array[index];
    }
}

template <class number>
void Array<number>::changeElem(int index, number value) {
    if (index >= 0 && index < length) {
        array[index] = value;
    }
}

template <class number>
number Array<number>::findElem(int index) {
    if (index >= 0 && index < length) {
        return array[index];
    }
    return number(0,0);
}

template <class number>
int Array<number>::getLength() const {
    return length;
}

// Явное инстанцирование шаблона для типа number
template class Array<number>;
