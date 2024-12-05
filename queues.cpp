#include <iostream>

using namespace std;

class CircularQueue {
private:
    int _front;
    int _back;
    int* _array;
    int _capacity;
    int _size;

    void resize() {
        int newCapacity = _capacity * 2;
        int* newArray = new int[newCapacity];

        int index = _front;
        for (int i = 0; i < _size; ++i) {
            newArray[i] = _array[index];
            index = (index + 1) % _capacity; // Circular index
        }

        delete[] _array;
        _array = newArray;
        _capacity = newCapacity;
        _front = 0;
        _back = _size - 1;
    }

public:
    CircularQueue(int capacity = 10) {
        _capacity = capacity;
        _array = new int[_capacity];
        _front = -1;
        _back = -1;
        _size = 0;
    }

    ~CircularQueue() {
        delete[] _array;
    }

    void enqueue(int value) {
        if (_size == _capacity) {
            resize(); // Redimensionar la cola si está llena
        }

        if (_size == 0) {
            _front = 0;
            _back = 0;
        }
        else {
            _back = (_back + 1) % _capacity; // Incremento circular
        }

        _array[_back] = value; // Insertar en la posición correcta de _back
        _size++;
    }

    int dequeue() {
        if (empty()) {
            cout << "Queue is empty." << endl;
            return -1; // Error si la cola está vacía
        }

        int dequeueValue = _array[_front];
        _front = (_front + 1) % _capacity; // Incremento circular del frente

        _size--;

        if (_size == 0) {
            _front = -1; // Reiniciar cuando la cola está vacía
            _back = -1;
        }

        return dequeueValue;
    }

    int size() const {
        return _size;
    }

    bool empty() const {
        return _size == 0;
    }

    void print() const {
        if (empty()) {
            cout << "Queue is empty. Nothing to print.\n";
            return;
        }

        std::cout << "Queue elements: ";
        int index = _front;
        for (int i = 0; i < _size; ++i) {
            std::cout << _array[index] << " ";
            index = (index + 1) % _capacity; // Incremento circular
        }
        std::cout << std::endl;
    }
};

int main() {
    CircularQueue q(3);

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.print();

    q.enqueue(40); // Esto debería hacer que se redimensione
    q.print();

    q.dequeue();
    q.enqueue(50);
    q.print();

    return 0;
}
