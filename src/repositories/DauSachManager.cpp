#include "repositories/DauSachManager.h"

DauSachManager::DauSachManager() : BaseManager("data/dausach.txt")
{
    auto items = this->readFromFile();
    for (int i = 0; i < items.size(); i++)
    {
        DauSach* newItem = new DauSach(items[i]); // Sao chép và cấp phát mới
        list.push(newItem);
    }
    for (int i = 0; i < list.size() - 1; i++)
    {
        for (int j = i + 1; j < list.size(); j++)
        {
            if (*list[j] < *list[i]) // So sánh qua con trỏ
            {
                DauSach* temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }
}

DauSachManager::~DauSachManager()
{
    this->saveItems();
    // Giải phóng bộ nhớ cho tất cả các con trỏ trong list
    for (int i = 0; i < list.size(); i++)
    {
        delete list[i];
    }
}

bool DauSachManager::readItem(std::istream &in, DauSach &obj)
{
    if (!(in >> obj.ISBN))
        return false;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (!std::getline(in, obj.ten_sach))
        return false;
    this->trimCR(obj.ten_sach);

    if (!(in >> obj.so_trang))
        return false;

    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (!std::getline(in, obj.tac_gia))
        return false;
    this->trimCR(obj.tac_gia);

    if (!(in >> obj.nam_xuat_ban))
        return false;

    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (!std::getline(in, obj.the_loai))
        return false;
    this->trimCR(obj.the_loai);

    // Khởi tạo dms là nullptr khi đọc từ file
    obj.dms = nullptr;
    return true;
}

void DauSachManager::writeItem(std::ostream &out, const DauSach &obj) const
{
    out << obj.ISBN << "\n"
        << obj.ten_sach << "\n"
        << obj.so_trang << "\n"
        << obj.tac_gia << "\n"
        << obj.nam_xuat_ban << "\n"
        << obj.the_loai << "\n";
}

bool DauSachManager::addRecord(int ISBN, const std::string &ten_sach, int so_trang,
                               const std::string &tac_gia, int nam_xuat_ban, const std::string &the_loai)
{
    if (isRecordExist(ISBN))
    {
        return false;
    }
    if (list.size() >= 10000)
    {
        throw std::runtime_error("Danh sách đầu sách đã đạt tối đa 10,000!");
    }

    DauSach* newRecord = new DauSach(); // Cấp phát mới
    newRecord->ISBN = ISBN;
    newRecord->ten_sach = ten_sach;
    newRecord->so_trang = so_trang;
    newRecord->tac_gia = tac_gia;
    newRecord->nam_xuat_ban = nam_xuat_ban;
    newRecord->the_loai = the_loai;
    newRecord->dms = nullptr; // Khởi tạo dms là nullptr

    if (list.isEmpty())
    {
        list.push(newRecord);
    }
    else
    {
        for (int i = 0; i < list.size(); i++)
        {
            if (*newRecord < *list[i]) // So sánh qua con trỏ
            {
                list.insert(i, newRecord);
                return true;
            }
        }
        list.push(newRecord);
    }
    return true;
}

bool DauSachManager::removeRecord(int ISBN)
{
    for (int i = 0; i < list.size(); i++)
    {
        if (list[i]->ISBN == ISBN) // Sử dụng -> vì là con trỏ
        {
            // Giải phóng danh sách DanhMucSach nếu tồn tại
            if (list[i]->dms != nullptr)
            {
                list[i]->dms->clear();
                delete list[i]->dms;
            }
            delete list[i]; // Giải phóng bộ nhớ của DauSach
            return list.remove(i); // Xóa con trỏ khỏi list
        }
    }
    std::cerr << "Không tìm thấy đầu sách với ISBN: " << ISBN << "\n";
    return false;
}

bool DauSachManager::updateRecord(int ISBN, const std::string &ten_sach, int so_trang,
                                  const std::string &tac_gia, int nam_xuat_ban, const std::string &the_loai)
{
    for (int i = 0; i < list.size(); i++)
    {
        if (list[i]->ISBN == ISBN) // Sử dụng -> vì là con trỏ
        {
            LinkedList<DanhMucSach*>* old_dms = list[i]->dms; // Lưu lại dms
            list[i]->ten_sach = ten_sach;
            list[i]->so_trang = so_trang;
            list[i]->tac_gia = tac_gia;
            list[i]->nam_xuat_ban = nam_xuat_ban;
            list[i]->the_loai = the_loai;
            list[i]->dms = old_dms; // Giữ nguyên dms

            DauSach* temp = list[i];
            list.remove(i);
            for (int j = 0; j < list.size(); j++)
            {
                if (*temp < *list[j]) // So sánh qua con trỏ
                {
                    list.insert(j, temp);
                    return true;
                }
            }
            list.push(temp);
            return true;
        }
    }
    return false;
}

DauSach* DauSachManager::searchRecord(int ISBN) const
{
    for (int i = 0; i < list.size(); i++)
    {
        if (list[i]->ISBN == ISBN) // Sử dụng -> vì là con trỏ
        {
            return list[i]; // Không cần const_cast vì list[i] là DauSach*
        }
    }
    return nullptr;
}

LinearList<DauSach> DauSachManager::getAllRecords() const
{
    LinearList<DauSach> result;
    for (int i = 0; i < list.size(); i++)
    {
        if (list[i]) // Kiểm tra con trỏ hợp lệ
        {
            result.push(*list[i]); // Sao chép nội dung DauSach
        }
    }
    return result;
}


bool DauSachManager::isRecordExist(int ISBN) const
{
    return searchRecord(ISBN) != nullptr;
}

bool DauSachManager::addDanhMucSach(int ISBN, DanhMucSach* danh_muc_sach)
{
    DauSach* record = searchRecord(ISBN);
    if (!record)
    {
        return false;
    }
    // Kiểm tra và cấp phát dms nếu chưa có
    if (record->dms == nullptr)
    {
        record->dms = new LinkedList<DanhMucSach*>();
    }
    record->dms->insertLast(danh_muc_sach);
    return true;
}

void DauSachManager::saveItems() const
{
    LinearList<DauSach> items = getAllRecords();
    LinearList<DauSach> tempList;
    for (int i = 0; i < items.size(); i++)
    {
        tempList.push(items[i]); // Sao chép nội dung để lưu
    }
    this->writeToFile(tempList);
}