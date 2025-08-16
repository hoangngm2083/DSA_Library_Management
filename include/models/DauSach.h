#ifndef DAU_SACH_H
#define DAU_SACH_H

#include <string>
#include "data_structs/LinkedList.h"
#include "models/DanhMucSach.h"

struct DauSach
{
    int ISBN;
    std::string ten_sach;
    int so_trang;
    std::string tac_gia;
    int nam_xuat_ban;
    std::string the_loai;
    LinkedList<DanhMucSach*> *dms; // con trỏ đến danh sách (LinkedList sẽ KHÔNG xóa data)

    // Constructor
    DauSach() : ISBN(0), so_trang(0), nam_xuat_ban(0), dms(nullptr) {}

    // Rule of Five: copy / move / assign
    DauSach(const DauSach& other);
    DauSach& operator=(const DauSach& other);
    DauSach(DauSach&& other) noexcept;
    DauSach& operator=(DauSach&& other) noexcept;

    // Destructor
    ~DauSach()
    {
        // LinkedList::~LinkedList() sẽ chỉ xóa node (theo chỉnh sửa trước)
        // ở đây chúng ta xóa con trỏ dms (chỉ node), không xóa DanhMucSach* bên trong
        if (dms != nullptr)
        {
            delete dms;
            dms = nullptr;
        }
    }

    void loadDanhMucSach();

    bool operator==(const DauSach &other) const { return this->ISBN == other.ISBN; }
    bool operator<(const DauSach &other) const { return this->ten_sach < other.ten_sach; }
};

#endif // DAU_SACH_H
