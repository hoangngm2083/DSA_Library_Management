#ifndef ID_MANAGER_H
#define ID_MANAGER_H

#include <random>
#include "data_structs/HashSet.h"
#include "BaseManager.h"

class IdManager : public BaseManager<int> {
    std::mt19937 gen;
    std::uniform_int_distribution<int> dist;
    HashSet used; // tập lưu các ID đã sinh

private:
    bool readItem(std::istream &in, int &obj) override;
    void writeItem(std::ostream &out, const int &obj) override;
    void saveItems() override;
    void loadItems() override;

public:
    IdManager()
      : BaseManager("data/card_ids.txt"),   // file lưu ID đã sinh
        gen(std::random_device{}()),
        dist(100000, 999999) {
        this->loadItems(); // đọc các ID đã sinh từ file
    }

    int next() {
        this->loadItems();
        while (true) {
            int id = dist(gen);
            if (used.insert(id)){
                this->saveItems();
                return id;
            } // chưa trùng
        }
    }
};
extern IdManager id_mgr;

#endif // ID_MANAGER_H
