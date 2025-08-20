#include "view/ThemDanhMucSachDialog.h"

ThemDanhMucSachDialog::ThemDanhMucSachDialog(int ISBN, QWidget *parent)
    : QDialog(parent), ISBN(ISBN)
{
    setWindowTitle("Thêm danh mục sách");
    resize(400, 500); // Tăng chiều cao để chứa cả hai phần

    auto *mainLayout = new QVBoxLayout(this);

    // Phần trên: Hiển thị thông tin DauSach
    auto *dauSachLayout = new QVBoxLayout;
    dauSachLayout->addWidget(new QLabel("Thông tin đầu sách:", this));

    // Tạo các label để hiển thị thông tin DauSach
    labelISBN = new QLabel(this);
    labelTenSach = new QLabel(this);
    labelSoTrang = new QLabel(this);
    labelTacGia = new QLabel(this);
    labelNamXuatBan = new QLabel(this);
    labelTheLoai = new QLabel(this);
    // Lấy thông tin DauSach từ DauSachManager
    DauSach *dauSach = dau_sach_mgr.searchRecord(ISBN);
    if (dauSach)
    {
        labelISBN->setText(QString("ISBN: %1").arg(dauSach->ISBN));
        labelTenSach->setText(QString("Tên sách: %1").arg(QString::fromStdString(dauSach->ten_sach)));
        labelSoTrang->setText(QString("Số trang: %1").arg(dauSach->so_trang));
        labelTacGia->setText(QString("Tác giả: %1").arg(QString::fromStdString(dauSach->tac_gia)));
        labelNamXuatBan->setText(QString("Năm xuất bản: %1").arg(dauSach->nam_xuat_ban));
        labelTheLoai->setText(QString("Thể loại: %1").arg(QString::fromStdString(dauSach->the_loai)));
    }
    else
    {
        labelISBN->setText("ISBN: Không tìm thấy");
        labelTenSach->setText("Tên sách: Không tìm thấy");
        labelSoTrang->setText("Số trang: Không tìm thấy");
        labelTacGia->setText("Tác giả: Không tìm thấy");
        labelNamXuatBan->setText("Năm xuất bản: Không tìm thấy");
        labelTheLoai->setText("Thể loại: Không tìm thấy");
    }

    dauSachLayout->addWidget(labelISBN);
    dauSachLayout->addWidget(labelTenSach);
    dauSachLayout->addWidget(labelSoTrang);
    dauSachLayout->addWidget(labelTacGia);
    dauSachLayout->addWidget(labelNamXuatBan);
    dauSachLayout->addWidget(labelTheLoai);

    // Phần dưới: Form nhập liệu cho DanhMucSach
    auto *formLayout = new QVBoxLayout;
    formLayout->addWidget(new QLabel("Thông tin danh mục sách:", this));

    // Chỉ cho phép mã sách là chữ và số, không chứa ký tự đặc biệt
    comboBoxTrangThai = new QComboBox;
    comboBoxTrangThai->addItem("Cho mượn được", 0);
    comboBoxTrangThai->addItem("Đã có độc giả mượn", 1);
    comboBoxTrangThai->addItem("Sách đã thanh lý ", 2);
    lineEditViTri = new QLineEdit;

    formLayout->addWidget(new QLabel("Trạng thái:"));
    formLayout->addWidget(comboBoxTrangThai);
    formLayout->addWidget(new QLabel("Vị trí:"));
    formLayout->addWidget(lineEditViTri);

    // Layout cho nút
    auto *btnLayout = new QHBoxLayout;
    btnAdd = new QPushButton("Thêm");
    btnClose = new QPushButton("Đóng");
    btnLayout->addStretch();
    btnLayout->addWidget(btnAdd);
    btnLayout->addWidget(btnClose);

    // Thêm các layout vào mainLayout
    mainLayout->addLayout(dauSachLayout);
    mainLayout->addStretch(); // Tạo khoảng cách giữa hai phần
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(btnLayout);

    // Kết nối signal-slot
    connect(btnAdd, &QPushButton::clicked, this, &ThemDanhMucSachDialog::onAddClicked);
    connect(btnClose, &QPushButton::clicked, this, &ThemDanhMucSachDialog::onCloseClicked);
}

void ThemDanhMucSachDialog::onAddClicked()
{

    int trangThai = comboBoxTrangThai->currentData().toInt();
    QString viTri = lineEditViTri->text().trimmed();
    if (viTri.isEmpty())
    {
        QMessageBox::warning(this, "Lỗi", "Vị trí không được để trống!");
        return;
    }

    try
    {
        // Thêm danh mục sách vào DanhMucSachManager

        std::string ma_sach = dms_mgr.addRecord(trangThai, viTri.toStdString(), ISBN);

        QMessageBox::information(
            this,
            "Thành công",
            QString("Đã thêm danh mục sách: %1").arg(QString::fromStdString(ma_sach)));
        resetForm(); // Reset form
        // accept();    // Đóng dialog sau khi thêm thành công
    }
    catch (const std::exception &e)
    {
        QMessageBox::critical(
            this,
            "Lỗi hệ thống",
            QString("Lỗi khi thêm danh mục sách: %1").arg(e.what()));
    }
}

void ThemDanhMucSachDialog::onCloseClicked()
{
    reject();
}

void ThemDanhMucSachDialog::resetForm()
{
    comboBoxTrangThai->setCurrentIndex(0); // Mặc định là "Có sẵn"
    lineEditViTri->clear();
}