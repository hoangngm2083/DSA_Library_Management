#include "repositories/DanhMucSachManager.h"

DanhMucSachManager::DanhMucSachManager() : BaseManager("data/danhmucsach.txt")
{
    auto items = this->readFromFile();
    for (int i = 0; i < items.size(); i++)
    {
        DanhMucSach *itemPtr = new DanhMucSach(items[i]);
        list.insertLast(itemPtr);
    }
}

DanhMucSachManager::~DanhMucSachManager()
{
    this->saveItems();
    list.clear();
}

bool DanhMucSachManager::readItem(std::istream &in, DanhMucSach &obj)
{
    if (!std::getline(in, obj.ma_sach))
        return false;
    this->trimCR(obj.ma_sach);

    if (!(in >> obj.trang_thai))
        return false;
    if (!(in >> obj.vi_tri))
        return false;
    this->trimCR(obj.vi_tri); // vi_tri có thể có \r nếu đọc từ file

    if (!(in >> obj.ISBN))
        return false;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return true;
}

void DanhMucSachManager::writeItem(std::ostream &out, const DanhMucSach &obj) const
{
    // Write fields to file
    out << obj.ma_sach << "\n"
        << obj.trang_thai << "\n"
        << obj.vi_tri << "\n"
        << obj.ISBN << "\n";
}

bool DanhMucSachManager::addRecord(const std::string &ma_sach, int trang_thai,
                                    const std::string &vi_tri, int ISBN)
{
    // Validate trang_thai
    if (trang_thai < 0 || trang_thai > 2)
    {
        throw std::invalid_argument("Trạng thái chỉ nhận giá trị 0 (có sẵn), 1 (đã mượn), hoặc 2 (thanh lý)");
    }

    // Check if record already exists
    if (isRecordExist(ma_sach))
    {
        return false;
    }

    // Create new book record
    DanhMucSach *newRecord = new DanhMucSach{
        ma_sach,
        trang_thai,
        vi_tri,
        ISBN};

    // Add to linked list
    list.insertLast(newRecord);
    return true;
}

bool DanhMucSachManager::removeRecord(const std::string &ma_sach)
{
    auto record = this->searchRecord(ma_sach);
    if (record == nullptr)
    {
        std::cerr << "Không tìm thấy bản ghi để xóa.\n";
        return false; // Hoặc xử lý khác nếu không tìm thấy
    }
    this->list.deleteValue(record); // Chỉ cần truyền con trỏ record
    return true;                    // Trả về true nếu xóa thành công
}

bool DanhMucSachManager::updateRecord(const std::string &ma_sach, int trang_thai,
                                       const std::string &vi_tri, int ISBN)
{
    DanhMucSach *record = searchRecord(ma_sach);
    if (!record)
    {
        return false;
    }

    // Validate trang_thai
    if (trang_thai < 0 || trang_thai > 2)
    {
        throw std::invalid_argument("Trạng thái chỉ nhận giá trị 0 (có sẵn), 1 (đã mượn), hoặc 2 (thanh lý)");
    }

    // Update fields
    record->trang_thai = trang_thai;
    record->vi_tri = vi_tri;
    record->ISBN = ISBN;
    return true;
}

 LinkedList<DanhMucSach *> DanhMucSachManager::searchRecords(int ISBN) const{
    LinkedList<DanhMucSach *> result;
    this->list.traverse([&result, ISBN](DanhMucSach *value)
                        { 
                            if(value->ISBN == ISBN)
                            {
                                result.insertLast(value);
                            } });
    return result;
 };

DanhMucSach *DanhMucSachManager::searchRecord(const std::string &ma_sach) const
{
    DanhMucSach temp;
    temp.ma_sach = ma_sach;

    // Sử dụng phương thức search của LinkedList
    return list.search(&temp); // Truyền địa chỉ của temp
}

LinearList<DanhMucSach> DanhMucSachManager::getAllRecords() const
{
    LinearList<DanhMucSach> result;
    this->list.traverse([&result](DanhMucSach *value)
                        { if (value != nullptr) // Add null check
                            {
                                result.push(*value);
                            } });
    return result;
}

bool DanhMucSachManager::isRecordExist(const std::string &ma_sach) const
{
    return searchRecord(ma_sach) != nullptr;
}

void DanhMucSachManager::saveItems() const
{
    LinearList<DanhMucSach> items = getAllRecords();
    this->writeToFile(items);
}