#pragma once

#include <cstddef>
#include <exception>

template <class T>
class vector {
public:
    vector() : capacity(4) {
        data = new T[capacity];
    }

    ~vector() {
        delete[] data;
    }

    T operator[](int other) {
        return data[other];
    }

    size_t get_capacity() const {
        return capacity;
    }

    void push_back(int n) {

        if(size == capacity) {
            resize(newCapacity());
        }
        data[size] = n;
        ++size;

    }

    size_t get_size() const {
        return size;
    }


    T at(unsigned int index){
        if(index < size)
        {
            return data[index];
        }
        throw std::bad_alloc();
    }

    void pop_back() {
        if (!size)
            throw std::bad_alloc();
        size--;
    }

    void insert(int index, T value) {
        if(size < index){
            throw std::bad_alloc();
        }
        if(size == capacity){
            capacity = newCapacity();
            T* newVector = new T[capacity];
            copy(data, index, newVector);
            copy(data+index, size - index, newVector+index+1);
            reassignData(newVector);
        } else {
            ror(data+index, size - index );
        }

        data[index] = value;
        size++;
    }

    void shrinkToFit() {
        if(size!=capacity) {
            resize(size);
        }
    }

    void pop(int index) {
        if(!size)
            throw std::bad_alloc();
        copy(data+index+1, size-index-1, data+index);
        size--;
    }

private:
    void copy(T *src, int size, T *dst) {
        for (unsigned i = 0; i < size; i++) {
            dst[i] = src[i];
        }
    }

    void ror(T *vec, int size) {
        for (unsigned i = size; i > 0; i--) {
            vec[i] = vec[i-1];
        }
    }

    void resize(int _size) {
        capacity=_size;
        T* newVector = new T[capacity];
        copy(data, size, newVector);
        reassignData(newVector);
    }

    void reassignData(T* newData) {
        delete [] data;
        data = newData;
    }

    int newCapacity () {
        return 2*capacity;
    }

    size_t size{};
    T* data;
    size_t capacity;
};