#include "data_structs/LinkedList.h"

// ===== Constructors / Assignment / Destructor =====

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), size(0) {}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& other) : head(nullptr), size(0) {
    Node* cur = other.getHead();
    while (cur) {                 // copy từng node; data được copy-shallow
        insertLast(cur->data);
        cur = cur->next;
    }
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList&& other) noexcept
    : head(other.head), size(other.size) {
    other.head = nullptr;
    other.size = 0;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other) {
    if (this != &other) {
        clear();                  // chỉ xóa node cũ
        Node* cur = other.getHead();
        while (cur) {
            insertLast(cur->data);
            cur = cur->next;
        }
    }
    return *this;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList&& other) noexcept {
    if (this != &other) {
        clear();                  // dọn node cũ
        head = other.head;
        size = other.size;
        other.head = nullptr;
        other.size = 0;
    }
    return *this;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    clear();                      // chỉ delete node
}

// ===== Trạng thái =====

template <typename T>
bool LinkedList<T>::isEmpty() const { return head == nullptr; }

template <typename T>
int LinkedList<T>::getSize() const { return size; }

// ===== Chèn =====

template <typename T>
void LinkedList<T>::insertFirst(const T& value) {
    Node* node = new Node(value);
    node->next = head;
    head = node;
    ++size;
}

template <typename T>
void LinkedList<T>::insertAfter(Node* prevNode, const T& value) {
    if (!prevNode) {
        std::cerr << "Lỗi: Node trước không thể là null\n";
        return;
    }
    Node* node = new Node(value);
    node->next = prevNode->next;
    prevNode->next = node;
    ++size;
}

template <typename T>
void LinkedList<T>::insertLast(const T& value) {
    if (isEmpty()) { insertFirst(value); return; }
    Node* cur = head;
    while (cur->next) cur = cur->next;
    cur->next = new Node(value);
    ++size;
}

// ===== Xóa node (KHÔNG xóa data) =====

template <typename T>
void LinkedList<T>::deleteFirst() {
    if (isEmpty()) {
        std::cerr << "Lỗi: Danh sách rỗng\n";
        return;
    }
    Node* temp = head;
    head = head->next;
    delete temp;         // chỉ xóa node
    --size;
}

template <typename T>
void LinkedList<T>::deleteAfter(Node* prevNode) {
    if (!prevNode || !prevNode->next) {
        std::cerr << "Lỗi: Không có node để xóa\n";
        return;
    }
    Node* temp = prevNode->next;
    prevNode->next = temp->next;
    delete temp;         // chỉ xóa node
    --size;
}

template <typename T>
bool LinkedList<T>::deleteValue(const T& value) {
    if (isEmpty()) {
        std::cerr << "Lỗi: Danh sách rỗng\n";
        return false;
    }

    if (head->data == value) {    // so sánh địa chỉ với T là con trỏ
        deleteFirst();
        return true;
    }

    Node* cur = head;
    while (cur->next) {
        if (cur->next->data == value) {
            Node* temp = cur->next;
            cur->next = temp->next;
            delete temp;          // chỉ xóa node
            --size;
            return true;
        }
        cur = cur->next;
    }
    return false;
}

// ===== Clear =====

template <typename T>
void LinkedList<T>::clear() {
    while (!isEmpty()) deleteFirst(); // chỉ xóa node
}

// ===== Search =====

template <typename T>
T LinkedList<T>::search(const T& value) const {
    Node* cur = head;
    while (cur) {
        if (cur->data == value)   // với T là con trỏ => so sánh địa chỉ
            return cur->data;
        cur = cur->next;
    }
    return T{};                   // pointer => nullptr
}

// ===== Sort (selection) =====

template <typename T>
void LinkedList<T>::sort() {
    if (isEmpty() || !head->next) return;

    for (Node* i = head; i; i = i->next) {
        Node* minNode = i;
        for (Node* j = i->next; j; j = j->next) {
            if (j->data < minNode->data) minNode = j;
        }
        if (minNode != i) std::swap(i->data, minNode->data);
    }
}

// ===== Utils =====

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::getHead() const {
    return head;
}
