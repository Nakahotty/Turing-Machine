#include "tape/tape.h"

int main() {
    DLL<int> list;
    list.push(1);
    list.push(2);
    list.push(3);
    list.push(4);
    list.print();
}