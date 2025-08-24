#include "view/MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), borrowWindow(nullptr)
{
    setWindowTitle("Library Management");
    resize(800, 600);
    auto *central = new QWidget(this);
    setCentralWidget(central);
    auto *layout = new QVBoxLayout(central);

    createMenus();
    openBorrowBookWindow();
}

void MainWindow::createMenus()
{

    QAction *actionMuonTra = menuBar()->addAction("Mượn/Trả");
    connect(actionMuonTra, &QAction::triggered, this, &MainWindow::openBorrowBookWindow);

    QAction *actionReader = menuBar()->addAction("Độc giả");
    connect(actionReader, &QAction::triggered, this, &MainWindow::openCardManagement);

    QMenu *menuBook = menuBar()->addMenu("Sách");
    menuBook->addAction("Nhập đầu sách", this, &MainWindow::openBookManagement);
    menuBook->addAction("In danh sách theo thể loại", this, &MainWindow::printBooksByCategory);
    menuBook->addAction("Tìm sách theo tên", this, &MainWindow::searchBookByName);
    menuBook->addAction("Top 10 sách được mượn nhiều", this, &MainWindow::top10BorrowedBooks);
}

// ============ Các slot mẫu ============

void MainWindow::openCardManagement()
{
    hideAllWindows();
    if (!docgiaWindow)
    {
        docgiaWindow = new DocGiaWindow(centralWidget());
        centralWidget()->layout()->addWidget(docgiaWindow);
    }
    docgiaWindow->show();
}

void MainWindow::printReadersList()
{
    QMessageBox::information(this, "Danh sách độc giả", "In danh sách độc giả...");
}

void MainWindow::openBookManagement()
{
    ThemDauSachDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted)
    {
        int ISBN = dialog.getISBN();
        // ThemDanhMucSachDialog
        ThemDanhMucSachDialog danhMucDialog(ISBN, this);
        danhMucDialog.exec();
    }
}

void MainWindow::printBooksByCategory()
{
    hideAllWindows();
    if (!inDauSachWindow)
    {
        inDauSachWindow = new InDauSachWindow(centralWidget());
        centralWidget()->layout()->addWidget(inDauSachWindow);
    }
    inDauSachWindow->show();
}

void MainWindow::searchBookByName()
{
    TimTenSachDialog dialog(this);
    dialog.exec();
}

void MainWindow::openBorrowBookWindow()
{
    hideAllWindows();
    if (!borrowWindow)
    {
        borrowWindow = new BorrowBookWindow(centralWidget());
        centralWidget()->layout()->addWidget(borrowWindow);
    }
    borrowWindow->show();
}

void MainWindow::listOverdueReaders()
{
    QMessageBox::information(this, "Độc giả quá hạn", "In danh sách độc giả quá hạn...");
}

void MainWindow::top10BorrowedBooks()
{
    QMessageBox::information(this, "Top 10 sách", "In 10 sách có số lượt mượn nhiều nhất...");
}

void MainWindow::hideAllWindows()
{
    if (borrowWindow)
        borrowWindow->hide();
    if (docgiaWindow)
        docgiaWindow->hide();
    if (inDauSachWindow)
        inDauSachWindow->hide();
}