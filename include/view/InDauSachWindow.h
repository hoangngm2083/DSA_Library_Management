#pragma once
#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QHeaderView>
#include "repositories/DauSachManager.h"
#include "models/DauSach.h"

class InDauSachWindow : public QWidget
{
    Q_OBJECT
public:
    explicit InDauSachWindow(QWidget *parent = nullptr);
    ~InDauSachWindow() = default;

private slots:
    void onRefreshClicked();
    void onCloseClicked();

private:
    QTableWidget *tableBooks;
    QPushButton *btnRefresh;
    QPushButton *btnClose;

    void loadBooksByCategory();
};
