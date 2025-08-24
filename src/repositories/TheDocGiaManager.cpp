#include "repositories/TheDocGiaManager.h"

TheDocGiaManager tdg_mgr;

TheDocGiaManager::TheDocGiaManager() : BaseManager("data/thedocgia.txt")
{
    this->loadItems();
}

void TheDocGiaManager::loadItems()
{
    bst.clear();
    auto items = this->readFromFile();
    for (int i = 0; i < items.size(); i++)
    {
        TheDocGia *itemPtr = new TheDocGia(items[i]);
        bst.insert(itemPtr, itemPtr->ma_the);
    }
}

TheDocGiaManager::~TheDocGiaManager()
{
    this->saveItems();
    this->bst.clear();
}
bool TheDocGiaManager::readItem(std::istream &in, TheDocGia &obj)
{
    // Đọc lần lượt các trường từ file
    if (!(in >> obj.ma_the))
        return false;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // bỏ phần dư của dòng

    if (!std::getline(in, obj.ho))
        return false;
    if (!std::getline(in, obj.ten))
        return false;
    if (!(in >> obj.phai))
        return false;
    if (!(in >> obj.trang_thai))
        return false;

    // Bỏ phần dư của dòng trước khi đọc bản ghi tiếp theo
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Khởi tạo danh sách mượn trả rỗng
    obj.danh_sach_muon_tra.clear();

    return true;
}

void TheDocGiaManager::writeItem(std::ostream &out, const TheDocGia &obj)
{

    // Ghi đúng format nhiều dòng
    out << obj.ma_the << "\n"
        << obj.ho << "\n"
        << obj.ten << "\n"
        << obj.phai << "\n"
        << obj.trang_thai << "\n";
}

int TheDocGiaManager::addCard(const std::string &ho, const std::string &ten,
                              int phai, int trang_thai)
{
    this->loadItems();
    // Validate giới tính
    if (phai != 0 && phai != 1)
    {
        throw std::invalid_argument("Phái chỉ nhận giá trị '0: Nam' hoặc '1: Nữ'");
    }

    // Validate trạng thái
    if (trang_thai != 0 && trang_thai != 1)
    {
        throw std::invalid_argument("Trạng thái chỉ nhận giá trị 0 (khóa) hoặc 1 (hoạt động)");
    }

    // Tạo mã thẻ mới
    int ma_the = id_mgr.next();
    while (isIdExist(ma_the))
    {
        ma_the = id_mgr.next();
    }

    // Tạo thẻ mới
    TheDocGia *newCard = new TheDocGia{
        ma_the,
        ho,
        ten,
        phai,
        trang_thai};

    // Thêm vào BST
    this->bst.insert(newCard, newCard->ma_the);
    this->saveItems();
    return ma_the;
}

bool TheDocGiaManager::removeCard(int maThe)
{
    if (!isIdExist(maThe))
    {
        return false;
    }

    this->bst.remove(maThe);
    this->saveItems();
    return true;
}

bool TheDocGiaManager::updateCard(int maThe, const std::string &ho, const std::string &ten,
                                  int phai, int trang_thai)
{
    TheDocGia *card = searchCard(maThe);
    if (!card)
    {
        return false;
    }

    // Validate giới tính
    if (phai != 0 && phai != 1)
    {
        throw std::invalid_argument("Phái chỉ nhận giá trị '0: Nam' hoặc '1: Nữ'");
    }

    // Validate trạng thái
    if (trang_thai != 0 && trang_thai != 1)
    {
        throw std::invalid_argument("Trạng thái chỉ nhận giá trị 0 (khóa) hoặc 1 (hoạt động)");
    }

    card->ho = ho;
    card->ten = ten;
    card->phai = phai;
    card->trang_thai = trang_thai;
    this->saveItems();
    return true;
}

TheDocGia *TheDocGiaManager::searchCard(int maThe)
{
    this->loadItems();
    return this->bst.getData(maThe);
}

LinearList<TheDocGia> TheDocGiaManager::getAllCards()
{
    this->loadItems();
    LinearList<TheDocGia> result;

    this->bst.inOrder([&result](TheDocGia *value)
                      {
                          result.push(*value); // copy dữ liệu ra list
                      });

    return result; // trả về bản sao an toàn
}

// void TheDocGiaManager::inOrderRec(TheDocGia* node, LinearList<TheDocGia*>& result) const {
//     if (node) {
//         inOrderRec(node->left, result);
//         result.push(node);
//         inOrderRec(node->right, result);
//     }
// }

// TheDocGia* TheDocGiaManager::findMin(TheDocGia* node) const {
//     while (node && node->left) {
//         node = node->left;
//     }
//     return node;
// }

bool TheDocGiaManager::isIdExist(int maThe)
{
    this->loadItems();
    return this->bst.search(maThe);
}

void TheDocGiaManager::saveItems()
{

    LinearList<TheDocGia> result;

    this->bst.inOrder([&result](TheDocGia *value)
                      {
                          result.push(*value); // copy dữ liệu ra list
                      });

    this->writeToFile(result);
};
