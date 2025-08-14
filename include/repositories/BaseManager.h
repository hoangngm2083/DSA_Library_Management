#ifndef BASE_MANAGER_H
#define BASE_MANAGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "data_structs/LinearList.h"

template <typename T>
class BaseManager {
protected:
    std::string filePath; // đường dẫn file dữ liệu

public:
    // Constructor nhận đường dẫn file
    explicit BaseManager(const std::string& path) : filePath(path) {}

    virtual ~BaseManager() = default; 
    // virtual destructor đảm bảo huỷ đúng thứ tự khi xoá qua con trỏ base

    // Đọc file
    LinearList<T> readFromFile() {
        std::ifstream fin(filePath);
        if (!fin) {
            throw std::runtime_error("Không thể mở file để đọc: " + filePath);
        }

        int so_records = 0;
        if (!(fin >> so_records)) {
            throw std::runtime_error("Lỗi khi đọc số lượng bản ghi từ file: " + filePath);
        }

        // Khởi tạo LinearList với kích thước phù hợp
        LinearList<T> items(so_records);

        T obj;
        for (int i = 0; i < so_records; ++i) {
            if (!readItem(fin, obj)) {
                throw std::runtime_error("Lỗi khi đọc bản ghi thứ " + std::to_string(i+1));
            }
            items.push(obj);
        }

        return items; // RVO sẽ tránh copy
    }

    // Ghi file
    void writeToFile(const LinearList<T>& items) const {
        std::ofstream fout(filePath);
        if (!fout) {
            throw std::runtime_error("Không thể mở file để ghi: " + filePath);
        }

        // Ghi số lượng bản ghi ở dòng đầu
        fout << items.size() << "\n";

        // Ghi từng đối tượng
        for (int i = 0; i < items.size(); ++i) {
            writeItem(fout, items[i]);
        }
    }

protected:
    virtual bool readItem(std::istream& in, T& obj) = 0;
    virtual void writeItem(std::ostream& out, const T& obj) const = 0;
};

#endif
