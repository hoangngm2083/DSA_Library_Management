#include "data_structs/BST.h"

// Constructor
template <typename T>
BST<T>::BST() : root(nullptr) {}

// Destructor
template <typename T>
BST<T>::~BST() {
    clear();
}

// Hủy toàn bộ cây (đệ quy)
template <typename T>
void BST<T>::destroyTree(Node* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

// Xóa toàn bộ cây
template <typename T>
void BST<T>::clear() {
    destroyTree(root);
    root = nullptr;
}

// Kiểm tra cây rỗng
template <typename T>
bool BST<T>::isEmpty() const {
    return root == nullptr;
}

// Chèn phần tử (đệ quy) - so sánh bằng index
template <typename T>
typename BST<T>::Node* BST<T>::insertRec(Node* node, const T& value, int index) {
    if (!node) {
        return new Node(value, index);
    }

    if (index < node->index) {
        node->left = insertRec(node->left, value, index);
    } else if (index > node->index) {
        node->right = insertRec(node->right, value, index);
    }
    // Nếu index bằng thì bỏ qua (không chèn trùng)

    return node;
}

// Chèn phần tử (public interface)
template <typename T>
void BST<T>::insert(const T& value, int index) {
    root = insertRec(root, value, index);
}

// Tìm node nhỏ nhất (đệ quy) - theo index
template <typename T>
typename BST<T>::Node* BST<T>::findMin(Node* node) const {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

// Xóa phần tử (đệ quy) - theo index
template <typename T>
typename BST<T>::Node* BST<T>::removeRec(Node* node, int index) {
    if (!node) return nullptr;

    if (index < node->index) {
        node->left = removeRec(node->left, index);
    } else if (index > node->index) {
        node->right = removeRec(node->right, index);
    } else {
        // Node với index cần xóa được tìm thấy

        // Trường hợp 1: Node có 0 hoặc 1 con
        if (!node->left) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (!node->right) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        // Trường hợp 2: Node có 2 con
        Node* temp = findMin(node->right);
        node->data = temp->data;
        node->index = temp->index;
        node->right = removeRec(node->right, temp->index);
    }
    return node;
}

// Xóa phần tử (public interface) - theo index
template <typename T>
void BST<T>::remove(int index) {
    root = removeRec(root, index);
}

// Tìm kiếm (đệ quy) - theo index
template <typename T>
typename BST<T>::Node* BST<T>::searchRec(Node* node, int index) const {
    if (!node || node->index == index) {
        return node;
    }

    if (index < node->index) {
        return searchRec(node->left, index);
    }
    return searchRec(node->right, index);
}

// Tìm kiếm (public interface) - theo index
template <typename T>
bool BST<T>::search(int index) const {
    return searchRec(root, index) != nullptr;
}

// Lấy data theo index
template <typename T>
T BST<T>::getData(int index) const {
    Node* node = searchRec(root, index);
    if (!node) throw std::runtime_error("Không tìm thấy index");
    return node->data;
}

// Duyệt tiền thứ tự (NLR)
template <typename T>
void BST<T>::preOrderRec(Node* node) const {
    if (node) {
        std::cout << "[" << node->index << ":" << node->data << "] ";
        preOrderRec(node->left);
        preOrderRec(node->right);
    }
}

template <typename T>
void BST<T>::preOrder() const {
    preOrderRec(root);
    std::cout << std::endl;
}

// Duyệt trung thứ tự (LNR) - in theo thứ tự index tăng dần
template <typename T>
void BST<T>::inOrderRec(Node* node) const {
    if (node) {
        inOrderRec(node->left);
        std::cout << "[" << node->index << ":" << node->data << "] ";
        inOrderRec(node->right);
    }
}

template <typename T>
void BST<T>::inOrder() const {
    inOrderRec(root);
    std::cout << std::endl;
}

// Duyệt hậu thứ tự (LRN)
template <typename T>
void BST<T>::postOrderRec(Node* node) const {
    if (node) {
        postOrderRec(node->left);
        postOrderRec(node->right);
        std::cout << "[" << node->index << ":" << node->data << "] ";
    }
}

template <typename T>
void BST<T>::postOrder() const {
    postOrderRec(root);
    std::cout << std::endl;
}

// Duyệt theo mức (BFS)
template <typename T>
void BST<T>::levelOrder() const {
    if (!root) return;
    int count = this->size();
    Queue<Node*> q(count);
    q.enqueue(root);

    while (!q.isEmpty()) {
        Node* current = q.frontElement();
        Node* rearEle = q.rearElement();
        q.dequeue(rearEle);

        std::cout << "[" << current->index << ":" << current->data << "] ";

        if (current->left) q.enqueue(current->left);
        if (current->right) q.enqueue(current->right);
    }
    std::cout << std::endl;
}

// Lấy index nhỏ nhất
template <typename T>
int BST<T>::getMinIndex() const {
    if (!root) throw std::runtime_error("Cây rỗng");

    Node* current = root;
    while (current->left) {
        current = current->left;
    }
    return current->index;
}

// Lấy index lớn nhất
template <typename T>
int BST<T>::getMaxIndex() const {
    if (!root) throw std::runtime_error("Cây rỗng");

    Node* current = root;
    while (current->right) {
        current = current->right;
    }
    return current->index;
}

// Lấy data của node có index nhỏ nhất
template <typename T>
T BST<T>::getMinData() const {
    if (!root) throw std::runtime_error("Cây rỗng");

    Node* current = root;
    while (current->left) {
        current = current->left;
    }
    return current->data;
}

// Lấy data của node có index lớn nhất
template <typename T>
T BST<T>::getMaxData() const {
    if (!root) throw std::runtime_error("Cây rỗng");

    Node* current = root;
    while (current->right) {
        current = current->right;
    }
    return current->data;
}

// Chiều cao của cây (đệ quy)
template <typename T>
int BST<T>::heightRec(Node* node) const {
    if (!node) return -1;
    return 1 + std::max(heightRec(node->left), heightRec(node->right));
}

template <typename T>
int BST<T>::height() const {
    return heightRec(root);
}

// Đếm số node (đệ quy)
template <typename T>
int BST<T>::countNodesRec(Node* node) const {
    if (!node) return 0;
    return 1 + countNodesRec(node->left) + countNodesRec(node->right);
}

template <typename T>
int BST<T>::size() const {
    return countNodesRec(root);
}