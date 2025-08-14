#include "Stack.h"

// Constructor
template <typename T>
Stack<T>::Stack(int size) {
    capacity = size;
    sp = -1; // Stack rỗng
    nodes = new T[capacity];
}

// Destructor
template <typename T>
Stack<T>::~Stack() {
    delete[] nodes;
}

// Kiểm tra rỗng
template <typename T>
bool Stack<T>::isEmpty() const {
    return sp == -1;
}

// Kiểm tra đầy
template <typename T>
bool Stack<T>::isFull() const {
    return sp == capacity - 1;
}

// Thêm phần tử vào stack (Push)
template <typename T>
bool Stack<T>::push(const T& x) {
    if (isFull()) {
        std::cerr << "Lỗi: Stack đầy, không thể push!\n";
        return false;
    }
    nodes[++sp] = x;
    return true;
}

// Lấy phần tử ra khỏi stack (Pop)
template <typename T>
bool Stack<T>::pop(T& x) {
    if (isEmpty()) {
        std::cerr << "Lỗi: Stack rỗng, không thể pop!\n";
        return false;
    }
    x = nodes[sp--];
    return true;
}

// Xem phần tử trên cùng nhưng không pop
template <typename T>
T Stack<T>::top() const {
    if (isEmpty()) {
        throw std::out_of_range("Stack rỗng, không có phần tử top!");
    }
    return nodes[sp];
}

// Xóa toàn bộ stack
template <typename T>
void Stack<T>::clear() {
    sp = -1;
}

// Duyệt và in stack (từ trên xuống)
template <typename T>
void Stack<T>::traverse() const {
    if (isEmpty()) {
        std::cout << "Stack rỗng!\n";
        return;
    }
    std::cout << "Stack (trên -> dưới): ";
    for (int i = sp; i >= 0; i--) {
        std::cout << nodes[i] << " ";
    }
    std::cout << "\n";
}
