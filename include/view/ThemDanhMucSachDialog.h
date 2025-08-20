#pragma once
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QComboBox>
#include "repositories/DanhMucSachManager.h"
#include "repositories/DauSachManager.h"
#include "models/DanhMucSach.h"
#include "models/DauSach.h"
#include <QRegularExpressionValidator>

class ThemDanhMucSachDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ThemDanhMucSachDialog(int ISBN, QWidget *parent = nullptr);

private slots:
    void onAddClicked();
    void onCloseClicked();

private:
    QLineEdit *lineEditMaSach;
    QComboBox *comboBoxTrangThai;
    QLineEdit *lineEditViTri;
    QPushButton *btnAdd;
    QPushButton *btnClose;
    QLabel *labelISBN;
    QLabel *labelTenSach;
    QLabel *labelSoTrang;
    QLabel *labelTacGia;
    QLabel *labelNamXuatBan;
    QLabel *labelTheLoai;
    int ISBN;         // Nhận từ MainWindow
    void resetForm(); // Reset form về trạng thái trống
};