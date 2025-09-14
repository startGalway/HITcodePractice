// types.h - 基本类型与常量
#pragma once
#include <string>
#include <array>

static constexpr std::size_t kMaxStudents = 45;
static constexpr int kSubjectCount = 4;

enum class Subject : int { ICS = 0, PDP = 1, DS = 2, DL = 3 };

struct Course {
    float ics{};
    float pdp{};
    float ds{};
    float dl{};
};

struct Student {
    std::string id;      // 学号，保留原样（字符串更灵活）
    std::string name;    // 姓名（UTF-8）
    std::array<float, kSubjectCount> scores{}; // 依次为 ICS, PDP, DS, DL
};

// 磁盘二进制存储用的定长结构（跨平台简化处理，不暴露 std::string）
struct DiskStudent {
    char id[32];
    char name[64];
    float scores[kSubjectCount];
};
