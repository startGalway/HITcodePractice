// sort.cpp
#include "sort.h"
#include <algorithm>

void SortBySubject(std::vector<Student>& students, Subject subj, bool descending) {
    const int idx = static_cast<int>(subj);
    std::stable_sort(students.begin(), students.end(), [=](const Student& a, const Student& b){
        if (descending) return a.scores[idx] > b.scores[idx];
        return a.scores[idx] < b.scores[idx];
    });
}

void SortByName(std::vector<Student>& students, bool ascending) {
    std::stable_sort(students.begin(), students.end(), [=](const Student& a, const Student& b){
        if (ascending) return a.name < b.name; // 按UTF-8字节序比较
        return a.name > b.name;
    });
}
