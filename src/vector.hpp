#pragma once

#include <cstddef>
#include <exception>

class vector {
public:
    vector() : capacity(4) {
        data = new int[capacity];
    }

    ~vector() {
    delete[] data;
    }

    size_t get_capacity() const;
    size_t get_size() const;
    void push_back(int n);
    int at(unsigned int index);

    int operator[](int other) {
        return data[other];
    }
    void pop_back();
    void insert(int index, int value);
    void shrinkToFit();
    void pop(int index);


private:
    void copy(int *src, int size, int * dst);
    void ror( int *vec, int size);
    void resize(int _size);
    void reassignData(int* newData);
    int newCapacity ();
    size_t size{};
    int* data;
    size_t capacity;
};