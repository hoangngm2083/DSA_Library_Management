#ifndef HASHSET_H
#define HASHSET_H

#include <iostream>
#include "data_structs/LinkedList.h"
#include "data_structs/LinearList.h"

class HashSet {
private:
    int M;                  // số slot trong bảng băm
    LinkedList<int>* table; // mảng danh sách liên kết

    int hashFunction(int k) const {
        return k % M;
    }

public:
    // Constructor
    // explicit = cấm chuyển đổi ngầm định, buộc bạn phải khởi tạo một cách rõ ràng.
    explicit HashSet(int size = 101) : M(size) { 
        table = new LinkedList<int>[M];
    }

    // Destructor
    ~HashSet() {
        delete[] table;
    }

    // Xóa toàn bộ bảng
    void clear() {
        for (int i = 0; i < M; i++) {
            table[i].clear();
        }
    }

    // Thêm khóa k
    bool insert(int k) {
        int h = hashFunction(k);

        // kiểm tra trùng
        int found = table[h].search(k);
        if (found == k) return false; // đã có

        table[h].insertLast(k); // thêm vào cuối danh sách
        return true;
    }

    // Kiểm tra tồn tại
    bool contains(int k) const {
        int h = hashFunction(k);
        int found = table[h].search(k);
        return found == k;
    }

    // Xóa khóa
    bool remove(int k) {
        int h = hashFunction(k);
        return table[h].deleteValue(k);
    }

    // Duyệt và in bảng
    void traverse() const {
        for (int i = 0; i < M; i++) {
            std::cout << i << ": ";
            table[i].traverse([](int x) {
                std::cout << x << " -> ";
            });
            std::cout << "NULL\n";
        }
    }
        // Trả về tất cả phần tử trong HashSet dưới dạng LinearList
    LinearList<int> toLinearList() const {
        LinearList<int> result;
        for (int i = 0; i < M; i++) {
            table[i].traverse([&](int x) {
                result.push(x);
            });
        }
        return result;
    }
};

#endif // HASHSET_H
