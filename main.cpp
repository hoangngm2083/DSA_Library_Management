// #include <iostream>
// #include "library.h"

// int main() {
//     std::cout << "Quản lý Thư viện\n";
//     std::cout << "Chương trình đang được phát triển...\n";

//     // TODO: Gọi menu ở đây
//     hien_danh_sach_chuc_nang();

//     return 0;
// }

// #include <iostream>
// #include <string>
// #include "repositories/TheDocGiaManager.h"
// #include <functional>

// int main()
// {

//     TheDocGiaManager the_doc_gia;

//     LinearList<TheDocGia> result = the_doc_gia.getAllCards();
//     result.traverse([](TheDocGia value)
//                     { std::cout
//                           << "Ma the: " << value.ma_the << "\n"
//                           << "Ho: " << value.ho << "\n"
//                           << "Ten: " << value.ten << "\n"
//                           << "Phai: " << (value.phai == 0 ? "Nam" : "Nu") << "\n"
//                           << "Trang thai: " << value.trang_thai << "\n"
//                           << "-----------------------\n"; });

//     return 0;
// }

// #include <iostream>
// #include <string>
// #include "repositories/MuonTraManager.h"
// #include <functional>

// int main()
// {

//     MuonTraManager muon_tra;

//     muon_tra.updateRecord("001", "2023-08-01", "2023-08-17", 1);

//     LinearList<MuonTra> result = muon_tra.getAllRecords();
//     result.traverse([](MuonTra value)
//                     { std::cout
//                           << "Ma sach: " << value.ma_sach << "\n"
//                           << "Ngay muon: " << value.ngay_muon << "\n"
//                           << "Ngay tra: " << value.ngay_tra << "\n"
//                           << "Trang thai: " << value.trang_thai << "\n"
//                           << "Ma the: " << value.ma_the << "\n"
//                           << "-----------------------\n"; });

//     auto result = muon_tra.searchRecords(789012);

//     result.traverse([](MuonTra *value)
//                     { std::cout
//                           << "Ma sach: " << value->ma_sach << "\n"
//                           << "Ngay muon: " << value->ngay_muon << "\n"
//                           << "Ngay tra: " << value->ngay_tra << "\n"
//                           << "Trang thai: " << value->trang_thai << "\n"
//                           << "Ma the: " << value->ma_the << "\n"
//                           << "-----------------------\n"; });

//     auto data = muon_tra.searchRecord("001", "2023-08-01");
//     std::cout
//         << "Ma sach: " << data->ma_sach << "\n"
//         << "Ngay muon: " << data->ngay_muon << "\n"
//         << "Ngay tra: " << data->ngay_tra << "\n"
//         << "Trang thai: " << data->trang_thai << "\n"
//         << "Ma the: " << data->ma_the << "\n"
//         << "-----------------------\n";
//     return 0;
// }


// #include <iostream>
// #include <string>
// #include "repositories/DanhMucSachManager.h"
// #include <functional>

// void printRecord(const DanhMucSach &value)
// {
//     std::cout << "Ma sach: " << value.ma_sach << "\n"
//               << "Trang thai: " << value.trang_thai << "\n"
//               << "Vi tri: " << value.vi_tri << "\n"
//               << "ISBN: " << value.ISBN << "\n"
//               << "-----------------------\n";
// }
// void printRecord2(const DanhMucSach *value)
// {
//     std::cout << "Ma sach: " << value->ma_sach << "\n"
//               << "Trang thai: " << value->trang_thai << "\n"
//               << "Vi tri: " << value->vi_tri << "\n"
//               << "ISBN: " << value->ISBN << "\n"
//               << "-----------------------\n";
// }

// int main()
// {
//     try
//     {
//         DanhMucSachManager danh_muc_sach;

//         // Test 1: Display all initial records
//         std::cout << "=== Test 1: All Records ===\n";
//         LinearList<DanhMucSach> all_records = danh_muc_sach.getAllRecords();
//         all_records.traverse(printRecord);

//         // Test 2: Add a new record
//         std::cout << "\n=== Test 2: Add New Record ===\n";
//         bool added = danh_muc_sach.addRecord("BOOK006", 0, "ShelfF", 777888999);
//         std::cout << "Add BOOK006: " << (added ? "Success" : "Failed") << "\n";

//         // Test 3: Add a duplicate record (should fail)
//         std::cout << "\n=== Test 3: Add Duplicate Record ===\n";
//         added = danh_muc_sach.addRecord("BOOK001", 0, "ShelfA", 123456789);
//         std::cout << "Add duplicate BOOK001: " << (added ? "Success" : "Failed") << "\n";

//         // Test 4: Update an existing record
//         std::cout << "\n=== Test 4: Update Existing Record ===\n";
//         bool updated = danh_muc_sach.updateRecord("BOOK001", 1, "ShelfA1", 123456789);
//         std::cout << "Update BOOK001: " << (updated ? "Success" : "Failed") << "\n";

//         // Test 5: Update a non-existent record
//         std::cout << "\n=== Test 5: Update Non-existent Record ===\n";
//         updated = danh_muc_sach.updateRecord("BOOK999", 1, "ShelfX", 999999999);
//         std::cout << "Update BOOK999: " << (updated ? "Success" : "Failed") << "\n";

//         // Test 6: Remove an existing record
//         std::cout << "\n=== Test 6: Remove Existing Record ===\n";
//         bool removed = danh_muc_sach.removeRecord("BOOK002");
//         std::cout << "Remove BOOK002: " << (removed ? "Success" : "Failed") << "\n";

//         // Test 7: Remove a non-existent record
//         std::cout << "\n=== Test 7: Remove Non-existent Record ===\n";
//         removed = danh_muc_sach.removeRecord("BOOK999");
//         std::cout << "Remove BOOK999: " << (removed ? "Success" : "Failed") << "\n";

//         // Test 8: Check if a record exists
//         std::cout << "\n=== Test 8: Check Record Existence ===\n";
//         std::cout << "BOOK003 exists: " << (danh_muc_sach.isRecordExist("BOOK003") ? "Yes" : "No") << "\n";
//         std::cout << "BOOK999 exists: " << (danh_muc_sach.isRecordExist("BOOK999") ? "Yes" : "No") << "\n";

//         // Test 9: Search for a specific record
//         std::cout << "\n=== Test 9: Search Record by ma_sach ===\n";
//         auto data = danh_muc_sach.searchRecord("BOOK003");
//         if (data)
//         {
//             std::cout << "Found record:\n";
//             printRecord(*data);
//         }
//         else
//         {
//             std::cout << "Không tìm thấy sách với mã BOOK003\n";
//         }

//         // Test 10: Display all records after modifications
//         std::cout << "\n=== Test 10: All Records After Modifications ===\n";
//         LinearList<DanhMucSach> all_records_1 = danh_muc_sach.getAllRecords();
//         all_records_1.traverse(printRecord);

//         // Test 11: Try invalid trang_thai (should throw exception)
//         std::cout << "\n=== Test 11: Invalid trang_thai ===\n";
//         try
//         {
//             danh_muc_sach.addRecord("BOOK007", 3, "ShelfG", 222333444);
//             std::cout << "Add BOOK007: Success\n";
//         }
//         catch (const std::invalid_argument &e)
//         {
//             std::cout << "Add BOOK007 failed: " << e.what() << "\n";
//         }

//         std::cout << "\n=== Test 12: Search ISBN 123456789 ===\n";

            
//             LinkedList<DanhMucSach*> all_records_2 = danh_muc_sach.searchRecords(123456789);
//             all_records_2.traverse(printRecord2);
        
        
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "Error: " << e.what() << "\n";
//         return 1;
//     }

//     return 0;
// }


#include <iostream>
#include <string>
#include "repositories/DauSachManager.h"
#include <functional>

void printRecord(const DauSach &value)
{
    std::cout << "ISBN: " << value.ISBN << "\n"
              << "Ten sach: " << value.ten_sach << "\n"
              << "So trang: " << value.so_trang << "\n"
              << "Tac gia: " << value.tac_gia << "\n"
              << "Nam xuat ban: " << value.nam_xuat_ban << "\n"
              << "The loai: " << value.the_loai << "\n"
              << "-----------------------\n";
}

void printDanhMucSach(const DanhMucSach &value)
{
    std::cout << "Ma sach: " << value.ma_sach << "\n"
              << "Trang thai: " << value.trang_thai << "\n"
              << "Vi tri: " << value.vi_tri << "\n"
              << "ISBN: " << value.ISBN << "\n"
              << "-----------------------\n";
}

void printDanhMucSach2(const DanhMucSach * value)
{
    std::cout << "Ma sach: " << value->ma_sach << "\n"
              << "Trang thai: " << value->trang_thai << "\n"
              << "Vi tri: " << value->vi_tri << "\n"
              << "ISBN: " << value->ISBN << "\n"
              << "-----------------------\n";
}

int main()
{
    try
    {
        DauSachManager dau_sach;

        // Test 1: Display all initial records
        std::cout << "=== Test 1: All Records ===\n";
        LinearList<DauSach> all_records = dau_sach.getAllRecords();
        all_records.traverse(printRecord);

        // Test 2: Add a new record
        std::cout << "\n=== Test 2: Add New Record ===\n";
        bool added = dau_sach.addRecord(111222333, "Design Patterns", 400, "Erich Gamma", 1994, "Software Engineering");
        std::cout << "Add ISBN 111222333: " << (added ? "Success" : "Failed") << "\n";

        // Test 3: Add a duplicate record (should fail)
        std::cout << "\n=== Test 3: Add Duplicate Record ===\n";
        added = dau_sach.addRecord(123456789, "Introduction to Algorithms", 500, "Thomas H. Cormen", 2009, "Computer Science");
        std::cout << "Add duplicate ISBN 123456789: " << (added ? "Success" : "Failed") << "\n";

        // Test 4: Update an existing record
        std::cout << "\n=== Test 4: Update Existing Record ===\n";
        bool updated = dau_sach.updateRecord(123456789, "Intro to Algorithms", 510, "Thomas H. Cormen", 2010, "Computer Science");
        std::cout << "Update ISBN 123456789: " << (updated ? "Success" : "Failed") << "\n";

        // Test 5: Update a non-existent record
        std::cout << "\n=== Test 5: Update Non-existent Record ===\n";
        updated = dau_sach.updateRecord(999999999, "Non-existent Book", 300, "Unknown", 2020, "Fiction");
        std::cout << "Update ISBN 999999999: " << (updated ? "Success" : "Failed") << "\n";

        // Test 6: Remove an existing record
        std::cout << "\n=== Test 6: Remove Existing Record ===\n";
        bool removed = dau_sach.removeRecord(987654321);
        std::cout << "Remove ISBN 987654321: " << (removed ? "Success" : "Failed") << "\n";

        // Test 7: Remove a non-existent record
        std::cout << "\n=== Test 7: Remove Non-existent Record ===\n";
        removed = dau_sach.removeRecord(999999999);
        std::cout << "Remove ISBN 999999999: " << (removed ? "Success" : "Failed") << "\n";

        // Test 8: Check if a record exists
        std::cout << "\n=== Test 8: Check Record Existence ===\n";
        std::cout << "ISBN 456789123 exists: " << (dau_sach.isRecordExist(456789123) ? "Yes" : "No") << "\n";
        std::cout << "ISBN 999999999 exists: " << (dau_sach.isRecordExist(999999999) ? "Yes" : "No") << "\n";

        // Test 9: Search for a specific record
        std::cout << "\n=== Test 9: Search Record by ISBN ===\n";
        auto data = dau_sach.searchRecord(456789123);
        if (data)
        {
            std::cout << "Found record:\n";
            printRecord(*data);
        }
        else
        {
            std::cout << "Không tìm thấy đầu sách với ISBN 456789123\n";
        }

        // Test 10: Display all records after modifications
        std::cout << "\n=== Test 10: All Records After Modifications ===\n";
        LinearList<DauSach> all_records_2 = dau_sach.getAllRecords();
        all_records_2.traverse(printRecord);

        // Test 11: Add a DanhMucSach to an existing DauSach
        std::cout << "\n=== Test 11: Add DanhMucSach to DauSach ===\n";
        DanhMucSach* new_dms = new DanhMucSach{"BOOK010", 0, "ShelfA", 123456789};
        bool added_dms = dau_sach.addDanhMucSach(123456789, new_dms);   
        std::cout << "Add DanhMucSach to ISBN 123456789: " << (added_dms ? "Success" : "Failed") << "\n";

        // Test 12: Display DanhMucSach of a DauSach
        std::cout << "\n=== Test 12: Display DanhMucSach of DauSach ===\n";
        auto dau_sach_record = dau_sach.searchRecord(123456789);
        dau_sach_record->loadDanhMucSach();
        if (dau_sach_record && dau_sach_record->dms != nullptr)
        {
            std::cout << "DanhMucSach for ISBN 123456789:\n";
            dau_sach_record->dms->traverse(printDanhMucSach2);
        }
        else
        {
            std::cout << "Không tìm thấy đầu sách hoặc danh sách DanhMucSach rỗng\n";
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}