#ifndef LINEARLIST_H
#define LINEARLIST_H

template <typename T>
class LinearList {
private:
    int n;          // Số phần tử hiện có
    int capacity;   // Sức chứa tối đa
    T *nodes;       // Mảng động chứa các phần tử

public:
    // Constructor
    LinearList(int initialCapacity = 10);

    // Destructor
    ~LinearList();

    // Kiểm tra rỗng
    bool isEmpty() const;

    // Kiểm tra đầy
    bool isFull() const;

    // Thêm phần tử vào vị trí i
    bool insert(int i, const T &info);

    // Xóa phần tử tại vị trí i
    bool remove(int i);

    // Truy cập phần tử tại vị trí i (operator[])
    T& operator[](int i);

    // Duyệt và in danh sách
    void traverse() const;

    // Tìm kiếm phần tử
    int search(const T &info) const;

    // Xóa toàn bộ danh sách
    void clear();
};

#include "../../src/data_structs/LinearList.cpp"

#endif // LINEARLIST_H