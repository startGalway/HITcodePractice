// print.h - 打印模块
#pragma once
#include <vector>
#include <string>
#include "types.h"
#include "analysis.h"

void PrintMenu();
void PrintStudentHeader();
void PrintStudentRow(const Student& s);
void PrintStudentsTable(const std::vector<Student>& students);
void PrintTotals(const std::vector<Student>& students);
void PrintCourseAverages(const std::array<float,kSubjectCount>& avg);
void PrintBuckets(const GradeBuckets& g);
