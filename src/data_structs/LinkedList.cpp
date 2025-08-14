#include "data_structs/LinkedList.h"

// Constructor
template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), size(0) {}

// Destructor
template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

// Kiểm tra rỗng
template <typename T>
bool LinkedList<T>::isEmpty() const {
    return head == nullptr;
}

// Lấy kích thước
template <typename T>
int LinkedList<T>::getSize() const {
    return size;
}

// Thêm vào đầu
template <typename T>
void LinkedList<T>::insertFirst(const T& value) {
    Node* newNode = new Node(value);
    newNode->next = head;
    head = newNode;
    size++;
}

// Thêm vào sau một node
template <typename T>
void LinkedList<T>::insertAfter(Node* prevNode, const T& value) {
    if (prevNode == nullptr) {
        std::cerr << "Lỗi: Node trước không thể là null\n";
        return;
    }
    
    Node* newNode = new Node(value);
    newNode->next = prevNode->next;
    prevNode->next = newNode;
    size++;
}

// Thêm vào cuối
template <typename T>
void LinkedList<T>::insertLast(const T& value) {
    if (isEmpty()) {
        insertFirst(value);
        return;
    }
    
    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    
    Node* newNode = new Node(value);
    current->next = newNode;
    size++;
}

// Xóa đầu
template <typename T>
void LinkedList<T>::deleteFirst() {
    if (isEmpty()) {
        std::cerr << "Lỗi: Danh sách rỗng\n";
        return;
    }
    
    Node* temp = head;
    head = head->next;
    delete temp;
    size--;
}

// Xóa sau một node
template <typename T>
void LinkedList<T>::deleteAfter(Node* prevNode) {
    if (prevNode == nullptr || prevNode->next == nullptr) {
        std::cerr << "Lỗi: Không có node để xóa\n";
        return;
    }
    
    Node* temp = prevNode->next;
    prevNode->next = temp->next;
    delete temp;
    size--;
}

// Xóa node chứa giá trị value
template <typename T>
void LinkedList<T>::deleteValue(const T& value) {
    if (isEmpty()) {
        std::cerr << "Lỗi: Danh sách rỗng\n";
        return;
    }
    
    if (head->data == value) {
        deleteFirst();
        return;
    }
    
    Node* current = head;
    while (current->next != nullptr && current->next->data != value) {
        current = current->next;
    }
    
    if (current->next != nullptr) {
        deleteAfter(current);
    }
}

// Xóa toàn bộ danh sách
template <typename T>
void LinkedList<T>::clear() {
    while (!isEmpty()) {
        deleteFirst();
    }
}

// Tìm kiếm
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::search(const T& value) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == value) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

// Duyệt và in danh sách
template <typename T>
void LinkedList<T>::traverse() const {
    if (isEmpty()) {
        std::cout << "Danh sách rỗng\n";
        return;
    }
    
    Node* current = head;
    std::cout << "Danh sách: ";
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

// Sắp xếp (selection sort)
template <typename T>
void LinkedList<T>::sort() {
    if (isEmpty() || head->next == nullptr) {
        return;
    }
    
    Node* current = head;
    while (current != nullptr) {
        Node* minNode = current;
        Node* temp = current->next;
        
        while (temp != nullptr) {
            if (temp->data < minNode->data) {
                minNode = temp;
            }
            temp = temp->next;
        }
        
        // Hoán đổi giá trị
        T tempData = current->data;
        current->data = minNode->data;
        minNode->data = tempData;
        
        current = current->next;
    }
}

// Lấy node đầu tiên
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::getHead() const {
    return head;
}