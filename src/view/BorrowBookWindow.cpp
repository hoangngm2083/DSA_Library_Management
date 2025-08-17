#include "view/BorrowBookWindow.h"

BorrowBookWindow::BorrowBookWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Mượn sách");

    // Layout chính
    auto *mainLayout = new QVBoxLayout(this);

    // Hàng nhập liệu
    auto *inputLayout = new QHBoxLayout;
    auto *lblCardId = new QLabel("Mã thẻ độc giả:");
    lineEditCardId = new QLineEdit;
    btnFind = new QPushButton("Tìm");
    inputLayout->addWidget(lblCardId);
    inputLayout->addWidget(lineEditCardId);
    inputLayout->addWidget(btnFind);

    // Bảng sách đang mượn
    tableBorrowedBooks = new QTableWidget(this);
    tableBorrowedBooks->setColumnCount(5);
    tableBorrowedBooks->setHorizontalHeaderLabels(
        {"Mã sách", "Ngày mượn", "Ngày trả", "Trạng thái", "Mã thẻ"});
    tableBorrowedBooks->horizontalHeader()->setStretchLastSection(true);

    // Hàng nút
    auto *btnLayout = new QHBoxLayout;
    btnReturn = new QPushButton("Trả sách");
    btnLost = new QPushButton("Làm mất sách");
    btnBorrow = new QPushButton("Mượn sách");
    btnClose = new QPushButton("Đóng");
    btnLayout->addStretch();
    btnLayout->addWidget(btnLost);
    btnLayout->addWidget(btnReturn);
    btnLayout->addWidget(btnBorrow);
    btnLayout->addWidget(btnClose);

    // Thêm vào layout chính
    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(tableBorrowedBooks);
    mainLayout->addLayout(btnLayout);

    // Kết nối signal-slot
    connect(btnFind, &QPushButton::clicked, this, &BorrowBookWindow::onFindClicked);
    connect(btnLost, &QPushButton::clicked, this, &BorrowBookWindow::onLostClicked);
    connect(btnReturn, &QPushButton::clicked, this, &BorrowBookWindow::onReturnClicked);
    connect(btnBorrow, &QPushButton::clicked, this, &BorrowBookWindow::onBorrowClicked);
    connect(btnClose, &QPushButton::clicked, this, &BorrowBookWindow::onCloseClicked);
}

void BorrowBookWindow::onFindClicked() {
    QString cardIdStr = lineEditCardId->text().trimmed();
    if (cardIdStr.isEmpty()) {
        QMessageBox::warning(this, "Lỗi", "Vui lòng nhập mã thẻ độc giả!");
        return;
    }

    bool ok;
    int cardId = cardIdStr.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Lỗi", "Mã thẻ độc giả phải là số nguyên hợp lệ!");
        return;
    }

    this->cardId = cardId;

    // Lấy danh sách mượn/trả từ "DB" (manager)
    auto list = muontra_mgr.searchRecords(cardId);

    borrowedBooks.clear();
    list.traverse([&](MuonTra *value) {
        if(value->trang_thai == 0)
        {
            borrowedBooks.append(*value);   // copy từ con trỏ ra QVector
        }
    });

    updateBorrowedBooksTable();
}

void BorrowBookWindow::onBorrowClicked() {
    if (borrowedBooks.size() >= 3) {
        QMessageBox::warning(this, "Không thể mượn",
                             "Độc giả đã mượn tối đa 3 cuốn sách!");
        return;
    }
    if (hasOverdueBooks()) {
        QMessageBox::warning(this, "Không thể mượn",
                             "Độc giả có sách quá hạn (7 ngày)!");
        return;
    }


    BorrowDialog dlg(this, this->cardId);
    dlg.exec();
}

void BorrowBookWindow::onReturnClicked() {
    int row = tableBorrowedBooks->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Lỗi", "Vui lòng chọn một sách để trả!");
        return;
    }
    QString ma_sach = tableBorrowedBooks->item(row, 0)->text();
    QString ngay_muon = tableBorrowedBooks->item(row, 1)->text();
    // std::cout << ma_sach.toStdString() << std::endl;
    // std::cout << ngay_muon.toStdString() << std::endl;
    QDate currentDate = QDate::currentDate();
    QString ngay_tra = currentDate.toString("yyyy-MM-dd");
    int trang_thai = 1;

   if(!muontra_mgr.updateRecord(ma_sach.toStdString(), ngay_muon.toStdString(), ngay_tra.toStdString(), trang_thai))
   {
        QMessageBox::warning(this, "Lỗi", "Có lỗi xảy ra!");
        return;
   }
   this->onFindClicked();
}

void BorrowBookWindow::onLostClicked() {
    int row = tableBorrowedBooks->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Lỗi", "Vui lòng chọn một sách để cập nhật làm mất!");
        return;
    }
    QString ma_sach = tableBorrowedBooks->item(row, 0)->text();
    QString ngay_muon = tableBorrowedBooks->item(row, 1)->text();
    std::string ngay_tra = "";
    int trang_thai = 2;

   if(!muontra_mgr.updateRecord(ma_sach.toStdString(), ngay_muon.toStdString(), ngay_tra, trang_thai))
   {
        QMessageBox::warning(this, "Lỗi", "Có lỗi xảy ra!");
        return;
   }
   this->onFindClicked();
}

void BorrowBookWindow::onCloseClicked() {
    close();
}

void BorrowBookWindow::updateBorrowedBooksTable() {
    tableBorrowedBooks->setRowCount(borrowedBooks.size());

    for (int i = 0; i < borrowedBooks.size(); ++i) {
        const MuonTra &mt = borrowedBooks[i];

        // Cột 0: Mã sách
        tableBorrowedBooks->setItem(i, 0,
            new QTableWidgetItem(QString::fromStdString(mt.ma_sach)));

        // Cột 1: Ngày mượn
        tableBorrowedBooks->setItem(i, 1,
            new QTableWidgetItem(QString::fromStdString(mt.ngay_muon)));

        // Cột 2: Ngày trả
        tableBorrowedBooks->setItem(i, 2,
            new QTableWidgetItem(QString::fromStdString(mt.ngay_tra)));

        // Cột 3: Trạng thái
        QString status;
        switch (mt.trang_thai) {
            case 0: status = "Đang mượn"; break;
            case 1: status = "Đã trả"; break;
            case 2: status = "Mất sách"; break;
            default: status = "Không rõ"; break;
        }
        tableBorrowedBooks->setItem(i, 3,
            new QTableWidgetItem(status));

        // Cột 4: Mã thẻ
        tableBorrowedBooks->setItem(i, 4,
            new QTableWidgetItem(QString::number(mt.ma_the)));
    }
}

bool BorrowBookWindow::hasOverdueBooks() const {
    QDate today = QDate::currentDate();

    for (const auto &b : borrowedBooks) {
        if (b.trang_thai == 0) { // chỉ xét sách đang mượn
            QDate borrowDate = QDate::fromString(
                QString::fromStdString(b.ngay_muon), "yyyy-MM-dd"); // Sửa định dạng
            if (borrowDate.isValid() && borrowDate.daysTo(today) > 7) {
                return true;
            }
        }
    }
    return false;
}
