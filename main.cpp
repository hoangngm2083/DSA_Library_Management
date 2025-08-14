// #include <iostream>
// #include "library.h"

// int main() {
//     std::cout << "Quản lý Thư viện\n";
//     std::cout << "Chương trình đang được phát triển...\n";

//     // TODO: Gọi menu ở đây
//     hien_danh_sach_chuc_nang();

//     return 0;
// }

#include <iostream>
#include <string>
#include "repositories/TheDocGiaManager.h"
#include <functional>

int main()
{

    TheDocGiaManager the_doc_gia;

    LinearList<TheDocGia> result = the_doc_gia.getAllCards();
    result.traverse([](TheDocGia value)
                    { std::cout
                          << "Ma the: " << value.ma_the << "\n"
                          << "Ho: " << value.ho << "\n"
                          << "Ten: " << value.ten << "\n"
                          << "Phai: " << (value.phai == 0 ? "Nam" : "Nu") << "\n"
                          << "Trang thai: " << value.trang_thai << "\n"
                          << "-----------------------\n"; });

    return 0;
}