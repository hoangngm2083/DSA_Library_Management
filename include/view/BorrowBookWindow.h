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
#include "repositories/TheDocGiaManager.h"
#include "models/MuonTra.h"
#include "view/BorrowDialog.h"
#include <string>

class BorrowBookWindow : public QWidget
{
    Q_OBJECT
public:
    explicit BorrowBookWindow(QWidget *parent = nullptr);
    ~BorrowBookWindow() = default;

private slots:
    void onFindClicked();
    void onBorrowClicked();
    void onLostClicked();
    void onReturnClicked();
    void onCloseClicked();

private:
    QLineEdit *lineEditCardId;
    QPushButton *btnFind;
    QTableWidget *tableBorrowedBooks;
    QPushButton *btnBorrow;
    QPushButton *btnReturn;
    QPushButton *btnLost;
    QPushButton *btnClose;

    QVector<MuonTra> borrowedBooks;
    int cardId = -1;

    void updateBorrowedBooksTable();
    bool hasOverdueBooks() const;
};
