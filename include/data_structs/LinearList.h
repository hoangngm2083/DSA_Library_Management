#ifndef LINEARLIST_H
#define LINEARLIST_H
#include <iostream>
#include <functional>

template <typename T>
class LinearList {
private:
    int n;          // Số phần tử hiện có
    int capacity;   // Sức chứa tối đa
    T *nodes;       // Mảng động chứa các phần tử

public:
    // Constructor
    LinearList(int initialCapacity = 10000);

    // Destructor
    ~LinearList();

    // Kiểm tra rỗng
    bool isEmpty() const;

    // Kiểm tra đầy
    bool isFull() const;

    // Thêm phần tử vào cuối
    bool push(const T &info);

    // Thêm phần tử vào vị trí i
    bool insert(int i, const T &info);

    // Xóa phần tử tại vị trí i
    bool remove(int i);

    // Truy cập phần tử tại vị trí i (operator[])
    T& operator[](int i);
    const T& operator[](int i) const;

    // Duyệt và in danh sách
    template<typename Func>
    void traverse(Func&& callback) const {
        if (isEmpty()) {
            std::cout << "Danh sách rỗng!\n";
            return;
        }
        for (int i = 0; i < n; i++) {
            callback(nodes[i]);
        }
    }

    // Tìm kiếm phần tử
    int search(const T &info) const;

    int size() const;

    // Xóa toàn bộ danh sách
    void clear();
};

#include "../../src/data_structs/LinearList.cpp"

#endif // LINEARLIST_H