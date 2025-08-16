#ifndef DANH_MUC_SACH_MANAGER_H
#define DANH_MUC_SACH_MANAGER_H

#include "models/DanhMucSach.h"
#include "data_structs/LinkedList.h"
#include "data_structs/LinearList.h"
#include "BaseManager.h"
#include <string>
#include <stdexcept>
#include <limits>

class DanhMucSachManager : public BaseManager<DanhMucSach>
{
private:
    LinkedList<DanhMucSach *> list; // Singly linked list to store DanhMucSach pointers

    bool readItem(std::istream &in, DanhMucSach &obj) override;
    void writeItem(std::ostream &out, const DanhMucSach &obj) const override;
    void saveItems() const override;

public:
    DanhMucSachManager();
    ~DanhMucSachManager();

    // Add a new book record
    bool addRecord(const std::string &ma_sach, int trang_thai,
                   const std::string &vi_tri, int ISBN);

    // Remove a book record by ma_sach
    bool removeRecord(const std::string &ma_sach);

    // Update a book record
    bool updateRecord(const std::string &ma_sach, int trang_thai,
                      const std::string &vi_tri, int ISBN);

    // Search for a book record by ma_sach
    LinkedList<DanhMucSach *> searchRecords(int ISBN) const;
    DanhMucSach *searchRecord(const std::string &ma_sach) const;

    // Get all book records
    LinearList<DanhMucSach> getAllRecords() const;

    // Check if a book record exists
    bool isRecordExist(const std::string &ma_sach) const;
};

// #include "../../src/repositories/DanhMucSachManager.cpp"

#endif // DANH_MUC_SACH_MANAGER_H