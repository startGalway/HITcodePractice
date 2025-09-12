#ifndef GMS
#define GMS
#include <string>
#include <iostream>
#define SUBJ_NUMS 4
class SubjectGrade {
public:  // 访问修饰符后跟冒号，且正确缩进
    std::string ClassName;
    int Sub_scores;
};
class StudentNode
{
public:
    std::string id;
    std::string name;
    SubjectGrade Subs[SUBJ_NUMS];
    void  AppendRecord(std::string id,std::string name,int iCS,int PDP,int DS,int DL)
    {
        std::cout<<"要添加学生信息，请依次输入：id，姓名，iCS成绩，PDP成绩，DS成绩，DL成绩。";
        
    }
};
#endif