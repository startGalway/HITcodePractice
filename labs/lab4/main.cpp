// main.cpp - 成绩管理系统
#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include "types.h"
#include "fileop.h"
#include "sort.h"
#include "search.h"
#include "calculate.h"
#include "analysis.h"
#include "print.h"

static bool ReadFloat(const char* prompt, float& x) {
	std::cout << prompt;
	if (!(std::cin >> x)) { std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); return false; }
	return true;
}

static void AppendRecord(std::vector<Student>& students) {
	if (students.size() >= kMaxStudents) { std::cout << "已达人数上限(45)\n"; return; }
	Student s; float a,b,c,d;
	std::cout << "请输入: 学号 姓名 iCS PDP DS DL（以空格分隔）\n> ";
	if (!(std::cin >> s.id >> s.name >> a >> b >> c >> d)) {
		std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "输入无效\n"; return;
	}
	s.scores = {a,b,c,d};
	students.push_back(std::move(s));
}

static void SearchByName(const std::vector<Student>& students) {
	std::cout << "输入姓名: "; std::string name; std::cin >> name;
	auto idxs = FindByName(students, name);
	if (idxs.empty()) { std::cout << "未找到\n"; return; }
	PrintStudentHeader();
	for (int i : idxs) PrintStudentRow(students[i]);
}

static void SearchById(const std::vector<Student>& students) {
	std::cout << "输入学号: "; std::string id; std::cin >> id;
	int i = FindById(students, id);
	if (i < 0) { std::cout << "未找到\n"; return; }
	PrintStudentHeader();
	PrintStudentRow(students[i]);
}

static void ModifyById(std::vector<Student>& students) {
	std::cout << "输入学号: "; std::string id; std::cin >> id;
	int i = FindById(students, id);
	if (i < 0) { std::cout << "未找到\n"; return; }
	Student& s = students[i];
	std::cout << "当前信息如下：\n"; PrintStudentHeader(); PrintStudentRow(s);
	float a=s.scores[0], b=s.scores[1], c=s.scores[2], d=s.scores[3];
	std::cout << "输入新姓名（原值: " << s.name << "): "; std::string name; std::cin >> name; s.name = name;
	if (!ReadFloat("新 iCS: ", a)) return;
	if (!ReadFloat("新 PDP: ", b)) return;
	if (!ReadFloat("新 DS: ", c)) return;
	if (!ReadFloat("新 DL: ", d)) return;
	s.scores = {a,b,c,d};
	std::cout << "已修改。\n";
}

static void DeleteById(std::vector<Student>& students) {
	std::cout << "输入学号: "; std::string id; std::cin >> id;
	int i = FindById(students, id);
	if (i < 0) { std::cout << "未找到\n"; return; }
	students.erase(students.begin() + i);
	std::cout << "已删除。\n";
}

static Subject AskSubject() {
	std::cout << "选择科目: 0=iCS 1=PDP 2=DS 3=DL\n> ";
	int k; std::cin >> k; if (k<0||k>=kSubjectCount) k=0; return static_cast<Subject>(k);
}

int main() {
	std::vector<Student> students;
	// 预载入同目录 students.txt（如果存在）
	std::string err;
	LoadFromText("students.txt", students, &err);

	while (true) {
		PrintMenu();
		int choice = -1; if (!(std::cin >> choice)) { std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); continue; }
		if (choice == 0) { std::cout << "Bye!\n"; break; }
		switch (choice) {
			case 1: AppendRecord(students); break;
			case 2: SearchByName(students); break;
			case 3: SearchById(students); break;
			case 4: ModifyById(students); break;
			case 5: DeleteById(students); break;
			case 6: PrintTotals(students); break;
			case 7: {
				auto avg = CalcCourseAverage(students);
				PrintCourseAverages(avg);
			} break;
			case 8: {
				Subject subj = AskSubject();
				std::cout << "选择排序：0=升序 1=降序\n> "; int d; std::cin >> d;
				SortBySubject(students, subj, d!=0);
				PrintStudentsTable(students);
			} break;
			case 9: {
				auto gb = AnalyzeBuckets(students);
				PrintBuckets(gb);
			} break;
			case 10: {
				std::cout << "保存到文本文件路径: "; std::string p; std::cin >> p;
				if (SaveToText(p, students)) std::cout << "已保存\n"; else std::cout << "保存失败\n";
			} break;
			case 11: {
				std::cout << "从文本文件加载路径: "; std::string p; std::cin >> p; std::vector<Student> tmp; std::string e;
				if (LoadFromText(p, tmp, &e)) { students = std::move(tmp); std::cout << "已加载\n"; }
				else { std::cout << "加载失败: " << e << "\n"; }
			} break;
			case 12: {
				std::cout << "保存到二进制文件路径: "; std::string p; std::cin >> p;
				if (SaveToBinary(p, students)) std::cout << "已保存\n"; else std::cout << "保存失败\n";
			} break;
			case 13: {
				std::cout << "从二进制文件加载路径: "; std::string p; std::cin >> p; std::vector<Student> tmp; std::string e;
				if (LoadFromBinary(p, tmp, &e)) { students = std::move(tmp); std::cout << "已加载\n"; }
				else { std::cout << "加载失败: " << e << "\n"; }
			} break;
			case 14: {
				std::cout << "选择排序：0=升序 1=降序\n> "; int d; std::cin >> d;
				SortByName(students, d==0);
				PrintStudentsTable(students);
			} break;
			case 15: {
				students.clear();
				std::cout << "已清空所有记录\n";
			} break;
			default: std::cout << "无效选择\n"; break;
		}
	}
	return 0;
}
