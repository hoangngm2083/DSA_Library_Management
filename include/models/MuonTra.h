#ifndef MUON_TRA_H
#define MUON_TRA_H

#include <string>

struct MuonTra
{
    std::string ma_sach;
    std::string ngay_muon;
    std::string ngay_tra;
    int trang_thai; // 0: borrowing, 1: returned, 2: lost
    int ma_the;

    // Định nghĩa toán tử ==
    bool operator==(const MuonTra &other) const
    {
        return (this->ma_sach == other.ma_sach) && (this->ngay_muon == other.ngay_muon);
    }
};

#endif
