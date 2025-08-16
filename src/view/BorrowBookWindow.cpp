#include "view/BorrowBookWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QHeaderView>
#include <QDate>

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
    tableBorrowedBooks->setColumnCount(2);
    tableBorrowedBooks->setHorizontalHeaderLabels({"Tên sách", "Ngày mượn"});
    tableBorrowedBooks->horizontalHeader()->setStretchLastSection(true);

    // Hàng nút
    auto *btnLayout = new QHBoxLayout;
    btnBorrow = new QPushButton("Mượn sách");
    btnClose = new QPushButton("Đóng");
    btnLayout->addStretch();
    btnLayout->addWidget(btnBorrow);
    btnLayout->addWidget(btnClose);

    // Thêm vào layout chính
    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(tableBorrowedBooks);
    mainLayout->addLayout(btnLayout);

    // Kết nối signal-slot
    connect(btnFind, &QPushButton::clicked, this, &BorrowBookWindow::onFindClicked);
    connect(btnBorrow, &QPushButton::clicked, this, &BorrowBookWindow::onBorrowClicked);
    connect(btnClose, &QPushButton::clicked, this, &BorrowBookWindow::onCloseClicked);
}

void BorrowBookWindow::onFindClicked() {
    QString cardId = lineEditCardId->text().trimmed();
    if (cardId.isEmpty()) {
        QMessageBox::warning(this, "Lỗi", "Vui lòng nhập mã thẻ độc giả!");
        return;
    }

    // TODO: load borrowedBooks từ DB theo cardId
    borrowedBooks.clear();
    borrowedBooks.append({"C++ Primer", QDate::currentDate().addDays(-2)});
    borrowedBooks.append({"Clean Code", QDate::currentDate().addDays(-8)}); // quá hạn
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

    // TODO: thêm logic mượn sách (vd: mở dialog chọn sách)
    QMessageBox::information(this, "Thành công", "Mượn sách thành công!");
}

void BorrowBookWindow::onCloseClicked() {
    close();
}

void BorrowBookWindow::updateBorrowedBooksTable() {
    tableBorrowedBooks->setRowCount(borrowedBooks.size());
    for (int i = 0; i < borrowedBooks.size(); ++i) {
        tableBorrowedBooks->setItem(i, 0,
            new QTableWidgetItem(borrowedBooks[i].title));
        tableBorrowedBooks->setItem(i, 1,
            new QTableWidgetItem(borrowedBooks[i].borrowDate.toString("dd/MM/yyyy")));
    }
}

bool BorrowBookWindow::hasOverdueBooks() const {
    QDate today = QDate::currentDate();
    for (auto &b : borrowedBooks) {
        if (b.borrowDate.daysTo(today) > 7) return true;
    }
    return false;
}
