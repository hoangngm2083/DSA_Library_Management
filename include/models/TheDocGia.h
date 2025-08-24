#ifndef THE_DOC_GIA_H
#define THE_DOC_GIA_H

#include <string>

#include "models/MuonTra.h"
#include "data_structs/LinkedList.h"

struct TheDocGia
{
    int ma_the;
    std::string ho;
    std::string ten;
    int phai;       // 0: Nam,1: Nữ
    int trang_thai; // 0: locked, 1: active
    LinkedList<MuonTra *> danh_sach_muon_tra;

    // Default constructor (cần cho LinearList, BaseManager...)
    TheDocGia() : ma_the(0), phai(0), trang_thai(1) {}

    // Constructor tham số (cần cho addCard)
    TheDocGia(int ma_the, const std::string &ho,
              const std::string &ten, int phai, int trang_thai)
        : ma_the(ma_the), ho(ho), ten(ten),
          phai(phai), trang_thai(trang_thai) {}

    // Copy constructor (deep copy danh_sach_muon_tra)
    TheDocGia(const TheDocGia &other)
        : ma_the(other.ma_the),
          ho(other.ho),
          ten(other.ten),
          phai(other.phai),
          trang_thai(other.trang_thai)
    {
        danh_sach_muon_tra.clear();
        other.danh_sach_muon_tra.traverse([&](MuonTra *mt)
                                          {
                                              danh_sach_muon_tra.insertLast(mt); // shallow copy con trỏ
                                          });
    }
};

#endif
