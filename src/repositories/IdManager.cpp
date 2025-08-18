#include "repositories/IdManager.h"
#include <limits>


IdManager id_mgr;

bool IdManager::readItem(std::istream &in, int &obj) {
    if (!(in >> obj)) return false;
    return true;
}

void IdManager::writeItem(std::ostream &out, const int &obj) {
    out << obj << "\n";
}

void IdManager::saveItems() {
    // Duyệt qua HashSet used và ghi tất cả các ID vào file
    LinearList<int> ids = used.toLinearList(); 
    this->writeToFile(ids);
}

void IdManager::loadItems() {
    used.clear();
    auto items = this->readFromFile();
    for (int i = 0; i < items.size(); i++) {
        used.insert(items[i]);
    }
}
