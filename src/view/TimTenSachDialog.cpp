#include "view/TimTenSachDialog.h"

TimTenSachDialog::TimTenSachDialog(QWidget *parent, int cardId)
    : QDialog(parent), cardId(cardId)
{
    setWindowTitle("Tìm tên sách");
    resize(800, 400);

    auto *mainLayout = new QVBoxLayout(this);

    // Hàng nhập tìm kiếm
    auto *searchLayout = new QHBoxLayout;
    auto *lblSearch = new QLabel("Tên sách:");
    lineEditSearch = new QLineEdit;
    btnSearch = new QPushButton("Tìm");
    searchLayout->addWidget(lblSearch);
    searchLayout->addWidget(lineEditSearch);
    searchLayout->addWidget(btnSearch);

    // Bảng kết quả
    tableResults = new QTableWidget(this);
    tableResults->setColumnCount(7);
    tableResults->setHorizontalHeaderLabels({"ISBN", "Tên sách", "Số trang", "Tác giả",
                                             "Năm XB", "Thể loại", "Mã sách (trong DMS)"});
    tableResults->horizontalHeader()->setStretchLastSection(true);
    tableResults->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Hàng nút
    auto *btnLayout = new QHBoxLayout;
    btnClose = new QPushButton("Đóng");
    btnLayout->addStretch();
    btnLayout->addWidget(btnClose);
    mainLayout->addLayout(searchLayout);
    mainLayout->addWidget(tableResults);
    mainLayout->addLayout(btnLayout);

    connect(btnSearch, &QPushButton::clicked, this, &TimTenSachDialog::onSearchClicked);
    connect(btnClose, &QPushButton::clicked, this, &QDialog::reject);
}

void TimTenSachDialog::onSearchClicked()
{
    QString keyword = lineEditSearch->text().trimmed();
    if (keyword.isEmpty())
    {
        QMessageBox::warning(this, "Lỗi", "Vui lòng nhập từ khóa tìm kiếm!");
        return;
    }

    auto results = dau_sach_mgr.searchLikeTenSach(keyword.toStdString());

    if (results.size() == 0)
    {
        QMessageBox::information(this, "Thông báo", "Không tìm thấy sách phù hợp!");
    }
    tableResults->setRowCount(0); // Clear bảng cũ

    for (int i = 0; i < results.size(); ++i)
    {
        DauSach ds = results[i];
        ds.loadDanhMucSach();
        if (ds.dms != nullptr)
        {
            ds.dms->traverse([&](DanhMucSach * dmsItem)
            {
                int row = tableResults->rowCount();
                tableResults->insertRow(row);
                tableResults->setItem(row, 0, new QTableWidgetItem(QString::number(ds.ISBN)));
                tableResults->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(ds.ten_sach)));
                tableResults->setItem(row, 2, new QTableWidgetItem(QString::number(ds.so_trang)));
                tableResults->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(ds.tac_gia)));
                tableResults->setItem(row, 4, new QTableWidgetItem(QString::number(ds.nam_xuat_ban)));
                tableResults->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(ds.the_loai)));
                tableResults->setItem(row, 6, new QTableWidgetItem(QString::fromStdString(dmsItem->ma_sach)));
            });
        }
    }
}
