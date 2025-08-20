#pragma once
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include "repositories/DauSachManager.h"
#include "models/DauSach.h"
#include "models/DanhMucSach.h"
#include <QIntValidator>
#include <QRegularExpressionValidator>

class ThemDauSachDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ThemDauSachDialog(QWidget *parent = nullptr);
    int getISBN() const { return ISBN; }

private slots:
    void onAddClicked();
    void onCloseClicked();

private:
    // QLineEdit *lineEditISBN;
    QLineEdit *lineEditTenSach;
    QLineEdit *lineEditSoTrang;
    QLineEdit *lineEditTacGia;
    QLineEdit *lineEditNamXuatBan;
    QLineEdit *lineEditTheLoai;
    QPushButton *btnAdd;
    QPushButton *btnClose;
    int ISBN;
};