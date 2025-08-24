#pragma once
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QHeaderView>
#include "repositories/DauSachManager.h"
#include "models/DauSach.h"
#include "models/DanhMucSach.h"
#include <QDate>

class TimTenSachDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TimTenSachDialog(QWidget *parent = nullptr, int cardId = -1);

private slots:
    void onSearchClicked();

private:
    QLineEdit *lineEditSearch;
    QPushButton *btnSearch;
    QTableWidget *tableResults;
    QPushButton *btnClose;
    int cardId;
};
