#include "view/DocGiaWindow.h"

DocGiaWindow::DocGiaWindow(QWidget *parent)
    : QWidget(parent)
{
    auto *mainLayout = new QVBoxLayout(this);

    // Thanh tìm kiếm
    auto *searchLayout = new QHBoxLayout();
    searchInput = new QLineEdit(this);
    btnSearch = new QPushButton("Tìm kiếm", this);
    btnAdd = new QPushButton("Thêm", this);
    searchLayout->addWidget(searchInput);
    searchLayout->addWidget(btnSearch);
    searchLayout->addWidget(btnAdd);
    mainLayout->addLayout(searchLayout);

    // Bảng hiển thị
    table = new QTableWidget(this);
    table->setColumnCount(5);
    QStringList headers;
    headers << "Mã thẻ" << "Họ" << "Tên" << "Phái" << "Trạng thái";
    table->setHorizontalHeaderLabels(headers);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mainLayout->addWidget(table);

    // Nhóm nút chức năng
    auto *btnLayout = new QHBoxLayout();
    btnDelete = new QPushButton("Xóa", this);
    btnSortByName = new QPushButton("Sắp xếp theo tên", this);
    btnSortById = new QPushButton("Sắp xếp theo mã", this);
    btnEdit = new QPushButton("Hiệu chỉnh", this);
    btnDsMuonQH = new QPushButton("Mượn sách quá hạn", this);
    btnLayout->addWidget(btnDsMuonQH);
    btnLayout->addWidget(btnEdit);
    btnLayout->addWidget(btnDelete);
    btnLayout->addWidget(btnSortByName);
    btnLayout->addWidget(btnSortById);
    mainLayout->addLayout(btnLayout);

    // Load dữ liệu ban đầu
    loadAllDocGia();

    // Kết nối signal-slot
    connect(btnDsMuonQH, &QPushButton::clicked, this, &DocGiaWindow::searchDsMuonQuaHan);
    connect(btnAdd, &QPushButton::clicked, this, &DocGiaWindow::openThemTheDocGiaDialog);
    connect(btnSearch, &QPushButton::clicked, this, &DocGiaWindow::searchTheDocGia);
    connect(btnDelete, &QPushButton::clicked, this, &DocGiaWindow::deleteTheDocGia);
    connect(btnEdit, &QPushButton::clicked, this, &DocGiaWindow::editTheDocGia);
    connect(btnSortByName, &QPushButton::clicked, this, &DocGiaWindow::sortByName);
    connect(btnSortById, &QPushButton::clicked, this, &DocGiaWindow::sortById);
}

void DocGiaWindow::openThemTheDocGiaDialog()
{
    TheDocGiaDialog dialog(true, this); // chế độ thêm mới
    if (dialog.exec() == QDialog::Accepted)
    {
        // gọi manager thêm thẻ mới (tùy logic bạn có thể auto-generate mã thẻ trong manager)
        if (tdg_mgr.addCard(dialog.getHo().toStdString(),
                            dialog.getTen().toStdString(),
                            dialog.getPhai(),
                            dialog.getTrangThai()))
        {
            loadAllDocGia();
            QMessageBox::information(this, "Thành công", "Đã thêm thẻ độc giả mới.");
        }
        else
        {
            QMessageBox::warning(this, "Thất bại", "Không thể thêm thẻ độc giả.");
        }
    }
}

void DocGiaWindow::searchTheDocGia()
{
    QString input = searchInput->text().trimmed();
    if (input.isEmpty())
    {
        // Nếu không nhập gì thì load lại tất cả
        auto list = tdg_mgr.getAllCards();
        displayResults(list);
        return;
    }

    bool ok;
    int maThe = input.toInt(&ok);
    if (!ok)
    {
        QMessageBox::warning(this, "Lỗi", "Vui lòng nhập mã thẻ hợp lệ!");
        return;
    }

    TheDocGia *dg = tdg_mgr.searchCard(maThe);
    table->setRowCount(0);
    if (dg)
    {
        table->insertRow(0);
        table->setItem(0, 0, new QTableWidgetItem(QString::number(dg->ma_the)));
        table->setItem(0, 1, new QTableWidgetItem(QString::fromStdString(dg->ho)));
        table->setItem(0, 2, new QTableWidgetItem(QString::fromStdString(dg->ten)));
        table->setItem(0, 3, new QTableWidgetItem(dg->phai == 0 ? "Nam" : "Nữ"));
        table->setItem(0, 4, new QTableWidgetItem(dg->trang_thai == 1 ? "Thẻ đang hoạt động" : "Thẻ bị khóa"));
    }
    else
    {
        QMessageBox::information(this, "Kết quả", "Không tìm thấy thẻ độc giả.");
    }
}

void DocGiaWindow::searchDsMuonQuaHan()
{

    auto dsmt = muontra_mgr.getAllRecords();
    LinearList<MuonTra> list;
    dsmt.traverse([&](MuonTra value)
                  { 
                                    if(value.trang_thai == 0 && this->isQuaHan(value.ngay_muon) )
                                    {
                                        list.push(value);
                                    } });
    list.sort([](const MuonTra &a, const MuonTra &b) -> int
              {
        if (a.ngay_muon > b.ngay_muon) return 1;
        if (a.ngay_muon < b.ngay_muon) return -1;
        return 0; });
    LinearList<TheDocGia> dsDocGia;

    list.traverse([&](MuonTra &value)
                  { 
    TheDocGia *tdg = tdg_mgr.searchCard(value.ma_the);
    if (tdg != nullptr) {
        dsDocGia.push(*tdg); 
    } });

    displayResults(dsDocGia);
}

bool DocGiaWindow::isQuaHan(const std::string &ngay_muon)
{
    QDate today = QDate::currentDate();
    QDate borrowDate = QDate::fromString(
        QString::fromStdString(ngay_muon), "yyyy-MM-dd");

    if (!borrowDate.isValid())
    {
        return false; // hoặc xử lý lỗi
    }

    int days = borrowDate.daysTo(today);
    int daysBorrowed = borrowDate.daysTo(today);

    if (days > 7)
    {
        return true; // quá hạn
    }

    return false; // chưa quá hạn hoặc ngày mượn ở tương lai
}

void DocGiaWindow::deleteTheDocGia()
{
    auto selected = table->currentRow();
    if (selected < 0)
    {
        QMessageBox::warning(this, "Lỗi", "Vui lòng chọn một thẻ để xóa!");
        return;
    }

    int maThe = table->item(selected, 0)->text().toInt();
    auto reply = QMessageBox::question(this, "Xác nhận",
                                       "Bạn có chắc chắn muốn xóa thẻ này?",
                                       QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        if (tdg_mgr.removeCard(maThe))
        {
            loadAllDocGia();
            QMessageBox::information(this, "Thành công", "Đã xóa thẻ độc giả.");
        }
        else
        {
            QMessageBox::warning(this, "Thất bại", "Không thể xóa thẻ độc giả.");
        }
    }
}

void DocGiaWindow::sortByName()
{
    auto list = tdg_mgr.getAllCards();
    list.sort([](const TheDocGia &a, const TheDocGia &b) -> int
              {
                std::string fullNameA = a.ten + " " + a.ho;
                std::string fullNameB = b.ten + " " + b.ho;
                if (fullNameA < fullNameB) return -1;
                if (fullNameA > fullNameB) return 1;
                return 0; });
    displayResults(list);
}

void DocGiaWindow::sortById()
{
    auto list = tdg_mgr.getAllCards();
    list.sort([](const TheDocGia &a, const TheDocGia &b) -> int
              {
                if (a.ma_the < b.ma_the) return -1;
                if (a.ma_the > b.ma_the) return 1;
                return 0; });
    displayResults(list);
}

void DocGiaWindow::loadAllDocGia()
{
    auto list = tdg_mgr.getAllCards();
    displayResults(list);
}

void DocGiaWindow::displayResults(const LinearList<TheDocGia> &list)
{
    table->setRowCount(0);
    for (int i = 0; i < list.size(); i++)
    {
        const auto &dg = list[i];
        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::number(dg.ma_the)));
        table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(dg.ho)));
        table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(dg.ten)));
        table->setItem(row, 3, new QTableWidgetItem(dg.phai == 0 ? "Nam" : "Nữ"));
        table->setItem(row, 4, new QTableWidgetItem(dg.trang_thai == 1 ? "Thẻ đang hoạt động" : "Thẻ bị khóa"));
    }
}

void DocGiaWindow::editTheDocGia()
{
    auto selected = table->currentRow();
    if (selected < 0)
    {
        QMessageBox::warning(this, "Lỗi", "Vui lòng chọn một thẻ để hiệu chỉnh!");
        return;
    }

    int maThe = table->item(selected, 0)->text().toInt();
    TheDocGia *dg = tdg_mgr.searchCard(maThe);
    if (!dg)
    {
        QMessageBox::warning(this, "Lỗi", "Không tìm thấy thẻ độc giả.");
        return;
    }

    TheDocGiaDialog dialog(*dg, this); // chế độ hiệu chỉnh
    if (dialog.exec() == QDialog::Accepted)
    {
        if (tdg_mgr.updateCard(dialog.getMaThe(),
                               dialog.getHo().toStdString(),
                               dialog.getTen().toStdString(),
                               dialog.getPhai(),
                               dialog.getTrangThai()))
        {
            loadAllDocGia();
            QMessageBox::information(this, "Thành công", "Đã hiệu chỉnh thẻ độc giả.");
        }
        else
        {
            QMessageBox::warning(this, "Thất bại", "Không thể hiệu chỉnh thẻ độc giả.");
        }
    }
}
