#include "repositories/DauSachManager.h"

DauSachManager dau_sach_mgr;

DauSachManager::DauSachManager() : BaseManager("data/dausach.txt")
{
    this->loadItems();
}

void DauSachManager::loadItems()
{
    list.clear();
    auto items = this->readFromFile();
    for (int i = 0; i < items.size(); i++)
    {
        DauSach *newItem = new DauSach(items[i]); // Sao chép và cấp phát mới
        list.push(newItem);
    }
    for (int i = 0; i < list.size() - 1; i++)
    {
        for (int j = i + 1; j < list.size(); j++)
        {
            if (*list[j] < *list[i]) // So sánh qua con trỏ
            {
                DauSach *temp = list[i];
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

void DauSachManager::writeItem(std::ostream &out, const DauSach &obj)
{
    out << obj.ISBN << "\n"
        << obj.ten_sach << "\n"
        << obj.so_trang << "\n"
        << obj.tac_gia << "\n"
        << obj.nam_xuat_ban << "\n"
        << obj.the_loai << "\n";
}

int DauSachManager::addRecord(const std::string &ten_sach, int so_trang,
                              const std::string &tac_gia, int nam_xuat_ban, const std::string &the_loai)
{
    this->loadItems();
    int ISBN = id_mgr.next();
    while (isRecordExist(ISBN))
    {
        ISBN = id_mgr.next();
    }

    if (list.size() >= 10000)
    {
        throw std::runtime_error("Danh sách đầu sách đã đạt tối đa 10,000!");
    }

    DauSach *newRecord = new DauSach(); // Cấp phát mới
    newRecord->ISBN = ISBN;
    newRecord->ten_sach = ten_sach;
    newRecord->so_trang = so_trang;
    newRecord->tac_gia = tac_gia;
    newRecord->nam_xuat_ban = nam_xuat_ban;
    newRecord->the_loai = the_loai;
    newRecord->dms = nullptr; // Khởi tạo dms là nullptr
    // . Danh sách đầu sách luôn tăng dần theo tên sách
    for (int i = 0; i < list.size(); i++)
    {
        if (newRecord->ten_sach < list[i]->ten_sach)
        {
            list.insert(i, newRecord);
            this->saveItems();
            return ISBN;
        }
    }

    // Nếu không tìm được vị trí phù hợp -> chèn cuối
    list.push(newRecord);
    this->saveItems();
    return ISBN;
}

bool DauSachManager::removeRecord(int ISBN)
{
    this->loadItems();
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
            delete list[i];             // Giải phóng bộ nhớ của DauSach
            bool flag = list.remove(i); // Xóa con trỏ khỏi list
            if (flag)
            {
                this->saveItems();
            }
            return flag;
        }
    }
    std::cerr << "Không tìm thấy đầu sách với ISBN: " << ISBN << "\n";
    return false;
}

bool DauSachManager::updateRecord(int ISBN, const std::string &ten_sach, int so_trang,
                                  const std::string &tac_gia, int nam_xuat_ban, const std::string &the_loai)
{
    this->loadItems();
    for (int i = 0; i < list.size(); i++)
    {
        if (list[i]->ISBN == ISBN) // Sử dụng -> vì là con trỏ
        {
            LinkedList<DanhMucSach *> *old_dms = list[i]->dms; // Lưu lại dms
            list[i]->ten_sach = ten_sach;
            list[i]->so_trang = so_trang;
            list[i]->tac_gia = tac_gia;
            list[i]->nam_xuat_ban = nam_xuat_ban;
            list[i]->the_loai = the_loai;
            list[i]->dms = old_dms; // Giữ nguyên dms

            DauSach *temp = list[i];
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
            this->saveItems();
            return true;
        }
    }
    return false;
}

DauSach *DauSachManager::searchRecord(int ISBN)
{
    this->loadItems();
    for (int i = 0; i < list.size(); i++)
    {
        if (list[i]->ISBN == ISBN) // Sử dụng -> vì là con trỏ
        {
            return list[i]; // Không cần const_cast vì list[i] là DauSach*
        }
    }
    return nullptr;
}

// Hàm phụ để chuyển chuỗi về lowercase
static std::string toLower(const std::string &s)
{
    std::string result;
    result.reserve(s.size());
    for (unsigned char c : s)
    {
        result.push_back(std::tolower(c));
    }
    return result;
}

// Tìm tất cả sách có tên chứa keyword (LIKE %keyword%)
LinearList<DauSach> DauSachManager::searchLikeTenSach(const std::string &keyword)
{
    this->loadItems();
    LinearList<DauSach> result;
    std::string keyLower = toLower(keyword);

    for (int i = 0; i < list.size(); i++)
    {
        std::string tenLower = toLower(list[i]->ten_sach);
        std::cout << tenLower << std::endl;
        if (tenLower.find(keyLower) != std::string::npos)
        {                          // std::string::npos là một hằng số đặc biệt của std::string dùng để biểu thị "không tìm thấy".
            result.push(*list[i]); // trả về danh sách các kết quả khớp
        }
    }

    return result;
}

LinearList<DauSach> DauSachManager::getAllRecords()
{
    this->loadItems();
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

bool DauSachManager::isRecordExist(int ISBN)
{
    return searchRecord(ISBN) != nullptr;
}

bool DauSachManager::addDanhMucSach(int ISBN, DanhMucSach *danh_muc_sach)
{
    DauSach *record = searchRecord(ISBN);
    if (!record)
    {
        return false;
    }
    // Kiểm tra và cấp phát dms nếu chưa có
    if (record->dms == nullptr)
    {
        record->dms = new LinkedList<DanhMucSach *>();
    }
    record->dms->insertLast(danh_muc_sach);
    return true;
}

void DauSachManager::saveItems()
{
    LinearList<DauSach> result;
    for (int i = 0; i < list.size(); i++)
    {
        if (list[i]) // Kiểm tra con trỏ hợp lệ
        {
            result.push(*list[i]); // Sao chép nội dung DauSach
        }
    }

    this->writeToFile(result);
}