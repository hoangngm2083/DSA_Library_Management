#pragma once
#include <QMainWindow>
#include "view/BorrowBookWindow.h"
#include "view/ThemDauSachDialog.h"
#include "view/TimTenSachDialog.h"
#include "view/ThemDanhMucSachDialog.h"
#include <QMenuBar>
#include <QMessageBox>
#include <QVBoxLayout>
#include "view/DocGiaWindow.h"
#include "view/InDauSachWindow.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private slots:
    void openCardManagement();   // a. Nhập thẻ độc giả
    void printReadersList();     // b. In danh sách độc giả
    void openBookManagement();   // c. Nhập thông tin đầu sách
    void printBooksByCategory(); // d. In danh sách đầu sách
    void searchBookByName();     // e. Tìm thông tin sách theo tên
    void openBorrowBookWindow(); // f. Mượn sách
    // void openReturnBookWindow();      // g. Trả sách
    // void listBorrowedByReader();      // h. Liệt kê sách đang mượn theo thẻ
    void listOverdueReaders(); // i. In độc giả quá hạn
    void top10BorrowedBooks(); // j. In 10 sách mượn nhiều nhất

private:
    void createMenus();
    void hideAllWindows();
    BorrowBookWindow *borrowWindow = nullptr;
    DocGiaWindow *docgiaWindow = nullptr;
    InDauSachWindow *inDauSachWindow = nullptr;
};
