// search.cpp
#include "search.h"

int FindById(const std::vector<Student>& students, const std::string& id) {
    for (size_t i = 0; i < students.size(); ++i) if (students[i].id == id) return static_cast<int>(i);
    return -1;
}

std::vector<int> FindByName(const std::vector<Student>& students, const std::string& name) {
    std::vector<int> idxs;
    for (size_t i = 0; i < students.size(); ++i) if (students[i].name == name) idxs.push_back(static_cast<int>(i));
    return idxs;
}
