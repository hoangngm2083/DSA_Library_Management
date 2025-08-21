#pragma once
#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include "models/TheDocGia.h"

class TheDocGiaDialog : public QDialog
{
    Q_OBJECT
public:
    // mode thêm mới
    TheDocGiaDialog(bool isAddMode, QWidget *parent = nullptr);
    // mode sửa
    TheDocGiaDialog(const TheDocGia &dg, QWidget *parent = nullptr);

    int getMaThe() const; // chỉ dùng khi sửa
    QString getHo() const;
    QString getTen() const;
    int getPhai() const;
    int getTrangThai() const;

private:
    void setupUI();

    QLineEdit *maTheEdit;
    QLineEdit *hoEdit;
    QLineEdit *tenEdit;
    QComboBox *phaiCombo;
    QComboBox *trangThaiCombo;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    bool addMode;
};
