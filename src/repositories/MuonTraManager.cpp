#include "repositories/MuonTraManager.h"

MuonTraManager muontra_mgr;

MuonTraManager::MuonTraManager() : BaseManager("data/muontra.txt")
{
    this->loadItems();
}

MuonTraManager::~MuonTraManager()
{
    this->saveItems();
    list.clear();
}

bool MuonTraManager::readItem(std::istream &in, MuonTra &obj)
{
    if (!std::getline(in, obj.ma_sach))
        return false;
    this->trimCR(obj.ma_sach);

    if (!std::getline(in, obj.ngay_muon))
        return false;
    this->trimCR(obj.ngay_muon);

    if (!std::getline(in, obj.ngay_tra))
        return false;
    this->trimCR(obj.ngay_tra);

    if (!(in >> obj.trang_thai))
        return false;
    if (!(in >> obj.ma_the))
        return false;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return true;
}

void MuonTraManager::writeItem(std::ostream &out, const MuonTra &obj)
{
    // Write fields to file
    out << obj.ma_sach << "\n"
        << obj.ngay_muon << "\n"
        << obj.ngay_tra << "\n"
        << obj.trang_thai << "\n"
        << obj.ma_the << "\n";
}

bool MuonTraManager::addRecord(const std::string &ma_sach, const std::string &ngay_muon,
                               const std::string &ngay_tra, int trang_thai, int ma_the)
{
    this->loadItems();
    // Validate trang_thai
    if (trang_thai < 0 || trang_thai > 2)
    {
        throw std::invalid_argument("Trạng thái chỉ nhận giá trị 0 (đang mượn), 1 (đã trả), hoặc 2 (mất sách)");
    }

    // Check if record already exists
    if (isRecordExist(ma_sach, ngay_muon))
    {
        return false;
    }

    // Create new borrowing record
    MuonTra *newRecord = new MuonTra{
        ma_sach,
        ngay_muon,
        ngay_tra,
        trang_thai,
        ma_the};

    // Add to linked list
    list.insertLast(newRecord);
    this->saveItems();
    return true;
}

bool MuonTraManager::removeRecord(const std::string &ma_sach, const std::string &ngay_muon)
{
    auto record = this->searchRecord(ma_sach, ngay_muon);
    if (record == nullptr)
    {
        std::cerr << "Không tìm thấy bản ghi để xóa.\n";
        return false; // Hoặc xử lý khác nếu không tìm thấy
    }
    this->list.deleteValue(record); // Chỉ cần truyền con trỏ record
    this->saveItems();
    return true; // Trả về true nếu xóa thành công
}

bool MuonTraManager::updateRecord(const std::string &ma_sach, const std::string &ngay_muon, const std::string &ngay_tra, int trang_thai)
{
    MuonTra *record = searchRecord(ma_sach, ngay_muon);
    if (!record)
    {
        return false;
    }

    // Validate trang_thai
    if (trang_thai < 0 || trang_thai > 2)
    {
        throw std::invalid_argument("Trạng thái chỉ nhận giá trị 0 (đang mượn), 1 (đã trả), hoặc 2 (mất sách)");
    }

    // Update fields
    record->ngay_tra = ngay_tra;
    record->trang_thai = trang_thai;
    this->saveItems();
    return true;
}

MuonTra *MuonTraManager::searchRecord(const std::string &ma_sach, const std::string &ngay_muon)
{
    this->loadItems();
    MuonTra temp;
    temp.ma_sach = ma_sach;
    temp.ngay_muon = ngay_muon;
    // Sử dụng phương thức search của LinkedList
    return list.search(&temp); // Truyền địa chỉ của temp
}

LinkedList<MuonTra *> MuonTraManager::searchRecords(int ma_the)
{
    this->loadItems();
    LinkedList<MuonTra *> result;
    this->list.traverse([&result, ma_the](MuonTra *value)
                        { 
                            if(value->ma_the == ma_the)
                            {
                                result.insertLast(value);
                            } });
    return result;
}

LinearList<MuonTra> MuonTraManager::getAllRecords()
{
    this->loadItems();
    LinearList<MuonTra> result;
    this->list.traverse([&result](MuonTra *value)
                        { result.push(*value); });
    return result;
}

bool MuonTraManager::isRecordExist(const std::string &ma_sach, const std::string &ngay_muon)
{
    return searchRecord(ma_sach, ngay_muon) != nullptr;
}

bool MuonTraManager::isBorrowing(const std::string &ma_sach)
{
    this->loadItems();
    bool isBorrowing = false;
    this->list.traverse([&isBorrowing, &ma_sach](MuonTra *value)
                        { 
        if (value->ma_sach == ma_sach && value->trang_thai != 1) {
            isBorrowing = true;
        } });
    return isBorrowing;
}

void MuonTraManager::saveItems()
{
    LinearList<MuonTra> result;
    this->list.traverse([&result](MuonTra *value)
                        { result.push(*value); });
    this->writeToFile(result);
}

void MuonTraManager::loadItems()
{
    list.clear();
    auto items = this->readFromFile();
    for (int i = 0; i < items.size(); i++)
    {
        MuonTra *itemPtr = new MuonTra(items[i]);
        list.insertLast(itemPtr);
    }
}
