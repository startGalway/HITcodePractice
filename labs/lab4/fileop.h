// fileop.h - 文本/二进制导入导出
#pragma once
#include <vector>
#include <string>
#include "types.h"

// 文本格式：id name ics pdp ds dl（以空白分隔；姓名允许无空格的UTF-8）
bool SaveToText(const std::string& path, const std::vector<Student>& students);
bool LoadFromText(const std::string& path, std::vector<Student>& out, std::string* err = nullptr);

// 二进制：按 DiskStudent 顺序逐条写入
bool SaveToBinary(const std::string& path, const std::vector<Student>& students);
bool LoadFromBinary(const std::string& path, std::vector<Student>& out, std::string* err = nullptr);
