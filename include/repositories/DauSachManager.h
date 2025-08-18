#ifndef DAU_SACH_MANAGER_H
#define DAU_SACH_MANAGER_H

#include "models/DauSach.h"
#include "data_structs/LinearList.h"
#include "BaseManager.h"
#include <string>
#include <stdexcept>
#include "repositories/IdManager.h"

class DauSachManager : public BaseManager<DauSach>
{
private:
    LinearList<DauSach*> list; // Danh sách tuyến tính chứa các con trỏ đến đầu sách

    bool readItem(std::istream &in, DauSach &obj) override;
    void writeItem(std::ostream &out, const DauSach &obj) override;
    void saveItems() override;
    void loadItems() override;

public:
    DauSachManager();
    ~DauSachManager();

    // Thêm một đầu sách mới (tự động sắp xếp theo ten_sach)
    int addRecord( const std::string &ten_sach, int so_trang,
                   const std::string &tac_gia, int nam_xuat_ban, const std::string &the_loai);

    // Xóa một đầu sách theo ISBN
    bool removeRecord(int ISBN);

    // Cập nhật một đầu sách
    bool updateRecord(int ISBN, const std::string &ten_sach, int so_trang,
                      const std::string &tac_gia, int nam_xuat_ban, const std::string &the_loai);

    // Tìm kiếm một đầu sách theo ISBN
    DauSach* searchRecord(int ISBN);

    LinearList<DauSach> searchLikeTenSach(const std::string &keyword);

    // Lấy tất cả đầu sách
    LinearList<DauSach> getAllRecords();


    // Kiểm tra xem đầu sách có tồn tại không
    bool isRecordExist(int ISBN);

    // Thêm một DanhMucSach vào đầu sách
    bool addDanhMucSach(int ISBN, DanhMucSach* danh_muc_sach);
};

extern DauSachManager dau_sach_mgr;


// #include "../../src/repositories/DauSachManager.cpp"

#endif // DAU_SACH_MANAGER_H