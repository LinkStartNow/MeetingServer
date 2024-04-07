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
#include <functional>
#include "mymap.h"
#include "Mysql.h"

using namespace std;

// 用户信息结构体
struct UserInfo
{
    string      m_name;
    Tcpsock     m_sock;

    UserInfo() = default;

    UserInfo(const string& name, int sock): m_name(name), m_sock(sock) {}
};

class CKernel
{
    using fun = function<void(CJson*, Tcpsock*)>;
    unique_ptr<CMysql>          m_sql;
    unique_ptr<Tcpsock>         m_sock_accept;
    unique_ptr<Myepoll>         m_epoll;
    MyMap<int, UserInfo>        m_MapIdToInfo;
    static unique_ptr<CKernel>  self;
    static once_flag            m_once;
    fun                         m_ProToFun[PRO_CNT];

    CKernel& operator=(CKernel&) = default;
    CKernel();

    void SetFun();

    void DealLogRq(CJson*, Tcpsock*);
    void DealRegRq(CJson*, Tcpsock*);
public:

    static CKernel* GetKernel();
};

#endif // CKERNEL_H
