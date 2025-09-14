// search.h - 查询模块
#pragma once
#include <vector>
#include <string>
#include "types.h"

int FindById(const std::vector<Student>& students, const std::string& id);
std::vector<int> FindByName(const std::vector<Student>& students, const std::string& name);
