#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <utility>   // std::swap, std::move
#include <cstddef>   // std::size_t
#include <type_traits>


template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        explicit Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;   // đầu danh sách
    int   size;   // số node

public:
    // Constructors / Assignment / Destructor
    LinkedList();
    LinkedList(const LinkedList& other);            // deep copy node, KHÔNG đụng data
    LinkedList(LinkedList&& other) noexcept;        // move
    LinkedList& operator=(const LinkedList& other); // deep copy node
    LinkedList& operator=(LinkedList&& other) noexcept;
    ~LinkedList();

    // Trạng thái
    bool isEmpty() const;
    int  getSize() const;

    // Thao tác chèn
    void insertFirst(const T& value);
    void insertAfter(Node* prevNode, const T& value);
    void insertLast(const T& value);

    // Thao tác xóa (chỉ xóa node, KHÔNG xóa data)
    void deleteFirst();
    void deleteAfter(Node* prevNode);
    bool deleteValue(const T& value); // trả về true nếu xóa được

    // Xóa toàn bộ node (KHÔNG xóa data)
    void clear();

    // Tìm kiếm: trả về giá trị tìm thấy (với T là con trỏ => chính con trỏ đó),
    // nếu không thấy trả về T{} (con trỏ => nullptr).
    T search(const T& value) const;

    // Duyệt danh sách
    template <typename Func>
    void traverse(Func&& callback) const {
        Node* current = head;
        while (current != nullptr) {
            callback(current->data);
            current = current->next;
        }
    }

    // Sắp xếp đơn giản (selection) theo toán tử < của T
    void sort();

    // Tiện ích
    Node* getHead() const;
};


#include "../../src/data_structs/LinkedList.tpp"

#endif // LINKEDLIST_H
