#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

template <typename T>
class LinkedList {
private:
    // Cấu trúc Node
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;  // Con trỏ đầu danh sách
    int size;    // Kích thước danh sách

public:
    // Constructor
    LinkedList();
    
    // Destructor
    ~LinkedList();
    
    // Kiểm tra rỗng
    bool isEmpty() const;
    
    // Lấy kích thước
    int getSize() const;
    
    // Thêm vào đầu
    void insertFirst(const T& value);
    
    // Thêm vào sau một node
    void insertAfter(Node* prevNode, const T& value);
    
    // Thêm vào cuối
    void insertLast(const T& value);
    
    // Xóa đầu
    void deleteFirst();
    
    // Xóa sau một node
    void deleteAfter(Node* prevNode);
    
    // Xóa node chứa giá trị value
    void deleteValue(const T& value);
    
    // Xóa toàn bộ danh sách
    void clear();
    
    // Tìm kiếm
    Node* search(const T& value) const;
    
    // Duyệt và in danh sách
    void traverse() const;
    
    // Sắp xếp (selection sort)
    void sort();
    
    // Lấy node đầu tiên (để hỗ trợ các thao tác khác)
    Node* getHead() const;
};

#include "../../src/data_structs/LinkedList.cpp"
#endif // LINKEDLIST_H