#include <ostream>
#include <iostream>

template <class T>
class DLL {
private:
    struct Node {
        Node* prev;
        Node* next;
        T data;

        Node(T _data, Node* _prev = nullptr, Node* _next = nullptr)
        {
            this->data = _data;
            this->prev = _prev;
            this->next = _next;
        }
    };
private:
    Node *first,*last;
    void copy(const DLL<T>&);
    void destroy();
public:
    DLL();
    DLL(const DLL<T>&);
    DLL<T>& operator=(const DLL<T>&);
    T& operator[](size_t);
    ~DLL();

    void print() const;
    DLL<T>& push(const T&);
    DLL<T>& push_back(const T&);
    DLL<T>& pop();
    DLL<T>& pop_back();
    DLL<T>& clear();
    DLL<T>& insertAfter(size_t,const T&);
    DLL<T>& deleteAt(size_t);
    void reverse();
    void swap(Node* left, Node* right);

    size_t size() const;
    T& getFirst() const;
    T& getLast() const;
    bool empty();

    class Iterator
    {
        private:
        Node* current;
        
        public:
        Iterator(Node*);
        bool operator!=(const Iterator&);
        Iterator& operator++();
        T& operator*();       
    };

    Iterator begin();
    Iterator end();

    class ReverseIterator
    {
        private:
        Node* current;

        public:
        ReverseIterator(Node*);
        bool operator!=(const ReverseIterator&);
        ReverseIterator& operator++();
        T& operator*();
    };

    ReverseIterator rbegin();
    ReverseIterator rend();
};

template<typename T>
std::ostream& operator<<(std::ostream&, const DLL<T>&);

#include "DLL.cpp"



