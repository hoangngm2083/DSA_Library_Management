#include "data_structs/Queue.h"

// Constructor
template <typename T>
Queue<T>::Queue(int size) {
    capacity = size;
    front = 0;
    rear = -1;
    count = 0;
    nodes = new T[capacity];
}

// Destructor
template <typename T>
Queue<T>::~Queue() {
    delete[] nodes;
}

// Kiểm tra rỗng
template <typename T>
bool Queue<T>::isEmpty() const {
    return count == 0;
}

// Kiểm tra đầy
template <typename T>
bool Queue<T>::isFull() const {
    return count == capacity;
}

// Thêm phần tử vào queue (Enqueue)
template <typename T>
bool Queue<T>::enqueue(const T& x) {
    if (isFull()) {
        std::cerr << "Lỗi: Queue đầy, không thể enqueue!\n";
        return false;
    }
    rear = (rear + 1) % capacity;
    nodes[rear] = x;
    count++;
    return true;
}

// Loại bỏ phần tử khỏi queue (Dequeue)
template <typename T>
bool Queue<T>::dequeue(T& x) {
    if (isEmpty()) {
        std::cerr << "Lỗi: Queue rỗng, không thể dequeue!\n";
        return false;
    }
    x = nodes[front];
    front = (front + 1) % capacity;
    count--;
    return true;
}

// Lấy phần tử ở đầu nhưng không xóa
template <typename T>
T Queue<T>::frontElement() const {
    if (isEmpty()) {
        throw std::out_of_range("Queue rỗng, không có phần tử đầu!");
    }
    return nodes[front];
}

// Lấy phần tử ở cuối nhưng không xóa
template <typename T>
T Queue<T>::rearElement() const {
    if (isEmpty()) {
        throw std::out_of_range("Queue rỗng, không có phần tử cuối!");
    }
    return nodes[rear];
}

// Xóa toàn bộ queue
template <typename T>
void Queue<T>::clear() {
    front = 0;
    rear = -1;
    count = 0;
}

// Duyệt và in queue
template <typename T>
void Queue<T>::traverse() const {
    if (isEmpty()) {
        std::cout << "Queue rỗng!\n";
        return;
    }
    std::cout << "Queue (front -> rear): ";
    for (int i = 0; i < count; i++) {
        std::cout << nodes[(front + i) % capacity] << " ";
    }
    std::cout << "\n";
}
