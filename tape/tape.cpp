#include "tape.h"

template <typename T>
Tape<T>::Tape() {
    for (size_t i = 0; i < 10; i++) {
        list.push_back(" ");
    }
}

template <typename T>
Tape<T>::Tape(const DLL<T> list) {
    this->list = list;
}

template <typename T>
void Tape<T>::print() const {
    int size = list.size();
    for(size_t i = 0; i < size; i++) {
        std::cout << list[i] << std::endl;
    }
}

template <typename T>
const T& Tape<T>::operator[](size_t i) {

}
