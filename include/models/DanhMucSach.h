#ifndef DANH_MUC_SACH_H
#define DANH_MUC_SACH_H

#include <string>

struct DanhMucSach
{
    std::string ma_sach; // unique
    int trang_thai;      // 0: available, 1: borrowed, 2: retired
    std::string vi_tri;
    int ISBN;
};

#endif
