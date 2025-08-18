#include "ThemDauSachDialog.h"
#include <QIntValidator>
#include <QRegularExpressionValidator>

ThemDauSachDialog::ThemDauSachDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Thêm đầu sách");
    resize(400, 300);

    auto *mainLayout = new QVBoxLayout(this);

    // Tạo layout cho các trường nhập liệu
    // lineEditISBN = new QLineEdit;
    // lineEditISBN->setValidator(new QIntValidator(0, 999999999, this)); // Chỉ cho phép số nguyên
    lineEditTenSach = new QLineEdit;
    lineEditSoTrang = new QLineEdit;
    lineEditSoTrang->setValidator(new QIntValidator(1, 10000, this));
    lineEditTacGia = new QLineEdit;
    lineEditNamXuatBan = new QLineEdit;
    lineEditNamXuatBan->setValidator(new QIntValidator(1000, 9999, this));
    lineEditTheLoai = new QLineEdit;

    // Layout cho từng trường
    auto *formLayout = new QVBoxLayout;
    // formLayout->addWidget(new QLabel("ISBN:"));
    // formLayout->addWidget(lineEditISBN);
    formLayout->addWidget(new QLabel("Tên sách:"));
    formLayout->addWidget(lineEditTenSach);
    formLayout->addWidget(new QLabel("Số trang:"));
    formLayout->addWidget(lineEditSoTrang);
    formLayout->addWidget(new QLabel("Tác giả:"));
    formLayout->addWidget(lineEditTacGia);
    formLayout->addWidget(new QLabel("Năm xuất bản:"));
    formLayout->addWidget(lineEditNamXuatBan);
    formLayout->addWidget(new QLabel("Thể loại:"));
    formLayout->addWidget(lineEditTheLoai);

    // Layout cho nút
    auto *btnLayout = new QHBoxLayout;
    btnAdd = new QPushButton("Thêm");
    btnClose = new QPushButton("Đóng");
    btnLayout->addStretch();
    btnLayout->addWidget(btnAdd);
    btnLayout->addWidget(btnClose);

    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(btnLayout);

    // Kết nối signal-slot
    connect(btnAdd, &QPushButton::clicked, this, &ThemDauSachDialog::onAddClicked);
    connect(btnClose, &QPushButton::clicked, this, &ThemDauSachDialog::onCloseClicked);
}

void ThemDauSachDialog::onAddClicked() {
    // kiểm tra tính hợp lệ của dữ liệu nhập vào khi bạn chuyển đổi QString sang int.
    bool ok;
    // Lấy dữ liệu từ các trường
    // int ISBN = lineEditISBN->text().toInt(&ok);
    // if (!ok || ISBN <= 0) {
    //     QMessageBox::warning(this, "Lỗi", "ISBN phải là số nguyên dương!");
    //     return;
    // }
    QString tenSach = lineEditTenSach->text().trimmed();
    if (tenSach.isEmpty()) {
        QMessageBox::warning(this, "Lỗi", "Tên sách không được để trống!");
        return;
    }
    int soTrang = lineEditSoTrang->text().toInt(&ok);
    if (!ok || soTrang <= 0) {
        QMessageBox::warning(this, "Lỗi", "Số trang phải là số nguyên dương!");
        return;
    }
    QString tacGia = lineEditTacGia->text().trimmed();
    if (tacGia.isEmpty()) {
        QMessageBox::warning(this, "Lỗi", "Tác giả không được để trống!");
        return;
    }
    int namXuatBan = lineEditNamXuatBan->text().toInt(&ok);
    if (!ok || namXuatBan < 1000 || namXuatBan > 9999) {
        QMessageBox::warning(this, "Lỗi", "Năm xuất bản phải là số từ 1000 đến 9999!");
        return;
    }
    QString theLoai = lineEditTheLoai->text().trimmed();
    if (theLoai.isEmpty()) {
        QMessageBox::warning(this, "Lỗi", "Thể loại không được để trống!");
        return;
    }

    try {
        // Thêm đầu sách vào DauSachManager
        int ISBN = dau_sach_mgr.addRecord(
            tenSach.toStdString(),
            soTrang,
            tacGia.toStdString(),
            namXuatBan,
            theLoai.toStdString()
        );

        // // Tạo mã sách tự động (ISBN-001)
        // std::string maSach = generateMaSach(ISBN, 1);
        // DanhMucSach* danhMucSach = new DanhMucSach();
        // danhMucSach->ma_sach = maSach;
        // danhMucSach->trang_thai = 0; // Sách có thể mượn

        // // Thêm DanhMucSach vào DauSach
        // if (!dau_sach_mgr.addDanhMucSach(ISBN, danhMucSach)) {
        //     QMessageBox::warning(this, "Lỗi", "Không thể thêm mã sách vào danh mục!");
        //     return;
        // }

        QMessageBox::information(
            this,
            "Thành công",
            QString("Đã thêm đầu sách: %1\nISBN: %2").arg(tenSach).arg(QString::number(ISBN))
        );
        accept(); // Đóng dialog sau khi thêm thành công
    } catch (const std::exception &e) {
        QMessageBox::critical(
            this,
            "Lỗi hệ thống",
            QString("Lỗi khi thêm đầu sách: %1").arg(e.what())
        );
    }
}

void ThemDauSachDialog::onCloseClicked() {
    reject();
}
