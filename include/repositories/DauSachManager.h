#ifndef DAU_SACH_MANAGER_H
#define DAU_SACH_MANAGER_H

#include "models/DauSach.h"
#include "data_structs/LinearList.h"
#include "BaseManager.h"
#include <string>
#include <stdexcept>

class DauSachManager : public BaseManager<DauSach>
{
private:
    LinearList<DauSach*> list; // Danh sách tuyến tính chứa các con trỏ đến đầu sách

    bool readItem(std::istream &in, DauSach &obj) override;
    void writeItem(std::ostream &out, const DauSach &obj) const override;
    void saveItems() const override;

public:
    DauSachManager();
    ~DauSachManager();

    // Thêm một đầu sách mới (tự động sắp xếp theo ten_sach)
    bool addRecord(int ISBN, const std::string &ten_sach, int so_trang,
                   const std::string &tac_gia, int nam_xuat_ban, const std::string &the_loai);

    // Xóa một đầu sách theo ISBN
    bool removeRecord(int ISBN);

    // Cập nhật một đầu sách
    bool updateRecord(int ISBN, const std::string &ten_sach, int so_trang,
                      const std::string &tac_gia, int nam_xuat_ban, const std::string &the_loai);

    // Tìm kiếm một đầu sách theo ISBN
    DauSach* searchRecord(int ISBN) const;

    // Lấy tất cả đầu sách
    LinearList<DauSach> getAllRecords() const;


    // Kiểm tra xem đầu sách có tồn tại không
    bool isRecordExist(int ISBN) const;

    // Thêm một DanhMucSach vào đầu sách
    bool addDanhMucSach(int ISBN, DanhMucSach* danh_muc_sach);
};

#include "../../src/repositories/DauSachManager.cpp"

#endif // DAU_SACH_MANAGER_H