#include "queue.cpp"

int main() {
    Queue<int> q;
    q.enqueue(10);
    q.enqueue(150);
    q.enqueue(3);
    q.enqueue(26);
    q.print();
    q.dequeue();
    q.dequeue(); 
    q.print();
}