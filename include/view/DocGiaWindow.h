#pragma once
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QInputDialog>
#include "models/TheDocGia.h"
#include <QHeaderView>
#include "view/TheDocGiaDialog.h"
#include "data_structs/LinearList.h"
#include "repositories/TheDocGiaManager.h"
#include "repositories/MuonTraManager.h"
#include <QDate>

class DocGiaWindow : public QWidget
{
    Q_OBJECT
public:
    explicit DocGiaWindow(QWidget *parent = nullptr);

private slots:
    void openThemTheDocGiaDialog();
    void searchTheDocGia();
    void editTheDocGia();
    void deleteTheDocGia();
    void sortByName();
    void sortById();
    void searchDsMuonQuaHan();
    bool isQuaHan(const std::string &ngay_muon);

private:
    void loadAllDocGia();
    void displayResults(const LinearList<TheDocGia> &list);

    QLineEdit *searchInput;
    QPushButton *btnSearch;
    QPushButton *btnAdd;
    QPushButton *btnEdit;
    QPushButton *btnDelete;
    QPushButton *btnSortByName;
    QPushButton *btnSortById;
    QPushButton *btnDsMuonQH;
    QTableWidget *table;
};
