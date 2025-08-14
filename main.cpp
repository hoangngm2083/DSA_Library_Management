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
// #include "data_structs/BST.h"

// int main() {
//     // Tạo cây BST kiểu string với index là int
//     BST<std::string> stringTree;

//     // Chèn các phần tử với index
//     stringTree.insert("Apple", 50);
//     stringTree.insert("Banana", 30);
//     stringTree.insert("Cherry", 20);
//     stringTree.insert("Date", 40);
//     stringTree.insert("Elderberry", 70);
//     stringTree.insert("Fig", 60);
//     stringTree.insert("Grape", 80);

//     // Duyệt cây
//     std::cout << "Duyệt trung thứ tự (LNR - theo index):\n";
//     stringTree.inOrder();

//     std::cout << "\nDuyệt tiền thứ tự (NLR):\n";
//     stringTree.preOrder();

//     std::cout << "\nDuyệt hậu thứ tự (LRN):\n";
//     stringTree.postOrder();

//     std::cout << "\nDuyệt theo mức:\n";
//     stringTree.levelOrder();

//     // Tìm kiếm theo index
//     std::cout << "\nTìm kiếm index 40: ";
//     if (stringTree.search(40)) {
//         std::cout << "Tìm thấy: " << stringTree.getData(40) << std::endl;
//     } else {
//         std::cout << "Không tìm thấy\n";
//     }

//     std::cout << "Tìm kiếm index 90: ";
//     if (stringTree.search(90)) {
//         std::cout << "Tìm thấy: " << stringTree.getData(90) << std::endl;
//     } else {
//         std::cout << "Không tìm thấy\n";
//     }

//     // Lấy min, max theo index
//     std::cout << "\nIndex nhỏ nhất: " << stringTree.getMinIndex()
//               << " (Data: " << stringTree.getMinData() << ")\n";
//     std::cout << "Index lớn nhất: " << stringTree.getMaxIndex()
//               << " (Data: " << stringTree.getMaxData() << ")\n";

//     // Kích thước và chiều cao
//     std::cout << "\nSố node: " << stringTree.size() << std::endl;
//     std::cout << "Chiều cao: " << stringTree.height() << std::endl;

//     // Xóa node theo index
//     stringTree.remove(20);
//     std::cout << "\nSau khi xóa index 20 (LNR):\n";
//     stringTree.inOrder();

//     stringTree.remove(30);
//     std::cout << "\nSau khi xóa index 30 (LNR):\n";
//     stringTree.inOrder();

//     stringTree.remove(50);
//     std::cout << "\nSau khi xóa index 50 (LNR):\n";
//     stringTree.inOrder();

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