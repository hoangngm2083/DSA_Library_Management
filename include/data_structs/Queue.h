#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <stdexcept>

template <typename T>
class Queue {
private:
    int front;     // Chỉ số đầu hàng
    int rear;      // Chỉ số cuối hàng
    int count;     // Số phần tử hiện tại
    int capacity;  // Kích thước tối đa
    T* nodes;      // Mảng chứa phần tử

public:
    // Constructor
    Queue(int size = 100);

    // Destructor
    ~Queue();

    // Kiểm tra rỗng
    bool isEmpty() const;

    // Kiểm tra đầy
    bool isFull() const;

    // Thêm phần tử vào queue (Enqueue)
    bool enqueue(const T& x);

    // Loại bỏ phần tử khỏi queue (Dequeue)
    bool dequeue(T& x);

    // Lấy phần tử ở đầu nhưng không xóa
    T frontElement() const;

    // Lấy phần tử ở cuối nhưng không xóa
    T rearElement() const;

    // Xóa toàn bộ queue
    void clear();

    // Duyệt và in queue (từ front -> rear)
    void traverse() const;
};

// Include phần triển khai template
#include "../../src/data_structs/Queue.cpp"

#endif // QUEUE_H
