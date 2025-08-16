#include "view/MainWindow.h"
#include "view/BorrowBookWindow.h"   // ví dụ cho f
#include <QMenuBar>
#include <QMessageBox>
#include <QVBoxLayout>



MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Library Management");
    resize(800, 600);
    auto *central = new QWidget(this);
    setCentralWidget(central);
    auto *layout = new QVBoxLayout(central);

    createMenus();
}

void MainWindow::createMenus() {
    QMenu *menuReader = menuBar()->addMenu("Độc giả");
    menuReader->addAction("Nhập thẻ độc giả", this, &MainWindow::openCardManagement);
    menuReader->addAction("In danh sách độc giả", this, &MainWindow::printReadersList);

    QMenu *menuBook = menuBar()->addMenu("Sách");
    menuBook->addAction("Nhập đầu sách", this, &MainWindow::openBookManagement);
    menuBook->addAction("In danh sách theo thể loại", this, &MainWindow::printBooksByCategory);
    menuBook->addAction("Tìm sách theo tên", this, &MainWindow::searchBookByName);

    QMenu *menuBorrow = menuBar()->addMenu("Mượn/Trả");
    menuBorrow->addAction("Mượn sách", this, &MainWindow::openBorrowBookWindow);
    menuBorrow->addAction("Trả sách", this, &MainWindow::openReturnBookWindow);
    menuBorrow->addAction("Danh sách sách độc giả đang mượn", this, &MainWindow::listBorrowedByReader);
    menuBorrow->addAction("Độc giả mượn quá hạn", this, &MainWindow::listOverdueReaders);
    menuBorrow->addAction("Top 10 sách được mượn nhiều", this, &MainWindow::top10BorrowedBooks);
}

// ============ Các slot mẫu ============

void MainWindow::openCardManagement() {
    QMessageBox::information(this, "Nhập thẻ độc giả", "Mở màn hình quản lý thẻ độc giả");
}

void MainWindow::printReadersList() {
    QMessageBox::information(this, "Danh sách độc giả", "In danh sách độc giả...");
}

void MainWindow::openBookManagement() {
    QMessageBox::information(this, "Đầu sách", "Mở màn hình nhập đầu sách");
}

void MainWindow::printBooksByCategory() {
    QMessageBox::information(this, "Danh sách sách", "In danh sách sách theo thể loại...");
}

void MainWindow::searchBookByName() {
    QMessageBox::information(this, "Tìm sách", "Mở màn hình tìm sách theo tên");
}


// Và khi mở màn:
void MainWindow::openBorrowBookWindow() {
    auto *w = new BorrowBookWindow(centralWidget());
    centralWidget()->layout()->addWidget(w);
    w->show();  // hoặc w->setVisible(true);
}

void MainWindow::openReturnBookWindow() {
    QMessageBox::information(this, "Trả sách", "Mở màn hình trả sách");
}

void MainWindow::listBorrowedByReader() {
    QMessageBox::information(this, "Danh sách sách", "Liệt kê sách đang mượn theo thẻ...");
}

void MainWindow::listOverdueReaders() {
    QMessageBox::information(this, "Độc giả quá hạn", "In danh sách độc giả quá hạn...");
}

void MainWindow::top10BorrowedBooks() {
    QMessageBox::information(this, "Top 10 sách", "In 10 sách có số lượt mượn nhiều nhất...");
}
