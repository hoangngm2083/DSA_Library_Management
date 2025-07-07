#ifndef THE_DOC_GIA_H
#define THE_DOC_GIA_H

#include <string>

#include "MuonTra.h"

struct TheDocGia {
    int ma_the;
    std::string ho;
    std::string ten;
    std::string phai; // Nam/Nữ
    int trang_thai;         // 0: locked, 1: active
    // pointer to linked list of BorrowRecord
    MuonTra* danh_sach_muon_tra;

    TheDocGia* left;
    TheDocGia* right;  // BST
};

#endif
