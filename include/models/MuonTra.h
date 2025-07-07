#ifndef MUON_TRA_H
#define MUON_TRA_H

#include <string>

struct MuonTra {
    std::string ma_sach;
    std::string ngay_muon;
    std::string ngay_tra;
    int trang_thai;  // 0: borrowing, 1: returned, 2: lost

    MuonTra* next; // linked list
};

#endif
