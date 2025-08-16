#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QDate>
#include <QString>
#include <QVector>

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

    struct BookRecord {
        QString title;
        QDate borrowDate;
    };
    QVector<BookRecord> borrowedBooks;

    void updateBorrowedBooksTable();
    bool hasOverdueBooks() const;
};
