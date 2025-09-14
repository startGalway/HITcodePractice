// fileop.cpp
#include "fileop.h"
#include <fstream>
#include <sstream>
#include <cstring>

static void ToDisk(const Student& s, DiskStudent& d) {
    std::memset(&d, 0, sizeof(DiskStudent));
    std::snprintf(d.id, sizeof(d.id), "%s", s.id.c_str());
    std::snprintf(d.name, sizeof(d.name), "%s", s.name.c_str());
    for (int i = 0; i < kSubjectCount; ++i) d.scores[i] = s.scores[i];
}

static Student FromDisk(const DiskStudent& d) {
    Student s;
    s.id = d.id;
    s.name = d.name;
    for (int i = 0; i < kSubjectCount; ++i) s.scores[i] = d.scores[i];
    return s;
}

bool SaveToText(const std::string& path, const std::vector<Student>& students) {
    std::ofstream ofs(path);
    if (!ofs) return false;
    for (const auto& s : students) {
        ofs << s.id << ' ' << s.name << ' '
            << s.scores[0] << ' ' << s.scores[1] << ' '
            << s.scores[2] << ' ' << s.scores[3] << "\n";
    }
    return true;
}

bool LoadFromText(const std::string& path, std::vector<Student>& out, std::string* err) {
    std::ifstream ifs(path);
    if (!ifs) { if (err) *err = "无法打开文本文件"; return false; }
    out.clear();
    std::string id, name;
    float a,b,c,d;
    std::size_t count = 0;
    while (ifs >> id >> name >> a >> b >> c >> d) {
        Student s;
        s.id = id; s.name = name;
        s.scores = {a,b,c,d};
        out.push_back(std::move(s));
        if (++count > kMaxStudents) { if (err) *err = "超过最大人数45"; break; }
    }
    return !out.empty();
}

bool SaveToBinary(const std::string& path, const std::vector<Student>& students) {
    std::ofstream ofs(path, std::ios::binary);
    if (!ofs) return false;
    for (const auto& s : students) {
        DiskStudent d{};
        ToDisk(s, d);
        ofs.write(reinterpret_cast<const char*>(&d), sizeof(DiskStudent));
        if (!ofs) return false;
    }
    return true;
}

bool LoadFromBinary(const std::string& path, std::vector<Student>& out, std::string* err) {
    std::ifstream ifs(path, std::ios::binary);
    if (!ifs) { if (err) *err = "无法打开二进制文件"; return false; }
    out.clear();
    DiskStudent d{};
    while (ifs.read(reinterpret_cast<char*>(&d), sizeof(DiskStudent))) {
        out.push_back(FromDisk(d));
        if (out.size() > kMaxStudents) { if (err) *err = "超过最大人数45"; break; }
    }
    return !out.empty();
}
