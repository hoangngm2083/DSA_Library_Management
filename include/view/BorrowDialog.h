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
#include "repositories/MuonTraManager.h"
#include <QDate> 


class BorrowDialog : public QDialog {
    Q_OBJECT
public:
    explicit BorrowDialog(QWidget *parent = nullptr, int cardId = -1);

private slots:
    void onSearchClicked();
    void onBorrowClicked();

private:
    QLineEdit *lineEditSearch;
    QPushButton *btnSearch;
    QTableWidget *tableResults;
    QPushButton *btnBorrow;
    QPushButton *btnClose;
    int cardId;
};
