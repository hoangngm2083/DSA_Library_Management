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

#include <iostream>
#include <string>
#include "repositories/MuonTraManager.h"
#include <functional>

int main()
{

    MuonTraManager muon_tra;

    // muon_tra.searchRecords("001", "2023-08-01", "2023-08-17", 1);

    // LinearList<MuonTra> result = muon_tra.getAllRecords();
    // result.traverse([](MuonTra value)
    //                 { std::cout
    //                       << "Ma sach: " << value.ma_sach << "\n"
    //                       << "Ngay muon: " << value.ngay_muon << "\n"
    //                       << "Ngay tra: " << value.ngay_tra << "\n"
    //                       << "Trang thai: " << value.trang_thai << "\n"
    //                       << "Ma the: " << value.ma_the << "\n"
    //                       << "-----------------------\n"; });

    auto result = muon_tra.searchRecords(789012);

    result.traverse([](MuonTra *value)
                    { std::cout
                          << "Ma sach: " << value->ma_sach << "\n"
                          << "Ngay muon: " << value->ngay_muon << "\n"
                          << "Ngay tra: " << value->ngay_tra << "\n"
                          << "Trang thai: " << value->trang_thai << "\n"
                          << "Ma the: " << value->ma_the << "\n"
                          << "-----------------------\n"; });

    // auto data = muon_tra.searchRecord("001", "2023-08-01");
    // std::cout
    //     << "Ma sach: " << data->ma_sach << "\n"
    //     << "Ngay muon: " << data->ngay_muon << "\n"
    //     << "Ngay tra: " << data->ngay_tra << "\n"
    //     << "Trang thai: " << data->trang_thai << "\n"
    //     << "Ma the: " << data->ma_the << "\n"
    //     << "-----------------------\n";
    return 0;
}