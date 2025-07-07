#ifndef DAU_SACH_H
#define DAU_SACH_H

#include <string>
#include "DanhMucSach.h"

struct DauSach {
    std::string ISBN;
    std::string ten_sach;
    int so_trang;
    std::string tac_gia;
    int nam_xuat_ban;
    std::string the_loai;
    // pointer to linked list of DanhMucSach
    DanhMucSach* danh_muc_sach;
};

#endif
