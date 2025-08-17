#ifndef MUON_TRA_MANAGER_H
#define MUON_TRA_MANAGER_H

#include "models/MuonTra.h"
#include "data_structs/LinkedList.h"
#include "data_structs/LinearList.h"
#include "BaseManager.h"
#include <string>
#include <stdexcept>
#include <limits>

class MuonTraManager : public BaseManager<MuonTra>
{
private:
    LinkedList<MuonTra *> list; // Singly linked list to store MuonTra pointers

    bool readItem(std::istream &in, MuonTra &obj) override;
    void writeItem(std::ostream &out, const MuonTra &obj) override;
    void saveItems()  override;
    void loadItems()  override;

public:
    MuonTraManager();
    ~MuonTraManager();

    // Add a new borrowing record
    bool addRecord(const std::string &ma_sach, const std::string &ngay_muon,
                   const std::string &ngay_tra, int trang_thai, int ma_the);

    // Remove a borrowing record by ma_sach and ma_the
    bool removeRecord(const std::string &ma_sach, const std::string &ngay_muon);

    // Update a borrowing record
    bool updateRecord(const std::string &ma_sach, const std::string &ngay_muon,
                      const std::string &ngay_tra, int trang_thai);

    // Search for a borrowing record by ma_sach and ma_the
    MuonTra *searchRecord(const std::string &ma_sach, const std::string &ngay_muon) ;
    // Overload: search by ma_the
    LinkedList<MuonTra *> searchRecords(int ma_the) ;

    // Get all borrowing records
    LinearList<MuonTra> getAllRecords() ;

    // Check if a borrowing record exists
    bool isRecordExist(const std::string &ma_sach, const std::string &ngay_muon) ;
    bool isBorrowing(const std::string &ma_sach) ;
};

extern MuonTraManager muontra_mgr;

// #include "../../src/repositories/MuonTraManager.cpp"

#endif // MUON_TRA_MANAGER_H