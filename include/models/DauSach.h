#ifndef DAU_SACH_H
#define DAU_SACH_H

#include <string>
#include "DanhMucSach.h"
#include "data_structs/LinkedList.h"

struct DauSach
{
    int ISBN;
    std::string ten_sach;
    int so_trang;
    std::string tac_gia;
    int nam_xuat_ban;
    std::string the_loai;

    // pointer to linked list of DanhMucSach
    LinkedList<DanhMucSach *> danh_muc_sach; // Danh sách đầu sách luôn tăng dần theo tên sách
};

#endif
