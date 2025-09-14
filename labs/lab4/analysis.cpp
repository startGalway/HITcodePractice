// analysis.cpp
#include "analysis.h"

static int ToBucket(float s) {
    if (s >= 90.0f && s <= 100.0f) return 0; // 优秀
    if (s >= 80.0f) return 1; // 良好
    if (s >= 70.0f) return 2; // 中等
    if (s >= 60.0f) return 3; // 及格
    if (s >= 0.0f)  return 4; // 不及格
    return 4; // 异常情况也计为不及格
}

GradeBuckets AnalyzeBuckets(const std::vector<Student>& students) {
    GradeBuckets g{};
    for (const auto& s : students) {
        for (int i=0;i<kSubjectCount;++i) {
            int b = ToBucket(s.scores[i]);
            ++g.buckets[i][b];
        }
    }
    const float n = static_cast<float>(students.size());
    if (n > 0.0f) {
        for (int subj=0; subj<kSubjectCount; ++subj) {
            for (int b=0;b<5;++b) g.percent[subj][b] = 100.0f * g.buckets[subj][b] / n;
        }
    }
    return g;
}
