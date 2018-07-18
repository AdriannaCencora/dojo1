#include <new>
#include "vector.hpp"



size_t vector::get_capacity() const {
    return capacity;
};

void vector::push_back(int n) {

    if(size == capacity) {
        resize(newCapacity());
    }
    data[size] = n;
    ++size;

}

size_t vector::get_size() const {
    return size;
}

void vector::resize(int _size) {
    capacity=_size;
    int* newVector = new int[capacity];
    copy(data, size, newVector);
    reassignData(newVector);
}

int vector::at(unsigned int index){
    if(index < size)
    {
        return data[index];
    }
    throw std::bad_alloc();
}

void vector::pop_back() {
    if (!size)
        throw std::bad_alloc();

    size --;
}

void vector::insert(int index, int value) {
    if(size < index){
        throw std::bad_alloc();
    }
    if(size == capacity){
        capacity = newCapacity();
        int* newVector = new int[capacity];
        copy(data, index, newVector);
        copy(data+index, size - index, newVector+index+1);
        reassignData(newVector);
    } else {
        ror(data+index, size - index );
    }

    data[index] = value;
    size++;
}

void vector::copy(int *src, int size, int * dst) {

    for (unsigned i = 0; i < size; i++) {
        dst[i] = src[i];
    }

}

void vector::ror( int *vec, int size) {
    for (unsigned i = size; i > 0; i--) {
        vec[i] = vec[i-1];
    }
}

void vector::reassignData(int* newData) {
    delete [] data;
    data = newData;

}

int vector::newCapacity () {
    return 2*capacity;
}

void vector::shrinkToFit() {
    if(size!=capacity) {
        resize(size);
    }
}

void vector::pop(int index) {
    if(!size)
       throw std::bad_alloc();
    copy(data+index+1, size-index-1, data+index);
    size--;
}