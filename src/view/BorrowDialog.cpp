#include "view/BorrowDialog.h"

BorrowDialog::BorrowDialog(QWidget *parent, int cardId)
    : QDialog(parent), cardId(cardId)
{
    setWindowTitle("Mượn sách");
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
    tableResults->setHorizontalHeaderLabels({
        "ISBN", "Tên sách", "Số trang", "Tác giả",
        "Năm XB", "Thể loại", "Mã sách (trong DMS)"
    });
    tableResults->horizontalHeader()->setStretchLastSection(true);
    tableResults->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Hàng nút
    auto *btnLayout = new QHBoxLayout;
    btnBorrow = new QPushButton("Mượn");
    btnClose = new QPushButton("Đóng");
    btnLayout->addStretch();
    btnLayout->addWidget(btnBorrow);
    btnLayout->addWidget(btnClose);

    mainLayout->addLayout(searchLayout);
    mainLayout->addWidget(tableResults);
    mainLayout->addLayout(btnLayout);

    // signal-slot
    connect(btnSearch, &QPushButton::clicked, this, &BorrowDialog::onSearchClicked);
    connect(btnBorrow, &QPushButton::clicked, this, &BorrowDialog::onBorrowClicked);
    connect(btnClose, &QPushButton::clicked, this, &QDialog::reject);
}

// void BorrowDialog::onSearchClicked() {
//     QString keyword = lineEditSearch->text().trimmed();
//     if (keyword.isEmpty()) {
//         QMessageBox::warning(this, "Lỗi", "Vui lòng nhập từ khóa tìm kiếm!");
//         return;
//     }

//     auto results = dau_sach_mgr.searchLikeTenSach(keyword.toStdString());
//     tableResults->setRowCount(results.size());
//     for (int i = 0; i < results.size(); ++i) {

//             tableResults->setItem(i, 0, new QTableWidgetItem(QString::number(results[i].ISBN)));
//             tableResults->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(results[i].ten_sach)));
//             tableResults->setItem(i, 2, new QTableWidgetItem(QString::number(results[i].so_trang)));
//             tableResults->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(results[i].tac_gia)));
//             tableResults->setItem(i, 4, new QTableWidgetItem(QString::number(results[i].nam_xuat_ban)));
//             tableResults->setItem(i, 5, new QTableWidgetItem(QString::fromStdString(results[i].the_loai)));
//             // tableResults->setItem(row, 6, new QTableWidgetItem(QString::fromStdString(dmsItem->ma_sach)));
//     }
// }

void BorrowDialog::onSearchClicked() {
    QString keyword = lineEditSearch->text().trimmed();
    if (keyword.isEmpty()) {
        QMessageBox::warning(this, "Lỗi", "Vui lòng nhập từ khóa tìm kiếm!");
        return;
    }

    auto results = dau_sach_mgr.searchLikeTenSach(keyword.toStdString());

    if (results.size() == 0) {
        QMessageBox::information(this, "Thông báo", "Không tìm thấy sách phù hợp!");
    }
    tableResults->setRowCount(0); // Clear bảng cũ

    for (int i = 0; i < results.size(); ++i) {
        DauSach ds = results[i];
        ds.loadDanhMucSach();

        if (ds.dms != nullptr) {
            // Duyệt một lần để vừa lọc vừa hiển thị
            ds.dms->traverse([&](DanhMucSach* dmsItem) {
                if (!muontra_mgr.isBorrowing(dmsItem->ma_sach)) {
                    int row = tableResults->rowCount();
                    tableResults->insertRow(row);
                    tableResults->setItem(row, 0, new QTableWidgetItem(QString::number(ds.ISBN)));
                    tableResults->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(ds.ten_sach)));
                    tableResults->setItem(row, 2, new QTableWidgetItem(QString::number(ds.so_trang)));
                    tableResults->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(ds.tac_gia)));
                    tableResults->setItem(row, 4, new QTableWidgetItem(QString::number(ds.nam_xuat_ban)));
                    tableResults->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(ds.the_loai)));
                    tableResults->setItem(row, 6, new QTableWidgetItem(QString::fromStdString(dmsItem->ma_sach)));
                }
            });
        }
    }
}



void BorrowDialog::onBorrowClicked() {
    int row = tableResults->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Lỗi", "Vui lòng chọn một sách để mượn!");
        return;
    }

    QString maSach = tableResults->item(row, 6)->text();

    // Lấy ngày hiện tại (yyyy-mm-dd)
    QDate currentDate = QDate::currentDate();
    QString ngayMuon = currentDate.toString("yyyy-MM-dd");

    try {
        // Gọi addRecord: trang_thai = 0 (đang mượn), ngay_tra = "" (chưa trả)
        bool success = muontra_mgr.addRecord(
            maSach.toStdString(),
            ngayMuon.toStdString(),
            "", // Ngày trả để trống (chưa trả)
            0,   // Trạng thái = 0 (đang mượn)
            this->cardId
        );

        if (success) {
            QMessageBox::information(
                this, 
                "Thành công", 
                QString("Thẻ %1 đã mượn sách có mã: %2").arg(this->cardId).arg(maSach)
            );
            accept(); // Đóng dialog sau khi mượn thành công
        } else {
            QMessageBox::warning(
                this, 
                "Lỗi", 
                "Không thể thêm bản ghi mượn sách (có thể sách đã được mượn trước đó)."
            );
        }
    } catch (const std::exception &e) {
        QMessageBox::critical(
            this, 
            "Lỗi hệ thống", 
            QString("Lỗi khi thêm bản ghi mượn sách: %1").arg(e.what())
        );
    }
}
