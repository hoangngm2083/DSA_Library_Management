#include "models/DauSach.h"
#include "repositories/DanhMucSachManager.h"

// Copy constructor: tạo bản sao node (deep-copy nodes) nhưng không copy ownership của DanhMucSach*
DauSach::DauSach(const DauSach& other)
    : ISBN(other.ISBN),
      ten_sach(other.ten_sach),
      so_trang(other.so_trang),
      tac_gia(other.tac_gia),
      nam_xuat_ban(other.nam_xuat_ban),
      the_loai(other.the_loai),
      dms(nullptr)
{
    if (other.dms) {
        // LinkedList copy ctor sẽ tạo node mới; data (DanhMucSach*) được shallow-copy (ok)
        dms = new LinkedList<DanhMucSach*>( *other.dms );
    }
}

DauSach& DauSach::operator=(const DauSach& other)
{
    if (this != &other) {
        ISBN = other.ISBN;
        ten_sach = other.ten_sach;
        so_trang = other.so_trang;
        tac_gia = other.tac_gia;
        nam_xuat_ban = other.nam_xuat_ban;
        the_loai = other.the_loai;

        // Xóa dms cũ (chỉ node), sau đó sao chép dms mới (nếu có)
        if (dms) {
            delete dms;
            dms = nullptr;
        }
        if (other.dms) {
            dms = new LinkedList<DanhMucSach*>( *other.dms );
        }
    }
    return *this;
}

// Move constructor: chuyển ownership của con trỏ dms
DauSach::DauSach(DauSach&& other) noexcept
    : ISBN(other.ISBN),
      ten_sach(std::move(other.ten_sach)),
      so_trang(other.so_trang),
      tac_gia(std::move(other.tac_gia)),
      nam_xuat_ban(other.nam_xuat_ban),
      the_loai(std::move(other.the_loai)),
      dms(other.dms)
{
    other.dms = nullptr;
}

// Move assignment
DauSach& DauSach::operator=(DauSach&& other) noexcept
{
    if (this != &other) {
        if (dms) { delete dms; dms = nullptr; }

        ISBN = other.ISBN;
        ten_sach = std::move(other.ten_sach);
        so_trang = other.so_trang;
        tac_gia = std::move(other.tac_gia);
        nam_xuat_ban = other.nam_xuat_ban;
        the_loai = std::move(other.the_loai);

        dms = other.dms;
        other.dms = nullptr;
    }
    return *this;
}

// loadDanhMucSach() giữ nguyên (nhưng tốt nhất dùng move hoặc new với copy ctor của LinkedList)
void DauSach::loadDanhMucSach()
{
    if (dms != nullptr)
    {
        delete dms;
        dms = nullptr;
    }

    DanhMucSachManager danh_muc_sach;
    // nếu searchRecords trả về LinkedList<T> by value:
    LinkedList<DanhMucSach*> tmp = danh_muc_sach.searchRecords(this->ISBN);
    if (!tmp.isEmpty()) {
        dms = new LinkedList<DanhMucSach*>( std::move(tmp) ); // move vào heap
    }
}
