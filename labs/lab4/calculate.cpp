// calculate.cpp
#include "calculate.h"

std::vector<std::pair<float,float>> CalcTotalAndAverage(const std::vector<Student>& students) {
    std::vector<std::pair<float,float>> res;
    res.reserve(students.size());
    for (const auto& s : students) {
        float sum = s.scores[0] + s.scores[1] + s.scores[2] + s.scores[3];
        res.emplace_back(sum, sum / kSubjectCount);
    }
    return res;
}

std::array<float, kSubjectCount> CalcCourseAverage(const std::vector<Student>& students) {
    std::array<float, kSubjectCount> sum{};
    sum.fill(0.0f);
    if (students.empty()) return sum;
    for (const auto& s : students) {
        for (int i=0;i<kSubjectCount;++i) sum[i] += s.scores[i];
    }
    for (int i=0;i<kSubjectCount;++i) sum[i] /= static_cast<float>(students.size());
    return sum;
}
