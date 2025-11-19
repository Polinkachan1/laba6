#ifndef ARRAY_H
#define ARRAY_H

#include "number.h"

template <class number>
class Array {
private:
    int length;
    number *array;

public:
    Array(int length = 0);
    Array(const Array& other);
    ~Array();
    int getLength() const;
    int changeLength(int new_length);
    void add();
    void printArray();
    double average();
    double sko();
    void sortIncrease();
    void sortDecrease();
    void changeElem(int index);
    void changeElem(int index, number value);
    number findElem(int index);
};

#endif // ARRAY_H