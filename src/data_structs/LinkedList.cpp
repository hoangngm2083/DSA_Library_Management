#include "data_structs/LinkedList.h"

// Constructor
template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), size(0) {}

// Destructor
template <typename T>
LinkedList<T>::~LinkedList()
{
    clear();
}

// Kiểm tra rỗng
template <typename T>
bool LinkedList<T>::isEmpty() const
{
    return head == nullptr;
}

// Lấy kích thước
template <typename T>
int LinkedList<T>::getSize() const
{
    return size;
}

// Thêm vào đầu
template <typename T>
void LinkedList<T>::insertFirst(const T &value)
{
    Node *newNode = new Node(value);
    newNode->next = head;
    head = newNode;
    size++;
}

// Thêm vào sau một node
template <typename T>
void LinkedList<T>::insertAfter(Node *prevNode, const T &value)
{
    if (prevNode == nullptr)
    {
        std::cerr << "Lỗi: Node trước không thể là null\n";
        return;
    }

    Node *newNode = new Node(value);
    newNode->next = prevNode->next;
    prevNode->next = newNode;
    size++;
}

// Thêm vào cuối
template <typename T>
void LinkedList<T>::insertLast(const T &value)
{
    if (isEmpty())
    {
        insertFirst(value);
        return;
    }

    Node *current = head;
    while (current->next != nullptr)
    {
        current = current->next;
    }

    Node *newNode = new Node(value);
    current->next = newNode;
    size++;
}

// Xóa đầu
template <typename T>
void LinkedList<T>::deleteFirst()
{
    if (isEmpty())
    {
        std::cerr << "Lỗi: Danh sách rỗng\n";
        return;
    }

    Node *temp = head;
    head = head->next;
    delete temp;
    size--;
}

// Xóa sau một node
template <typename T>
void LinkedList<T>::deleteAfter(Node *prevNode)
{
    if (prevNode == nullptr || prevNode->next == nullptr)
    {
        std::cerr << "Lỗi: Không có node để xóa\n";
        return;
    }

    Node *temp = prevNode->next;
    prevNode->next = temp->next;
    delete temp;
    size--;
}

// Xóa node chứa giá trị value
template <typename T>
void LinkedList<T>::deleteValue(const T &value)
{
    if (isEmpty())
    {
        std::cerr << "Lỗi: Danh sách rỗng\n";
        return;
    }

    // Special case: head node
    if (std::is_pointer<T>::value)
    {
        if (*head->data == *value)
        {
            Node *temp = head;
            head = head->next;
            delete temp->data; // Delete the DanhMucSach* data
            delete temp;       // Delete the node
            size--;
            return;
        }
    }
    else
    {
        if (head->data == value)
        {
            deleteFirst();
            return;
        }
    }

    Node *current = head;
    while (current->next != nullptr)
    {
        if (std::is_pointer<T>::value)
        {
            if (*(current->next->data) == *value)
            {
                Node *temp = current->next;
                current->next = temp->next;
                delete temp->data; // Delete the DanhMucSach* data
                delete temp;       // Delete the node
                size--;
                return;
            }
        }
        else
        {
            if (current->next->data == value)
            {
                deleteAfter(current);
                return;
            }
        }
        current = current->next;
    }
}

// Xóa toàn bộ danh sách
template <typename T>
void LinkedList<T>::clear()
{
    while (!isEmpty())
    {
        deleteFirst();
    }
}

// Tìm kiếm
template <typename T>
T LinkedList<T>::search(const T &value) const
{
    Node *current = head;
    while (current != nullptr)
    {
        if (std::is_pointer<T>::value)
        {
            // So sánh giá trị mà con trỏ trỏ đến
            if (*(current->data) == *value)
            {
                return current->data;
            }
        }
        else
        {
            // So sánh trực tiếp giá trị
            if (current->data == value)
            {
                return current->data;
            }
        }
        current = current->next;
    }
    return nullptr;
}
// Sắp xếp (selection sort)
template <typename T>
void LinkedList<T>::sort()
{
    if (isEmpty() || head->next == nullptr)
    {
        return;
    }

    Node *current = head;
    while (current != nullptr)
    {
        Node *minNode = current;
        Node *temp = current->next;

        while (temp != nullptr)
        {
            if (temp->data < minNode->data)
            {
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
typename LinkedList<T>::Node *LinkedList<T>::getHead() const
{
    return head;
}