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


#include <iostream>
#include <string>
#include "repositories/DanhMucSachManager.h"
#include <functional>

void printRecord(const DanhMucSach &value)
{
    std::cout << "Ma sach: " << value.ma_sach << "\n"
              << "Trang thai: " << value.trang_thai << "\n"
              << "Vi tri: " << value.vi_tri << "\n"
              << "ISBN: " << value.ISBN << "\n"
              << "-----------------------\n";
}
void printRecord2(const DanhMucSach *value)
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
        DanhMucSachManager danh_muc_sach;

        // Test 1: Display all initial records
        std::cout << "=== Test 1: All Records ===\n";
        LinearList<DanhMucSach> all_records = danh_muc_sach.getAllRecords();
        all_records.traverse(printRecord);

        // Test 2: Add a new record
        std::cout << "\n=== Test 2: Add New Record ===\n";
        bool added = danh_muc_sach.addRecord("BOOK006", 0, "ShelfF", 777888999);
        std::cout << "Add BOOK006: " << (added ? "Success" : "Failed") << "\n";

        // Test 3: Add a duplicate record (should fail)
        std::cout << "\n=== Test 3: Add Duplicate Record ===\n";
        added = danh_muc_sach.addRecord("BOOK001", 0, "ShelfA", 123456789);
        std::cout << "Add duplicate BOOK001: " << (added ? "Success" : "Failed") << "\n";

        // Test 4: Update an existing record
        std::cout << "\n=== Test 4: Update Existing Record ===\n";
        bool updated = danh_muc_sach.updateRecord("BOOK001", 1, "ShelfA1", 123456789);
        std::cout << "Update BOOK001: " << (updated ? "Success" : "Failed") << "\n";

        // Test 5: Update a non-existent record
        std::cout << "\n=== Test 5: Update Non-existent Record ===\n";
        updated = danh_muc_sach.updateRecord("BOOK999", 1, "ShelfX", 999999999);
        std::cout << "Update BOOK999: " << (updated ? "Success" : "Failed") << "\n";

        // Test 6: Remove an existing record
        std::cout << "\n=== Test 6: Remove Existing Record ===\n";
        bool removed = danh_muc_sach.removeRecord("BOOK002");
        std::cout << "Remove BOOK002: " << (removed ? "Success" : "Failed") << "\n";

        // Test 7: Remove a non-existent record
        std::cout << "\n=== Test 7: Remove Non-existent Record ===\n";
        removed = danh_muc_sach.removeRecord("BOOK999");
        std::cout << "Remove BOOK999: " << (removed ? "Success" : "Failed") << "\n";

        // Test 8: Check if a record exists
        std::cout << "\n=== Test 8: Check Record Existence ===\n";
        std::cout << "BOOK003 exists: " << (danh_muc_sach.isRecordExist("BOOK003") ? "Yes" : "No") << "\n";
        std::cout << "BOOK999 exists: " << (danh_muc_sach.isRecordExist("BOOK999") ? "Yes" : "No") << "\n";

        // Test 9: Search for a specific record
        std::cout << "\n=== Test 9: Search Record by ma_sach ===\n";
        auto data = danh_muc_sach.searchRecord("BOOK003");
        if (data)
        {
            std::cout << "Found record:\n";
            printRecord(*data);
        }
        else
        {
            std::cout << "Không tìm thấy sách với mã BOOK003\n";
        }

        // Test 10: Display all records after modifications
        std::cout << "\n=== Test 10: All Records After Modifications ===\n";
        LinearList<DanhMucSach> all_records_1 = danh_muc_sach.getAllRecords();
        all_records_1.traverse(printRecord);

        // Test 11: Try invalid trang_thai (should throw exception)
        std::cout << "\n=== Test 11: Invalid trang_thai ===\n";
        try
        {
            danh_muc_sach.addRecord("BOOK007", 3, "ShelfG", 222333444);
            std::cout << "Add BOOK007: Success\n";
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << "Add BOOK007 failed: " << e.what() << "\n";
        }

        std::cout << "\n=== Test 12: Search ISBN 123456789 ===\n";

            
            LinkedList<DanhMucSach*> all_records_2 = danh_muc_sach.searchRecords(123456789);
            all_records_2.traverse(printRecord2);
        
        
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}