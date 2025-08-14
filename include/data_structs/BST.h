#ifndef BST_H
#define BST_H

#include <iostream>
#include "Queue.h"

template <typename T>
class BST {
private:
    // Cấu trúc Node với index
    struct Node {
        T data;
        int index;  // Trường index dùng để so sánh
        Node* left;
        Node* right;
        Node(const T& value, int idx) : data(value), index(idx), left(nullptr), right(nullptr) {}
    };

    Node* root;  // Gốc của cây

    // Các hàm hỗ trợ đệ quy
    Node* insertRec(Node* node, const T& value, int index);
    Node* removeRec(Node* node, int index);
    Node* findMin(Node* node) const;
    Node* searchRec(Node* node, int index) const;
    void destroyTree(Node* node);
    void preOrderRec(Node* node) const;
    void inOrderRec(Node* node) const;
    void postOrderRec(Node* node) const;
    int heightRec(Node* node) const;
    int countNodesRec(Node* node) const;

public:
    // Constructor & Destructor
    BST();
    ~BST();

    // Các thao tác cơ bản
    void insert(const T& value, int index);
    void remove(int index);
    bool search(int index) const;
    T getData(int index) const;
    bool isEmpty() const;
    void clear();

    // Các phép duyệt cây
    void preOrder() const;    // NLR
    void inOrder() const;     // LNR
    void postOrder() const;   // LRN
    void levelOrder() const;  // Duyệt theo mức

    // Các thao tác khác
    int getMinIndex() const;
    int getMaxIndex() const;
    T getMinData() const;
    T getMaxData() const;
    int height() const;
    int size() const;
};

#include "../../src/data_structs/BST.cpp"

#endif // BST_H