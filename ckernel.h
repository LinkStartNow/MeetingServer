#ifndef CKERNEL_H
#define CKERNEL_H

#include "Tcpsock.h"
#include "myepoll.h"
#include "Protocol.h"
#include <iostream>
#include <cjson.h>
#include <string.h>
#include <memory>
#include <mutex>
#include <list>
#include <functional>
#include "mymap.h"
#include "MyList.h"
#include "Mysql.h"
#include "CStruct.h"

using namespace std;

// 用户信息结构体
struct UserInfo
{
    string      m_name;
    Tcpsock     m_sock;
    MemberInfo  m_info;

    UserInfo() = default;

    UserInfo(const string& name, int sock): m_name(name), m_sock(sock) {}

    void SetInfo(const MemberInfo& info)
    {
        m_info = info;
    }

    Tcpsock* GetSock()
    {
        return new Tcpsock(m_sock);
    }

    void Send(CJson& rs)
    {
        const char* con = rs.json_to_string();
        m_sock.Write(con, strlen(con) + 1);
    }

    void Send(char* buf, int len)
    {
        m_sock.Write(buf, len);
    }
};

class CKernel
{
    using fun = function<void(CJson*, Tcpsock*)>;
    unique_ptr<CMysql>                      m_sql;
    unique_ptr<Tcpsock>                     m_sock_accept;
    unique_ptr<Myepoll>                     m_epoll;
    MyMap<int, UserInfo>                    m_MapIdToInfo;
    unordered_map<int, MyList<int>>         m_MapRoomIdToUserId;
    static unique_ptr<CKernel>              self;
    static once_flag                        m_once;
    fun                                     m_ProToFun[PRO_CNT];

    CKernel& operator=(CKernel&) = default;
    CKernel();

    void SetFun();

    void DealLogRq(CJson*, Tcpsock*);
    void DealRegRq(CJson*, Tcpsock*);
    void DealCreateRoom(CJson*, Tcpsock*);
    void DealJoinRoom(CJson*, Tcpsock*);
    void DealLeaveInfo(CJson*, Tcpsock*);

#if USE_NO_JSON_AUDIO
    void DealAudio(char*, int);
#else
    void DealAudio(CJson*, Tcpsock*);
#endif

    // 辅助函数
//    MemberInfo GetInfoById(int id);
public:

    static CKernel* GetKernel();
};

#endif // CKERNEL_H
