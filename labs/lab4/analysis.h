// analysis.h - 分档统计
#pragma once
#include <array>
#include <vector>
#include "types.h"

// 五档：优秀90-100、良好80-89、中等70-79、及格60-69、不及格0-59
struct GradeBuckets {
    // 每科一个 5 档统计
    // buckets[subjectIndex][bucketIndex]
    std::array<std::array<int,5>, kSubjectCount> buckets{};
    std::array<std::array<float,5>, kSubjectCount> percent{}; // 百分比
};

GradeBuckets AnalyzeBuckets(const std::vector<Student>& students);
