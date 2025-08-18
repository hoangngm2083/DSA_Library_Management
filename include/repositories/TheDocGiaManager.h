#ifndef THE_DOC_GIA_MANAGER_H
#define THE_DOC_GIA_MANAGER_H

#include "models/TheDocGia.h"
#include "data_structs/LinearList.h"
#include "data_structs/BST.h"
#include "BaseManager.h"
#include <algorithm>
#include <stdexcept>
#include <string>
#include <limits>

#include <random>

class TheDocGiaManager : public BaseManager<TheDocGia>
{
private:
    BST<TheDocGia *> bst;

    // Hàm tạo ID ngẫu nhiên không trùng
    int generateRandomId();
    bool readItem(std::istream &in, TheDocGia &obj) override;
    void writeItem(std::ostream &out, const TheDocGia &obj) override;
    void saveItems() override;
    void loadItems() override;

public:
    TheDocGiaManager();

    ~TheDocGiaManager();

    // Thêm thẻ độc giả mới
    int addCard(const std::string &ho, const std::string &ten, int phai, int trang_thai);

    // Xóa thẻ độc giả
    bool removeCard(int maThe);

    // Hiệu chỉnh thông tin thẻ
    bool updateCard(int maThe, const std::string &ho, const std::string &ten,
                    int phai, int trang_thai);

    // Tìm kiếm thẻ theo mã
    TheDocGia *searchCard(int maThe) ;

    // LinearList<TheDocGia*> searchCards(int maThe[]) ;

    // Lấy danh sách tất cả thẻ (in-order)
    LinearList<TheDocGia> getAllCards() ;

    bool isIdExist(int maThe) ;
};

// #include "../../src/repositories/TheDocGiaManager.cpp"

#endif // THE_DOC_GIA_MANAGER_H