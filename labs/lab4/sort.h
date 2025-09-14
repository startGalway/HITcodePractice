// sort.h - 排序模块
#pragma once
#include <vector>
#include "types.h"

// 按指定科目排序，descending=true 为降序，false 为升序
void SortBySubject(std::vector<Student>& students, Subject subj, bool descending);

// 按姓名（UTF-8字节序）排序，ascending=true 升序
void SortByName(std::vector<Student>& students, bool ascending);
