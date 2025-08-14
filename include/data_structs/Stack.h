#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <stdexcept>

template <typename T>
class Stack
{
private:
    int sp;       // Stack pointer - chỉ số phần tử trên cùng
    int capacity; // Dung lượng stack
    T *nodes;     // Mảng lưu phần tử

public:
    // Constructor
    Stack(int size = 100);

    // Destructor
    ~Stack();

    // Kiểm tra rỗng
    bool isEmpty() const;

    // Kiểm tra đầy
    bool isFull() const;

    // Thêm phần tử vào stack (Push)
    bool push(const T &x);

    // Lấy phần tử ra khỏi stack (Pop)
    bool pop(T &x);

    // Xem phần tử trên cùng nhưng không pop
    T top() const;

    // Xóa toàn bộ stack
    void clear();

    // Duyệt và in stack (từ trên xuống)
    void traverse() const;
};

// Include phần cài đặt template
#include "../../src/data_structs/Stack.cpp"

#endif // STACK_H
