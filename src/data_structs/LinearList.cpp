
#include "data_structs/LinearList.h"

// Constructor
template <typename T>
LinearList<T>::LinearList(int initialCapacity)
{
    n = 0;
    capacity = initialCapacity;
    nodes = new T[capacity];
}

// Destructor
template <typename T>
LinearList<T>::~LinearList()
{
    delete[] nodes;
}

// Kiểm tra rỗng
template <typename T>
bool LinearList<T>::isEmpty() const
{
    return n == 0;
}

// Kiểm tra đầy
template <typename T>
bool LinearList<T>::isFull() const
{
    return n == capacity;
}

// Thêm phần tử cuối
template <typename T>
bool LinearList<T>::push(const T &info)
{
    if (isFull())
    {
        std::cerr << "Lỗi: Không thể thêm phần tử!\n";
        return false;
    }
    nodes[n] = info;
    n++;
    return true;
}

// Thêm phần tử vào vị trí i
template <typename T>
bool LinearList<T>::insert(int i, const T &info)
{
    if (i < 0 || i > n || isFull())
    {
        std::cerr << "Lỗi: Không thể thêm phần tử!\n";
        return false;
    }

    // Dịch chuyển các phần tử
    for (int j = n; j > i; j--)
    {
        nodes[j] = nodes[j - 1];
    }

    nodes[i] = info;
    n++;
    return true;
}

// Xóa phần tử tại vị trí i
template <typename T>
bool LinearList<T>::remove(int i)
{
    if (i < 0 || i >= n || isEmpty())
    {
        std::cerr << "Lỗi: Không thể xóa phần tử!\n";
        return false;
    }

    // Dịch chuyển các phần tử
    for (int j = i; j < n - 1; j++)
    {
        nodes[j] = nodes[j + 1];
    }

    n--;
    return true;
}

// Truy cập phần tử tại vị trí i
template <typename T>
T &LinearList<T>::operator[](int i)
{
    if (i < 0 || i >= n)
    {
        throw std::out_of_range("Vị trí không hợp lệ!");
    }
    return nodes[i];
}

template <typename T>
const T &LinearList<T>::operator[](int i) const
{
    if (i < 0 || i >= n)
    {
        throw std::out_of_range("Vị trí không hợp lệ!");
    }
    return nodes[i];
}

// Tìm kiếm phần tử
template <typename T>
int LinearList<T>::search(const T &info) const
{
    for (int i = 0; i < n; i++)
    {
        if (nodes[i] == info)
        {
            return i;
        }
    }
    return -1;
}

template <typename T>
int LinearList<T>::size() const
{
    return n;
}

// Xóa toàn bộ danh sách
template <typename T>
void LinearList<T>::clear()
{
    n = 0;
}