// print.cpp
#include "print.h"
#include <iostream>
#include <iomanip>
#include "calculate.h"

static const char* SubjectName(int i) {
    switch (i) {
        case 0: return "iCS"; case 1: return "PDP"; case 2: return "DS"; default: return "DL";
    }
}

void PrintMenu() {
    std::cout << "1. Append record\n"
              << "2. Search by name\n"
              << "3. Search by ID\n"
              << "4. Modify by ID\n"
              << "5. Delete by ID\n"
              << "6. Caculate total and average score of every student\n"
              << "7. Caculate average score of every course\n"
              << "8. Sort in descending/ascending order by course score\n"
              << "9. Statistic analysis for every course\n"
              << "10.Save to text file\n"
              << "11.Load from text file\n"
              << "12.Save to binary file\n"
              << "13.Load from binary file\n"
              << "14.Sort by name (UTF-8)\n"
              << "15.Clear all records\n\n"
              << "0. Exit\n"
              << "Please enter your choice: ";
}

void PrintStudentHeader() {
    std::cout << std::left << std::setw(14) << "ID"
              << std::left << std::setw(14) << "Name"
              << std::right << std::setw(8) << "iCS"
              << std::right << std::setw(8) << "PDP"
              << std::right << std::setw(8) << "DS"
              << std::right << std::setw(8) << "DL" << "\n";
}

void PrintStudentRow(const Student& s) {
    std::cout << std::left << std::setw(14) << s.id
              << std::left << std::setw(14) << s.name
              << std::right << std::setw(8) << std::fixed << std::setprecision(2) << s.scores[0]
              << std::right << std::setw(8) << s.scores[1]
              << std::right << std::setw(8) << s.scores[2]
              << std::right << std::setw(8) << s.scores[3] << "\n";
}

void PrintStudentsTable(const std::vector<Student>& students) {
    PrintStudentHeader();
    for (const auto& s : students) PrintStudentRow(s);
}

void PrintTotals(const std::vector<Student>& students) {
    auto tv = CalcTotalAndAverage(students);
    PrintStudentHeader();
    for (size_t i=0;i<students.size();++i) {
        const auto& s = students[i];
        std::cout << std::left << std::setw(14) << s.id
                  << std::left << std::setw(14) << s.name
                  << std::right << std::setw(8) << s.scores[0]
                  << std::right << std::setw(8) << s.scores[1]
                  << std::right << std::setw(8) << s.scores[2]
                  << std::right << std::setw(8) << s.scores[3]
                  << "  | Total=" << std::setw(6) << tv[i].first
                  << " Avg=" << std::setw(6) << std::setprecision(2) << tv[i].second << "\n";
    }
}

void PrintCourseAverages(const std::array<float,kSubjectCount>& avg) {
    for (int i=0;i<kSubjectCount;++i) {
        std::cout << SubjectName(i) << " avg: " << std::fixed << std::setprecision(2) << avg[i] << "\n";
    }
}

void PrintBuckets(const GradeBuckets& g) {
    static const char* bucketNames[5] = {"90-100","80-89","70-79","60-69","0-59"};
    for (int s=0;s<kSubjectCount;++s) {
        std::cout << SubjectName(s) << ":\n";
        for (int b=0;b<5;++b) {
            std::cout << "  " << bucketNames[b] << ": " << g.buckets[s][b]
                      << " (" << std::fixed << std::setprecision(2) << g.percent[s][b] << "%)\n";
        }
    }
}
