#ifndef CSTRUCT_H
#define CSTRUCT_H


#include <string>

using namespace std;

// 房间成员结构体
struct MemberInfo
{
    string   m_name;
    int      m_id;
    int      m_icon;

//    MemberInfo() = default;

    MemberInfo(string name = "", int id = 0, int icon = 0): m_name(name), m_id(id), m_icon(icon) {}
};

#endif // CSTRUCT_H
