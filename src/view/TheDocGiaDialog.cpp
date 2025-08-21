#include "view/TheDocGiaDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

TheDocGiaDialog::TheDocGiaDialog(bool isAddMode, QWidget *parent)
    : QDialog(parent), addMode(isAddMode)
{
    setupUI();
    setWindowTitle("Thêm thẻ độc giả");

    maTheEdit->setVisible(false); // khi thêm mới, không hiển thị mã thẻ

    // Mặc định giá trị khi thêm mới
    hoEdit->clear();
    tenEdit->clear();
    phaiCombo->setCurrentIndex(0);         // Nam
    int idx = trangThaiCombo->findData(1); // Active
    if (idx != -1)
        trangThaiCombo->setCurrentIndex(idx);
}

TheDocGiaDialog::TheDocGiaDialog(const TheDocGia &dg, QWidget *parent)
    : QDialog(parent), addMode(false)
{
    setupUI();
    setWindowTitle("Hiệu chỉnh thẻ độc giả");

    // Hiển thị mã thẻ nhưng không cho sửa
    maTheEdit->setText(QString::number(dg.ma_the));
    maTheEdit->setReadOnly(true);

    // Set các trường khác
    hoEdit->setText(QString::fromStdString(dg.ho));
    tenEdit->setText(QString::fromStdString(dg.ten));

    int phaiIdx = phaiCombo->findData(dg.phai);
    if (phaiIdx != -1)
        phaiCombo->setCurrentIndex(phaiIdx);

    int ttIdx = trangThaiCombo->findData(dg.trang_thai);
    if (ttIdx != -1)
        trangThaiCombo->setCurrentIndex(ttIdx);
}

void TheDocGiaDialog::setupUI()
{
    auto *layout = new QVBoxLayout(this);

    // Mã thẻ
    auto *maLayout = new QHBoxLayout();
    maLayout->addWidget(new QLabel("Mã thẻ:"));
    maTheEdit = new QLineEdit();
    maLayout->addWidget(maTheEdit);
    layout->addLayout(maLayout);

    // Họ
    auto *hoLayout = new QHBoxLayout();
    hoLayout->addWidget(new QLabel("Họ:"));
    hoEdit = new QLineEdit();
    hoLayout->addWidget(hoEdit);
    layout->addLayout(hoLayout);

    // Tên
    auto *tenLayout = new QHBoxLayout();
    tenLayout->addWidget(new QLabel("Tên:"));
    tenEdit = new QLineEdit();
    tenLayout->addWidget(tenEdit);
    layout->addLayout(tenLayout);

    // Phái
    auto *phaiLayout = new QHBoxLayout();
    phaiLayout->addWidget(new QLabel("Phái:"));
    phaiCombo = new QComboBox();
    phaiCombo->addItem("Nam", 0);
    phaiCombo->addItem("Nữ", 1);
    phaiLayout->addWidget(phaiCombo);
    layout->addLayout(phaiLayout);

    // Trạng thái
    auto *ttLayout = new QHBoxLayout();
    ttLayout->addWidget(new QLabel("Trạng thái:"));
    trangThaiCombo = new QComboBox();
    trangThaiCombo->addItem("Thẻ bị khóa", 0);
    trangThaiCombo->addItem("Thẻ đang hoạt động", 1);
    ttLayout->addWidget(trangThaiCombo);
    layout->addLayout(ttLayout);

    // Nút
    auto *btnLayout = new QHBoxLayout();
    okBtn = new QPushButton("OK");
    cancelBtn = new QPushButton("Hủy");
    btnLayout->addWidget(okBtn);
    btnLayout->addWidget(cancelBtn);
    layout->addLayout(btnLayout);

    connect(okBtn, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
}

int TheDocGiaDialog::getMaThe() const
{
    return maTheEdit->text().toInt();
}
QString TheDocGiaDialog::getHo() const { return hoEdit->text(); }
QString TheDocGiaDialog::getTen() const { return tenEdit->text(); }
int TheDocGiaDialog::getPhai() const { return phaiCombo->currentData().toInt(); }
int TheDocGiaDialog::getTrangThai() const { return trangThaiCombo->currentData().toInt(); }
