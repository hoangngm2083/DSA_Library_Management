#include "view/InDauSachWindow.h"

InDauSachWindow::InDauSachWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Danh sách đầu sách theo thể loại");

    auto *mainLayout = new QVBoxLayout(this);

    // Bảng hiển thị sách
    tableBooks = new QTableWidget(this);
    tableBooks->setColumnCount(5);   // Chỉ còn 5 cột
    tableBooks->setHorizontalHeaderLabels(
        {"Thể loại", "Tên sách", "Tác giả", "Năm XB", "ISBN"});
    tableBooks->horizontalHeader()->setStretchLastSection(true);
    tableBooks->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Nút chức năng
    auto *btnLayout = new QHBoxLayout;
    btnRefresh = new QPushButton("Làm mới");
    btnClose = new QPushButton("Đóng");
    btnLayout->addStretch();
    btnLayout->addWidget(btnRefresh);
    btnLayout->addWidget(btnClose);

    mainLayout->addWidget(tableBooks);
    mainLayout->addLayout(btnLayout);

    connect(btnRefresh, &QPushButton::clicked, this, &InDauSachWindow::onRefreshClicked);
    connect(btnClose, &QPushButton::clicked, this, &InDauSachWindow::onCloseClicked);

    loadBooksByCategory();
}

void InDauSachWindow::onRefreshClicked()
{
    loadBooksByCategory();
}

void InDauSachWindow::onCloseClicked()
{
    close();
}

void InDauSachWindow::loadBooksByCategory()
{
    tableBooks->setRowCount(0); // clear bảng cũ

    auto allBooks = dau_sach_mgr.getAllRecords();

    // Sắp xếp: thể loại ↑, sau đó tên sách ↑
    allBooks.sort([](const DauSach &a, const DauSach &b) {
        if (a.the_loai == b.the_loai)
            return a.ten_sach > b.ten_sach;
        return a.the_loai > b.the_loai;
    });

    for (int i = 0; i < allBooks.size(); ++i)
    {
        const DauSach &ds = allBooks[i];
        int row = tableBooks->rowCount();
        tableBooks->insertRow(row);

        tableBooks->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(ds.the_loai)));
        tableBooks->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(ds.ten_sach)));
        tableBooks->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(ds.tac_gia)));
        tableBooks->setItem(row, 3, new QTableWidgetItem(QString::number(ds.nam_xuat_ban)));
        tableBooks->setItem(row, 4, new QTableWidgetItem(QString::number(ds.ISBN)));
    }
}
