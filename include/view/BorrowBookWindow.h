#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QDate>
#include <QString>
#include <QVector>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QHeaderView>
#include "repositories/MuonTraManager.h"
#include "models/MuonTra.h"


class BorrowBookWindow : public QWidget {
    Q_OBJECT
public:
    explicit BorrowBookWindow(QWidget *parent = nullptr);
    ~BorrowBookWindow() = default;

private slots:
    void onFindClicked();
    void onBorrowClicked();
    void onCloseClicked();

private:
    QLineEdit *lineEditCardId;
    QPushButton *btnFind;
    QTableWidget *tableBorrowedBooks;
    QPushButton *btnBorrow;
    QPushButton *btnClose;

    QVector<MuonTra> borrowedBooks;

    void updateBorrowedBooksTable();
    bool hasOverdueBooks() const;
};
