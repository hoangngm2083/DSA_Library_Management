#ifndef THE_DOC_GIA_H
#define THE_DOC_GIA_H

#include <string>

#include "MuonTra.h"
#include "data_structs/LinkedList.h"

struct TheDocGia
{
    int ma_the;
    std::string ho;
    std::string ten;
    int phai;       // 0: Nam,1: Nữ
    int trang_thai; // 0: locked, 1: active
    // pointer to linked list of danh_sach_muon_tra
    LinkedList<MuonTra *> danh_sach_muon_tra;
};

#endif
