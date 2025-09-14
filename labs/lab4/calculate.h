// calculate.h - 计算模块
#pragma once
#include <vector>
#include "types.h"

// 返回每个学生的总分与平均分（与 students 同长度）
std::vector<std::pair<float,float>> CalcTotalAndAverage(const std::vector<Student>& students);

// 返回各科平均分（按顺序：ICS,PDP,DS,DL）
std::array<float, kSubjectCount> CalcCourseAverage(const std::vector<Student>& students);
